package com.tcre;

public class Game {
    public int score() {
        return itsScore;
    }

    public void add(int pins) {

        itsThrows[itsCurrentThrow++] = pins;
        itsScore += pins;
    }

    public int scoreForFrame(int theFrame) {
        int score = 0;
        int ball = 0;
        for (int currentFrame = 0; currentFrame < theFrame; ++currentFrame) {
            int firstThrow = itsThrows[ball++];
            int secondThrow = itsThrows[ball++];
            score += firstThrow + secondThrow;
            // score += itsThrows[ball++] + itsThrows[ball++];
        }
        return score;
    }

    private int itsScore = 0;
    private int[] itsThrows = new int[21];
    private int itsCurrentThrow = 0;

}
