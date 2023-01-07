package com.tcre;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Assembly implements Part {
    private List itsParts = new LinkedList();
    private String itsPartNumber;
    private String itsDescription;

    public Assembly(String partNumber, String description) {
        itsPartNumber = partNumber;
        itsDescription = description;
    }


    @Override
    public void accept(PartVisitor v) {
        v.visit(this);
        Iterator i = getParts();
        while (i.hasNext()) {
            Part p = (Part) i.next();
            p.accept(v);
        }
    }

    public void add(Part part) {
        itsParts.add(part);
    }

    public Iterator getParts() {
        return itsParts.iterator();
    }

    @Override
    public String getPartNumber() {
        return itsPartNumber;
    }

    @Override
    public String getDescription() {
        return itsDescription;
    }
}
