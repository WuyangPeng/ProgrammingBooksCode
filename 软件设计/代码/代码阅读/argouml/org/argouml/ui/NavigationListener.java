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


package org.argouml.ui;

/**
 *   This interface is used to received notification of navigation 
 *   events.
 *
 *    @author Curt Arnold
 */
public interface NavigationListener {
    /**
     *     Called by a user interface element when a request to 
     *     navigate to a model element has been received.
     */
    public void navigateTo(Object element);
    /**
     *    Called by a user interface element when a request to 
     *    open a model element in a new window has been recieved.
     */
    public void open(Object element);


    /**
     *    Called to navigate to previous selection
     *    returns true if navigation performed
     *
     *    @param attempt false if navigation accomplished by earlier listener
     *    @return true if navigation performed
     */
    public boolean navigateBack(boolean attempt);  
    
    /**
     *    Called to navigate to next selection
     *    returns true if navigation performed
     *
     *    @param attempt false if navigation accomplished by earlier listener
     *    @return true if navigation performed
     */
    public boolean navigateForward(boolean attempt);    

    /**  
     *    Returns true if this listener has a target for
     *    a back navigation.  Only one listener needs to
     *    return true for the back button to be enabled.
    */
    public boolean isNavigateBackEnabled();

    /**  
     *    Returns true if this listener has a target for
     *    a back navigation.  Only one listener needs to
     *    return true for the back button to be enabled.
    */
    public boolean isNavigateForwardEnabled();

      
}