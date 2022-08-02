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

package org.argouml.cognitive.ui;

import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import org.argouml.ui.*;
import org.argouml.cognitive.*;

public class GoListToPriorityToItem implements TreeModelPrereqs {
  
  ////////////////////////////////////////////////////////////////
  // TreeModel implementation

  public Object getRoot() {
    System.out.println("getRoot should never be called");
    return null;
  } 
  public void setRoot(Object r) { }

  public Object getChild(Object parent, int index) {
    if (parent instanceof ToDoList) {
      return PriorityNode.getPriorities().elementAt(index);
    }
    if (parent instanceof PriorityNode) {
      PriorityNode pn = (PriorityNode) parent;
      ToDoList list = Designer.TheDesigner.getToDoList();
      int size = list.size();
      for (int i = 0; i < size; i++) {
	ToDoItem item = list.elementAt(i);
	if (item.getPriority() == pn.getPriority()) {
	  if (index == 0) return item;
	  index--;
	}
      }
    }
    System.out.println("getChild shouldnt get here GoListToPriorityToItem");
    return null;
  }

  public int getChildCount(Object parent) {
    if (parent instanceof ToDoList) {
      return PriorityNode.getPriorities().size();
    }
    if (parent instanceof PriorityNode) {
      int res = 0;
      PriorityNode pn = (PriorityNode) parent;
      ToDoList list = Designer.TheDesigner.getToDoList();
      int size = list.size();
      for (int i = 0; i < size; i++) {
	ToDoItem item = list.elementAt(i);
	if (item.getPriority() == pn.getPriority()) res++;
      }
      return res;
    }
    return 0;
  }

  public int getIndexOfChild(Object parent, Object child) {
    if (parent instanceof ToDoList) {
      return PriorityNode.getPriorities().indexOf(child);
    }
    if (parent instanceof PriorityNode) {
      int index = 0;
      PriorityNode pn = (PriorityNode) parent;
      ToDoList list = Designer.TheDesigner.getToDoList();
      int size = list.size();
      for (int i = 0; i < size; i++) {
	ToDoItem item = list.elementAt(i);
	if (item.getPriority() == pn.getPriority()) {
	  if (item == child) return index;
	  index++;
	}
      }
    }
    return -1;
  }

  public boolean isLeaf(Object node) {
    if (node instanceof ToDoList) return false;
    if (node instanceof PriorityNode && getChildCount(node) > 0) return false;
    return true;
  }

  public void valueForPathChanged(TreePath path, Object newValue) { }
  public void addTreeModelListener(TreeModelListener l) { }
  public void removeTreeModelListener(TreeModelListener l) { }

  public Vector getPrereqs() {
    Vector res = new Vector();
    res.addElement(ToDoList.class);
    return res;
  }

  public Vector getProvidedTypes() {
    Vector pros = new Vector();
    pros.addElement(PriorityNode.class);
    pros.addElement(ToDoItem.class);
    return pros;
  }

  
} /* end class GoListToPriorityToItem */
