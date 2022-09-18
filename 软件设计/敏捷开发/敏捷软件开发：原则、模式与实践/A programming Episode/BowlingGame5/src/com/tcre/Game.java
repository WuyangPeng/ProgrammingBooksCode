package com.tcre;

public class Game {
    public int score() {
        return itsScore;
    }

    public void add(int pins) {

        itsThrows[itsCurrentThrow++] = pins;
        itsScore += pins;
    }

    public int scoreForFrame(int frame) {
        int score = 0;
        for (int ball = 0; frame > 0 && (ball < itsCurrentThrow); ball += 2,frame--)
        {
            score += itsThrows[ball] + itsThrows[ball + 1];
        }
        return score;
    }

    private int itsScore = 0;
    private int[] itsThrows = new int[21];
    private int itsCurrentThrow = 0;

}
