package com.tcre;

import junit.framework.TestCase;

public class TestThrow extends TestCase {
    public static void main(String args[]) {
        junit.swingui.TestRunner.main(
                new String[]{"com.tcre.TestThrow", "com.tcre.TestFrame"});
    }

    public TestThrow(String name) {
        super(name);
    }

    // public void test???
}
