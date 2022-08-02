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

package org.argouml.uml.diagram.static_structure.layout;

import java.awt.*;
import java.util.*;
import org.argouml.uml.diagram.layout.*;
import org.argouml.uml.diagram.ui.*;
import org.tigris.gef.presentation.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;


/**
 * This class implements a layout algoritms for class diagrams.
 */
public class ClassdiagramLayouter implements Layouter {

    /**
     * This constructor is mainly for convenience, so we don't have 
     * add every node manually to the layouter.
     */
    public ClassdiagramLayouter(UMLDiagram diagram) {

	// Get all the figures from the diagram.
	Vector nodes = diagram.getLayer().getContents(); 

	// Create ClassdiagramNodes for all the figures
	// and add them to the layouter.
	for(int i=0; i < nodes.size(); i++) {
	    if(nodes.elementAt(i) instanceof FigNode) {
		add(new ClassdiagramNode((FigNode)(nodes.elementAt(i))));
	    }
	}
    }

    /**
     * Add a object to layout.
     *
     * @param obj represents the object to layout.
     */
    public void add(LayoutedObject obj) {
	_layoutedObjects.add(obj);
    }

    /**
     * Add a ClassdiagramNode to layout.
     *
     * @param obj represents the object to layout.
     */
    public void add(ClassdiagramNode obj) {
	_layoutedObjects.add(obj);
    }

    /**
     * Remove a object from the layout process.
     *
     * @param obj represents the object to remove.
     */
    public void remove(LayoutedObject obj) {
	_layoutedObjects.remove(obj);
    }

    /**
     * Operation getObjects returns all the objects
     * currently participating in the layout process.
     *
     * @return An array holding all the object in the layouter.
     */
    public LayoutedObject [] getObjects() {
	// Create an array for the result.
	LayoutedObject [] result = new LayoutedObject[_layoutedObjects.size()];

	_layoutedObjects.copyInto(result);  // Copy the objects into the array.

        return result;  // And return the array.
    }

    /**
     * Operation getObject returns a object with a given index from the layouter.
     *
     * @param index represents the index of this object in the layouter.
     * @return The LayoutedObject for the given index.
     */
    public LayoutedObject getObject(int index) {
	return (LayoutedObject)(_layoutedObjects.elementAt(index));
    }
    
    /**
     * Get a ClassdiagramNode from the layouted objects.
     *
     * @param index represents the index of this ClassdiagramNode.
     * @return The ClassdiagramNode for this index.
     */
    public ClassdiagramNode getClassdiagramNode(int index) {
	return (ClassdiagramNode)(_layoutedObjects.elementAt(index));
    }

