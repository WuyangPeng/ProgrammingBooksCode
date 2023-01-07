package com.tcre;

public interface Modem {
    public void dial(String pno);
    public void setSpeakerVolume(int volume);
    public String getPhoneNumber();
    public int getSpeakerVolume();
}
