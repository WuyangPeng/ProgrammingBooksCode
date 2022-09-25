package com.tcre;

public class Game {
    public int score() {
        return scoreForFrame(getCurrentFrame() - 1);
    }

    public int getCurrentFrame() {
        return itsCurrentFrame;
    }

    public void add(int pins) {

        itsScorer.addThrow(pins);
        itsScore += pins;
        adjustCurrentFrame(pins);
    }

    private void adjustCurrentFrame(int pins) {
        if (firstThrowInFrame == true) {
            if (pins == 10) // strike
                itsCurrentFrame++;
            else
                firstThrowInFrame = false;
        } else {
            firstThrowInFrame = true;
            ++itsCurrentFrame;
        }

        itsCurrentFrame = Math.min(11, itsCurrentFrame);
    }

    public int scoreForFrame(int theFrame) {

        return itsScorer.scoreForFrame(theFrame);
    }

    private int itsScore = 0;
    private int itsCurrentFrame = 1;
    private boolean firstThrowInFrame = true;
    private Scorer itsScorer = new Scorer();
}
