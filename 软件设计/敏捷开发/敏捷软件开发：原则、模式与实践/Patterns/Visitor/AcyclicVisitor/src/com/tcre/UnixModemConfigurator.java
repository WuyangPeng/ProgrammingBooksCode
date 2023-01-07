package com.tcre;

public class UnixModemConfigurator implements ErnieModemVisitor, ZoomModemVisitor, HayesModemVisitor {

    public void visit(HayesModem modem) {
        modem.configurationString = "&s1=4&D=3";
    }

    public void visit(ZoomModem modem) {
        modem.configurationValue = 42;
    }

    public void visit(ErnieModem modem) {
        modem.configurationPattern = "C is too slow";
    }
}
