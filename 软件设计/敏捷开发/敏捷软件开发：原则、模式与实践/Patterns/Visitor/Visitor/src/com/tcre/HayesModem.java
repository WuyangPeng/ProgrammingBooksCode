package com.tcre;

public class HayesModem implements Modem {
    String configurationString = null;

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
