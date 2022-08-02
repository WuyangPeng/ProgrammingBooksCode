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

package org.argouml.ui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import ru.novosoft.uml.foundation.core.MModelElement;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;

import org.argouml.application.api.*;
import org.argouml.util.*;
import org.argouml.uml.ui.*;
import org.argouml.cognitive.ui.*;

/** The lower-right pane of the main Argo/UML window.  This panel has
 *  several tabs that show details of the selected ToDoItem, or the
 *  selected model element in the NavigationPane, or the
 *  MultiEditorPane. */

public class DetailsPane extends JPanel
implements ChangeListener, MouseListener {
  ////////////////////////////////////////////////////////////////
  // constants

  public static int WIDTH = 690;
  public static int HEIGHT = 520;
  public static int INITIAL_WIDTH = 400;
  public static int INITIAL_HEIGHT = 200;

  ////////////////////////////////////////////////////////////////
  // instance variables

  /** Target is the currently selected object from the UML MModel,
   *  usually selected from a Fig in the diagram or from the
   *  navigation panel. */
  protected Fig _figTarget = null;
  protected Object _modelTarget = null;
  protected Object _item = null;

  // vector of TreeModels
  protected JTabbedPane _tabs = new JTabbedPane();
  protected Vector _tabPanels = new Vector();
  protected int _lastNonNullTab = 0;

  ////////////////////////////////////////////////////////////////
  // constructors

  public DetailsPane(StatusBar sb) {
    Argo.log.info("making DetailsPane");
    ConfigLoader.loadTabs(_tabPanels, "details", sb);


//     _tabPanels.addElement(new TabToDo());
//     _tabPanels.addElement(new TabProps());
//     _tabPanels.addElement(new TabDocs());

//     Class scanner = null;  // detect JDK or JRE
//     try { scanner = Class.forName("sun.tools.java.Scanner"); }
//     catch (ClassNotFoundException cnfe) { }
//     if (scanner == null)
//       _tabPanels.addElement(new TabSrc()); // for JRE
//     else
//       _tabPanels.addElement(new TabJavaSrc()); // for JDK

//     _tabPanels.addElement(new TabConstraints());
//     _tabPanels.addElement(new TabTaggedValues());
//     _tabPanels.addElement(new TabChecklist());
//     _tabPanels.addElement(new TabHistory());

    setLayout(new BorderLayout());
    setFont(new Font("Dialog", Font.PLAIN, 10));
    add(_tabs, BorderLayout.CENTER);

    _tabs.addChangeListener(this);
    for (int i = 0; i < _tabPanels.size(); i++) {
      String title = "tab";
      JPanel t = (JPanel) _tabPanels.elementAt(i);
      if (t instanceof TabSpawnable)
	title = ((TabSpawnable)t).getTitle();
      if (t instanceof TabToDoTarget) {
	_tabs.addTab(title, _leftArrowIcon, t);
      }
      else if (t instanceof TabModelTarget) {
	_tabs.addTab(title, _upArrowIcon, t);
      }
      else if (t instanceof TabFigTarget) {
	_tabs.addTab(title, _upArrowIcon, t);
      }
      else {
	_tabs.addTab(title, t);
      }
    } /* end for */

    setTarget(null);
    _item = null;
    _tabs.addMouseListener(this);
    _tabs.addChangeListener(this);
  }



  ////////////////////////////////////////////////////////////////
  // accessors

  public JTabbedPane getTabs() { return _tabs; }

  // needs-more-work: ToDoItem
  public void setToDoItem(Object item) {
    _item = item;
    for (int i = 0; i < _tabPanels.size(); i++) {
      JPanel t = (JPanel) _tabPanels.elementAt(i);
      if (t instanceof TabToDoTarget) {
	((TabToDoTarget)t).setTarget(_item);
	_tabs.setSelectedComponent(t);
      }
    }
  }


	public void setTarget(Object target) {
		//System.out.println("details target set to:" + target);
		long start = System.currentTimeMillis();
		if (target == null) {
			_figTarget = null;
			_modelTarget = null;
		}
		if (target instanceof Fig) _figTarget = (Fig) target;
		if (target instanceof Fig && ((Fig)target).getOwner() != null)
			_modelTarget = ((Fig)target).getOwner();
		else _modelTarget = target;
		//System.out.println("Fig: "+_figTarget+" mElement: "+_modelTarget);

		int firstEnabled = -1;
		boolean jumpToFirstEnabledTab = false;
		boolean jumpToPrevEnabled = false;
		int currentTab = _tabs.getSelectedIndex();
		for (int i = 0; i < _tabPanels.size(); i++) {
			//long tabstart = System.currentTimeMillis();
			JPanel tab = (JPanel) _tabPanels.elementAt(i);
			if (tab instanceof TabModelTarget) {
				TabModelTarget tabMT = (TabModelTarget) tab;
				tabMT.setTarget(_modelTarget);
				boolean shouldEnable = tabMT.shouldBeEnabled();
				_tabs.setEnabledAt(i, shouldEnable);
				if (shouldEnable && firstEnabled == -1) firstEnabled = i;
				if (_lastNonNullTab == i && shouldEnable && _modelTarget != null) {
					jumpToPrevEnabled = true;
				}
				if (currentTab == i && !shouldEnable) {
					jumpToFirstEnabledTab = true;
				}
			}
			if (tab instanceof TabFigTarget) {
				TabFigTarget tabFT = (TabFigTarget) tab;
				tabFT.setTarget(_figTarget);
				boolean shouldEnable = tabFT.shouldBeEnabled();
				_tabs.setEnabledAt(i, shouldEnable);
				if (shouldEnable && firstEnabled == -1) firstEnabled = i;
				if (_lastNonNullTab == i && shouldEnable && _figTarget != null) {
					jumpToPrevEnabled = true;
				}
				if (currentTab == i && !shouldEnable) {
					jumpToFirstEnabledTab = true;
				}
			}
			//long tabnow = System.currentTimeMillis();
			//System.out.println(tab.getClass().getName() + ": " + (tabnow - tabstart));
		}
		if (jumpToPrevEnabled) {
			_tabs.setSelectedIndex(_lastNonNullTab);
			return;
		}
		if (jumpToFirstEnabledTab && firstEnabled != -1)
			_tabs.setSelectedIndex(firstEnabled);
		if (jumpToFirstEnabledTab && firstEnabled == -1)
			_tabs.setSelectedIndex(0);
		if (target != null) _lastNonNullTab = _tabs.getSelectedIndex();
		long now = System.currentTimeMillis();
		Globals.showStatus("[" + (now - start) + "]");
	}

  public Object getTarget() { return _modelTarget; }

  public Dimension getMinimumSize() { return new Dimension(100, 100); }
  public Dimension getPreferredSize() { return new Dimension(400, 150); }

  ////////////////////////////////////////////////////////////////
  // actions

  public int getIndexOfNamedTab(String tabName) {
    for (int i = 0; i < _tabPanels.size(); i++) {
      String title = _tabs.getTitleAt(i);
      if (title != null && title.equals(tabName)) return i;
    }
    return -1;
  }

  public void selectTabNamed(String tabName) {
    int index = getIndexOfNamedTab(tabName);
    if (index != -1) _tabs.setSelectedIndex(index);
  }

  public void selectNextTab() {
    int size = _tabPanels.size();
    int currentTab = _tabs.getSelectedIndex();
    for (int i = 1; i < _tabPanels.size(); i++) {
      int newTab = (currentTab + i) % size;
      if (_tabs.isEnabledAt(newTab)) {
	_tabs.setSelectedIndex(newTab);
	return;
      }
    }
  }

    public void addNavigationListener(NavigationListener navListener) {
        Iterator iter = _tabPanels.iterator();
        Object panel;
        while(iter.hasNext()) {
            panel = iter.next();
            if(panel instanceof TabProps) {
                ((TabProps) panel).addNavigationListener(navListener);
            }
        }
    }
    
    public void removeNavigationListener(NavigationListener navListener) {
        Iterator iter = _tabPanels.iterator();
        Object panel;
        while(iter.hasNext()) {
            panel = iter.next();
            if(panel instanceof TabProps) {
                ((TabProps) panel).removeNavigationListener(navListener);
            }
        }
    }


  ////////////////////////////////////////////////////////////////
  // event handlers

  /** called when the user selects a new tab, by clicking or
   *  otherwise. */
  public void stateChanged(ChangeEvent e) {
    //System.out.println("DetailsPane state changed");
    Component sel = _tabs.getSelectedComponent();
    //System.out.println(sel.getClass().getName());
    if (sel instanceof TabToDoTarget)
      ((TabToDoTarget)sel).refresh();
    else if (sel instanceof TabModelTarget)
      ((TabModelTarget)sel).refresh();
    else if (sel instanceof TabFigTarget)
      ((TabFigTarget)sel).refresh();
    if (_modelTarget != null) _lastNonNullTab = _tabs.getSelectedIndex();
  }

  /** called when the user clicks once on a tab. */ 
  public void mySingleClick(int tab) {
    //needs-more-work: should fire its own event and ProjectBrowser
    //should register a listener
    //System.out.println("single: " + _tabs.getComponentAt(tab).toString());
  }

  /** called when the user clicks twice on a tab. */ 
  public void myDoubleClick(int tab) {
    //needs-more-work: should fire its own event and ProjectBrowser
    //should register a listener
    //System.out.println("double: " + _tabs.getComponentAt(tab).toString());
    JPanel t = (JPanel) _tabPanels.elementAt(tab);
    if (t instanceof TabSpawnable) ((TabSpawnable)t).spawn();
  }

  public void mousePressed(MouseEvent me) { }
  public void mouseReleased(MouseEvent me) { }
  public void mouseEntered(MouseEvent me) { }
  public void mouseExited(MouseEvent me) { }
  public void mouseClicked(MouseEvent me) {
    int tab = _tabs.getSelectedIndex();
    if (tab != -1) {
      Rectangle tabBounds = _tabs.getBoundsAt(tab);
      if (!tabBounds.contains(me.getX(), me.getY())) return;
      if (me.getClickCount() == 1) mySingleClick(tab);
      else if (me.getClickCount() >= 2) myDoubleClick(tab);
    }
  }

  
  protected Icon _upArrowIcon = new UpArrowIcon();

  protected Icon _leftArrowIcon = new LeftArrowIcon();
  
} /* end class DetailsPane */


////////////////////////////////////////////////////////////////
// related classes


class UpArrowIcon implements Icon {
  public void paintIcon(Component c, Graphics g, int x, int y) {
    int w = getIconWidth(), h = getIconHeight();
    g.setColor(Color.black);
    Polygon p = new Polygon();
    p.addPoint(x, y + h);
    p.addPoint(x + w/2+1, y);
    p.addPoint(x + w, y + h);
    g.fillPolygon(p);
    }
  public int getIconWidth() { return 9; }
  public int getIconHeight() { return 9; }
}

class LeftArrowIcon implements Icon {
  public void paintIcon(Component c, Graphics g, int x, int y) {
    int w = getIconWidth(), h = getIconHeight();
    g.setColor(Color.black);
    Polygon p = new Polygon();
    p.addPoint(x+1, y + h/2+1);
    p.addPoint(x + w, y);
    p.addPoint(x + w, y + h);
    g.fillPolygon(p);
  }
  public int getIconWidth() { return 9; }
  public int getIconHeight() { return 9; }
}
