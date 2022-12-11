package com.tcre;

public class ClockDriver implements ClockObserver {
    private TimeSink itsSink;

    public ClockDriver(MockTimeSource source, TimeSink sink) {
        source.registerObjserver(this);
        itsSink = sink;
    }

    public void update(int hours, int minutes, int seconds) {
        itsSink.setTime(hours, minutes, seconds);
    }
}
