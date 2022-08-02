// Copyright (c) 1996-2001 The Regents of the University of California. All
// Rights Reserved. Permission to use, copy, modify, and distribute this
// software and its documentation without fee, and without a written
// agreement is hereby granted, provided that the above copyright notice
// and this paragraph appear in all copies.  This software program and
// documentation are copyrighted by The Regents of the University of
// California. The software program and documentation are supplied "AS
// IS", without any accompanying services from The Regents. The Regents
// does not warrant that the operation of the program will be
// uninterrupted or error-free. The end-user understands that the program
// was developed for research purposes and is advised not to rely
// exclusively on the program for any reason.  IN NO EVENT SHALL THE
// UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
// ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
// THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE. THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
// CALIFORNIA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
// UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

// File: FigNodeModelElement.java
// Classes: FigNodeModelElement
// Original Author: abonner
// $Id: FigNodeModelElement.java,v 1.9 2001/10/12 20:20:31 thierrylach Exp $

package org.argouml.uml.diagram.ui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.plaf.metal.MetalLookAndFeel;

import ru.novosoft.uml.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;
import ru.novosoft.uml.foundation.data_types.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;
import org.tigris.gef.graph.*;

import org.argouml.application.api.*;
import org.argouml.application.events.*;
import org.argouml.kernel.*;
import org.argouml.ui.*;
import org.argouml.cognitive.*;
import org.argouml.uml.*;
import org.argouml.uml.ui.*;
import org.argouml.uml.generator.*;
import org.argouml.uml.diagram.ui.*;
import org.argouml.util.*;


/** Abstract class to display diagram icons for UML ModelElements that
 *  look like nodes and that have editiable names and can be
 *  resized. */

