package com.tcre;

import java.util.Iterator;
import java.util.Vector;

public interface TimeSource {
    public void registerObjserver(ClockObserver observer);
}
