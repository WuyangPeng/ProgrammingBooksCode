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

package org.argouml.uml.ui;
import ru.novosoft.uml.*;
import javax.swing.*;
import ru.novosoft.uml.foundation.core.*;
import java.util.*;
import java.awt.*;
import java.lang.reflect.*;

/**
 *  This class is an implements a list model using reflection.
 *
 *  @author Curt Arnold
 */
public class UMLReflectionListModel extends UMLModelElementListModel   {

    private Method _getMethod = null;
    private Method _setMethod = null;
    private Method _addMethod = null;
    private Method _deleteMethod = null;
    private static final Object[] _noArgs = {};

    /**
     *   Creates a new list model
     *   @param container the container (typically a PropPanelClass or PropPanelInterface)
     *                    that provides access to the target classifier.
     *   @param property  a string that specifies the name of an event that should force a refresh
     *                       of the list model.  A null value will cause all events to trigger a refresh.
     *   @param showNone  if true, an element labelled "none" will be shown where there are
     *                        no actual entries in the list.
     */
    public UMLReflectionListModel(UMLUserInterfaceContainer container,
				  String property,
				  boolean showNone,
				  String getMethod,
				  String setMethod,
				  String addMethod,
				  String deleteMethod) {

        super(container,property,showNone);
        Class[] noArgs = {};
        try {
            _getMethod = container.getClass().getMethod(getMethod,noArgs);
            if(setMethod != null) {
                Class[] collectionArg = { Collection.class };
                _setMethod = container.getClass().getMethod(setMethod,collectionArg);
            }
            Class[] indexArg = { Integer.class };
            if(addMethod != null) {
                _addMethod = container.getClass().getMethod(addMethod,indexArg);
            }
            if(deleteMethod != null) {
                _deleteMethod = container.getClass().getMethod(deleteMethod,indexArg);
            }
        }
        catch(Exception e) {
            System.out.println(e.toString() + " in UMLReflectionListModel:" + getMethod);
        }
    }


    /**
     *  This method is called from getModelElementSize
     *    when the list size has been marked as invalid.
     *  @returns number of "actual" list entries.
     *
     */
    protected int recalcModelElementSize() {
        int size = 0;
        if(_getMethod != null) {
            try {
                Object collection = _getMethod.invoke(getContainer(),_noArgs);
                if(collection != null) {
                    if(collection instanceof Collection) {
                        size = ((Collection) collection).size();
                    }
                    else {
                        size = 1;
                    }
                }
            }
	    catch(InvocationTargetException ex) {
                System.out.println(ex.getTargetException().toString() + " is InvocationTargetException in UMLReflectionListModel.recalcModelElementSize.");
            }
            catch(Exception e) {
                System.out.println(e.toString() + " in UMLReflectionListModel.recalcModelElementSize.");
            }
        }
        return size;
    }

    /**
     *  This method returns the model element that corresponds to
     *  to the specific index.  Called from getElementAt which handles
     *  entries for "none" and formatting of elements.
     *
     *  @param index index of model element (zero based).
     *  @returns corresponding model element
     */
    protected MModelElement getModelElementAt(int index) {
        MModelElement element = null;
        if(_getMethod != null) {
            try {
                Object collection = _getMethod.invoke(getContainer(),_noArgs);
                if(collection != null) {
                    if(collection instanceof Collection) {
                        Object obj;
                        Iterator iter = ((Collection) collection).iterator();
                        for(int i = 0;iter.hasNext();i++) {
                            obj = iter.next();
                            if(i == index && obj instanceof MModelElement) {
                                element = (MModelElement) obj;
                                break;
                            }
                        }
                    }
                    else {
                        if(index == 0 && collection instanceof MModelElement) {
                            element = (MModelElement) collection;
                        }
                    }
                }
            }
            catch(Exception e) {
                System.out.println(e.toString() + " in UMLReflectionListModel.getElementAt()");
            }
        }
        return element;
    }


