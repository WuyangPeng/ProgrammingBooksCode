package com.tcre;

public class MockTimeSource extends Subject implements TimeSource {
    private int itsHours;
    private int itsMinutes;
    private int itsSecond;

    public void setTime(int hours, int minutes, int seconds) {
        itsHours = hours;
        itsMinutes = minutes;
        itsSecond = seconds;
        notifyObserver();
    }

    @Override
    public int getHours() {
        return itsHours;
    }

    @Override
    public int getMinutes() {
        return itsMinutes;
    }

    @Override
    public int getSeconds() {
        return itsSecond;
    }
}
