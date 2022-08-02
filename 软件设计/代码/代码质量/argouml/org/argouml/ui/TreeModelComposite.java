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

import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import org.argouml.cognitive.ToDoItem;
import org.tigris.gef.util.Localizer;

public class TreeModelComposite
implements TreeModel, Cloneable {

  ////////////////////////////////////////////////////////////////
  // instance variables

  protected Vector _subTreeModels = new Vector();
  protected Vector _providedClasses = new Vector();
  //protected Vector _treeListeners = null;
  protected Object _root;
  protected boolean _flat;
  protected Vector _flatChildren = new Vector();
  protected String _name;
  
  ////////////////////////////////////////////////////////////////
  // contructors

  public TreeModelComposite(String name) {
    setName(Localizer.localize("Tree", name));
  }

  public TreeModelComposite(String name, Vector subs) {
    this(name);
    _subTreeModels = subs;
  }


  ////////////////////////////////////////////////////////////////
  // accessors

  public void setFlat(boolean b) {
    _flat = false;
    if (b) calcFlatChildren();
    _flat = b;
  }
  public boolean getFlat() { return _flat; }

  public void addSubTreeModel(TreeModel tm) {
    if (_subTreeModels.contains(tm)) return;
    if (tm instanceof TreeModelPrereqs) {
      Vector prereqs = ((TreeModelPrereqs)tm).getPrereqs();
      java.util.Enumeration preEnum = prereqs.elements();
      while (preEnum.hasMoreElements()) {
	Object pre = preEnum.nextElement();
	// needs-more-work: check superclasses
	if (!_providedClasses.contains(pre)) {
	  //System.out.println("You cannot add " + tm +
	  //		     " until something provides " + pre);
	  //return;
	}
      }
      Vector provided = ((TreeModelPrereqs)tm).getProvidedTypes();
      java.util.Enumeration proEnum = provided.elements();
      while (proEnum.hasMoreElements()) {
	_providedClasses.addElement(proEnum.nextElement());
      }
    }    
    _subTreeModels.addElement(tm);
  }

  public void removeSubTreeModel(TreeModel tm) {
    // needs-more-work: check for dangling prereqs
    _subTreeModels.removeElement(tm);
  }
  
  public Vector getSubTreeModels() { return _subTreeModels; }

  public void calcFlatChildren() {
    _flatChildren.removeAllElements();
    addFlatChildren(_root);
  }

  public void addFlatChildren(Object node) {
    if (node == null) return;
    //System.out.println("addFlatChildren");
    // hack for to do items only, should check isLeaf(node), but that
    // includes empty folders. Really I need alwaysLeaf(node).
    if ((node instanceof ToDoItem) && !_flatChildren.contains(node)) 
      _flatChildren.addElement(node);
    
    int nKids = getChildCount(node);
    for (int i = 0; i <nKids; i++) {
      addFlatChildren(getChild(node, i));
    }
  }

  public String getName() { return _name; }
  public void setName(String s) { _name = s; }
  
  ////////////////////////////////////////////////////////////////
  // TreeModel implementation
  
  public Object getRoot() { return _root; }

  public void setRoot(Object r) { _root = r; }


  public Object getChild(Object parent, int index) {
    if (_flat && parent == _root) {
      return _flatChildren.elementAt(index);
    }
    int nSubs = _subTreeModels.size();
    for (int i = 0; i < nSubs; i++) {
      TreeModel tm = (TreeModel) _subTreeModels.elementAt(i);
      int childCount = tm.getChildCount(parent);
      if (index < childCount) return tm.getChild(parent, index);
      index -= childCount;
    }
    System.out.println("TreeModelComposite should never get here");
    return null;
  }

  public int getChildCount(Object parent) {
    if (_flat && parent == _root) {
      return _flatChildren.size();
    }
    int childCount = 0;
    int nSubs = _subTreeModels.size();
    for (int i = 0; i < nSubs; i++) {
      TreeModel tm = (TreeModel) _subTreeModels.elementAt(i);
      childCount += tm.getChildCount(parent);
    }
    return childCount;
  }

  public int getIndexOfChild(Object parent, Object child) {
    if (_flat && parent == _root) {
      return _flatChildren.indexOf(child);
    }
    int childCount = 0;
    int nSubs = _subTreeModels.size();
    for (int i = 0; i < nSubs; i++) {
      TreeModel tm = (TreeModel) _subTreeModels.elementAt(i);
      int childIndex = tm.getIndexOfChild(parent, child);
      if (childIndex != -1) return childIndex + childCount;
      childCount += tm.getChildCount(parent);
    }
    //System.out.println("child not found!");
    //The child is sometimes not found when the tree is being updated
    return -1;
  }


  /**
   * Returns true if <I>node</I> is a leaf.  It is possible for this method
   * to return false even if <I>node</I> has no children.  A directory in a
   * filesystem, for example, may contain no files; the node representing
   * the directory is not a leaf, but it also has no children.
   *
   * @param   node    a node in the tree, obtained from this data source
   * @return  true if <I>node</I> is a leaf
   */
  public boolean isLeaf(Object node) {
    int nSubs = _subTreeModels.size();
    for (int i = 0; i < nSubs; i++) {
      TreeModel tm = (TreeModel) _subTreeModels.elementAt(i);
      if (!tm.isLeaf(node)) return false;
    }
    return true;
  }

  /** Return true if this node will always be a leaf, it is not an
   *  "empty folder" */
  public boolean isAlwaysLeaf(Object node) { return false; }


  /**
   * Messaged when the user has altered the value for the item identified
   * by <I>path</I> to <I>newValue</I>.  If <I>newValue</I> signifies
   * a truly new value the model should post a treeNodesChanged
   * event.
   *
   * @param path path to the node that the user has altered.
   * @param newValue the new value from the TreeCellEditor.
   */
  public void valueForPathChanged(TreePath path, Object newValue) {
    System.out.println("valueForPathChanged TreeModelComposite");
  }


  public void fireTreeStructureChanged() {
//     Object path[] = new Object[1];
//     path[0] = getRoot();
//     fireTreeStructureChanged(new TreePath(path));
  }

  public void fireTreeStructureChanged(TreePath path) {
//     if (_treeListeners == null) return;
//     TreeModelEvent evt =
//       new TreeModelEvent(this, path);
//     System.out.println("fire _treeListeners.size() = " +
//     _treeListeners.size());
//     for (int i = 0; i < _treeListeners.size(); i++) {
//       TreeModelListener target =
// 	(TreeModelListener) _treeListeners.elementAt(i);
//       target.treeStructureChanged(evt);
//     }
  }

  public void addTreeModelListener(TreeModelListener l) {
//     System.out.println("adding tree listener to " + toString());
//     if (_treeListeners == null) _treeListeners = new Vector();
//     _treeListeners.removeElement(l);
//     _treeListeners.addElement(l);
  }
  public void removeTreeModelListener(TreeModelListener l) {
//     if (_treeListeners == null) return;
//     _treeListeners.removeElement(l);
//     //System.out.println("rm _treeListeners.size() = " + _treeListeners.size());
  }


  ////////////////////////////////////////////////////////////////
  // debugging

  public String toString() {
    if (getName() != null) return getName();
    else return super.toString();
  }
  
} /* end class TreeModelComposite */
