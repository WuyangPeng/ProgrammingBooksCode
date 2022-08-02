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

// File: StateDiagramRenderer.java
// Classes: StateDiagramRenderer
// Original Author: ics125b spring 1998
// $Id: StateDiagramRenderer.java,v 1.1.1.1 2000/09/04 12:50:20 1sturm Exp $

package org.argouml.uml.diagram.state.ui;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.behavior.activity_graphs.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;
import org.tigris.gef.graph.*;

import org.argouml.uml.diagram.activity.ui.*;
// could be singleton


/** This class defines a renderer object for UML Use Case Diagrams. In a
 *  Class Diagram the following UML objects are displayed with the
 *  following Figs: <p>
 * <pre>
 *  UML Object      ---  Fig
 *  ---------------------------------------
 *  MState           ---  FigState
 *  MCompositeState  ---  FigCompositeState
 *  MActionState     ---  FigActionState
 *  MFinalState      ---  FigFinalState
 *  MPseudostate     ---  FigPseudostate
 *    Inititial     ---  FigInitialState
 *    Branch        ---  FigBranchState
 *    Fork          ---  FigForkState
 *    Join          ---  FigJoinState
 *    DeepHistory       ---  FigDeepHistoryState
 *    ShallowHistory       ---  FigShallowistoryState
 *  MTransition      ---  FigTransition
 *  more...
 *  </pre>
 */

public class StateDiagramRenderer
implements GraphNodeRenderer, GraphEdgeRenderer {

  /** Return a Fig that can be used to represent the given node */
  public FigNode getFigNodeFor(GraphModel gm, Layer lay, Object node) {
    if (node instanceof MActionState) return new FigActionState(gm, node);
	else if (node instanceof MFinalState) return new FigFinalState(gm, node);
    else if (node instanceof MCompositeState) return new FigCompositeState(gm, node);
    else if (node instanceof MState) return new FigState(gm, node);
    else if (node instanceof MPseudostate) {
      MPseudostate pState = (MPseudostate) node;
      if (pState.getKind() == null) return null;
      if (pState.getKind().equals(MPseudostateKind.INITIAL))
	return new FigInitialState(gm, node);
      else if (pState.getKind().equals(MPseudostateKind.BRANCH))
	return new FigBranchState(gm, node);
      else if (pState.getKind().equals(MPseudostateKind.FORK))
	return new FigForkState(gm, node);
      else if (pState.getKind().equals(MPseudostateKind.JOIN))
	return new FigJoinState(gm, node);
      else if (pState.getKind().equals(MPseudostateKind.SHALLOW_HISTORY))
	return new FigShallowHistoryState(gm, node);
      else if (pState.getKind().equals(MPseudostateKind.DEEP_HISTORY))
	return new FigDeepHistoryState(gm, node);      else
	System.out.println("found a type not known");
    }
    System.out.println("needs-more-work StateDiagramRenderer getFigNodeFor");
    return null;
  }

  /** Return a Fig that can be used to represent the given edge */
  public FigEdge getFigEdgeFor(GraphModel gm, Layer lay, Object edge) {
    //System.out.println("making figedge for " + edge);
    if (edge instanceof MTransition) {
      MTransition tr = (MTransition) edge;
      FigTransition trFig = new FigTransition(tr);
      // set source and dest
      // set any arrowheads, labels, or colors
      MStateVertex sourceSV = tr.getSource();
      MStateVertex destSV = tr.getTarget();
      FigNode sourceFN = (FigNode) lay.presentationFor(sourceSV);
      FigNode destFN = (FigNode) lay.presentationFor(destSV);
      trFig.setSourcePortFig(sourceFN);
      trFig.setSourceFigNode(sourceFN);
      trFig.setDestPortFig(destFN);
      trFig.setDestFigNode(destFN);
      return trFig;
    }

    System.out.println("needs-more-work StateDiagramRenderer getFigEdgeFor");
    return null;
  }


  static final long serialVersionUID = 8448809085349795886L;

} /* end class StateDiagramRenderer */
