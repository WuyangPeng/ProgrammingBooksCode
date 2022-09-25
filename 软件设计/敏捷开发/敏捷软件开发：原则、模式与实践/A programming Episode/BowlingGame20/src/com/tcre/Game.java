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
        adjustCurrentFrame(pins);
    }

    private void adjustCurrentFrame(int pins) {
        if (firstThrowInFrame == true) {
            if (adjustFrameForStrike(pins) == false)
                firstThrowInFrame = false;
        } else {
            firstThrowInFrame = true;
            advanceFrame();
        }
    }

    private boolean adjustFrameForStrike(int pins){
        if (pins == 10)  {
            advanceFrame();
            return true;
        }

        return false;
    }

    public int scoreForFrame(int theFrame) {

        return itsScorer.scoreForFrame(theFrame);
    }

    private void advanceFrame() {
        itsCurrentFrame = Math.min(11, itsCurrentFrame + 1);
    }

    private int itsCurrentFrame = 1;
    private boolean firstThrowInFrame = true;
    private Scorer itsScorer = new Scorer();
}
