package com.tcre;

public interface PartVisitor {
    public void visit(PiecePart p);

    public void visit(Assembly a);
}
