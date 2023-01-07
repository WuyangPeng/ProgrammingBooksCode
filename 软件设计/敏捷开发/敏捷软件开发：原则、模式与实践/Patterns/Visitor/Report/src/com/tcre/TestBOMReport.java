package com.tcre;

import junit.framework.TestCase;

import java.util.Iterator;

public class TestBOMReport extends TestCase {

    public TestBOMReport(String name) {
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

    private boolean p1Found = false;
    private boolean p2Found = false;
    private boolean aFound = false;

    public void testVisitorCoverage() {
        a.add(p1);
        a.add(p2);
        a.accept(new PartVisitor() {
            @Override
            public void visit(PiecePart p) {
                if (p == p1)
                    p1Found = true;
                else if (p == p2)
                    p2Found = true;
            }

            @Override
            public void visit(Assembly assy) {
                if (assy == a)
                    aFound = true;
            }
        });

        assertTrue(p1Found);
        assertTrue(p2Found);
        assertTrue(aFound);
    }

    private Assembly cellphone;

    void setUpReportDatabase() {
        cellphone = new Assembly("CP-7734","Cell Phone");
        PiecePart display = new PiecePart("DS-1428","LCD Display",14.37);
        PiecePart speaker = new PiecePart("SP-92","Speaker",3.50);
        PiecePart microphone = new PiecePart("MC-28","Microphone",5.30);
        PiecePart cellRadio = new PiecePart("CR-56","Cell Radio",30);
        PiecePart frontCover = new PiecePart("FC-77","Front Cover",1.4);
        PiecePart backCover = new PiecePart("RC-77","RearCover",1.2);
        Assembly keypad = new Assembly("KP-62","Keypad");
        Assembly button = new Assembly("B52","Button");
        PiecePart buttonCover = new PiecePart("CV-15","Cover",.5);
        PiecePart buttonContact = new PiecePart("CN-2","Contact",1.2);
        button.add(buttonCover);
        button.add(buttonContact);
        for (int i = 0;i < 15;++i){
            keypad.add(button);
        }
        cellphone.add(display);
        cellphone.add(speaker);
        cellphone.add(microphone);
        cellphone.add(cellRadio);
        cellphone.add(frontCover);
        cellphone.add(backCover);
        cellphone.add(keypad);
    }

    public void testExplodedCost() {
        setUpReportDatabase();
        ExplodedCostVisitor v= new ExplodedCostVisitor();
        cellphone.accept(v);
        assertEquals(81.27,v.cost(),.001);
    }

    public void testPartCount() {
        setUpReportDatabase();
        PartCountVisitor v = new PartCountVisitor();
        cellphone.accept(v);

        assertEquals(36,v.getPiectCount());
        assertEquals(8,v.getPartNumberCount());
        assertEquals("DS-1428",1,v.getCountForPart("DS-1428"));
        assertEquals("SP-92",1,v.getCountForPart("SP-92"));
        assertEquals("MC-28",1,v.getCountForPart("MC-28"));
        assertEquals("CR-56",1,v.getCountForPart("CR-56"));
        assertEquals("RC-77",1,v.getCountForPart("RC-77"));
        assertEquals("CV-15",15,v.getCountForPart("CV-15"));
        assertEquals("CN-2",15,v.getCountForPart("CN-2"));
        assertEquals("Bob",0,v.getCountForPart("Bob"));
    }
}
