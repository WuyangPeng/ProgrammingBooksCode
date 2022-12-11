package com.tcre;

public class MockTimeSource implements TimeSource {
    TimeSourceImplmentation tsImp = new TimeSourceImplmentation();

    @Override
    public void registerObjserver(ClockObserver observer) {
        tsImp.registerObjserver(observer);
    }

    public void setTime(int hours, int minutes, int seconds) {

        tsImp.notify(hours, minutes, seconds);
    }


}
