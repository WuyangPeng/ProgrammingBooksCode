package com.tcre;

import javax.swing.text.html.HTMLDocument;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Assembly extends Part {
    private List itsParts = new LinkedList();
    private String itsPartNumber;
    private String itsDescription;

    public Assembly(String partNumber, String description) {
        itsPartNumber = partNumber;
        itsDescription = description;
        addExtension("CSV", new CSVAssemblyExtension(this));
        addExtension("XML", new XMLAssemblyExtension(this));
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
