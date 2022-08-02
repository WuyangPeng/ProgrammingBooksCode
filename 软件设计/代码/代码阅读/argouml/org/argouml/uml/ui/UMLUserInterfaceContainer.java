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
import org.argouml.ui.*;
import org.argouml.uml.*;
import ru.novosoft.uml.foundation.core.*;
import java.util.*;

/**
 *    Interface supported by any container of UML user interface components.
 *    This interface allows UML user interface components to determine
 *    the currently selected target and profile and allows the control
 *    to request a navigation.  Implemented by PropPanel
 *
 *    @author Curt Arnold
 *    @see PropPanel
 */
public interface UMLUserInterfaceContainer extends NavigationListener {
    /**
     *   Returns the current target for the container, may be null.
     */
    public Object getTarget();
    /**
     *   Returns the current target for the container if the target is a
     *      MModelElement, otherwise null.
     */
    public MModelElement getModelElement();
    /**
     *    Returns the current profile, may not be null.
     */
    public Profile getProfile();
    /**
     *    Formats the specified model element.  Typically, deferred to the
     *    profile.
     */
    public String formatElement(MModelElement element);
    /**
     *    Formats a collection of model elements.  Typically, deferred to the 
     *    profile.
     */
    public String formatCollection(Iterator iter);
    /**
     *    Formats the model element as a namespace.  
     */
    public String formatNamespace(MNamespace ns);
    
    /**
     *     Registers a listener for navigation events.
     */
    public void addNavigationListener(NavigationListener navListener);
    
    /**
     *     Removes a listener for navigation events.
     */
    public void removeNavigationListener(NavigationListener navListener);

    /**
     *     Returns a localized string corresponding to the key
     *     @param key key for resource bundle, typically english literal
     *     @returns localized string for key based on system settings and configuration file
     */
    public String localize(String key);    
}