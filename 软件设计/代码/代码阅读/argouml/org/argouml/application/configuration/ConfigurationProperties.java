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


package org.argouml.application.configuration;
import org.argouml.application.api.*;
import java.io.*;
import java.awt.event.*;
import java.util.*;
import java.net.*;
import javax.swing.*;

/**
 *   This class provides a user configuration based upon properties files.
 *
 *   @author Thierry Lach
 */
public class ConfigurationProperties extends ConfigurationHandler {

  /** The location of Argo's default properties resource.
   */
  private static String PROPERTIES = "/org/argouml/resource/default.properties";
  /** The primary property bundle.
   */
  protected Properties _properties = null;

  /** Flag to ensure that only the first load failure is reported
   *  even though we keep trying because the file or URL may only
   *  be temporarily unavailable.
   */
  private boolean _canComplain = true;

  /** Anonymous constructor.
   */
  public ConfigurationProperties() {
      super(true);
      Properties defaults = new Properties();
      try {
          defaults.load(getClass().getResourceAsStream(PROPERTIES));
	  Configuration.cat.debug("Configuration loaded from " + PROPERTIES);
      }
      catch (Exception ioe) {
          // needs-more-work:  What should we do here?
	  Configuration.cat.warn("Configuration not loaded from " + PROPERTIES,
	                          ioe);
      }
      _properties = new Properties(defaults);
  }

  /** Returns the default path for user properties.
   *
   *  @return a generic path string.
   */
  public String getDefaultPath() {
      return System.getProperty("user.home") + "/argo.user.properties";
  }


  /** Load the configuration from a specified location.
   * 
   * @param file  the path to load the configuration from.
   *
   * @return true if the load was successful, false if not.
   */
  public boolean loadFile(File file) {
      try {
          _properties.load(new FileInputStream(file));
	  Argo.log.info ("Configuration loaded from " + file + "\n");
          return true;
      }
      catch (Exception e) {
          if (_canComplain)
              Argo.log.warn ("Unable to load configuration " + file + "\n");
          _canComplain = false;
      }

      return false;
  }

  /** Save the configuration to a specified location.
   * 
   * @param file  the path to save the configuration at.
   *
   * @return true if the save was successful, false if not.
   */
  boolean saveFile(File file) {
      try {
          _properties.store(new FileOutputStream(file), "Argo properties");
	  Argo.log.info ("Configuration saved to " + file);
          return true;
      }
      catch (Exception e) {
          if (_canComplain)
              Argo.log.warn ("Unable to save configuration " + file + "\n");
          _canComplain = false;
      }

      return false;
  }
  /** Load the configuration from a specified location.
   * 
   * @param url  the path to load the configuration from.
   *
   * @return true if the load was successful, false if not.
   */
  public boolean loadURL(URL url) {
      try {
          _properties.load(url.openStream());
	  Argo.log.info ("Configuration loaded from " + url + "\n");
          return true;
      }
      catch (Exception e) {
          if (_canComplain)
              Argo.log.warn ("Unable to load configuration " + url + "\n");
          _canComplain = false;
          return false;
      }
  }

  /** Save the configuration to a specified location.
   * 
   * @param url  the path to save the configuration at.
   *
   * @return true if the save was successful, false if not.
   */
  boolean saveURL(URL url) {
      // System.out.println ("Configuration saved to " + url + "\n");
      return false;
  }

  /** Returns the string value of a configuration property.
   *
   *  @param key the key to return the value of.
   *  @param defaultValue the value to return if the key was not found.
   *
   *  @return the string value of the key if found, otherwise null;
   */
  public String getValue(String key, String defaultValue) {
      String result = "";
      try {
          result = _properties.getProperty(key, defaultValue);
      }
      catch (Exception e) {
          result = defaultValue;
      }
      Configuration.cat.debug("key '" + key + "' returns '" + result + "'");
      return result;
  }

  /** Sets the string value of a configuration property.
   *
   *  @param key the key to set.
   *  @param value the value to set the key to.
   */
  public void setValue(String key, String value) {
     Configuration.cat.debug("key '" + key + "' set to '" + value + "'");
     _properties.setProperty(key, value);
  }
}

