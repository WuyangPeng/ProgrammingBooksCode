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



// File: CrConflictingComposites.java
// Classes: CrConflictingComposites
// Original Author: jrobbins@ics.uci.edu
// $Id: CrConflictingComposites.java,v 1.1.1.1 2000/09/04 12:50:24 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;

import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

/** Well-formedness rule [2] for MAssociationEnd. See page 28 of UML 1.1
 *  Semantics. OMG document ad/97-08-04. */

public class CrConflictingComposites extends CrUML {

  public CrConflictingComposites() {
    setHeadline("Remove Conflicting Composite Associations");
    sd("A composite (black diamond) role of an association indicates that "+
       "instances of that class contain instances of the associated classes. "+
       "Since each instance can only be contained in one other object, each "+
       "object can be the 'part' in at most one is-part-of relationship.\n\n"+
       "Good OO design depends on building good is-part-of relationships.\n\n"+
       "To fix this, use the \"Next>\" button, or manually change one association "+
       "to have multiplicity to 0..1 or 1..1, or another kind "+
       "of aggregation (e.g., a white diamond is less strict), "+
       "or remove one of the associations");

    addSupportedDecision(CrUML.decCONTAINMENT);
    setKnowledgeTypes(Critic.KT_SEMANTICS);
    // no good trigger
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MClassifier)) return NO_PROBLEM;
    MClassifier cls = (MClassifier) dm;
    Collection conns = cls.getAssociationEnds();
    if (conns == null) return NO_PROBLEM;
    int compositeCount = 0;
    Iterator enum = conns.iterator();
    while (enum.hasNext()) {
      MAssociationEnd myEnd = (MAssociationEnd) enum.next();
      if (MAggregationKind.COMPOSITE.equals(myEnd.getAggregation()))
	continue;
      MMultiplicity m = myEnd.getMultiplicity();
      if (m.getLower() == 0) continue;
      MAssociation asc = myEnd.getAssociation();
      if (asc != null && hasCompositeEnd(asc)) compositeCount++;
    }
    if (compositeCount > 1) return PROBLEM_FOUND;
    return NO_PROBLEM;
  }

  private final boolean hasCompositeEnd(MAssociation asc)
  {
    List ends = asc.getConnections();
    for (Iterator iter = ends.iterator(); iter.hasNext();) {
      MAssociationEnd end = (MAssociationEnd)iter.next();
      if (end.getAggregation()==MAggregationKind.COMPOSITE)
        return true;
    };
    return false;
  };

} /* end class CrConflictingComposites.java */

