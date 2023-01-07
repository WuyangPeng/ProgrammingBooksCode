package com.tcre;

public class ErnieModem implements Modem {
    String configurationPattern = null;

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
        try
        {
            ErnieModemVisitor ev = (ErnieModemVisitor)v;
            ev.visit(this);
        }
        catch(ClassCastException e){

        }
    }
}
