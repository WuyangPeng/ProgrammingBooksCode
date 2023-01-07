package com.tcre;


import java.util.Iterator;

public class XMLAssemblyExtension implements XMLPartExtension {
    private Assembly itsAssembly = null;

    public XMLAssemblyExtension(Assembly assembly) {
        itsAssembly = assembly;
    }

    @Override
    public Element getXMLElement() {
        Element e = new Element("Assembly");
        e.addContent(new Element("PartNumber").setText(itsAssembly.getPartNumber()));
        e.addContent(new Element("Description").setText(itsAssembly.getDescription()));
        Element parts = new Element("Parts");
        e.addContent(parts);
        Iterator i = itsAssembly.getParts();
        while (i.hasNext()) {
            Part p = (Part) i.next();
            PartExtension pe = p.getExtension("XML");
            XMLPartExtension xpe = (XMLPartExtension) pe;
            parts.addContent(xpe.getXMLElement());
        }
        return e;
    }
}
