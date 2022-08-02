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
import org.argouml.application.configuration.*;
import org.argouml.application.modules.*;
import org.argouml.application.events.*;
import org.argouml.util.logging.*;

import org.apache.log4j.*;
import org.apache.log4j.helpers.*;
import org.apache.log4j.or.*;
import org.apache.log4j.spi.*;

import java.util.*;
import java.io.*;
import javax.swing.*;

/** 
 * The <code>Argo</code> class provides static methods and definitions
 * that can be used as helpers throughout the Argo code.
 *
 * This class is a variation of the <i>Expert</i> design pattern
 * <cite>[Grand]</cite>.  By incorporating a number of unrelated
 * but commonly
 * used methods in a single class, it attempts to decrease the
 * complexity of the overall code while increasing its own complexity.
 *
 * The 
 *
 * These include
 * <ul>
 * <li>definitions of configuration keys</li>
 * <li>definitions of resource bundle identifier strings</li>
 * <li>methods for localization using <code>gef</code></li>
 * <li>methods for environment manipulation</li>
 * <li>methods for console <code>log4j</code> logging</li>
 * </ul>
 * 
 */

public class Argo {

  /** Key for argo resource directory.
   */
  public static final String RESOURCEDIR = "/org/argouml/resource/";

  /** argo.ini path
   */
  public static final String ARGOINI = "/org/argouml/argo.ini";

  /** Key for menu resource bundle.
   */
  public static final String MENU_BUNDLE = "CoreMenu";

  /** Key for default startup directory.
   */
  public static final ConfigurationKey KEY_STARTUP_DIR = Configuration.makeKey("default", "user", "dir");

  /** Key to show splash screen.
   */
  public static final ConfigurationKey KEY_SPLASH = Configuration.makeKey("init", "splash");

  /** Key to preload classes.
   */
  public static final ConfigurationKey KEY_PRELOAD = Configuration.makeKey("init", "preload");

  /** Key to report usage statistics.
   */
  public static final ConfigurationKey KEY_EDEM = Configuration.makeKey("init", "edem");

  /** Key to profile initialization.
   */
  public static final ConfigurationKey KEY_PROFILE = Configuration.makeKey("init", "profile");

  /** Key for screen top
   */
  public static final ConfigurationKey KEY_SCREEN_TOP_Y = Configuration.makeKey("screen", "top");

  /** Key for screen left
   */
  public static final ConfigurationKey KEY_SCREEN_LEFT_X = Configuration.makeKey("screen", "left");

  /** Key for screen width
   */
  public static final ConfigurationKey KEY_SCREEN_WIDTH = Configuration.makeKey("screen", "width");

  /** Key for screen height
   */
  public static final ConfigurationKey KEY_SCREEN_HEIGHT = Configuration.makeKey("screen", "height");

  /** Key for screen horizontal split
   */
  public static final ConfigurationKey KEY_SCREEN_HSPLIT = Configuration.makeKey("screen", "split", "horizontal");

  /** Key for screen top vertical split
   */
  public static final ConfigurationKey KEY_SCREEN_VSPLITTOP = Configuration.makeKey("screen", "split", "vertical", "top");

  /** Key for screen top vertical split
   */
  public static final ConfigurationKey KEY_SCREEN_VSPLITBOTTOM = Configuration.makeKey("screen", "split", "vertical", "bottom");

  /** Key for user email address
   */
  public static final ConfigurationKey KEY_USER_EMAIL = Configuration.makeKey("user", "email");

  /** Key for user full name
   */
  public static final ConfigurationKey KEY_USER_FULLNAME = Configuration.makeKey("user", "fullname");


   /** Standard definition of the logging category for the console.
    */
   public static final String CONSOLE_LOG = "argo.console.log";

   /** Standard definition of the logging category for the console.
    */
   public static final String ARGO_CONSOLE_SUPPRESS = "argo.console.suppress";

   /** Standard definition of system variable to add text prefix to console log.
    */
   public static final String ARGO_CONSOLE_PREFIX = "argo.console.prefix";

   /** Define a static log4j category variable for ArgoUML to log to
    *  the console.  This would be used in preference to System.out.println
    *  for console output because this information can be intercepted
    *  by <code>log4j</code> and included in other logs.  This also allows
    *  custom <code>log4j</code> formatters
    *  to be used on objects displayed on the console log.
    */
   public final static Category log;

   /** Don't let this class be instantiated. */
   private Argo() {
   }

   /** Change the default startup directory.
    */
   public static void setDirectory(String dir) {
       // Store in the user configuration, and
       // let gef know also.
       org.tigris.gef.base.Globals.setLastDirectory(dir);
       // Configuration.setString(KEY_STARTUP_DIR, dir);
   }

   /** Get the default startup directory.
    */
   public static String getDirectory() {
       // Use the configuration if it exists, otherwise
       // use what gef thinks.
       return Configuration.getString(KEY_STARTUP_DIR,
		      org.tigris.gef.base.Globals.getLastDirectory());
   } 

   /** Helper for localization to eliminate the need to import
    *  the gef util library.
    */
   public static String localize(String bundle, String key) {
       return org.tigris.gef.util.Localizer.localize(bundle, key);
   }

   /** Returns a vector of plugins of the class type passed
    *  which satisfy both of the contexts required.
    *
    *  If no plugins are available, returns null.
    */
   public static final ArrayList getPlugins (Class pluginType,
                                        Object[] context) {
       return ModuleLoader.getInstance().getPlugins(pluginType, context);
   }

   /** Returns a vector of all plugins of the class type passed.
    *
    *  If no plugins are available, returns null.
    */
   public static final ArrayList getPlugins (Class pluginType) {
       return ModuleLoader.getInstance().getPlugins(pluginType, null);
   }

   /** Initializes the module loader.  Multiple calls are ignored.
    */
   public static final void initializeModules() {
	ModuleLoader.getInstance().initialize();
   }

   public static String getArgoHome() {
       return ModuleLoader.getInstance().getArgoHome();
   }

   public static String getArgoRoot() {
       return ModuleLoader.getInstance().getArgoRoot();
   }

   public static Icon lookupIconResource(String arg1) {
       return org.tigris.gef.util.ResourceLoader.lookupIconResource(arg1);
   }

   public static Icon lookupIconResource(String arg1, String arg2) {
       return org.tigris.gef.util.ResourceLoader.lookupIconResource(arg1, arg2);
   }

   static {
       // Create a throwable renderer
       ThrowableRenderer tr = new ThrowableRenderer();

       // Create a separate hierarchy for the argo logger
       Hierarchy hier = new Hierarchy(new RootCategory(Priority.INFO));

       // Add the ThrowableRenderer
       hier.getRendererMap().put(Throwable.class, tr);
 
       // Set up the argo console logger in its own hierarchy
       Category cat = hier.getInstance(CONSOLE_LOG);
       cat.addAppender(
            new ConsoleAppender(
                new PatternLayout(
		    System.getProperty(ARGO_CONSOLE_PREFIX, "") + "%m%n"),
		    ConsoleAppender.SYSTEM_OUT));
       // Add the throwable renderer
       cat.getRoot().getHierarchy().getRendererMap().put(Throwable.class, tr);
       if (System.getProperty(ARGO_CONSOLE_SUPPRESS) != null) {
           cat.getRoot().getHierarchy().disableAll();
       }
       
       // Set log here.  No going back.
       log = cat; 
    }

}

