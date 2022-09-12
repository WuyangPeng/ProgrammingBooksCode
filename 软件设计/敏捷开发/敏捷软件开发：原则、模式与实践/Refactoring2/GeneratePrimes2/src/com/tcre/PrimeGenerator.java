package com.tcre;

/**
 * This class Generates prime numbers up to a user specified
 * maximum.  The algorithm used is the Sieve of Eratosthenes.
 * Given an array of integers starting at 2:
 * 此类生成用户指定最大值的素数。
 * 使用的算法是埃拉托色尼筛法。 给定一个从2开始的整数数组：
 * Find the first uncrossed integer, and cross out all its
 * multiples.  Repeat until there are no more multiples
 * in the array.
 * 找到第一个未交叉的整数，并删除它的所有倍数。
 * 重复直到数组中不再有倍数。
 */

public class PrimeGenerator {
    private static int s;
    private static boolean[] f;
    private static int[] primes;

    public static int[] generatePrimes(int maxValue) {
        if (maxValue < 2)
            return new int[0];
        else {
            initializeSieve(maxValue);
            sieve();
            loadPrimes();
            return primes; // return the primes
        }
    }

    private static void loadPrimes() {
        int i;
        int j;

        // how many primes are there?
        int count = 0;
        for (i = 0; i < s; i++) {
            if (f[i])
                count++; // bump count.
        }

        primes = new int[count];

        // move the primes into the result
        for (i = 0, j = 0; i < s; i++) {
            if (f[i])             // if prime
                primes[j++] = i;
        }
    }

    private static void sieve() {
        int i;
        int j;

        for (i = 2; i < Math.sqrt(s) + 1; i++) {
            if (f[i]) { // if i is uncrossed,cross out its multiples
                for (j = 2 * i; j < s; j += i)
                    f[j] = false; // multiple is not prime
            }
        }
    }

    private static void initializeSieve(int maxValue) {
        // declarations
        s = maxValue + 1; // size of array
        f = new boolean[s];
        int i;

        // initialize array to true.
        for (i = 0; i < s; i++)
            f[i] = true;

        // get rid of known non-primes
        f[0] = f[1] = false;
    }
}