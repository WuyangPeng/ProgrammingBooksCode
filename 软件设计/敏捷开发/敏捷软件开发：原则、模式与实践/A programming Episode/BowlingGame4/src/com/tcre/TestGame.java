package com.tcre;

import junit.framework.TestCase;

public class TestGame extends TestCase {

    public void testTwoThrowsNoMark() {
        Game g = new Game();
        g.add(5);
        g.add(4);
        assertEquals(9, g.getScore());
    }

}
