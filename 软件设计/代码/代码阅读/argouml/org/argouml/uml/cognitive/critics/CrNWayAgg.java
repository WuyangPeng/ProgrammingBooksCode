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



// File: CrNWayAgg.java
// Classes: CrNWayAgg
// Original Author: jrobbins@ics.uci.edu
// $Id: CrNWayAgg.java,v 1.1.1.1 2000/09/04 12:50:24 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.collaborations.*;

import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

/** Well-formedness rule [3] for Associations. See page 27 of UML 1.1
 *  Semantics. OMG document ad/97-08-04. */

public class CrNWayAgg extends CrUML {

  public CrNWayAgg() {
    setHeadline("Aggregate Role in N-way MAssociation");
    sd("Three-way (or more) Associations can not have aggregate ends.\n\n" +
       "A clear and consistent is-part-of hierarchy is a key to design clarity, \n"+
       "managable object storage, and the implementation of recursive methods.\n"+
       "To fix this, use the \"Next>\" button, or manually select the MAssociation \n"+
       "and set all of its role aggregations to None.");

    addSupportedDecision(CrUML.decCONTAINMENT);
    setKnowledgeTypes(Critic.KT_SEMANTICS);
    addTrigger("connection");
    addTrigger("end_aggregation");
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MAssociation)) return NO_PROBLEM;
    MAssociation asc = (MAssociation) dm;
    Collection conns = asc.getConnections();
    if (asc instanceof MAssociationRole)
      conns = ((MAssociationRole)asc).getConnections();
    if (conns == null || conns.size() <= 2) return NO_PROBLEM;
    int aggCount = 0;
    Iterator enum = conns.iterator();
    while (enum.hasNext()) {
      MAssociationEnd ae = (MAssociationEnd) enum.next();
      MAggregationKind ak = ae.getAggregation();
      if (//!MAggregationKind.UNSPEC.equals(ak) &&
	  !MAggregationKind.NONE.equals(ak))
	aggCount++;
    }
    if (aggCount > 0) return PROBLEM_FOUND;
    else return NO_PROBLEM;
  }

} /* end class CrNWayAgg.java */

