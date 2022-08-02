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

// File: ClassDiagramGraphModel.java
// Classes: ClassDiagramGraphModel
// Original Author: jrobbins@ics.uci.edu
// $Id: ClassDiagramGraphModel.java,v 1.3 2001/04/02 14:28:41 5heyden Exp $

package org.argouml.uml.diagram.static_structure;

import java.util.*;
import java.beans.*;

import ru.novosoft.uml.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.behavior.common_behavior.*;
import ru.novosoft.uml.foundation.extension_mechanisms.MStereotype;

import org.tigris.gef.graph.*;

import org.argouml.uml.MMUtil;

/** This class defines a bridge between the UML meta-model
 *  representation of the design and the GraphModel interface used by
 *  GEF.  This class handles only UML Class digrams.  */

public class ClassDiagramGraphModel extends MutableGraphSupport
implements MutableGraphModel, VetoableChangeListener, MElementListener {
  ////////////////////////////////////////////////////////////////
  // instance variables
  protected Vector _nodes = new Vector();
  protected Vector _edges = new Vector();

  /** The "home" UML model of this diagram, not all ModelElements in this
   *  graph are in the home model, but if they are added and don't
   *  already have a model, they are placed in the "home model".
   *  Also, elements from other models will have their FigNodes add a
   *  line to say what their model is. */

  protected MNamespace _model;

  ////////////////////////////////////////////////////////////////
  // accessors

  public MNamespace getNamespace() { return _model; }
  public void setNamespace(MNamespace m) {
    if (_model != null) _model.removeMElementListener(this);
    _model = m;
    if (_model != null) _model.addMElementListener(this);
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
    if (nodeOrEdge instanceof MClass) res.addElement(nodeOrEdge);
    if (nodeOrEdge instanceof MInterface) res.addElement(nodeOrEdge);
    if (nodeOrEdge instanceof MInstance) res.addElement(nodeOrEdge);
    if (nodeOrEdge instanceof MModel) res.addElement(nodeOrEdge);
    return res;
  }

  /** Return the node or edge that owns the given port */
  public Object getOwner(Object port) {
    return port;
  }

  /** Return all edges going to given port */
  public Vector getInEdges(Object port) {
    Vector res = new Vector(); //wasteful!
    if (port instanceof MClass) {
      MClass cls = (MClass) port;
      Collection ends = cls.getAssociationEnds();
      if (ends == null) return res; // empty Vector 
      //java.util.Enumeration endEnum = ends.elements();
	  Iterator iter = ends.iterator();
      while (iter.hasNext()) {
		  MAssociationEnd ae = (MAssociationEnd) iter.next();
		  res.add(ae.getAssociation());
      }
    }
    if (port instanceof MInterface) {
      MInterface Intf = (MInterface) port;
      Collection ends = Intf.getAssociationEnds();
      if (ends == null) return res; // empty Vector 
      Iterator endEnum = ends.iterator();
      while (endEnum.hasNext()) {
	    MAssociationEnd ae = (MAssociationEnd) endEnum.next();
	    res.addElement(ae.getAssociation());
	  }
    }
    /*if (port instanceof MPackage) {
      MPackage cls = (MPackage) port;
      Vector ends = cls.getAssociationEnd();
      if (ends == null) return res; // empty Vector
      java.util.Enumeration endEnum = ends.elements();
      while (endEnum.hasMoreElements()) {
	    MAssociationEnd ae = (MAssociationEnd) endEnum.nextElement();
	    res.addElement(ae.getAssociation());
      }
    }*/
    if (port instanceof MInstance) {
      MInstance inst = (MInstance) port;
      Collection ends = inst.getLinkEnds();
	  res.addAll(ends);
    }
    return res;
  }

  /** Return all edges going from given port */
  public Vector getOutEdges(Object port) {
    return new Vector(); // needs-more-work?
  }

  /** Return one end of an edge */
  public Object getSourcePort(Object edge) {
    if (edge instanceof MAssociation) {
      MAssociation assoc = (MAssociation) edge;
      List conns = assoc.getConnections();
      return conns.get(0);
    }
    System.out.println("needs-more-work getSourcePort");
    return null;
  }

  /** Return  the other end of an edge */
  public Object getDestPort(Object edge) {
    if (edge instanceof MAssociation) {
      MAssociation assoc = (MAssociation) edge;
      List conns = assoc.getConnections();
      return conns.get(1);
    }
    System.out.println("needs-more-work getDestPort");
    return null;
  }


  ////////////////////////////////////////////////////////////////
  // MutableGraphModel implementation

  /** Return true if the given object is a valid node in this graph */
  public boolean canAddNode(Object node) {
    if (_nodes.contains(node)) return false;
    return (node instanceof MClass) || (node instanceof MInterface)
    || (node instanceof MModel)  || (node instanceof MPackage) || (node instanceof MInstance);
  }

  /** Return true if the given object is a valid edge in this graph */
  public boolean canAddEdge(Object edge)  {
    if(_edges.contains(edge)) return false;
    Object end0 = null, end1 = null;
    if (edge instanceof MAssociation) {
      List conns = ((MAssociation)edge).getConnections();
      if (conns.size() < 2) return false;
      MAssociationEnd ae0 = (MAssociationEnd) conns.get(0);
      MAssociationEnd ae1 = (MAssociationEnd) conns.get(1);
      if (ae0 == null || ae1 == null) return false;
      end0 = ae0.getType();
      end1 = ae1.getType();
    }
    else if (edge instanceof MGeneralization) {
      end0 = ((MGeneralization)edge).getChild();
      end1 = ((MGeneralization)edge).getParent();
    }
    else if (edge instanceof MDependency) {
      Collection clients = ((MDependency)edge).getClients();
      Collection suppliers = ((MDependency)edge).getSuppliers();
      if (clients == null || suppliers == null) return false;
      end0 = ((Object[])clients.toArray())[0];
      end1 = ((Object[])suppliers.toArray())[0];
    }
    else if (edge instanceof MLink) {
      Collection roles = ((MLink)edge).getConnections();
      MLinkEnd le0 = (MLinkEnd)((Object[]) roles.toArray())[0];
      MLinkEnd le1 = (MLinkEnd)((Object[]) roles.toArray())[0];
      if (le0 == null || le1 == null) return false;
      end0 = le0.getInstance();
      end1 = le1.getInstance();
    }
    if (end0 == null || end1 == null) return false;
    if (!_nodes.contains(end0)) return false;
    if (!_nodes.contains(end1)) return false;
    return true;
  }

  /** Remove the given node from the graph. */
  public void removeNode(Object node) {
    if (!_nodes.contains(node)) return;
    _nodes.removeElement(node);
    fireNodeRemoved(node);
  }

  /** Add the given node to the graph, if valid. */
  public void addNode(Object node) {
    //System.out.println("adding class node!!");
    if (_nodes.contains(node)) return;
    _nodes.addElement(node);
    if (node instanceof MModelElement &&
	((MModelElement)node).getNamespace() == null) {
	_model.addOwnedElement((MModelElement) node);
    }
    if (node instanceof MInterface){
	//System.out.println("Interface stereo: "+MMUtil.STANDARDS.lookup("interface"));

	((MInterface)node).setStereotype((MStereotype)MMUtil.STANDARDS.lookup("interface"));
    }
    
    fireNodeAdded(node);
    // System.out.println("adding "+node+" OK");
  }

  /** Add the given edge to the graph, if valid. */
  public void addEdge(Object edge) {
    //System.out.println("adding class edge!!!!!!");
    if (_edges.contains(edge)) return;
    _edges.addElement(edge);
    // needs-more-work: assumes public
    if (edge instanceof MModelElement &&
       ((MModelElement)edge).getNamespace() == null) {
      _model.addOwnedElement((MModelElement) edge);
    }
    fireEdgeAdded(edge);
  }


  public void addNodeRelatedEdges(Object node) {
    if ( node instanceof MClassifier ) {
      Collection ends = ((MClassifier)node).getAssociationEnds();
      Iterator iter = ends.iterator();
      while (iter.hasNext()) {
         MAssociationEnd ae = (MAssociationEnd) iter.next();
         if(canAddEdge(ae.getAssociation()))
           addEdge(ae.getAssociation());
      }
    }
    if ( node instanceof MGeneralizableElement ) {
      Collection gn = ((MGeneralizableElement)node).getGeneralizations();
      Iterator iter = gn.iterator();
      while (iter.hasNext()) {
         MGeneralization g = (MGeneralization) iter.next();
         if(canAddEdge(g))
           addEdge(g);
      }
      Collection sp = ((MGeneralizableElement)node).getSpecializations();
      iter = sp.iterator();
      while (iter.hasNext()) {
         MGeneralization s = (MGeneralization) iter.next();
         if(canAddEdge(s))
           addEdge(s);
      }
    }
    if ( node instanceof MModelElement ) {
      Vector specs = new Vector(((MModelElement)node).getClientDependencies());
      specs.addAll(((MModelElement)node).getSupplierDependencies());
      Iterator iter = specs.iterator();
      while (iter.hasNext()) {
         MDependency dep = (MDependency) iter.next();
         if(canAddEdge(dep))
           addEdge(dep);
      }
    }
  }


  /** Remove the given edge from the graph. */
  public void removeEdge(Object edge) {
    if (!_edges.contains(edge)) return;
    _edges.removeElement(edge);
    fireEdgeRemoved(edge);
  }

  /** Return true if the two given ports can be connected by a 
   * kind of edge to be determined by the ports. */
  public boolean canConnect(Object fromP, Object toP) { return true; }


  /** Contruct and add a new edge of a kind determined by the ports */
  public Object connect(Object fromPort, Object toPort) {
    System.out.println("should not enter here! connect2");
    return null;
  }

  /** Contruct and add a new edge of the given kind */
  public Object connect(Object fromPort, Object toPort,
			java.lang.Class edgeClass) {
	  //    System.out.println("connecting: "+fromPort+toPort+edgeClass);
      if ((fromPort instanceof MClass) && (toPort instanceof MClass)) {
	    MClass fromCls = (MClass) fromPort;
	    MClass toCls = (MClass) toPort;

	    if (edgeClass == MGeneralizationImpl.class) {
			MGeneralization gen = MMUtil.SINGLETON.buildGeneralization(fromCls, toCls);
			addEdge(gen);
			return gen;
	    }
	    else if (edgeClass == MAssociationImpl.class) {
		  MAssociation asc = MMUtil.SINGLETON.buildAssociation(fromCls, toCls);
 	      addEdge(asc);
		  return asc;
		  //return asc;
	    }
	    else if (edgeClass == MDependencyImpl.class) {
			// nsuml: using Binding as default
			MDependency dep = MMUtil.SINGLETON.buildDependency(fromCls, toCls);
			addEdge(dep);
			return dep;
	    }
	    else {
	      System.out.println("connect: Cannot make a "+ edgeClass.getName() +
			     " between a " + fromPort.getClass().getName() +
			     " and a " + toPort.getClass().getName());
	      return null;
	    }
      }
      else if ((fromPort instanceof MPackage) && (toPort instanceof MPackage)) {
		  MPackage fromPack = (MPackage) fromPort;
		  MPackage toPack = (MPackage) toPort;
    // needs-more-work: assumes public, user pref for default visibility?
	//do I have to check the namespace here? (Toby)
		  if (edgeClass == MDependencyImpl.class) {
			  // nsuml: using Usage as default
			  MDependency dep = MMUtil.SINGLETON.buildDependency(fromPack, toPack);
			  addEdge(dep);
			  return dep;
		  }
      }

      // break
      else if ((fromPort instanceof MClass) && (toPort instanceof MInterface)) {
	MClass fromCls = (MClass) fromPort;
	MInterface toIntf = (MInterface) toPort;
	 
	if (edgeClass == MAbstractionImpl.class) {
		MAbstraction real = MMUtil.SINGLETON.buildRealization(fromCls, toIntf);
		addEdge(real);
		return real;
	}
	
	  else  if (edgeClass == MAssociationImpl.class) {
		  MAssociation asc = MMUtil.SINGLETON.buildAssociation(fromCls, toIntf);
 	      addEdge(asc);
		  return asc;
	}
	else {
	  System.out.println("Cannot make a "+ edgeClass.getName() +
			     " between a " + fromPort.getClass().getName() +
			     " and a " + toPort.getClass().getName());
	  return null;
	}
      }

      // break
      else if ((fromPort instanceof MInterface) && (toPort instanceof MClass)) {
	MInterface fromIntf = (MInterface) fromPort;
	MClass toCls = (MClass) toPort;


	if (edgeClass == MAssociationImpl.class) {
		  MAssociation asc = MMUtil.SINGLETON.buildAssociation(fromIntf, false, toCls, true);
 	      addEdge(asc);
		  return asc;
	}

// 	else if (edgeClass == MAbstractionImpl.class) {
// 		MAbstraction real = MMUtil.SINGLETON.buildRealization(toCls, fromIntf);
// 		addEdge(real);
// 		return real;
// 	}

	else {
	  System.out.println("Cannot make a "+ edgeClass.getName() +
			     " between a " + fromPort.getClass().getName() +
			     " and a " + toPort.getClass().getName());
	  return null;
	}
      }

      // break
      else if ((fromPort instanceof MInterface) && (toPort instanceof MInterface)) {
	MInterface fromIntf = (MInterface) fromPort;
	MInterface toIntf = (MInterface) toPort;

	if (edgeClass == MGeneralizationImpl.class) {
		MGeneralization gen = new MGeneralizationImpl();
	  gen.setChild(fromIntf);
	  gen.setParent(toIntf);
	  addEdge(gen);
	  return gen;
	}
	else if (edgeClass == MDependencyImpl.class) {
		//nsuml: using Binding
	MDependency dep = new MDependencyImpl();
		dep.addSupplier(fromIntf);
		dep.addClient(toIntf);
		addEdge(dep);
	  addEdge(dep);
	  return dep;
	}
	else {
	  System.out.println("Cannot make a "+ edgeClass.getName() +
			     " between a " + fromPort.getClass().getName() +
			     " and a " + toPort.getClass().getName());
	  return null;
	}
      }

      // break
      else if ((fromPort instanceof MInstance) && (toPort instanceof MInstance)) {
        MInstance fromInst = (MInstance) fromPort;
        MInstance toInst = (MInstance) toPort;
    	if (edgeClass == MLinkImpl.class) {
    	  MLink link = new MLinkImpl();
		  MLinkEnd le0 = new MLinkEndImpl();
		  le0.setInstance(fromInst);
		  MLinkEnd le1 = new MLinkEndImpl();
		  le1.setInstance(toInst);
		  link.addConnection(le0);
		  link.addConnection(le1);
    	  addEdge(link);
    	  return link;
    	}
      }
    
    System.out.println("should not enter here! connect3");
    return null;
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
	if (me instanceof MClassifier) removeNode(me);	
	if (me instanceof MPackage) removeNode(me);
	if (me instanceof MAssociation) removeEdge(me);
	if (me instanceof MDependency) removeEdge(me);
	if (me instanceof MGeneralization) removeEdge(me);
	//if (me instanceof Realization) removeEdge(me);
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


  static final long serialVersionUID = -2638688086415040146L;

} /* end class ClassDiagramGraphModel */

