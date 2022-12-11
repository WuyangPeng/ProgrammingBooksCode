package com.tcre;

public interface TimeSource {
    public void registerObjserver(ClockObserver observer);
}
