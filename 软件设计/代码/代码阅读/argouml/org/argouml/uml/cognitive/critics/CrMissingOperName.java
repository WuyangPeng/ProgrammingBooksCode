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



// File:CrMissingOperName.java
// Classes:CrMissingOperName
// Original Author: jrobbins@ics.uci.edu
// $Id: CrMissingOperName.java,v 1.1.1.1 2000/09/04 12:50:24 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;

import org.argouml.kernel.*;
import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

public class CrMissingOperName extends CrUML {

  public CrMissingOperName() {
    setHeadline("Choose a name");
    sd("Every operation must have a name. \n\n"+
       "Clear and unambiguous naming is key to code generation and \n"+
       "the understandability and maintainability of the design. \n\n"+
       "To fix this, use the \"Next>\" button, or manually select the \n"+
       "attribute and use the Properties tab to give it a name.");
    addSupportedDecision(CrUML.decNAMING);
    setKnowledgeTypes(Critic.KT_SYNTAX);
    addTrigger("name");
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MOperation)) return NO_PROBLEM;
    MOperation oper = (MOperation) dm;
    String myName = oper.getName();
    if (myName == null || myName.equals("")) return PROBLEM_FOUND;
    if (myName.length() == 0) return PROBLEM_FOUND;
    return NO_PROBLEM;
  }

  public void initWizard(Wizard w) {
    if (w instanceof WizMEName) {
      ToDoItem item = w.getToDoItem();
      MModelElement me = (MModelElement) item.getOffenders().elementAt(0);
      String ins = "Set the name of this attribute.";
      String sug = "AttributeName";
      if (me instanceof MOperation) {
	MOperation a = (MOperation) me;
	int count = 1;
	if (a.getOwner() != null)
	  count = a.getOwner().getFeatures().size();
	sug = "oper" + (count + 1);
      }
      ((WizMEName)w).setInstructions(ins);
      ((WizMEName)w).setSuggestion(sug);
    }
  }
  public Class getWizardClass(ToDoItem item) { return WizMEName.class; }

} /* end class CrMissingOperName */

