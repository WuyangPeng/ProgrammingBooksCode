package com.tcre;

public class ClockDriver {
    private TimeSink itsSink;

    public ClockDriver(MockTimeSource source, MockTimeSink sink) {
        source.setDriver(this);
        itsSink = sink;
    }

    public void update(int hours, int minutes, int seconds) {
        itsSink.setTime(hours, minutes, seconds);
    }
}
