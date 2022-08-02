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
import java.beans.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.Document;
import javax.swing.plaf.metal.MetalLookAndFeel;
import javax.swing.border.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;

import org.tigris.gef.presentation.*;

import org.argouml.ui.*;

public class StylePanel extends TabSpawnable
implements TabFigTarget, ItemListener, DocumentListener, ListSelectionListener, ActionListener {

  ////////////////////////////////////////////////////////////////
  // instance vars
  protected Fig    _target;


  ////////////////////////////////////////////////////////////////
  // constructors

  public StylePanel(String title) {
    super(title);
    GridBagLayout gb = new GridBagLayout();
    setLayout(gb);
    GridBagConstraints c = new GridBagConstraints();
    c.fill = GridBagConstraints.BOTH;
    c.weightx = 0.0;
    c.weighty = 0.0;
    c.ipadx = 3; c.ipady = 3;
  }



  ////////////////////////////////////////////////////////////////
  // accessors

  public void setTarget(Fig t) {
    _target = t;
    refresh();
  }


  public Fig getTarget() { return _target; }

  public void refresh() {
    //_tableModel.setTarget(_target);
    //_table.setModel(_tableModel);
  }

  public boolean shouldBeEnabled() { return _target != null; }

  ////////////////////////////////////////////////////////////////
  // actions


  ////////////////////////////////////////////////////////////////
  // document event handling

  public void insertUpdate(DocumentEvent e) {
    //System.out.println(getClass().getName() + " insert");
  }

  public void removeUpdate(DocumentEvent e) { insertUpdate(e); }

  public void changedUpdate(DocumentEvent e) {
    //System.out.println(getClass().getName() + " changed");
    // Apparently, this method is never called.
  }

  ////////////////////////////////////////////////////////////////
  // combobox event handling

  public void itemStateChanged(ItemEvent e) {
    Object src = e.getSource();
//     if (src == _persCombo) {
//       //System.out.println("class keywords now is " +
//       //_keywordsField.getSelectedItem());
//       setTablePerspective();
//     }
//     else if (src == _filterCombo) {
//       //System.out.println("class MVisibilityKind now is " +
//       //_visField.getSelectedItem());
//       setFilter();
//     }
  }

  /////////////////////////////////////////////////////////////////
  // ListSelectionListener implemention

  public void valueChanged(ListSelectionEvent lse) {
//     if (lse.getValueIsAdjusting()) return;
//     Object src = lse.getSource();
//     if (src == _table.getSelectionModel()) {
//       int row = lse.getFirstIndex();
//       if (_tableModel != null) {
// 	Vector rowObjects = _tableModel.getRowObjects();
// 	if (row >= 0 && row < rowObjects.size()) {
// 	  Object sel = rowObjects.elementAt(row);
// 	  objectSelected(sel);
// 	  return;
// 	}
//       }
//     }
//     objectSelected(null);
  }

//   public void objectSelected(Object sel) {
//     ProjectBrowser pb = ProjectBrowser.TheInstance;
//     pb.setDetailsTarget(sel);
//   }
  
  /////////////////////////////////////////////////////////////////
  // ActionListener implementation

  public void actionPerformed(ActionEvent ae) {
    Object src = ae.getSource();
    //if (src == _config) doConfig();
  }

  
} /* end class StylePanel */



