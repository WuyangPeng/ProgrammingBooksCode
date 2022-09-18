package com.tcre;

public class Game {
    public int getScore() {
        return itsScore;
    }

    public void add(int pins) {
        itsScore += pins;
    }

    private int itsScore = 0;
}
