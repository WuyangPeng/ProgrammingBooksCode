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


// File: Wizard.java
// Classes: Wizard
// Original Author: jrobbins@ics.uci.edu
// $Id: Wizard.java,v 1.1.1.1 2000/09/04 12:50:13 1sturm Exp $

package org.argouml.kernel;

import java.util.*;
import javax.swing.*;

import org.argouml.cognitive.*;

/** "Abstract" base class for non-modal wizards.  Each subclass should
 *  define its own makeNextPanel methods. Because most
 *  wizards will not be run to completion, the panels are constructed
 *  only as needed. This implies that Wizards should no initialize
 *  many instance variables in their constructors.<p>
 *
 *  By convention step 0 is the problem description of the ToDoItem,
 *  step 1 is the first panel displayed after the user presses
 *  "Next>", and so on.  The problem description panel is not stored in
 *  this wizard, only the panels that are specific to the wizard are
 *  stored. If the user presses "Back>" enough times to get back to the
 *  problem description, backPanel should return null.  A null panel
 *  indicates that problem description should be shown. <p>
 *
 *  Several of the comments in this class refer to "context".  Context
 *  is the data about this execution of this wizard, for example, valus
 *  that the user enters in step 1 is part of the context of later steps,
 *  and the ToDoItem with its offenders Set is always context.  Most
 *  context should be stored in instance variables of Wizard subclasses.
 */

public abstract class Wizard implements java.io.Serializable {

  ////////////////////////////////////////////////////////////////
  // instance variables

  /** User interface panels displayed so far. */
  protected Vector _panels = new Vector();

  /** The current step that the Wizard is on.  Zero indicates that the
   *  wizard has not yet begun. */
  protected int _step = 0;

  /** True when the wizard has done everything it can. */
  protected boolean _finished = false;
  protected boolean _started = false;

  protected ToDoItem _item = null;

  ////////////////////////////////////////////////////////////////
  // constructors

  /** Construct a new wizard to help the user repair a design flaw. */
  public Wizard() { }

  ////////////////////////////////////////////////////////////////
  // accessors

  public void setToDoItem(ToDoItem item) { _item = item; }

  public ToDoItem getToDoItem() { return _item; }

  /** An integer between 0 and 100, shows percent done. The current
   *  Argo/UML user itnerface shows different PostIt note icons for
   *  0, 1-25, 26-50. 51-75, and 76-100. */
  public int getProgress() { return _step * 100 / getNumSteps(); }

  /** Get the number of steps in this wizard.  Subclasses should
   *  override to return a constant, or compute based on context. */
  public abstract int getNumSteps();

  /** Get the panel that should be displayed now.  Usually called
   *  after the user pressed "Next>" and next() has returned, or after
   *  the user pressed "<Back" and back() has returned.  Also called
   *  when the user turns away from the wizard to do something else and
   *  then returns his or her attention to the wizard. */
  public JPanel getCurrentPanel() { return getPanel(_step); }


  /** Get the exising panel at step s. Step 1 is the first wizard
   *  panel. */
  public JPanel getPanel(int s) {
    if (s > 0 && s <= _panels.size())
      return (JPanel) _panels.elementAt(s - 1);
    return null;
  }

  ////////////////////////////////////////////////////////////////
  // wizard actions

  /** Return true iff the "Next>" button should be enabled.
   *  Subclasses should override to first check super.nextEnabled()
   *  and then check for legal context values. */
  public boolean canGoNext() { return _step < getNumSteps(); }

  public void next() {
    if (_step - 1 < _panels.size() - 1) {
      redoAction(_step);
      _step++;
    }
    else {
      doAction(_step);
      _step++;
      JPanel p = makePanel(_step);
      if (p != null) _panels.addElement(p);
    }
    _started = true;
    if (_item != null) _item.changed();
  }

  public boolean canGoBack() { return _step > 0; }

  public void back() {
    _step--;
    if (_step < 0) _step = 0;
    undoAction(_step);
    if (_item != null) _item.changed();
  }

  public boolean canFinish() { return true; }
  public boolean isStarted() { return _started; }
  public boolean isFinsished() { return _finished; }

  public void finish() {
    _started = true;
    int numSteps = getNumSteps();
    for (int i = _step; i <= numSteps; i++) {
      doAction(i);
      if (_item != null) _item.changed();
    }
    // needs-more-work: do all following steps
    // needs-more-work: resolve item from ToDoList
    _finished = true;
  }

  /** Create a new panel for the given step. For example, When the
   *  given step is 1, create the first step of the wizard. <p>
   *
   *  Needs-More-Work: It might be convient to make a reusable
   *  subclass of Wizard that shows all textual steps to guide the
   *  user without any automation.  Such a Wizard could be easily
   *  authored, stored in an XML file, and effiecntly presented by
   *  reusing a single panel with a single JTextArea. */
  public abstract JPanel makePanel(int newStep);

  /** Take action at the completion of a step. For example, when the
   *  given step is 0, do nothing; and when the given step is 1, do
   *  the first action.  Argo non-modal wizards should take action as
   *  they do along, as soon as possible, they should not wait until
   *  the final step. Also, if the user pressed "Finish" doAction may
   *  be called for steps that never constructored or displayed their
   *  panels. */
  public abstract void doAction(int oldStep);

  public void doAction() { doAction(_step); }

  /** Undo the action done after the given step. For example, when the
   *  given step is 0, nothing was done, so nothing can be undone; and
   *  when the given step is 1, undo the first action.  Undo allows
   *  users to work part way through fixing a problem, see the partial
   *  result, and explore a different alternative. */
  public void undoAction(int oldStep) { }

  public void undoAction() { undoAction(_step); }

  /** Redo the action at the completion of a step. For example, when
   *  the given step is 0, nothing was done, so redo nothing; and when
   *  the given step is 1, redo the first action.  This implementation
   *  simply calls doAction(). */
  public void redoAction(int oldStep) { doAction(oldStep); }

  public void redoAction() { doAction(_step); }

} /* end class Wizard */
