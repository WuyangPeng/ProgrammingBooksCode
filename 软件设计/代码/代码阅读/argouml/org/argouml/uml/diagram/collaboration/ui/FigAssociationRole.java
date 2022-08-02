// Copyright (c) 1996-2001 The Regents of the University of California. All
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

package org.argouml.uml.diagram.collaboration.ui;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.collaborations.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;

import org.argouml.application.api.*;
import org.argouml.uml.generator.*;
import org.argouml.uml.diagram.ui.*;

public class FigAssociationRole extends FigEdgeModelElement {

  // needs-more-work: should be part of some preferences object
  public static boolean SUPPRESS_BIDIRECTIONAL_ARROWS = true;

  protected FigText _srcMult, _srcRole;
  protected FigText _destMult, _destRole;

  public FigAssociationRole() {
    addPathItem(_name, new PathConvPercent(this, 50, 10));

    _srcMult = new FigText(10, 30, 90, 20);
    _srcMult.setFont(LABEL_FONT);
    _srcMult.setTextColor(Color.black);
    _srcMult.setTextFilled(false);
    _srcMult.setFilled(false);
    _srcMult.setLineWidth(0);
    addPathItem(_srcMult, new PathConvPercentPlusConst(this, 0, 15, 15));

    _srcRole = new FigText(10, 30, 90, 20);
    _srcRole.setFont(LABEL_FONT);
    _srcRole.setTextColor(Color.black);
    _srcRole.setTextFilled(false);
    _srcRole.setFilled(false);
    _srcRole.setLineWidth(0);
    addPathItem(_srcRole, new PathConvPercentPlusConst(this, 0, 35, -15));

    _destMult = new FigText(10, 30, 90, 20);
    _destMult.setFont(LABEL_FONT);
    _destMult.setTextColor(Color.black);
    _destMult.setTextFilled(false);
    _destMult.setFilled(false);
    _destMult.setLineWidth(0);
    addPathItem(_destMult, new PathConvPercentPlusConst(this, 100, -15, 15));

    _destRole = new FigText(10, 30, 90, 20);
    _destRole.setFont(LABEL_FONT);
    _destRole.setTextColor(Color.black);
    _destRole.setTextFilled(false);
    _destRole.setFilled(false);
    _destRole.setLineWidth(0);
    addPathItem(_destRole, new PathConvPercentPlusConst(this, 100, -35, -15));
    setBetweenNearestPoints(true);
  }

  public FigAssociationRole(Object edge) {
    this();
    setOwner(edge);
  }

  protected void textEdited(FigText ft) throws PropertyVetoException {
    MAssociationRole asc = (MAssociationRole) getOwner();
    super.textEdited(ft);

    Collection conn = asc.getConnections();
    if (conn == null || conn.size() == 0) return;

    if (ft == _srcRole) {
      MAssociationEndRole srcAE = (MAssociationEndRole) ((Object[])conn.toArray())[0];
      srcAE.setName(_srcRole.getText());
    }
    if (ft == _destRole) {
		MAssociationEndRole destAE = (MAssociationEndRole)((Object[])conn.toArray())[1];
      destAE.setName(_destRole.getText());
    }
  }

  protected void modelChanged() {
    MAssociationRole as = (MAssociationRole) getOwner();
    if (as == null) return;
    String asNameStr = Notation.generate(this, as.getName());

    super.modelChanged();

    Collection endRoles = as.getConnections();
    if (endRoles == null || endRoles.size() != 2) {
      System.out.println("endRoles=" + endRoles);
    }
    
    MAssociationEndRole ae0 = (MAssociationEndRole) ((Object[])endRoles.toArray())[0];
    MAssociationEndRole ae1 = (MAssociationEndRole) ((Object[])endRoles.toArray())[1];

    MMultiplicity mult0 = ae0.getMultiplicity();
    MMultiplicity mult1 = ae1.getMultiplicity();
    _srcMult.setText(Notation.generate(this, mult0));
    if (MMultiplicity.M1_1.equals(mult0)) _srcMult.setText("");
    _destMult.setText(Notation.generate(this, mult1));
    if (MMultiplicity.M1_1.equals(mult1)) _destMult.setText("");

    _srcRole.setText(Notation.generate(this, ae0.getName()));
    _destRole.setText(Notation.generate(this, ae1.getName()));

    boolean srcNav = ae0.isNavigable();
    boolean destNav = ae1.isNavigable();
    if (srcNav && destNav && SUPPRESS_BIDIRECTIONAL_ARROWS)
      srcNav = destNav = false;
    setSourceArrowHead(chooseArrowHead(ae0.getAggregation(), srcNav));
    setDestArrowHead(chooseArrowHead(ae1.getAggregation(), destNav));
  }


  static ArrowHead _NAV_AGGREGATE =
  new ArrowHeadComposite(ArrowHeadDiamond.WhiteDiamond,
			 ArrowHeadGreater.TheInstance);

  static ArrowHead _NAV_COMP =
  new ArrowHeadComposite(ArrowHeadDiamond.BlackDiamond,
			 ArrowHeadGreater.TheInstance);

  protected ArrowHead chooseArrowHead(MAggregationKind ak, boolean nav) {
    if (nav) {
//       if (MAggregationKind.UNSPEC.equals(ak))
// 	    return ArrowHeadGreater.TheInstance;
      if (MAggregationKind.NONE.equals(ak))
	    return ArrowHeadGreater.TheInstance;
      else if (MAggregationKind.AGGREGATE.equals(ak))
	    return _NAV_AGGREGATE;
      else if (MAggregationKind.COMPOSITE.equals(ak))
	    return _NAV_COMP;
    }
//     if (MAggregationKind.UNSPEC.equals(ak))
//       return ArrowHeadNone.TheInstance;
    if (MAggregationKind.NONE.equals(ak))
      return ArrowHeadNone.TheInstance;
    else if (MAggregationKind.AGGREGATE.equals(ak))
      return ArrowHeadDiamond.WhiteDiamond;
    else if (MAggregationKind.COMPOSITE.equals(ak))
      return ArrowHeadDiamond.BlackDiamond;
    // System.out.println("unknown case in drawing assoc arrowhead");
    return ArrowHeadNone.TheInstance;
  }

} /* end class FigAssociationRole */

