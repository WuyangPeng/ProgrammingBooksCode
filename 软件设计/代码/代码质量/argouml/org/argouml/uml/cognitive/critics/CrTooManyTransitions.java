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

// File: CrTooManyTransitions.java
// Classes: CrTooManyTransitions
// Original Author: jrobbins@ics.uci.edu
// $Id: CrTooManyTransitions.java,v 1.1.1.1 2000/09/04 12:50:25 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.state_machines.*;

import org.argouml.cognitive.*;

/** A critic to detect when a class can never have instances (of
 *  itself of any subclasses). */

public class CrTooManyTransitions extends CrUML {

  ////////////////////////////////////////////////////////////////
  // constants
  public static String THRESHOLD = "Threshold";

  ////////////////////////////////////////////////////////////////
  // constructor
  public CrTooManyTransitions() {
    setHeadline("Reduce Transitions on <ocl>self</ocl>");
    sd("There are too many Transitions on state <ocl>self</ocl>.  Whenever one state "+
       "becomes too central to the machine it may become a maintenance "+
       "bottleneck that must be updated frequently. \n\n"+
       "Defining the transitions between states is an important "+
       "part of your design. \n\n"+
       "To fix this, press the \"Next>\" button, or remove transitions manually "+
       "by clicking on a transition in the navigator pane or "+
       "diagram and presing the \"Del\" key. ");

    addSupportedDecision(CrUML.decSTATE_MACHINES);
    setArg(THRESHOLD, new Integer(10));
    addTrigger("incoming");
    addTrigger("outgoing");

  }

  ////////////////////////////////////////////////////////////////
  // critiquing API
  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MStateVertex)) return NO_PROBLEM;
    MStateVertex sv = (MStateVertex) dm;

    int threshold = ((Integer)getArg(THRESHOLD)).intValue();
    Collection in = sv.getIncomings();
    Collection out = sv.getOutgoings();
    int inSize = (in == null) ? 0 : in.size();
    int outSize = (out == null) ? 0 : out.size();
    if (inSize + outSize <= threshold) return NO_PROBLEM;
    return PROBLEM_FOUND;
  }

} /* end class CrTooManyTransitions */