    /**
     *  This method builds a context (pop-up) menu for the list.  This method
     *  may be overriden for lists that have additional menu items or when
     *  the default list of actions is inappropriate.
     *
     *  @param popup popup menu
     *  @param index index of selected list item
     *  @returns "true" if popup menu should be displayed
     */
    public boolean buildPopup(JPopupMenu popup,int index) {
        UMLUserInterfaceContainer container = getContainer();
        UMLListMenuItem open = new UMLListMenuItem(container.localize("Open"),this,"open",index);
        int size = getModelElementSize();
        if(size == 0) {
            open.setEnabled(false);
        }
        popup.add(open);

        if(_deleteMethod != null) {
            UMLListMenuItem delete = new UMLListMenuItem(container.localize("Delete"),this,"delete",index);
            if(size <= 0) {
                delete.setEnabled(false);
            }
            popup.add(delete);
        }

        if(_addMethod != null) {
            UMLListMenuItem add = new UMLListMenuItem(container.localize("Add"),this,"add",index);
            int upper = getUpperBound();
	    
	    // System.out.println("upper "+upper);
	    // System.out.println("size "+size);

            if(upper > 0 && size >= upper) {
                add.setEnabled(false);
            }
	    else
            popup.add(add);
        }

        if(_setMethod != null) {
            UMLListMenuItem moveUp = new UMLListMenuItem(container.localize("Move Up"),this,"moveUp",index);
            if(index == 0) moveUp.setEnabled(false);
            popup.add(moveUp);
            UMLListMenuItem moveDown = new UMLListMenuItem(container.localize("Move Down"),this,"moveDown",index);
            if(index == getSize()-1) moveDown.setEnabled(false);
            popup.add(moveDown);
        }
        return true;
    }


    public void add(int index) {
        try {
            Object[] indexArg = { new Integer(index) };
            Object newTarget = _addMethod.invoke(getContainer(),indexArg);
            if(newTarget != null) {
		int oldSize = getModelElementSize();
		//add(newTarget);
		/* if(newOps == null)
		     fireIntervalAdded(this,oldSize,oldSize);
		    else */
		//		if (_upper==1)
		//fireIntervalAdded(this,0,size());
		    //else
		    //fireIntervalAdded(this,index+1,index+1);

                getContainer().navigateTo(newTarget);
            }
        }
	catch(InvocationTargetException ex) {
            System.out.println(ex.getTargetException().toString() + " is InvocationTargetException in UMLReflectionListModel.add() ");
        }
        catch(Exception e) {
            System.out.println(e.toString() + " in UMLReflectionListModel.add()");
        }


    }


    public void moveUp(int index) {
        if(_getMethod != null && _setMethod != null) {
            try {
                Collection oldCollection = (Collection) _getMethod.invoke(getContainer(),_noArgs);
                Collection newCollection = moveUpUtil(oldCollection,index);
                _setMethod.invoke(getContainer(),new Object[] { newCollection });
            }
	    catch(InvocationTargetException ex) {
		System.out.println(ex.getTargetException().toString() + " is InvocationTargetException in UMLReflectionListModel.moveUp()");
	    }
            catch(Exception e) {
                System.out.println(e.toString() + " in UMLReflectionListModel.moveUp()");
            }
        }
    }

    public void moveDown(int index) {
        if(_getMethod != null && _setMethod != null) {
            try {
                Collection oldCollection = (Collection) _getMethod.invoke(getContainer(),_noArgs);
                Collection newCollection = moveDownUtil(oldCollection,index);
                _setMethod.invoke(getContainer(), new Object[] { newCollection });
            }
	    catch(InvocationTargetException ex) {
		System.out.println(ex.getTargetException().toString() + " is InvocationTargetException in UMLReflectionListModel.moveDown() ");
	    }
            catch(Exception e) {
                System.out.println(e.toString() + " in UMLReflectionListModel.moveDown()");
            }
        }
    }


    public void delete(int index) {
        if(_deleteMethod != null) {
            try {
                _deleteMethod.invoke(getContainer(),new Object[] { new Integer(index) });
            }
	    catch(InvocationTargetException ex) {
		System.out.println(ex.getTargetException().toString() + " is InvocationTargetException in UMLReflectionListModel.delete()");
	    }
	    catch(Exception e) {
                System.out.println(e.toString() + " in UMLReflectionListModel.delete()");
            }
        }
    }

}




