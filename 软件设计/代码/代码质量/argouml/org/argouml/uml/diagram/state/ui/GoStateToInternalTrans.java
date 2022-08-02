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

package org.argouml.uml.diagram.state.ui;

import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.state_machines.*;

import org.argouml.ui.*;

public class GoStateToInternalTrans implements TreeModelPrereqs {

  public String toString() { return "State->Internal Transitions"; }

  public Object getRoot() {
    System.out.println("getRoot should never be called");
    return null;
  }
  public void setRoot(Object r) { }

  public Object getChild(Object parent, int index) {
    Vector children = getChildren(parent);
    return (children == null) ? null : children.elementAt(index);
  }

  public int getChildCount(Object parent) {
    Vector children = getChildren(parent);
    return (children == null) ? 0 : children.size();
  }

  public int getIndexOfChild(Object parent, Object child) {
    Vector children = getChildren(parent);
    return (children == null) ? -1 : children.indexOf(child);
  }

  public boolean isLeaf(Object node) {
    return !(node instanceof MStateVertex && getChildCount(node) > 0);
  }

  public Vector getChildren(Object parent) {
    if (!(parent instanceof MState)) return null;
    MState st = (MState) parent;
    //return st.getInternalTransition();

    Vector in = new Vector(st.getIncomings());
    Vector out = new Vector(st.getOutgoings());

    if (in == null || in.size() == 0) return null;
    if (out == null || out.size() == 0) return null;
    Vector children = new Vector();
    int size = in.size();
    for (int i = 0; i < size; i++) {
      Object t = in.elementAt(i);
      if (out.contains(t)) children.addElement(t);
    }
    return children;
  }

  public void valueForPathChanged(TreePath path, Object newValue) { }
  public void addTreeModelListener(TreeModelListener l) { }
  public void removeTreeModelListener(TreeModelListener l) { }

  public Vector getPrereqs() {
    Vector pros = new Vector();
    pros.addElement(MStateVertex.class);
    return pros;
  }
  public Vector getProvidedTypes() {
    Vector pros = new Vector();
    pros.addElement(MTransition.class);
    return pros;
  }


} /* end class GoStateToInternalTrans */
