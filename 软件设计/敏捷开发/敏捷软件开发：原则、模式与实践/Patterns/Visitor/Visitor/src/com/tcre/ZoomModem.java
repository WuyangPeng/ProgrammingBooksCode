package com.tcre;

public class ZoomModem implements Modem {
    int configurationValue = 0;

    @Override
    public void dial(String pno) {

    }

    @Override
    public void hangup() {

    }

    @Override
    public void send(char c) {

    }

    @Override
    public void recv() {

    }

    @Override
    public void accept(ModemVisitor v) {
        v.visit(this);
    }
}
