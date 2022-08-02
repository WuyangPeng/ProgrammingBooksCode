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

package org.argouml.uml.ui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import javax.swing.plaf.basic.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.model_management.*;

public class UMLListCellRenderer extends DefaultListCellRenderer {
  ////////////////////////////////////////////////////////////////
  // class variables
//   protected ImageIcon _AttributeIcon = ResourceLoader.lookupIconResource("MAttribute");
//   protected ImageIcon _OperationIcon = ResourceLoader.lookupIconResource("MOperation");
//   protected ImageIcon _ClassIcon = ResourceLoader.lookupIconResource("Class");
//   protected ImageIcon _PackageIcon = ResourceLoader.lookupIconResource("Package");
//   protected ImageIcon _AssociationIcon = ResourceLoader.lookupIconResource("MAssociation");
//   protected ImageIcon _AssociationIcon2 = ResourceLoader.lookupIconResource("Association2");
//   protected ImageIcon _AssociationIcon3 = ResourceLoader.lookupIconResource("Association3");
//   protected ImageIcon _AssociationIcon4 = ResourceLoader.lookupIconResource("Association4");
//   protected ImageIcon _AssociationIcon5 = ResourceLoader.lookupIconResource("Association5");
//   protected ImageIcon _GeneralizationIcon = ResourceLoader.lookupIconResource("MGeneralization");
//   protected ImageIcon _RealizationIcon = ResourceLoader.lookupIconResource("Realization");
//   protected ImageIcon _ClassDiagramIcon = ResourceLoader.lookupIconResource("ClassDiagram");
//   protected ImageIcon _UseCaseDiagramIcon = ResourceLoader.lookupIconResource("UseCaseDiagram");
//   protected ImageIcon _StateDiagramIcon = ResourceLoader.lookupIconResource("StateDiagram");

//   protected ImageIcon _StateIcon = ResourceLoader.lookupIconResource("MState");
//   protected ImageIcon _StartStateIcon = ResourceLoader.lookupIconResource("StartState");
//   protected ImageIcon _DeepIcon = ResourceLoader.lookupIconResource("DeepHistory");
//   protected ImageIcon _ShallowIcon = ResourceLoader.lookupIconResource("ShallowHistory");
//   protected ImageIcon _ForkIcon = ResourceLoader.lookupIconResource("Fork");
//   protected ImageIcon _JoinIcon = ResourceLoader.lookupIconResource("Join");
//   protected ImageIcon _BranchIcon = ResourceLoader.lookupIconResource("Branch");
//   protected ImageIcon _FinalStateIcon = ResourceLoader.lookupIconResource("FinalState");

//   protected ImageIcon _StateMachineIcon = ResourceLoader.lookupIconResource("MStateMachine");
//   protected ImageIcon _CompositeStateIcon = ResourceLoader.lookupIconResource("MCompositeState");
//   protected ImageIcon _TransitionIcon = ResourceLoader.lookupIconResource("MTransition");

  public Component getListCellRendererComponent( JList list, Object value, 
						 int index, boolean isSelected,
						 boolean cellHasFocus) {
    JLabel lab;
    lab = (JLabel) super.getListCellRendererComponent(list, value, index,
					     isSelected, cellHasFocus);
    if ((value instanceof String) && ((String)value).equals("")) {
      lab.setText("\"\"");
      return lab;
    }
    if (!(value instanceof MModelElement)) return lab;
    String name = ((MModelElement) value).getName();
    if (name == null) {
      lab.setText("(null anon)");
      return lab;
    }
    String nameStr = name;
    if (nameStr.length() == 0) nameStr = "(anon)";
    lab.setText(nameStr);
    lab.setToolTipText(nameStr + " ");
    list.setToolTipText(nameStr + " ");
    // icons?
    return lab;
  }



} /* end class UMLListCellRenderer */
