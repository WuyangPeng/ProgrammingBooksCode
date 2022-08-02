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

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import javax.swing.border.*;
import javax.swing.plaf.basic.*;
import javax.swing.plaf.metal.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.model_management.*;
import org.argouml.cognitive.ui.PriorityNode;
import org.argouml.cognitive.ui.KnowledgeTypeNode;

import org.tigris.gef.util.*;

import org.argouml.cognitive.*;
import org.argouml.uml.ui.*;

public class ToDoTreeRenderer extends DefaultTreeCellRenderer {
  ////////////////////////////////////////////////////////////////
  // class variables
  public ImageIcon _PostIt0     = ResourceLoader.lookupIconResource("PostIt0");
  public ImageIcon _PostIt25    = ResourceLoader.lookupIconResource("PostIt25");
  public ImageIcon _PostIt50    = ResourceLoader.lookupIconResource("PostIt50");
  public ImageIcon _PostIt75    = ResourceLoader.lookupIconResource("PostIt75");
  public ImageIcon _PostIt99    = ResourceLoader.lookupIconResource("PostIt99");
  public ImageIcon _PostIt100   = ResourceLoader.lookupIconResource("PostIt100");
  //public ImageIcon _MultiPostIt = ResourceLoader.lookupIconResource("MultiPostIt");

  protected UMLTreeCellRenderer _navRenderer = new UMLTreeCellRenderer();

  ////////////////////////////////////////////////////////////////
  // TreeCellRenderer implementation

  public Component getTreeCellRendererComponent(JTree tree, Object value,
						boolean sel,
						boolean expanded,
						boolean leaf, int row,
						boolean hasFocus) {

    Component r = super.getTreeCellRendererComponent(tree, value, sel,
						     expanded, leaf,
						     row, hasFocus);

    if (r instanceof JLabel) {
      JLabel lab = (JLabel) r;
      if (value instanceof ToDoItem) {
	ToDoItem item = (ToDoItem) value;
	if (item.getProgress() == 0) lab.setIcon(_PostIt0);
	else if (item.getProgress() <= 25) lab.setIcon(_PostIt25);
	else if (item.getProgress() <= 50) lab.setIcon(_PostIt50);
	else if (item.getProgress() <= 75) lab.setIcon(_PostIt75);
	else if (item.getProgress() <= 100) lab.setIcon(_PostIt99);
	else lab.setIcon(_PostIt100);
      }
      else if (value instanceof Decision) {
	lab.setIcon(MetalIconFactory.getTreeFolderIcon());
      }
      else if (value instanceof Goal) {
	lab.setIcon(MetalIconFactory.getTreeFolderIcon());
      }
      else if (value instanceof Poster) {
	lab.setIcon(MetalIconFactory.getTreeFolderIcon());
      }
      else if (value instanceof PriorityNode) {
	lab.setIcon(MetalIconFactory.getTreeFolderIcon());
      }
      else if (value instanceof KnowledgeTypeNode) {
	lab.setIcon(MetalIconFactory.getTreeFolderIcon());
      }
      else if (value instanceof MModelElement) {
	return _navRenderer.getTreeCellRendererComponent(tree, value, sel,
					      expanded, leaf, row, hasFocus);
      }

      String tip = lab.getText();
      lab.setToolTipText(tip + " ");
      tree.setToolTipText(tip + " ");

      if (!sel)
	lab.setBackground(getBackgroundNonSelectionColor());
      else {
	Color high = org.tigris.gef.base.Globals.getPrefs().getHighlightColor();
	high = high.brighter().brighter();
	lab.setBackground(high);
      }
      lab.setOpaque(sel);
    }
    return r;
  }


} /* end class ToDoTreeRenderer */
