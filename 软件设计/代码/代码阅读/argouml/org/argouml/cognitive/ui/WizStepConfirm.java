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
import javax.swing.border.*;

import org.argouml.kernel.*;
import org.argouml.ui.*;

/** A simple non-modal wizard step that shows instructions and prompts
 *  the user to confirm an action.
 *
 * @see org.argouml.cognitive.critics.Critic
 * @see org.argouml.kernel.Wizard
 */

public class WizStepConfirm extends WizStep {
  JTextArea _instructions = new JTextArea();

  public WizStepConfirm() {
    _instructions.setEditable(false);
    _instructions.setBorder(null);
    _instructions.setBackground(_mainPanel.getBackground());
    _instructions.setWrapStyleWord(true);

    _mainPanel.setBorder(new EtchedBorder());

    GridBagLayout gb = new GridBagLayout();
    _mainPanel.setLayout(gb);

    GridBagConstraints c = new GridBagConstraints();
    c.ipadx = 3; c.ipady = 3;
    c.weightx = 0.0; c.weighty = 0.0;
    c.anchor = GridBagConstraints.EAST;

    JLabel image = new JLabel("");
    //image.setMargin(new Insets(0, 0, 0, 0));
    image.setIcon(WIZ_ICON);
    image.setBorder(null);
    c.gridx = 0;
    c.gridheight = 4;
    c.gridy = 0;
    gb.setConstraints(image, c);
    _mainPanel.add(image);

    c.weightx = 1.0;
    c.gridx = 2;
    c.gridheight = 1;
    c.gridwidth = 3;
    c.gridy = 0;
    c.fill = GridBagConstraints.HORIZONTAL;
    gb.setConstraints(_instructions, c);
    _mainPanel.add(_instructions);

    c.gridx = 1;
    c.gridy = 1;
    c.weightx = 0.0;
    c.gridwidth = 1;
    c.fill = GridBagConstraints.NONE;
    SpacerPanel spacer = new SpacerPanel();
    gb.setConstraints(spacer, c);
    _mainPanel.add(spacer);

  }

  public WizStepConfirm(Wizard w, String instr) {
    this();
    // store wizard?
    _instructions.setText(instr);
  }

} /* end class WizStepConfirm */
