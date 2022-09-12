package com.tcre;

/**
 * This class Generates prime numbers up to a user specified maximum.
 * the algorithm used is the Sieve of Eratosthenes.
 * 此类生成用户指定最大值的素数。使用的算法是埃拉托色尼筛法。
 * <p>
 * Eratosthenes of Cyrene, b. c. 276 BC, Cyrene, Libya --
 * d. c. 194, Alexandria.  The first man to calculate the circumference
 * of the Earth.  Also known for working on calendars with leap
 * years and ran the library at Alexandria.
 * 昔兰尼, b. c的埃拉托色尼。 公元前276年，利比亚昔兰尼--d. c. 194，亚历山大。
 * 第一个计算地球周长的人。还以研究闰年日历而闻名，并在亚历山大港经营图书馆。
 * <p>
 * The algorithm is quite simple.  Given an array of integers starting
 * at 2.  Cross out all multiples of 2.  Find the next uncrossed
 * integer, and cross out all of its multiples.  Repeat until
 * you have passed the square root of the maximum value.
 * 该算法非常简单。给定一个从2开始的整数数组。
 * 划掉2的所有倍数。找到下一个未交叉的整数，并划掉它的所有倍数。
 * 重复直到通过最大值的平方根。
 *
 * @author Robert C. Martin
 * @version 9 Dec 1999 rcm
 */

/**
 * Class declaration
 *
 * @author Robert C. Martin
 * @version %I%, %G%
 */
public class GeneratePrimes {
    /**
     * @param maxValue is the generation limit.
     */
    public static int[] generatePrimes(int maxValue) {
        if (maxValue >= 2) // the only valid case
        {
            // declarations
            int s = maxValue + 1; // size of array
            boolean[] f = new boolean[s];
            int i;

            // initialize array to true.
            for (i = 0; i < s; i++)
                f[i] = true;

            // get rid of known non-primes
            f[0] = f[1] = false;

            // sieve
            int j;
            for (i = 2; i < Math.sqrt(s) + 1; i++) {
                for (j = 2 * i; j < s; j += i)
                    f[j] = false; // multiple is not prime
            }

            // how many primes are there?
            int count = 0;
            for (i = 0; i < s; i++) {
                if (f[i])
                    count++; // bump count.
            }

            int[] primes = new int[count];

            // move the primes into the result
            for (i = 0, j = 0; i < s; i++) {
                if (f[i])             // if prime
                    primes[j++] = i;
            }

            return primes;  // return the primes
        } else // maxValue < 2
            return new int[0]; // return null array if bad input.
    }
}


