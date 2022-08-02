Solutions to Exercise 2 in Chapter 15


-Changed the include directive for list in CSketcherDoc to vector.

-Changed the using directive for SketchIterator to an iterator for a vector.

-Changed the m_Sketch member of CSketcherDoc to be a vector container.

-A vector container does not have a function to delete an element. You can only erase an element pointed to by an iterator. Changed the DeleteElement() and SendToBack() members of CSketcherDoc to find the iterator corresponding to the element to be erased and calling erase() for the iterator argument.



