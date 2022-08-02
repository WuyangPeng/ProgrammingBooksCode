// Copyright (c) 1996-01 The Regents of the University of California. All
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



// File: FigEdgeNote.java
// Classes: FigEdgeNote
// Original Author: Andreas Rueckert <a_rueckert@gmx.net>
// $Id: FigEdgeNote.java,v 1.1 2001/06/11 14:02:29 toby Exp $

package org.argouml.uml.diagram.static_structure.ui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;

import org.argouml.kernel.*;
import org.argouml.ui.*;
import org.argouml.cognitive.*;
import org.argouml.uml.*;
import org.argouml.uml.generator.*;
import org.argouml.uml.diagram.ui.*;


/** 
 * Abstract class to display a UML note connection to a
 * annotated model element.
 */
public class FigEdgeNote extends FigEdgeModelElement implements VetoableChangeListener, DelayedVChangeListener, MouseListener, KeyListener, PropertyChangeListener  {

    ////////////////////////////////////////////////////////////////     
    // constants

    ////////////////////////////////////////////////////////////////
    // constructors
    
    /** 
     * Construct a new note connection. Use the same layout as for
     * other edges.
     */
    public FigEdgeNote() {
	setBetweenNearestPoints(true);
	((FigPoly)_fig).setRectilinear(false);
	setDashed(true);
    }
    
    /**
     * This is just a dummy constructor. A note connection has no underlying
     * model element (called owner).
     */
    public FigEdgeNote(Object edge) {
	this();
    }

    ////////////////////////////////////////////////////////////////
    // accessors

    public void setFig(Fig f) {
	super.setFig(f);
	_fig.setDashed(true);
    }    

    protected boolean canEdit(Fig f) { return false; }

} /* end class FigEdgeNote */
