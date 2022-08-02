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



// File: CrParamTypeNotImported.java
// Classes: CrParamTypeNotImported
// Original Author: jrobbins@ics.uci.edu
// $Id: CrParamTypeNotImported.java,v 1.1.1.1 2000/09/04 12:50:25 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;

import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

/** Well-formedness rule [2] for MBehavioralFeature. See page 28 of UML 1.1
 *  Semantics. OMG document ad/97-08-04. */

public class CrParamTypeNotImported extends CrUML {

  public CrParamTypeNotImported() {
    setHeadline("Import MParameter Type into Class");
    sd("The type of each operation parameter must be visible and imported "+
       "into the class that owns the operation.\n\n"+
       "Importing classes is needed for code generation. Good modularization "+
       "of classes into packages is key to an understandable design.\n\n"+
       "To fix this, use the \"Next>\" button, or manually add in import to the "+
       "class that owns this operation.");

    addSupportedDecision(CrUML.decCONTAINMENT);
    setKnowledgeTypes(Critic.KT_SYNTAX);
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MBehavioralFeature)) return NO_PROBLEM;
    // needs-more-work
    return NO_PROBLEM;
  }

} /* end class CrParamTypeNotImported.java */

