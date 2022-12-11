package com.tcre;

public class MockTimeSource implements TimeSource {
    private ClockDriver itsDriver;

    public void setTime(int hours, int minutes, int seconds) {
        itsDriver.update(hours, minutes, seconds);
    }

    @Override
    public void setDriver(ClockDriver dirver) {
        itsDriver = dirver;
    }
}