    /**
     * Operation layout implements the actual layout algorithm
     */
    public void layout() {

	// Determine all the up- and downlinks for each node
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    ClassdiagramNode classdiagramNode = getClassdiagramNode(i);
	    
	    if(!classdiagramNode.isPackage()) {
		Object node = classdiagramNode.getFigure().getOwner(); 

		if ( node instanceof MModelElement ) {
		    Vector specs = new Vector(((MModelElement)node).getClientDependencies());
		    specs.addAll(((MModelElement)node).getSupplierDependencies());
		    for( Iterator iter = specs.iterator(); iter.hasNext(); ) {

			// Realizations are stored as MAbstractions with a stereotype 'realize'.
			// MAbstraction is a subclass of MDependency, so get all the dependencies
			// for this node to get the abstractions, too.
			MDependency dep = (MDependency) iter.next();
			if( dep instanceof MAbstraction) {   // Is this a abstraction?
			    MAbstraction abstr = (MAbstraction)dep;
			    MStereotype stereotype = abstr.getStereotype();  // With a stereotype 'realize' ?
			    if( (stereotype != null) && "realize".equals( stereotype.getName())) {

				// Is this node the class, that implements the interface?
				Collection clients = abstr.getClients();
				for( Iterator iter2 = clients.iterator(); iter2.hasNext(); ) {
				    MModelElement me = (MModelElement)iter2.next();
				    if(node == me) {
					Collection suppliers = abstr.getSuppliers();
					for( Iterator iter3 = suppliers.iterator(); iter3.hasNext(); ) {
					    MModelElement me2 = (MModelElement)iter3.next();
					    if(me2 instanceof MClassifier) {
						ClassdiagramNode superNode = getClassdiagramNode4owner((MClassifier)me2);

						if(superNode != null) {
						    classdiagramNode.addUplink(superNode);
						}
					    }
					}
				    }
				}

				// Or the implemented interface?
				Collection suppliers = abstr.getSuppliers();
				for( Iterator iter2 = suppliers.iterator(); iter2.hasNext(); ) {
				    MModelElement me = (MModelElement)iter2.next();
				    if(node == me) {
					clients = abstr.getClients();
					for( Iterator iter3 = clients.iterator(); iter3.hasNext(); ) {
					    MModelElement me2 = (MModelElement)iter3.next();
					    if(me2 instanceof MClassifier) {
						ClassdiagramNode subNode = getClassdiagramNode4owner((MClassifier)me2);   

						if(subNode != null) {
						    classdiagramNode.addDownlink(subNode);
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}      

		if ( node instanceof MGeneralizableElement ) {

		    Collection gn = ((MClassifier)node).getGeneralizations();
		    for( Iterator iter = gn.iterator(); iter.hasNext(); ) {
			MGeneralization g = (MGeneralization) iter.next();
			ClassdiagramNode superNode = getClassdiagramNode4owner((MClassifier)(g.getParent()));

			if(superNode != null) {
			    classdiagramNode.addUplink(superNode);
			}
		    }

		    Collection sp = ((MClassifier)node).getSpecializations();
		    for( Iterator iter = sp.iterator(); iter.hasNext(); ) {
			MGeneralization s = (MGeneralization)iter.next();
			ClassdiagramNode subNode = getClassdiagramNode4owner((MClassifier)(s.getChild()));
			
			if(subNode != null) {
			    classdiagramNode.addDownlink(subNode);
			}
		    }
		}           
	    }
	}

	//
	// Check for circular references here??? Or let the RE code handle this?
	//

	// For now, all packages go above the classes and
	// interfaces
	int currentColumnPosition = 0;  // The number of elements in the current row
	int currentRow = 0;
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    ClassdiagramNode node = getClassdiagramNode(i);

	    if(node.isPackage()) {
		if(currentColumnPosition <= _vMax) {  // If there are not too many elements in the current Row
		    node.setRank(currentRow);
		    currentColumnPosition++;
		} else {
		    node.setRank(++currentRow);
		    currentColumnPosition = 0;
		}
	    }
	}
	
	// Find the maximum rank of the packages, and move
	// the classes below the packages
	int maxPackageRank = -1;
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    if(getClassdiagramNode(i).isPackage() 
	       && (getClassdiagramNode(i).getRank() > maxPackageRank)) {
		maxPackageRank = getClassdiagramNode(i).getRank();
	    }
	}
	maxPackageRank++;

	// Move the classes down below the rows containing
	// the packages.
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    if(!getClassdiagramNode(i).isPackage())
		getClassdiagramNode(i).addRank(maxPackageRank);
	}

	// It might help to add pseudo notes here to improve layout, but for 
	// the moment I'll try to do without. They should be inserted, when
	// a link spans more than 1 row.

	// Compute a weight for every ClassdiagramNode, that is supposed
	// to be used later when the nodes are sorted within their row.
	int xPos, yPos = getVGap() / 2;
	int rows = getRows();

	// Layout the packages above the classes and interfaces
	for( int curRow=0; curRow < maxPackageRank; curRow++) {

	    // The placement for the leftmost figure on the screen.
	    xPos = getHGap() / 2;

	    // Get all the objects for this row
	    ClassdiagramNode [] rowObject = getObjectsInRow(curRow);
	    
	    // Go through this row.
	    for(int i=0; i < rowObject.length; i++) {

		rowObject[i].setColumn(i);  // Required to sort the next rows.
		
		// Now set the position within the diagram.
		rowObject[i].setLocation(new Point(xPos, yPos));
		
		// Advance the horizontal position by the width of this figure.
		xPos += rowObject[i].getSize().getWidth() + getHGap();
	    }

	    // Advance the vertical position by the height of that row 
	    // (which is the max. height of the figures in that row).
	    yPos += getRowHeight(curRow) + getVGap(); 
	}

	for( int curRow=maxPackageRank; curRow < rows; curRow++) {  // Do not include packages in this process

	    // The placement for the leftmost figure on the screen.
	    xPos = getHGap() / 2;

	    // Get all the objects for this row
	    ClassdiagramNode [] rowObject = getObjectsInRow(curRow);

	    // Go through this row.
	    for(int i=0; i < rowObject.length; i++) {
		
		if(curRow == maxPackageRank) {
		    // Since we cannot use any uplinks at row 0, I simply use the 
		    // number of downlinks to place the nodes. If a node has
		    // many objects linked to it, I'll place it more to the left.
		    // Another strategy would be to start with middle, but if there
		    // are several nodes with many links, they shouldn't be near
		    // to each other, so this would cause another problem.

		    // Get the number of downlinks of this object.
		    int nDownlinks = rowObject[i].getDownlinks().size();

		    rowObject[i].setWeight( (nDownlinks > 0) ? (1/nDownlinks) : 2);
		} else {
		    
		    // Get the uplinks for this node
		    Vector uplinks = rowObject[i].getUplinks();

		    int nUplinks = uplinks.size();
		    if(nUplinks > 0) {
			
			// Find the average of all the columns of the uplinked
			// objects.
			float average_col = 0;
			for(int j=0; j < uplinks.size(); j++) {
			    average_col += ((ClassdiagramNode)(uplinks.elementAt(j))).getColumn();
			}
			average_col /= nUplinks;
			rowObject[i].setWeight(average_col);
		    } else {  // Just place this node at the right side.
			rowObject[i].setWeight(1000);
		    }
		}
	    }

	    // At this point all the nodes in the current row have a weight assigned.
	    // Sort the nodes according to this weight and assign them a column.
	    int [] pos = new int[rowObject.length];  // Array to hold the current column of the objects.
	    for(int i=0; i < pos.length; i++) { pos[i] = i; }  // Init the array.

	    // Now just do a very simple bubblesort on the array (slow, but the array should be small...)
	    boolean swapped = true;
	    while(swapped) {
		swapped = false;
		for(int i=0; i < pos.length - 1; i++) {
		    if(rowObject[pos[i]].getWeight() > rowObject[pos[i+1]].getWeight()) {
			int temp = pos[i];
			pos[i] = pos[i+1];
			pos[i+1] = temp;
			swapped = true;
		    }
		}
	    }

	    // Now all the elements in this row are sorted and we can place them within the column.
	    for(int i=0; i < pos.length; i++) {

		rowObject[pos[i]].setColumn(i);  // Required to sort the next rows.

		// If we have enough elements in this row and this node has no links,
		// move it down in the diagram
		if( (i > _vMax) 
		    && (rowObject[pos[i]].getUplinks().size() == 0) 
		    && (rowObject[pos[i]].getDownlinks().size() == 0)) {

		    if(getColumns(rows-1) > _vMax) {  // If there are already too many elements in that row
			rows++;                       // add a new empty row.
		    }
		    rowObject[pos[i]].setRank(rows - 1);  // Place the object in the last row.
		} else {
		    // Now set the position within the diagram.
		    rowObject[pos[i]].setLocation(new Point(xPos, yPos));
		    
		    // Advance the horizontal position by the width of this figure.
		    xPos += rowObject[pos[i]].getSize().getWidth() + getHGap();
		}
	    }

	    // Advance the vertical position by the height of that row 
	    // (which is the max. height of the figures in that row).
	    yPos += getRowHeight(curRow) + getVGap(); 
	}
    }
	
    /**
     * Search the nodes in this classdiagram for a node
     * with a given owner.
     * 
     * @return The classdiagram node for this owner, if it's in this
     *         diagram, or null if not.
     */
    private ClassdiagramNode getClassdiagramNode4owner(MClassifier m) {
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    if(getClassdiagramNode(i).getFigure().getOwner() == m)
		return getClassdiagramNode(i);
	}
	return null;
    }

    /**
     * Operation getMinimumDiagramSize returns the minimum diagram
     * size after the layout process.
     *
     * @return The minimum diagram size after the layout process.
     */
    public Dimension getMinimumDiagramSize() {
	int width = 0, height = 0;

	for(int i=0; i < _layoutedObjects.size(); i++) {
	    ClassdiagramNode node = getClassdiagramNode(i);
	    
	    if(node.getLocation().x + node.getSize().getWidth() + getHGap() / 2 >= width)
		width = (int)(node.getLocation().x + node.getSize().getWidth() + getHGap() / 2);

	    if(node.getLocation().y + node.getSize().getHeight() + getVGap() / 2 >= height)
		height = (int)(node.getLocation().y + node.getSize().getHeight() + getVGap() / 2);
	}
	return new Dimension(width, height); 
    }

    /**
     * Get the number of rows in this diagram.
     *
     * @return The number of rows in this layout.
     */
    private int getRows() {
	int result = 0;

	for(int i=0; i < _layoutedObjects.size(); i++) {
	    ClassdiagramNode node = getClassdiagramNode(i);

	    if(node.getRank() >= result)
		result = node.getRank() + 1;
	}
	return result;
    }

    /**
     * Operation getRowHeight does ...
     *
     * @param row represents ...
     */
    private int getRowHeight(int row) {
	int currentHeight = 0;  // Buffer for the result.

	// Check all the nodes in the layouter
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    if((getClassdiagramNode(i)).getRank() == row) {  // If the object is in this row
		if((getClassdiagramNode(i)).getSize().height > currentHeight)
		    currentHeight = (getClassdiagramNode(i)).getSize().height;
	    }
	}

	return currentHeight;
    }
    
    /**
     * Get the number of elements in a given row
     *
     * @param row The row to check.
     * @return The number of elements in the given row.
     */
    private int getColumns(int row) {
	int result = 0;

	// Check all the nodes in the layouter
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    if((getClassdiagramNode(i)).getRank() == row)    // If the object is in this row
		result++;                                    // add it to the result.
	}
	return result;
    }

    /**
     * Operation getObject InRow returns all the objects for a given row.
     *
     * @param row represents the row of the returned objects.
     */
    private ClassdiagramNode [] getObjectsInRow(int row) {
	Vector resultBuffer = new Vector();  // A Vector to store the results.

	// Check all the nodes in the layouter
	for(int i=0; i < _layoutedObjects.size(); i++) {
	    if((getClassdiagramNode(i)).getRank() == row)    // If the object is in this row
		resultBuffer.add(getClassdiagramNode(i));  // add it to the buffer.
	}

	// Create an array for the result.
	ClassdiagramNode [] result = new ClassdiagramNode[resultBuffer.size()];

	// If there are any results, copy them into the array.
	if(resultBuffer.size() > 0)
	    resultBuffer.copyInto(result);

	return result;  // Return the array.
    }

    /**
     * Get the vertical gap between nodes.
     *
     * @return The vertical gap between nodes.
     */
    protected int getVGap() {
	return _vGap;
    }

    /**
     * Get the horizontal gap between nodes.
     *
     * @return The horizontal gap between nodes.
     */
    protected int getHGap() {
	return _hGap;
    }
    
    // Attributes

    /**
     * Attribute _layoutedObjects holds the objects to layout.
     */
    private Vector _layoutedObjects = new Vector();

    /**
     * The horizontal gap between nodes.
     */
    private int _hGap = 80;

    /**
     * The vertical gap between nodes.
     */
    private int _vGap = 80;

    /**
     * The maximum of elements in a particular row
     */
    private int _vMax = 5;
}









