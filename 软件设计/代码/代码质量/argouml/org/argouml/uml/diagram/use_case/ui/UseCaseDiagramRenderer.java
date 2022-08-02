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

// File: UseCaseDiagramRenderer.java
// Classes: UseCaseDiagramRenderer
// Original Author: abonner@ics.uci.edu
// $Id: UseCaseDiagramRenderer.java,v 1.2 2001/04/02 14:28:42 5heyden Exp $

package org.argouml.uml.diagram.use_case.ui;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.use_cases.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;
import org.tigris.gef.graph.*;

import org.argouml.uml.diagram.ui.*;

// could be singleton

/** This class defines a renderer object for UML Use Case Diagrams. In a
 *  Class Diagram the following UML objects are displayed with the
 *  following Figs: <p>
 * <pre>
 *  UML Object      ---  Fig
 *  ---------------------------------------
 *  MActor           ---  FigActor
 *  MUseCase         ---  FigUseCase
 *  </pre>
 */

public class UseCaseDiagramRenderer
implements GraphNodeRenderer, GraphEdgeRenderer {

  /** Return a Fig that can be used to represent the given node */
  public FigNode getFigNodeFor(GraphModel gm, Layer lay, Object node) {
    if (node instanceof MActor) return new FigActor(gm, node);
    else if (node instanceof MUseCase) return new FigUseCase(gm, node);
    System.out.println("needs-more-work UseCaseDiagramRenderer getFigNodeFor");
    return null;
  }

  /** Return a Fig that can be used to represent the given edge */
  /** Generally the same code as for the ClassDiagram, since its
      very related to it. */
  public FigEdge getFigEdgeFor(GraphModel gm, Layer lay, Object edge) {
    //System.out.println("making figedge for " + edge);
    if (edge instanceof MAssociation) {
      MAssociation asc = (MAssociation) edge;
      FigAssociation ascFig = new FigAssociation(asc);
      Vector connections = new Vector(asc.getConnections());
      if (connections == null) System.out.println("null connections....");
      MAssociationEnd fromEnd = (MAssociationEnd) connections.elementAt(0);
      MClassifier fromCls = (MClassifier) fromEnd.getType();
      MAssociationEnd toEnd = (MAssociationEnd) connections.elementAt(1);
      MClassifier toCls = (MClassifier) toEnd.getType();
      FigNode fromFN = (FigNode) lay.presentationFor(fromCls);
      FigNode toFN = (FigNode) lay.presentationFor(toCls);
      ascFig.setSourcePortFig(fromFN);
      ascFig.setSourceFigNode(fromFN);
      ascFig.setDestPortFig(toFN);
      ascFig.setDestFigNode(toFN);
      return ascFig;
    }
    if (edge instanceof MGeneralization) {
      MGeneralization gen = (MGeneralization) edge;
      FigGeneralization genFig = new FigGeneralization(gen);
      MGeneralizableElement subType = gen.getChild();
      MGeneralizableElement superType = gen.getParent();
      FigNode subTypeFN = (FigNode) lay.presentationFor(subType);
      FigNode superTypeFN = (FigNode) lay.presentationFor(superType);
      genFig.setSourcePortFig(subTypeFN);
      genFig.setSourceFigNode(subTypeFN);
      genFig.setDestPortFig(superTypeFN);
      genFig.setDestFigNode(superTypeFN);
      return genFig;
    }
      if (edge instanceof MDependency) {
      MDependency dep = (MDependency) edge;
      FigDependency depFig = new FigDependency(dep);
      MModelElement supplier = (MModelElement)((dep.getSuppliers().toArray())[0]);
      MModelElement client = (MModelElement)((dep.getClients().toArray())[0]);
      FigNode supplierFN = (FigNode) lay.presentationFor(supplier);
      FigNode clientFN = (FigNode) lay.presentationFor(client);
      depFig.setSourcePortFig(clientFN);
      depFig.setSourceFigNode(clientFN);
      depFig.setDestPortFig(supplierFN);
      depFig.setDestFigNode(supplierFN);
      return depFig;
    }
    // what about realizations? They are not distince objects in my UML model
    // maybe they should be, just as an implementation issue, dont
    // remove any of the methods that are there now.

    System.out.println("needs-more-work UseCaseDiagramRenderer getFigEdgeFor");
    return null;
  }

  static final long serialVersionUID = 2217410137377934879L;

} /* end class UseCaseDiagramRenderer */
