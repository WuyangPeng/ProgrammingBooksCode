package com.tcre;

import java.util.Iterator;
import java.util.Vector;

public class MockTimeSource implements TimeSource {
    private Vector itsObservers = new Vector();

    public void setTime(int hours, int minutes, int seconds) {
        Iterator i = itsObservers.iterator();
        ClockObserver observer = (ClockObserver)i.next();
        observer.update(hours, minutes, seconds);
    }

    @Override
    public void registerObjserver(ClockObserver observer) {
        itsObservers.add(observer);
    }
}
