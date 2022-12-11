package com.tcre;

import java.util.*;

public class TimeSourceImplmentation {
    private Vector itsObservers = new Vector();

    protected void notify(int hours, int minutes, int seconds) {
        Iterator i = itsObservers.iterator();
        while (i.hasNext()) {
            ClockObserver observer = (ClockObserver) i.next();
            observer.update(hours, minutes, seconds);
        }
    }

    public void registerObjserver(ClockObserver observer) {
        itsObservers.add(observer);
    }
}
