package com.tcre;

import junit.framework.TestCase;

public class ClockDriverTest extends TestCase {

    public ClockDriverTest(String name) {
        super(name);
    }

    public void testTimeChange() {
        MockTimeSource source = new MockTimeSource();
        MockTimeSink sink = new MockTimeSink();
        source.setObserver(sink);

        source.setTime(3, 4, 5);
        assertEquals(3, sink.getHours());
        assertEquals(4, sink.getMinutes());
        assertEquals(5, sink.getSeconds());

        source.setTime(7, 8, 9);
        assertEquals(7, sink.getHours());
        assertEquals(8, sink.getMinutes());
        assertEquals(9, sink.getSeconds());
    }

}
