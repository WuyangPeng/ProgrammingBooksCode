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

package org.argouml.application.api;
import javax.swing.*;

/**  An interface which identifies an ArgoUML plug-in to the menu.
 *   Plug-ins are replacements or additions to standard Argo classes.
 *   
 *   PluggableMenu require two criteria.  The first is a JMenuItem.
 *   The second is an unlocalized string which identifies the menu
 *   requesting the plugin, such as "File" or "Edit".
 *
 *   @author Thierry Lach
 *   @since 0.9.4
 */
public interface PluggableMenu extends Pluggable {

    /** Return the JMenuItem controlled by the plugin under the specific
     *  context.  One menu plugin may control multiple menu items.
     *
     *  @param parentMenuItem The menuitem which this menuitem would attach to.
     *
     *  @param menuType The type of the parentMenu.
     *
     *  @return A JMenuItem object controlled by the plug-in.
     */
    public JMenuItem getMenuItem(JMenuItem parentMenuItem, String menuType);

    // public boolean inContext(Object[] context);

    public Object[] buildContext(JMenuItem parentMenuItem, String menuType);

} /* End interface PluggableMenu */

