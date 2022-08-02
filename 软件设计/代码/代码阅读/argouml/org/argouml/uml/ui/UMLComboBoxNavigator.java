// Copyright (c) 1996-2001 The Regents of the University of California. All
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

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import org.tigris.gef.util.*;
import ru.novosoft.uml.foundation.core.*;

/**
 *   This class implements a panel that adds a navigation button
 *   to the right of the combo box
 *
 *   @author Curt Arnold
 *   @since 0.9
 */
public class UMLComboBoxNavigator extends JPanel implements ActionListener {


  private static ImageIcon _icon = ResourceLoader.lookupIconResource("ComboNav");
  private UMLUserInterfaceContainer _container;
  private JComboBox _box;


   /**
    *  Constructor
    *  @param container Container, typically a PropPanel
    *  @param tooltip Tooltip key for button
    *  @param box Associated combo box
    */
    public UMLComboBoxNavigator(UMLUserInterfaceContainer container,
        String tooltip,
        JComboBox box) {
        super(new BorderLayout());
        JButton button = new JButton(_icon);
        _container = container;
        _box = box;
        button.setPreferredSize(new Dimension(_icon.getIconWidth()+6,_icon.getIconHeight()+6));
        button.setToolTipText(container.localize(tooltip));
        button.addActionListener(this);
        add(box,BorderLayout.CENTER);
        add(button,BorderLayout.EAST);
    }

    /**
     *  Fired when the button is pushed.  Navigates to the currently
     *  selected item in the combo box
     */
    public void actionPerformed(final java.awt.event.ActionEvent event) {
        Object item = _box.getSelectedItem();
        if(item instanceof UMLComboBoxEntry) {
            UMLComboBoxEntry entry = (UMLComboBoxEntry) item;
            if(!entry.isPhantom()) {
                MModelElement target = entry.getElement(null);
                if(target != null) {
                    _container.navigateTo(target);
                }
            }
        }
    }

}
