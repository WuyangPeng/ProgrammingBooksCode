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



// File: ControlMech.java
// Classes: ControlMech EnabledCM NotHushedCM CompositeCM
// Original Author: jrobbins@ics.uci.edu
// $Id: ControlMech.java,v 1.1.1.1 2000/09/04 12:50:28 1sturm Exp $

// TO DO: Do all these classes need to be in their own files? public?

package org.argouml.cognitive.critics;

import java.util.*;

import org.argouml.cognitive.*;

/** A ControlMech determines when a Critic should be active.  New
 *  ControlMech's can be added to add value to existing Critic's.  Each
 *  ControlMech implements a isRelevant() predicate that determines if a
 *  given critic is relevant to a given Designer at the current
 *  time. */

public abstract class ControlMech implements java.io.Serializable {

  public ControlMech() { }
  public boolean isRelevant(Critic c, Designer d) {
    return true;
  }
} // end class ControlMech




