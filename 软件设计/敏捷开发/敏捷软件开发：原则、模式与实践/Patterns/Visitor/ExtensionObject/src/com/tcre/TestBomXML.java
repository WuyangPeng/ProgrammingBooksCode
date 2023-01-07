package com.tcre;

import junit.framework.TestCase;

import java.util.Iterator;
import java.util.List;

public class TestBomXML extends TestCase {

    public TestBomXML(String name) {
        super(name);
    }

    private PiecePart p1;
    private PiecePart p2;
    private Assembly a;

    public void setUp() {
        p1 = new PiecePart("997624", "MyPart", 3.20);
        p2 = new PiecePart("7734", "Hell", 666);
        a = new Assembly("5879", "MyAssembly");
    }

    public void testCreatePart() {
        assertEquals("997624", p1.getPartNumber());
        assertEquals("MyPart", p1.getDescription());
        assertEquals(3.20, p1.getCost(), .01);
    }

    public void testCreateAssembly() {
        assertEquals("5879", a.getPartNumber());
        assertEquals("MyAssembly", a.getDescription());
    }

    public void testAssembly() {
        a.add(p1);
        a.add(p2);
        Iterator i = a.getParts();
        PiecePart p = (PiecePart) i.next();
        assertEquals(p, p1);
        p = (PiecePart) i.next();
        assertEquals(p, p2);
        assertEquals(i.hasNext(), false);
    }

    public void testAssemblyOfAssemblies() {
        Assembly subAssembly = new Assembly("1324", "SubAssembly");
        subAssembly.add(p1);
        a.add(subAssembly);
        Iterator i = a.getParts();
        assertEquals(subAssembly, i.next());
    }

    public void testPiecePart1XML() {
        PartExtension e = p1.getExtension("XML");
        XMLPartExtension xe = (XMLPartExtension)e;
        Element xml = xe.getXMLElement();
        assertEquals("PiecePart",xml.getName());
        assertEquals("997624",xml.getChild("PartNumber").getTextTrim());
        assertEquals("MyPart",xml.getChild("Description").getTextTrim());
        assertEquals(3.2,Double.parseDouble(xml.getChild("Cost").getTextTrim()),.01);
    }

    public void testPiecePart2XML() {
        PartExtension e = p2.getExtension("XML");
        XMLPartExtension xe = (XMLPartExtension)e;
        Element xml = xe.getXMLElement();
        assertEquals("PiecePart",xml.getName());
        assertEquals("7734",xml.getChild("PartNumber").getTextTrim());
        assertEquals("Hell",xml.getChild("Description").getTextTrim());
        assertEquals(666,Double.parseDouble(xml.getChild("Cost").getTextTrim()),.01);
    }

    public void testSimpleAssemblyXML() {
        PartExtension e = a.getExtension("XML");
        XMLPartExtension xe = (XMLPartExtension)e;
        Element xml = xe.getXMLElement();
        assertEquals("Assembly",xml.getName());
        assertEquals("5879",xml.getChild("PartNumber").getTextTrim());
        assertEquals("MyAssembly",xml.getChild("Description").getTextTrim());
        Element parts = xml.getChild("Parts");
        List partList = parts.getChildren();
        assertEquals(0,partList.size());
    }

    public void testAssemblyWithPartsXML() {
        a.add(p1);
        a.add(p2);
        PartExtension e = a.getExtension("XML");
        XMLPartExtension xe = (XMLPartExtension)e;
        Element xml = xe.getXMLElement();
        assertEquals("Assembly",xml.getName());
        assertEquals("5879",xml.getChild("PartNumber").getTextTrim());
        assertEquals("MyAssembly",xml.getChild("Description").getTextTrim());
        Element parts = xml.getChild("Parts");
        List partList = parts.getChildren();
        assertEquals(2,partList.size());

        Iterator i = partList.iterator();
        Element partElement = (Element)i.next();
        assertEquals("PiecePart",partElement.getName());
        assertEquals("997624",partElement.getChild("PartNumber").getTextTrim());

        partElement = (Element)i.next();
        assertEquals("PiecePart",partElement.getName());
        assertEquals("7734",partElement.getChild("PartNumber").getTextTrim());
    }

    public void testPiecePart1CSV() {
        PartExtension e = p1.getExtension("CSV");
        CSVPartExtension ce = (CSVPartExtension)e;
        String csv = ce.getCSV();
        assertEquals("PiecePart, 997624, MyPart, 3.2",csv);
    }

    public void testPiecePart2CSV() {
        PartExtension e = p2.getExtension("CSV");
        CSVPartExtension ce = (CSVPartExtension)e;
        String csv = ce.getCSV();
        assertEquals("PiecePart, 7734, Hell, 666.0",csv);
    }

    public void testSimpleCSV() {
        PartExtension e = a.getExtension("CSV");
        CSVPartExtension ce = (CSVPartExtension)e;
        String csv = ce.getCSV();
        assertEquals("Assembly, 5879, MyAssembly",csv);
    }

    public void testAssemblyWithPartsCSV() {
        a.add(p1);
        a.add(p2);

        PartExtension e = a.getExtension("CSV");
        CSVPartExtension ce = (CSVPartExtension)e;
        String csv = ce.getCSV();
        assertEquals("Assembly, 5879, MyAssembly, " +
                "{PiecePart, 997624, MyPart, 3.2}, " +
                "{PiecePart, 7734, Hell, 666.0}",csv);
    }

    public void testBadExtension() {
        PartExtension pe = a.getExtension("ThisStringDoesn'tMatchAnyException");
        assertTrue(pe instanceof BadPartExtension);
    }
}
