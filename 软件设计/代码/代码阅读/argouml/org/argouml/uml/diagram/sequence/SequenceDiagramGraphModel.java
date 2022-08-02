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


// File: SequenceDiagramGraphModel.java
// Classes: SequenceDiagramGraphModel
// Original Author: 5eichler@informatik.uni-hamburg.de
// $Id: SequenceDiagramGraphModel.java,v 1.2 2001/01/03 12:59:40 boger Exp $

package org.argouml.uml.diagram.sequence;

import java.util.*;
import java.beans.*;
import java.awt.Point;
import java.awt.event.MouseEvent;

import ru.novosoft.uml.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;
import ru.novosoft.uml.behavior.use_cases.*;
import ru.novosoft.uml.behavior.collaborations.*;
import ru.novosoft.uml.behavior.common_behavior.*;
import ru.novosoft.uml.model_management.*;


import org.tigris.gef.graph.*;
import org.tigris.gef.base.Mode;
import org.tigris.gef.base.ModeManager;
import org.tigris.gef.base.Editor;
import org.tigris.gef.base.Globals;




/** This class defines a bridge between the UML meta-model
 *  representation of the design and the GraphModel interface used by
 *  GEF.  This class handles only UML Sequence Digrams.  */

public class SequenceDiagramGraphModel extends MutableGraphSupport
implements MutableGraphModel, MElementListener, VetoableChangeListener {
  ////////////////////////////////////////////////////////////////
  // instance variables
  protected Vector _nodes = new Vector();
  protected Vector _edges = new Vector();

  /** The "home" UML model of this diagram, not all ModelElements in this
   *  graph are in the home model, but if they are added and don't
   *  already have a model, they are placed in the "home model".
   *  Also, elements from other models will have their FigNodes add a
   *  line to say what their model is. */

  /** The Sequence / interaction we are diagramming */
  protected MNamespace _Sequence;
  //protected MInteraction _interaction;

  ////////////////////////////////////////////////////////////////
  // accessors

  public MNamespace getNamespace() { return _Sequence; }
  public void setNamespace(MNamespace m) {
    if (_Sequence != null) _Sequence.removeMElementListener(this);
    _Sequence = m;
    if (_Sequence != null) _Sequence.addMElementListener(this);
  }

  ////////////////////////////////////////////////////////////////
  // GraphModel implementation

  /** Return all nodes in the graph */
  public Vector getNodes() { return _nodes; }

  /** Return all nodes in the graph */
  public Vector getEdges() { return _edges; }

  /** Return all ports on node or edge */
  public Vector getPorts(Object nodeOrEdge) {
    Vector res = new Vector();  //wasteful!
    if (nodeOrEdge instanceof MObject) res.addElement(nodeOrEdge);
    return res;
  }

  /** Return the node or edge that owns the given port */
  public Object getOwner(Object port) {
    return port;
  }

  /** Return all edges going to given port */
  public Vector getInEdges(Object port) {
    Vector res = new Vector(); //wasteful!
    if (port instanceof MObject) {
      MObject mo = (MObject) port;
      Collection ends = mo.getLinkEnds();
      if (ends == null) return res; // empty Vector
	  Iterator iter = ends.iterator();
      while (iter.hasNext()) {
	    MLinkEnd aer = (MLinkEnd) iter.next();
	    res.addElement(aer.getLink());
      }
    }
    return res;
  }

  /** Return all edges going from given port */
  public Vector getOutEdges(Object port) {
    return new Vector(); // needs-more-work?
  }

  /** Return one end of an edge */
  public Object getSourcePort(Object edge) {
    if (edge instanceof MLink ) {
      MLink ml = (MLink) edge;
      Collection conns = ml.getConnections();
      return ((Object[])conns.toArray())[0];
    }
    System.out.println("needs-more-work getSourcePort");
    return null;
  }

  /** Return  the other end of an edge */
  public Object getDestPort(Object edge) {
    if (edge instanceof MLink) {
      MLink ml = (MLink) edge;
      Collection conns = ml.getConnections();
      return ((Object[])conns.toArray())[1];
    }
    System.out.println("needs-more-work getDestPort");
    return null;
  }


  ////////////////////////////////////////////////////////////////
  // MutableGraphModel implementation

  /** Return true if the given object is a valid node in this graph */
  public boolean canAddNode(Object node) {
    return (node instanceof MObject || node instanceof MStimulus);
  }

  /** Return true if the given object is a valid edge in this graph */
  public boolean canAddEdge(Object edge)  {
    return (edge instanceof MLink);
  }

  /** Remove the given node from the graph. */
  public void removeNode(Object node) {
    if (!_nodes.contains(node)) return;
    _nodes.removeElement(node);
    fireNodeRemoved(node);
  }

  /** Add the given node to the graph, if valid. */
  public void addNode(Object node) {
    if (_nodes.contains(node)) return;
    _nodes.addElement(node);
    // needs-more-work: assumes public, user pref for default visibility?
      if (node instanceof MModelElement) {
		  _Sequence.addOwnedElement((MModelElement) node);
		  // ((MClassifier)node).setNamespace(_Sequence.getNamespace());
      }

    fireNodeAdded(node);
  }

  /** Add the given edge to the graph, if valid. */
  public void addEdge(Object edge) {
    if (_edges.contains(edge)) return;
    _edges.addElement(edge);
    // needs-more-work: assumes public
     if (edge instanceof MLink) {
       _Sequence.addOwnedElement((MLink) edge);
       // ((MAssociation)edge).setNamespace(_Sequence.getNamespace());
      }
    fireEdgeAdded(edge);

  }

  public void addNodeRelatedEdges(Object node) {}

  /** Remove the given edge from the graph. */
  public void removeEdge(Object edge) {
    if (!_edges.contains(edge)) return;
    _edges.removeElement(edge);
    fireEdgeRemoved(edge);
  }

  /** Return true if the two given ports can be connected by a
   * kind of edge to be determined by the ports. */
  public boolean canConnect(Object fromP, Object toP) {
    if ((fromP instanceof MObject) && (toP instanceof MObject)) return true;
    return false;
  }


  /** Contruct and add a new edge of a kind determined by the ports */
  public Object connect(Object fromPort, Object toPort) {
    System.out.println("should not enter here! connect2");
    return null;
  }

  /** Contruct and add a new edge of the given kind */
  public Object connect(Object fromPort, Object toPort,
			java.lang.Class edgeClass) {
  
    if (edgeClass == MLinkImpl.class &&
      (fromPort instanceof MObject && toPort instanceof MObject)) {
      MLink ml = new MLinkImpl();
      MLinkEnd le0 = new MLinkEndImpl();
      le0.setInstance((MObject) fromPort);
      MLinkEnd le1 = new MLinkEndImpl();
      le1.setInstance((MObject) toPort);
      ml.addConnection(le0);
      ml.addConnection(le1);
      addEdge(ml);
     
      // add stimulus with given action, taken from global mode
      Editor curEditor = Globals.curEditor();

      if (ml.getStimuli()==null || ml.getStimuli().size() == 0) {
        ModeManager modeManager = curEditor.getModeManager();
        Mode mode = (Mode)modeManager.top();
        Hashtable args = mode.getArgs();
        if ( args != null ) {
          MAction action=null;
          // get "action"-Class taken from global mode
          Class actionClass = (Class) args.get("action");
          if (actionClass != null) {
            try { action = (MAction) actionClass.newInstance(); }
            catch (java.lang.IllegalAccessException ignore) { }
            catch (java.lang.InstantiationException ignore) { }
            if (action != null)  {
              // determine action type of arguments in mode
              action.setName("new action");

              if (action instanceof MSendAction || action instanceof MReturnAction) {
                action.setAsynchronous(true);
              } else {
                action.setAsynchronous(false);
              }
              // create stimulus
              MStimulus stimulus = new MStimulusImpl();
              stimulus.setName("");
              //set sender and receiver
              stimulus.setSender((MObject)fromPort);
              stimulus.setReceiver((MObject)toPort);
              // set action type
              stimulus.setDispatchAction(action);
              // add stimulus to link
              ml.addStimulus(stimulus);
              // add new modelelements: stimulus and action to namesapce
              _Sequence.addOwnedElement(stimulus);
              _Sequence.addOwnedElement(action);
            }
          }
        }
      }
      return ml;
    } else {
      System.out.println("Incorrect edge");
      return null;
    }
    //}
    //catch (java.beans.PropertyVetoException ex) { }
    //System.out.println("should not enter here! connect3");
    //return null;

  }





  ////////////////////////////////////////////////////////////////
  // VetoableChangeListener implementation

  public void vetoableChange(PropertyChangeEvent pce) {
    //throws PropertyVetoException

    if ("ownedElement".equals(pce.getPropertyName())) {
      Vector oldOwned = (Vector) pce.getOldValue();
      MElementImport eo = (MElementImport) pce.getNewValue();
      MModelElement me = eo.getModelElement();
      if (oldOwned.contains(eo)) {
	    //System.out.println("model removed " + me);
	    if (me instanceof MObject) removeNode(me);
	    if (me instanceof MStimulus) removeNode(me);
	    if (me instanceof MAssociation) removeEdge(me);
      }
      else {
	    //System.out.println("model added " + me);
      }
    }
  }

  public void propertySet(MElementEvent mee) {
  }
  public void listRoleItemSet(MElementEvent mee) {
  }
  public void recovered(MElementEvent mee) {
  }
  public void removed(MElementEvent mee) {
  }
  public void roleAdded(MElementEvent mee) {
  }
  public void roleRemoved(MElementEvent mee) {
  }
} /* end class SequenceDiagramGraphModel */

