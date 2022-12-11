package com.tcre;

import java.util.*;

public class Subject {
    private Vector itsObservers = new Vector();

    protected void notifyObserver() {
        Iterator i = itsObservers.iterator();
        while (i.hasNext()) {
            Observer observer = (Observer) i.next();
            observer.update();
        }
    }

    public void registerObjserver(Observer observer) {
        itsObservers.add(observer);
    }
}
