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

package org.argouml.application.configuration;
import org.argouml.application.api.*;
import java.beans.*;

/**
 *   This class provides definition and manipulation of configuration keys.
 *   All keys in the configuration system will be accessed using the
 *   ConfigurationKey wrapper.
 *
 *   @author Thierry Lach
 *   @since ARGO0.9.4
 */
public class ConfigurationKeyImpl 
implements ConfigurationKey {

  /** The string value for the key.
   */
  private String _key = null;

  /** Create a single component configuration key.
   */
  public ConfigurationKeyImpl(String k1) {
      _key = "argo." + k1;
  }

  /** Create a sub-component of an existing configuration key.
   */
  public ConfigurationKeyImpl(ConfigurationKey ck, String k1) {
      _key = ck.getKey() + "." + k1;
  }

  /** Create a two-component configuration key.
   */
  public ConfigurationKeyImpl(String k1, String k2) {
      _key = "argo." + k1 + "." + k2;
  }

  /** Create a three-component configuration key.
   */
  public ConfigurationKeyImpl(String k1, String k2, String k3) {
      _key = "argo." + k1 + "." + k2 + "." + k3;
  }

  /** Create a four-component configuration key.
   */
  public ConfigurationKeyImpl(String k1, String k2, String k3, String k4) {
      _key = "argo." + k1 + "." + k2 + "." + k3 + "." + k4;
  }

  /** Create a five-component configuration key.
   */
  public ConfigurationKeyImpl(String k1, String k2, String k3, String k4, String k5) {
      _key = "argo." + k1 + "." + k2 + "." + k3 + "." + k4 + "." + k5;
  }

  /** Return the actual key used to access the configuration.
   */ 
  public final String getKey() {
      return _key;
  }

  /** Compare the configuration key to a string.
   */
  public boolean isChangedProperty(PropertyChangeEvent pce) {
      if (pce == null) return false;
      return pce.getPropertyName().equals(_key);
  }

  public String toString() {
      return "{ConfigurationKeyImpl:" + _key + "}";
  }
}