public abstract class FigNodeModelElement extends FigNode
implements VetoableChangeListener, DelayedVChangeListener, MouseListener, KeyListener, PropertyChangeListener, MElementListener, NotationContext, ArgoNotationEventListener  {

  ////////////////////////////////////////////////////////////////
  // constants

  public static Font LABEL_FONT;
  public static Font ITALIC_LABEL_FONT;
  public final int MARGIN = 2;


  static {
    LABEL_FONT = MetalLookAndFeel.getSubTextFont();
    ITALIC_LABEL_FONT = new Font(LABEL_FONT.getFamily(),
				 Font.ITALIC, LABEL_FONT.getSize());
  }

  ////////////////////////////////////////////////////////////////
  // instance variables

  protected FigText _name;
  protected FigText _stereo;
  protected Vector _enclosedFigs = new Vector();
  protected Fig _encloser = null;
  protected boolean _readyToEdit = true;

  ////////////////////////////////////////////////////////////////
  // constructors

  public FigNodeModelElement() {
    _name = new FigText(10, 10, 90, 21, true);
    _name.setFont(LABEL_FONT);
    _name.setTextColor(Color.black);
    // _name.setFilled(false);
    _name.setMultiLine(false);
    _name.setAllowsTab(false);
    _name.setText(placeString());

    _stereo = new FigText(10,10,90,15, true);
    _stereo.setFont(LABEL_FONT);
    _stereo.setTextColor(Color.black);
    _stereo.setFilled(false);
    // _stereo.setLineWidth(0);
    //_stereo.setLineColor(Color.black);
    _stereo.setEditable(false);
    _readyToEdit = false;
    ArgoEventPump.addListener(ArgoEvent.ANY_NOTATION_EVENT, this);
  }

  /** Partially construct a new FigNode.  This method creates the
   *  _name element that holds the name of the model element and adds
   *  itself as a listener. */
  public FigNodeModelElement(GraphModel gm, Object node) {
    this();
    setOwner(node);
    _name.setText(placeString());
    _readyToEdit = false;
    ArgoEventPump.addListener(ArgoEvent.ANY_NOTATION_EVENT, this);
  }

  public void finalize() {
    ArgoEventPump.removeListener(ArgoEvent.ANY_NOTATION_EVENT, this);
  }

  /** Reply text to be shown while placing node in diagram */
  public String placeString() {
    if (getOwner() instanceof MModelElement) {
      MModelElement me = (MModelElement) getOwner();
      String placeString = me.getName();
      if (placeString == null) placeString = "new " + me.getUMLClassName();
      return placeString;
    }
    return "";
  }

  ////////////////////////////////////////////////////////////////
  // accessors

  public FigText getNameFig() { return _name; }

  public Vector getPopUpActions(MouseEvent me) {
    Vector popUpActions = super.getPopUpActions(me);
    ToDoList list = Designer.TheDesigner.getToDoList();
    Vector items = (Vector) list.elementsForOffender(getOwner()).clone();
    if (items != null && items.size() > 0) {
      JMenu critiques = new JMenu("Critiques");
      ToDoItem itemUnderMouse = hitClarifier(me.getX(), me.getY());
      if (itemUnderMouse != null)
	critiques.add(new ActionGoToCritique(itemUnderMouse));
      critiques.addSeparator();
      int size = items.size();
      for (int i = 0; i < size; i++) {
	ToDoItem item = (ToDoItem) items.elementAt(i);
	if (item == itemUnderMouse) continue;
	critiques.add(new ActionGoToCritique(item));
      }
      popUpActions.insertElementAt(critiques, 0);
    }
    popUpActions.addElement(ActionProperties.SINGLETON);
    return popUpActions;
  }

  ////////////////////////////////////////////////////////////////
  // Fig API

  public Fig getEnclosingFig() { return _encloser; }

  public void setEnclosingFig(Fig f) {
    super.setEnclosingFig(f);
    if (_encloser instanceof FigNodeModelElement)
      ((FigNodeModelElement)_encloser)._enclosedFigs.removeElement(this);
    _encloser = f;
    if (_encloser instanceof FigNodeModelElement)
      ((FigNodeModelElement)_encloser)._enclosedFigs.addElement(this);
  }

  public Vector getEnclosedFigs() { return _enclosedFigs; }

  /** Update the order of this fig and the order of the
   *    figs that are inside of this fig */
  public void elementOrdering(Vector figures) {
    int size = figures.size();
    getLayer().bringToFront(this);
    if (figures != null && (size > 0)) {
      for (int i=0; i<size; i++) {
        Object o = figures.elementAt(i);
        if (o instanceof FigNodeModelElement && o != getEnclosingFig() ) {
          FigNodeModelElement fignode = (FigNodeModelElement) o;
          Vector enclosed = fignode.getEnclosedFigs();
          fignode.elementOrdering(enclosed);
        }
      }
    }
  }

  public Selection makeSelection() {
    return new SelectionNodeClarifiers(this);
  }

  /**
   * Displays visual indications of pending ToDoItems.
   * Please note that the list of advices (ToDoList) is not the same
   * as the list of element known by the FigNode (_figs). Therefore,
   * it is necessary to check if the graphic item exists before drawing
   * on it. See ClAttributeCompartment for an example.
   * @see org.argouml.uml.cognitive.critics.ClAttributeCompartment
   */
  public void paintClarifiers(Graphics g) {
    int iconX = _x;
    int iconY = _y - 10;
    ToDoList list = Designer.theDesigner().getToDoList();
    Vector items = list.elementsForOffender(getOwner());
    int size = items.size();
    for (int i = 0; i < size; i++) {
      ToDoItem item = (ToDoItem) items.elementAt(i);
      Icon icon = item.getClarifier();
      if (icon instanceof Clarifier) {
	((Clarifier)icon).setFig(this);
	((Clarifier)icon).setToDoItem(item);
      }
      icon.paintIcon(null, g, iconX, iconY);
      iconX += icon.getIconWidth();
    }
    items = list.elementsForOffender(this);
    size = items.size();
    for (int i = 0; i < size; i++) {
      ToDoItem item = (ToDoItem) items.elementAt(i);
      Icon icon = item.getClarifier();
      if (icon instanceof Clarifier) {
	((Clarifier)icon).setFig(this);
	((Clarifier)icon).setToDoItem(item);
      }
      icon.paintIcon(null, g, iconX, iconY);
      iconX += icon.getIconWidth();
    }
  }

  public ToDoItem hitClarifier(int x, int y) {
    int iconX = _x;
    ToDoList list = Designer.theDesigner().getToDoList();
    Vector items = list.elementsForOffender(getOwner());
    int size = items.size();
    for (int i = 0; i < size; i++) {
      ToDoItem item = (ToDoItem) items.elementAt(i);
      Icon icon = item.getClarifier();
      int width = icon.getIconWidth();
      if (y >= _y - 15 && y <= _y + 10 &&
	  x >= iconX && x <= iconX + width) return item;
      iconX += width;
    }
    for (int i = 0; i < size; i++) {
      ToDoItem item = (ToDoItem) items.elementAt(i);
      Icon icon = item.getClarifier();
      if (icon instanceof Clarifier) {
	((Clarifier)icon).setFig(this);
	((Clarifier)icon).setToDoItem(item);
	if (((Clarifier)icon).hit(x, y)) return item;
      }
    }
    items = list.elementsForOffender(this);
    size = items.size();
    for (int i = 0; i < size; i++) {
      ToDoItem item = (ToDoItem) items.elementAt(i);
      Icon icon = item.getClarifier();
      int width = icon.getIconWidth();
      if (y >= _y - 15 && y <= _y + 10 &&
	  x >= iconX && x <= iconX + width) return item;
      iconX += width;
    }
    for (int i = 0; i < size; i++) {
      ToDoItem item = (ToDoItem) items.elementAt(i);
      Icon icon = item.getClarifier();
      if (icon instanceof Clarifier) {
	((Clarifier)icon).setFig(this);
	((Clarifier)icon).setToDoItem(item);
	if (((Clarifier)icon).hit(x, y)) return item;
      }
    }
    return null;
  }

  public String getTipString(MouseEvent me) {
    ToDoItem item = hitClarifier(me.getX(), me.getY());
    String tip = "";
    if (item != null) tip = item.getHeadline() + " ";
    else if (getOwner() != null) tip = getOwner().toString();
    else tip = toString();
    if (tip != null && tip.length() > 0 && !tip.endsWith(" ")) tip += " ";
    return tip;
  }

  ////////////////////////////////////////////////////////////////
  // event handlers

  public void vetoableChange(PropertyChangeEvent pce) {
    //System.out.println("in vetoableChange");
    Object src = pce.getSource();
    if (src == getOwner()) {
      DelayedChangeNotify delayedNotify = new DelayedChangeNotify(this, pce);
      SwingUtilities.invokeLater(delayedNotify);
    }
    else System.out.println("FigNodeModelElement got vetoableChange"+
			    " from non-owner:" + src);
  }

  public void delayedVetoableChange(PropertyChangeEvent pce) {
    //System.out.println("in delayedVetoableChange");
    Object src = pce.getSource();
    startTrans();
    // update any text, colors, fonts, etc.
    modelChanged();
    // update the relative sizes and positions of internel Figs
    updateBounds();
    endTrans();
  }

  protected void updateBounds() {
    Rectangle bbox = getBounds();
    Dimension minSize = getMinimumSize();
    bbox.width = Math.max(bbox.width, minSize.width);
    bbox.height = Math.max(bbox.height, minSize.height);
    setBounds(bbox.x, bbox.y, bbox.width, bbox.height);
  }

  public void propertyChange(PropertyChangeEvent pve) {
    Object src = pve.getSource();
    String pName = pve.getPropertyName();
    if (pName.equals("editing") && Boolean.FALSE.equals(pve.getNewValue())) {
      //System.out.println("finished editing");
      try {
	startTrans();
	//parse the text that was edited
	textEdited((FigText) src);
	// resize the FigNode to accomodate the new text
	Rectangle bbox = getBounds();
	Dimension minSize = getMinimumSize();
	bbox.width = Math.max(bbox.width, minSize.width);
	bbox.height = Math.max(bbox.height, minSize.height);
	setBounds(bbox.x, bbox.y, bbox.width, bbox.height);
	endTrans();
      }
      catch (PropertyVetoException ex) {
	System.out.println("could not parse and use the text you entered");
      }
    }
    else super.propertyChange(pve);
  }

  /** This method is called after the user finishes editing a text
   *  field that is in the FigNodeModelElement.  Determine which field
   *  and update the model.  This class handles the name, subclasses
   *  should override to handle other text elements. */
  protected void textEdited(FigText ft) throws PropertyVetoException {
    if (ft == _name) {
      MModelElement me = (MModelElement) getOwner();
      if (me == null) return;
      me.setName(ft.getText());
    }
  }

  ////////////////////////////////////////////////////////////////
  // event handlers - MouseListener implementation

  /** If the user double clicks on anu part of this FigNode, pass it
   *  down to one of the internal Figs.  This allows the user to
   *  initiate direct text editing. */
	public void mouseClicked(MouseEvent me) {
		if (!_readyToEdit) {
			if (getOwner() instanceof MModelElement) {
				MModelElement own = (MModelElement) getOwner();
				own.setName("");
				_readyToEdit = true;
			}
			else {
				System.out.println("not ready to edit name");
				return;
			}
		}
		if (me.isConsumed()) return;
		if (me.getClickCount() >= 2 &&
			!(me.isPopupTrigger() || me.getModifiers() == InputEvent.BUTTON3_MASK)) {
			if (getOwner() == null) return;
			Fig f = hitFig(new Rectangle(me.getX() - 2, me.getY() - 2, 4, 4));
			if (f instanceof MouseListener) ((MouseListener)f).mouseClicked(me);
		}
		me.consume();
	}

  public void keyPressed(KeyEvent ke) {
    if (!_readyToEdit) {
      if (getOwner() instanceof MModelElement) {
	MModelElement me = (MModelElement) getOwner();
	me.setName("");
	_readyToEdit = true;
      }
      else {
	System.out.println("not ready to edit name");
	return;
      }
    }
    if (ke.isConsumed()) return;
    if (getOwner() == null) return;
    _name.keyPressed(ke);
    //ke.consume();
//     MModelElement me = (MModelElement) getOwner();
//     if (me == null) return;
//     try { me.setName(new Name(_name.getText())); }
//     catch (PropertyVetoException pve) { }
  }

  /** not used, do nothing. */
  public void keyReleased(KeyEvent ke) { }

  public void keyTyped(KeyEvent ke) {
//     if (ke.isConsumed()) return;
//     _name.keyTyped(ke);
//     //ke.consume();
//     MModelElement me = (MModelElement) getOwner();
//     if (me == null) return;
//     try { me.setName(new Name(_name.getText())); }
//     catch (PropertyVetoException pve) { }
  }

  ////////////////////////////////////////////////////////////////
  // internal methods

  /** This is called aftern any part of the UML MModelElement has
   *  changed. This method automatically updates the name FigText.
   *  Subclasses should override and update other parts. */
  protected void modelChanged() {
    MModelElement me = (MModelElement) getOwner();
    if (me == null) return;
    if (_readyToEdit) {
      String nameStr = Notation.generate(this, me.getName());
      _name.setText(nameStr);
    }
    updateStereotypeText();
  }


	public void propertySet(MElementEvent mee) {
	    //if (_group != null) _group.propertySet(mee);
	    modelChanged();
	    damage();
	}
	public void listRoleItemSet(MElementEvent mee) {
	    //if (_group != null) _group.listRoleItemSet(mee);
	    modelChanged();
	    damage();
	}
	public void recovered(MElementEvent mee) {
	    //if (_group != null) _group.recovered(mee);
	}
	public void removed(MElementEvent mee) {
		//System.out.println("deleting: "+this + mee);
	    //if (_group != null) _group.removed(mee);
	    this.delete();
	}
	public void roleAdded(MElementEvent mee) {
	    //if (_group != null) _group.roleAdded(mee);
	    modelChanged();
	    damage();
	}
	public void roleRemoved(MElementEvent mee) {
	    //if (_group != null) _group.roleRemoved(mee);
	    modelChanged();
	    damage();
	}

    /**
     * Add the owner of this element to the trash, so other Argo components (i.e. critics) 
     * realize, that it is deleted.
     */
    public void delete() {
	if(getOwner() != null) {
	    Trash.SINGLETON.addItemFrom( getOwner(), null);
	}
	super.delete();
    }

  public void setOwner(Object own) {
    Object oldOwner = getOwner();
    super.setOwner(own);
    if (oldOwner instanceof MModelElement)
      ((MModelElement)oldOwner).removeMElementListener(this);
    if (own instanceof MModelElement) {
	MModelElement me = (MModelElement)own;
	me.addMElementListener(this);
	if ( me.getUUID() == null) 
	    me.setUUID(UUIDManager.SINGLETON.getNewUUID());
    }
    modelChanged();
    _readyToEdit = true;
    updateBounds();
  }

    // override this method in subclasses if you want to show stereotype information
  protected void updateStereotypeText() {
  }
  
 /** This default implementation simply requests the default notation.
  */
    public NotationName getContextNotation() { return null; }

    public void notationChanged(ArgoNotationEvent event) {
	renderingChanged();
        damage();
    }

    public void renderingChanged() {
    }

} /* end class FigNodeModelElement */
