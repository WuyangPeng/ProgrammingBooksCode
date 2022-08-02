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
import javax.swing.event.*;
import javax.swing.*;
import java.lang.reflect.*;
import ru.novosoft.uml.*;
import ru.novosoft.uml.foundation.core.*;
import java.awt.event.*;
import java.awt.*;
import java.lang.*;

/**
 *   This class extends JMenuItem to invoke a method upon selection.
 *   The method must have the form of "void method(int index);".
 *   @author Curt Arnold
 */
public class UMLListMenuItem extends JMenuItem implements ActionListener {

    private Object _actionObj;
    private int _index;
    private Method _action;
    static final Class[] _argClass = { int.class };
    
    /**
     *   Creates a new menu item.
     *   @param caption Caption for menu item.
     *   @param actionObj object on which method will be invoked.
     *   @param action name of method.
     *   @param index integer value passed to method, typically position in list.
     */
    public UMLListMenuItem(String caption, Object actionObj,String action,int index) {
        super(caption);
        _actionObj = actionObj;
        _index = index;

        //
        //  it would be a little more efficient to resolve the
        //     action only when the popup was invoked, however
        //     this will identify bad "actions" more readily
        try {
            _action = _actionObj.getClass().getMethod(action,_argClass);
        }
        catch(Exception e) {
            System.out.println("Exception in " + _action + " popup.");
            System.out.println(e.toString());
            setEnabled(false);
        }
        
        addActionListener(this);
    }

    /**
     *   This method is invoked when the menu item is selected.
     *   @param event
     */
    public void actionPerformed(final java.awt.event.ActionEvent event) {
        try {
             Object[] argValue = { new Integer(_index) };
            _action.invoke(_actionObj,argValue);
        }
        catch(InvocationTargetException ex) {
            System.out.println(ex.getTargetException().toString() + " is InvocationTargetException in UMLListMenuItem.actionPerformed()");
        }
        catch(Exception e) {
            System.out.println(e.toString() + " in UMLListMenuItem.actionPerformed()");
        }
    }
}
