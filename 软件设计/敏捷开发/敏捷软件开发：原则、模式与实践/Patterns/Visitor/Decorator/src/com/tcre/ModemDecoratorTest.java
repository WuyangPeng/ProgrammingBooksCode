package com.tcre;

import junit.framework.TestCase;

public class ModemDecoratorTest extends TestCase {

    public ModemDecoratorTest(String name) {
        super(name);
    }

    public void testCreateHayes() {
        Modem m = new HayesModem();
        assertEquals(null, m.getPhoneNumber());
        m.dial("5551212");
        assertEquals("5551212", m.getPhoneNumber());
        assertEquals(0, m.getSpeakerVolume());
        m.setSpeakerVolume(10);
        assertEquals(10, m.getSpeakerVolume());
    }

    public void testLoudDialModem(){
        Modem m = new HayesModem();
        Modem d = new LoudDialModem(m);

        assertEquals(null,d.getPhoneNumber());
        assertEquals(0,d.getSpeakerVolume());
        d.dial("5551212");
        assertEquals("5551212", d.getPhoneNumber());
        assertEquals(10, d.getSpeakerVolume());
    }
}
