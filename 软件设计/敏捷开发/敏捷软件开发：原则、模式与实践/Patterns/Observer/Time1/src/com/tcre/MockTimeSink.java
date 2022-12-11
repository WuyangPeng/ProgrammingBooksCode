package com.tcre;

public class MockTimeSink implements TimeSink {
    private int itsHours;
    private int itsMinutes;
    private int itsSecond;

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
    public void setTime(int hours, int minutes, int seconds) {
        itsHours = hours;
        itsMinutes = minutes;
        itsSecond = seconds;
    }
}
