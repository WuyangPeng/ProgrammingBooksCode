package com.tddinaction.concurrency.waitforthreads;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.RunWith;

public class TestWaitingForSpawnedThreads {

    private static final String THROW_EXCEPTION = "THROW_EXCEPTION";

    private static final String EXPIRE_TIMEOUT = "EXPIRE_TIMEOUT";

    private static final String DO_NOT_ADD_DATA = "DO_NOT_ADD_DATA";

    /**
     * Sample test class that spawns threads from inside test methods.
     */
    @RunWith(value = ThreadedRunner.class)
    public static class ControllableTestCase {
        @Test
        public void test() throws Exception {
            int count = 3;
            List<String> data = new ArrayList<String>();
            spawnThreads(count, data);
            ThreadedRunner.waitForSpawnedThreads();
            for (int i = 0; i < count; i++) {
                String threadName = "Spawned-" + (i + 1);
                assertTrue("Thread \"" + threadName
                        + "\" didn't produce its data!", data
                        .contains(threadName));
            }
        }

        public void spawnThreads(int count, final List<String> data) {
            for (int i = 0; i < count; i++) {
                new Thread("Spawned-" + (i + 1)) {
                    @Override
                    public void run() {
                        try {
                            Thread.sleep(1000);
                            if (mode(EXPIRE_TIMEOUT)) {
                                Thread.sleep(10000);
                            }
                            if (!mode(DO_NOT_ADD_DATA)) {
                                data.add(getName());
                            }
                            if (mode(THROW_EXCEPTION)) {
                                throw new RuntimeException(getName()
                                        + ": KABOOM!");
                            }
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }

                }.start();
            }
        }

        private boolean mode(String mode) {
            return Boolean.valueOf(System.getProperty(mode, "false"));
        }
    }

    @Before
    public void setUp() {
        System.setProperty(DO_NOT_ADD_DATA, "false");
        System.setProperty(EXPIRE_TIMEOUT, "false");
        System.setProperty(THROW_EXCEPTION, "false");
    }

    @Test
    public void testFailsWhenThreadsDontAddData() {
        System.setProperty(DO_NOT_ADD_DATA, "true");
        assertNumberOfFailuresEquals(1);
    }

    @Test
    public void testFailsWhenTimeoutExpires() {
        System.setProperty(EXPIRE_TIMEOUT, "true");
        assertNumberOfFailuresEquals(1);
    }

    @Test
    public void testFailsWhenThreadsThrowExceptions() {
        System.setProperty(THROW_EXCEPTION, "true");
        assertNumberOfFailuresEquals(1);
    }

    @Test
    public void everythingShouldPassWhenNoIntentionalFailuresAreIntroduced()
            throws Exception {
        assertNumberOfFailuresEquals(0);
    }

    private void assertNumberOfFailuresEquals(int expected) {
        Class<?> testClass = ControllableTestCase.class;
        Result result = JUnitCore.runClasses(testClass);
        int failures = result.getFailureCount();
        assertEquals("Number of failures.", expected, failures);
    }
}
