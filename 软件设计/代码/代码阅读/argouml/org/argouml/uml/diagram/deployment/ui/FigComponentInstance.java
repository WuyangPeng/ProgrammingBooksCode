// Copyright (c) 1996-99 The Regents of the University of California. All
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

// File: FigComponentInstance.java
// Classes: FigComponentInstance
// Original Author: 5eichler@informatik.uni-hamburg.de
// $Id: FigComponentInstance.java,v 1.5 2001/10/12 20:20:30 thierrylach Exp $

package org.argouml.uml.diagram.deployment.ui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.plaf.metal.MetalLookAndFeel;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.common_behavior.*;
import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;
import org.tigris.gef.graph.*;

import org.argouml.application.api.*;
import org.argouml.uml.diagram.ui.*;
import org.argouml.uml.generator.*;

/** Class to display graphics for a UML ComponentInstance in a diagram. */

public class FigComponentInstance extends FigNodeModelElement {

  ////////////////////////////////////////////////////////////////
  // instance variables

  public static int OVERLAP = 4;
  
  protected FigRect _bigPort;
  protected FigRect _cover;
  protected FigRect _upperRect;
  protected FigRect _lowerRect;


  ////////////////////////////////////////////////////////////////
  // constructors

  public FigComponentInstance() {
    _bigPort = new FigRect(10, 10, 120, 80, Color.cyan, Color.cyan);

    _cover = new FigRect(10, 10, 120, 80, Color.black, Color.white);
    _upperRect = new FigRect(0, 20, 20, 10, Color.black, Color.white);
    _lowerRect = new FigRect(0, 40, 20, 10, Color.black, Color.white);

    _name.setLineWidth(0);
    _name.setFilled(false);
    _name.setUnderline(true);
    
    addFig(_bigPort);
    addFig(_cover);
    addFig(_stereo);
    addFig(_name);  
    addFig(_upperRect);
    addFig(_lowerRect);

    Rectangle r = getBounds();
    setBounds(r.x, r.y, r.width, r.height);
  }

  public FigComponentInstance(GraphModel gm, Object node) {
    this();
    setOwner(node);
    if (node instanceof MClassifier && (((MClassifier)node).getName() != null))
	_name.setText(((MModelElement)node).getName());
    updateBounds();
  }

  public String placeString() { 
    return "new ComponentInstance";
  }

  public Object clone() {
    FigComponentInstance figClone = (FigComponentInstance) super.clone();
    Vector v = figClone.getFigs();
    figClone._bigPort = (FigRect) v.elementAt(0);
    figClone._cover = (FigRect) v.elementAt(1);
    figClone._stereo = (FigText) v.elementAt(2);
    figClone._name = (FigText) v.elementAt(3);
    figClone._upperRect = (FigRect) v.elementAt(4);
    figClone._lowerRect = (FigRect) v.elementAt(5);

    return figClone;
  }
 
  ////////////////////////////////////////////////////////////////
  // acessors

  public void setLineColor(Color c) {
//     super.setLineColor(c);
     _cover.setLineColor(c);
     _stereo.setFilled(false);
     _stereo.setLineWidth(0);
     _name.setFilled(false);
     _name.setLineWidth(0);
     _upperRect.setLineColor(c);
     _lowerRect.setLineColor(c);
  }

 
  public Selection makeSelection() {
      return new SelectionComponentInstance(this);
  }

  public void setOwner(Object node) {
    super.setOwner(node);
    bindPort(node, _bigPort);
  }

  public Dimension getMinimumSize() {
    Dimension stereoDim = _stereo.getMinimumSize();
    Dimension nameDim = _name.getMinimumSize();
    int h = stereoDim.height + nameDim.height - OVERLAP;
    int w = Math.max(stereoDim.width, nameDim.width);
    return new Dimension(w, h);
  }

  public void setBounds(int x, int y, int w, int h) {
    if (_name == null) return;

    Rectangle oldBounds = getBounds();
    _bigPort.setBounds(x, y, w, h);
    _cover.setBounds(x, y, w, h);

    Dimension stereoDim = _stereo.getMinimumSize();
    Dimension nameDim = _name.getMinimumSize();

    if (h<50) {
      _upperRect.setBounds(x-10, y+h/6, 20, 10);
      _lowerRect.setBounds(x-10, y+3*h/6, 20, 10); 
    }
    else {
      _upperRect.setBounds(x-10, y+13, 20, 10);
      _lowerRect.setBounds(x-10, y+39, 20, 10); 
    }

    _stereo.setBounds(x+1, y+1, w-2, stereoDim.height);
    _name.setBounds(x+1, y + stereoDim.height - OVERLAP + 1, w-2, nameDim.height);
    _x = x; _y = y; _w = w; _h = h;
    firePropChange("bounds", oldBounds, getBounds());
    updateEdges();
  }

