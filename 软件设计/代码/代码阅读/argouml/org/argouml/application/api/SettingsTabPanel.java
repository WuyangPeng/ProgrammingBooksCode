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

/**  An interface which must be implemented as the UI for 
 *   tabs used on the settings panel.
 *
 *   Tabs will only need to load data during {@link #handleSettingsTabRefresh}
 *   and should only save data during {@link #handleSettingsTabSave}.
 *   Changes can be made during editing of the tabs, but the tab must
 *   be able to undo any change if requested
 *   through {@link #handleSettingsTabCancel}.
 *
 *   @author Thierry Lach
 *   @since 0.9.4
 */
public interface SettingsTabPanel {

    /** Save any fields changed.
     */
    public void handleSettingsTabSave();

    /** Cancel any changes.
     */
    public void handleSettingsTabCancel();

    /** Load or reload field settings.
     */
    public void handleSettingsTabRefresh();

    /** Returns the unlocalized settings tab name.
     */
    public String getTabKey();

    /** Returns the name of the resource bundle to use.
     */
    public String getTabResourceBundleKey();

    /** Returns the JPanel which implements the tab.
     */
    public JPanel getTabPanel();

} /* End interface SettingsTabPanel */

