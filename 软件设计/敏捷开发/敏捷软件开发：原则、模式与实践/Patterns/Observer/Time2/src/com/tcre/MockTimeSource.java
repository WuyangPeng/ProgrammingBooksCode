package com.tcre;

public class MockTimeSource implements TimeSource {
    private ClockObserver itsObserver;

    public void setTime(int hours, int minutes, int seconds) {
        itsObserver.update(hours, minutes, seconds);
    }

    @Override
    public void setObserver(ClockObserver observer) {
        itsObserver = observer;
    }
}
