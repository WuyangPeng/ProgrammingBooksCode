package com.tcre;

public class MockTimeSink implements Observer {
    private int itsHours;
    private int itsMinutes;
    private int itsSecond;
    private TimeSource itsSource;

    public MockTimeSink(TimeSource source){
        itsSource = source;
    }

    public int getSeconds() {
        return itsSecond;
    }

    public int getMinutes() {
        return itsMinutes;
    }

    public int getHours() {
        return itsHours;
    }

    @Override
    public void update( ) {
        itsHours = itsSource.getHours();
        itsMinutes = itsSource.getMinutes();
        itsSecond = itsSource.getSeconds();
    }
}
