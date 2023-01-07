package com.tcre;

public class HayesModem implements Modem {
    private String itsPhoneNumber;
    private int itsSpeakerVolune;

    @Override
    public void dial(String pno) {
        itsPhoneNumber = pno;
    }

    @Override
    public void setSpeakerVolume(int volume) {
        itsSpeakerVolune = volume;
    }

    @Override
    public String getPhoneNumber() {
        return itsPhoneNumber;
    }

    @Override
    public int getSpeakerVolume() {
        return itsSpeakerVolune;
    }
}
