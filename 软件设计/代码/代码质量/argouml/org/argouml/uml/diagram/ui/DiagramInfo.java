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

// File: DiagramInfo.java
// Classes: DiagramInfo
// Original Author: jrobbins@ics.uci.edy
// $Id: DiagramInfo.java,v 1.1.1.1 2000/09/04 12:50:17 1sturm Exp $

package org.argouml.uml.diagram.ui;

import java.util.*;
import java.awt.*;
import java.beans.*;
import javax.swing.*;
import javax.swing.border.*;

import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.common_behavior.*;

import org.tigris.gef.base.*;

import org.argouml.uml.diagram.activity.ui.*;
import org.argouml.uml.diagram.collaboration.ui.*;
import org.argouml.uml.diagram.state.ui.*;
import org.argouml.uml.diagram.static_structure.ui.*;
import org.argouml.uml.diagram.use_case.ui.*;

public class DiagramInfo extends JComponent {

  ////////////////////////////////////////////////////////////////
  // instance variables

  protected Diagram _diagram = null;
  protected JLabel _name = new JLabel("");

  ////////////////////////////////////////////////////////////////
  // constructor

  public DiagramInfo(Diagram d) {
    _diagram = d;
    //setBorder(new EtchedBorder());
    setLayout(new BorderLayout());
    add(_name, BorderLayout.CENTER);
    updateName();
  }


  ////////////////////////////////////////////////////////////////
  // updates
  public void updateName() {
    String type = "Diagram";
    if (_diagram instanceof UMLClassDiagram)
      type = "Class Diagram";
    if (_diagram instanceof UMLStateDiagram)
      type = "State Diagram";
    if (_diagram instanceof UMLUseCaseDiagram)
      type = "Use Case Diagram";
    if (_diagram instanceof UMLActivityDiagram)
      type = "Activity Diagram";
    if (_diagram instanceof UMLCollaborationDiagram)
      type = "Collaboration Diagram";
//     if (_diagram instanceof UMLSequenceDiagram)
//       type = "Sequence Diagram";
//     if (_diagram instanceof UMLDeploymentDiagram)
//       type = "Deployment Diagram";
    
    _name.setText(type + ": " + _diagram.getName());
  }

} /* end class DiagramInfo */
