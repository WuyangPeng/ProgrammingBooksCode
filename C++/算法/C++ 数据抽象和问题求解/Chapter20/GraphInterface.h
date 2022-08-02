//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** An interface for the ADT undirected, connected graph.
 Listing 20-1.
 @file GraphInterface.h */

#ifndef _GRAPH_INTERFACE
#define _GRAPH_INTERFACE

template<class LabelType>
class GraphInterface
{
public:
   /** Gets the number of vertices in this graph.
    @pre   None.
    @return  The number of vertices in the graph. */
   virtual int getNumVertices() const = 0;
   
   /** Gets the number of edges in this graph.
    @pre   None.
    @return  The number of edges in the graph. */
   virtual int getNumEdges() const = 0;
   
   /** Creates an undirected edge in this graph between two vertices
       that have the given labels. If such vertices do not exist, creates
       them and adds them to the graph before creating the edge.
    @param start  A label for the first vertex. 
    @param end  A label for the second vertex.
    @param edgeWeight  The integer weight of the edge.
    @return  True if the edge is created, or false otherwise. */
   virtual bool add(LabelType start, LabelType end, int edgeWeight) = 0;
   
   /** Removes an edge from this graph. If a vertex has no other edges, 
       it is removed from the graph since this is a connected graph. 
    @pre  None.
    @param start  A label for the first vertex.
    @param end  A label for the second vertex.
    @return  True if the edge is removed, or false otherwise. */
   virtual bool remove(LabelType start, LabelType end) = 0;
   
   /** Gets the weight of an edge in this graph.
    @return  The weight of the specified edge. 
       If no such edge exists, returns a negative integer. */
   virtual int getEdgeWeight(LabelType start, LabelType end) const = 0;
   
   /** Performs a depth-first search of this graph beginning at the given
       vertex and calls a given function once for each vertex visited.
    @param start  A label for the first vertex.
    @param visit  A client-defined function that performs an operation on
       or with each visited vertex. */
   virtual void depthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;

   /** Performs a breadth-first search of this graph beginning at the given
       vertex and calls a given function once for each vertex visited.
    @param start  A label for the first vertex.
    @param visit  A client-defined function that performs an operation on
       or with each visited vertex. */
   virtual void breadthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
}; // end GraphInterface
#endif