  ////////////////////////////////////////////////////////////////
  // user interaction methods

  public void mouseClicked(MouseEvent me) {
    super.mouseClicked(me);
    setLineColor(Color.black);
  }

  public void mousePressed(MouseEvent me) {
    super.mousePressed(me);
    Editor ce = Globals.curEditor();
    Selection sel = ce.getSelectionManager().findSelectionFor(this);
    if (sel instanceof SelectionComponentInstance)
      ((SelectionComponentInstance)sel).hideButtons();
  }


  public void setEnclosingFig(Fig encloser) {
    super.setEnclosingFig(encloser);

    Vector figures = getEnclosedFigs();

    if (getLayer() != null) {  
      elementOrdering(figures);
      Vector contents = getLayer().getContents();
      int contentsSize = contents.size();
      for (int j=0; j<contentsSize; j++) {
        Object o = contents.elementAt(j);
        if (o instanceof FigEdgeModelElement) {
          FigEdgeModelElement figedge = (FigEdgeModelElement) o;
          figedge.getLayer().bringToFront(figedge);
        }
      }
    }

    if (!(getOwner() instanceof MModelElement)) return;
    if (getOwner() instanceof MComponentInstanceImpl) {
      MComponentInstance me = (MComponentInstance) getOwner();
      MNodeInstance mnode = null;

      if (encloser != null && (encloser.getOwner() instanceof MNodeInstanceImpl)) {
        mnode = (MNodeInstance) encloser.getOwner();
      }
      if (encloser != null && (encloser.getOwner() instanceof MComponentInstanceImpl)) { 
        MComponentInstance comp = (MComponentInstance) encloser.getOwner();
        mnode = (MNodeInstance) comp.getNodeInstance(); 
      } 
      try {
        if(mnode != null) {
          me.setNodeInstance(mnode);
        }
        else {
          if (me.getNodeInstance() != null) {
            me.setNodeInstance(null);
          }
        }
        setNode(figures);
      }
      catch (Exception e) {
        System.out.println("could not set package");
      }
    }
  }

  public void setNode(Vector figures) {
    int size = figures.size();
    if (figures != null && (size > 0)) {
      for (int i=0; i<size; i++) {
        Object o = figures.elementAt(i);
        if (o instanceof FigComponentInstance) {
          FigComponentInstance figcomp = (FigComponentInstance) o;
          figcomp.setEnclosingFig(this);
        }
      }
    }
  }

  public boolean getUseTrapRect() { return true; }
	
  ////////////////////////////////////////////////////////////////
  // internal methods

  protected void textEdited(FigText ft) throws PropertyVetoException { 
      //super.textEdited(ft); 
    MComponentInstance coi = (MComponentInstance) getOwner(); 
    if (ft == _name) { 
      String s = ft.getText().trim();
      //why this???
//       if (s.length()>0) {
//         s = s.substring(0, (s.length() - 1)); 
//       }
      ParserDisplay.SINGLETON.parseComponentInstance(coi, s); 
    } 
  } 


  protected void updateStereotypeText() {
    MModelElement me = (MModelElement) getOwner();
    if (me == null) return;
    // MStereotype stereo = me.getStereotype();
    // if (stereo == null || stereo.getName() == null || stereo.getName().length() == 0) 
    //    _stereo.setText("");
    // else {
    //    String stereoStr = stereo.getName();
    //    _stereo.setText("<<" + stereoStr + ">>");
    // }
    _stereo.setText(Notation.generateStereotype(this, me.getStereotype()));

    Rectangle oldBounds = getBounds();
    _stereo.calcBounds();
    calcBounds();
    firePropChange("bounds", oldBounds, getBounds());
  
  }

  protected void modelChanged() {
    super.modelChanged();
    MComponentInstance coi = (MComponentInstance) getOwner(); 
    if (coi == null) return; 
    String nameStr = ""; 
    if (coi.getName() != null) { 
      nameStr = coi.getName().trim(); 
    }
    
    // construct bases string (comma separated)
    String baseStr = "";
    Collection col = coi.getClassifiers(); 
    if (col != null && col.size() > 0){
	Iterator it = col.iterator();
	baseStr = ((MClassifier)it.next()).getName(); 
	while (it.hasNext()) { 
	    baseStr += ", "+((MClassifier)it.next()).getName(); 
	} 
    }
    if (_readyToEdit) { 
      if( nameStr == "" && baseStr == "") 
	_name.setText(""); 
      else 
	_name.setText(nameStr.trim() + " : " + baseStr); 
    } 
    Dimension nameMin = _name.getMinimumSize(); 
    Rectangle r = getBounds(); 
    setBounds(r.x, r.y, r.width, r.height); 

    updateStereotypeText();
  }

  static final long serialVersionUID = 1647392857462847651L;

} /* end class FigComponentInstance */

