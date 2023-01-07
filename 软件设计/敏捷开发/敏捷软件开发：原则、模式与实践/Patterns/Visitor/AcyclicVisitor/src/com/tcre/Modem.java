package com.tcre;

public interface Modem {
    public void dial(String pno);
    public void hangup();
    public void send(char c);
    public void recv();
    public void accept(ModemVisitor v);
}
