package com.tcre;

public class LoudDialModem implements Modem {
    private Modem itsModem;

    public LoudDialModem(Modem m){
        itsModem = m;
    }

    @Override
    public void dial(String pno) {
        itsModem.setSpeakerVolume(10);
        itsModem.dial(pno);
    }

    @Override
    public void setSpeakerVolume(int volume) {
        itsModem.setSpeakerVolume(volume);
    }

    @Override
    public String getPhoneNumber() {
        return itsModem.getPhoneNumber();
    }

    @Override
    public int getSpeakerVolume() {
        return itsModem.getSpeakerVolume();
    }
}
