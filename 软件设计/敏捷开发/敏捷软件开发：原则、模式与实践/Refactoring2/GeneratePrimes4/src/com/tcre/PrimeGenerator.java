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
    private static boolean[] isCrossed;
    private static int[] result;

    public static int[] generatePrimes(int maxValue) {
        if (maxValue < 2)
            return new int[0];
        else {
            initializeArrayOfIntegers(maxValue);
            crossOutMultiples();
            putUncrossedIntegersIntoResult();
            return result;
        }
    }

    private static void initializeArrayOfIntegers(int maxValue) {

        isCrossed = new boolean[maxValue + 1];
        for (int i = 2; i < isCrossed.length; i++)
            isCrossed[i] = false;
    }

    private static void crossOutMultiples() {
        int maxPrimeFactor = calcMaxPrimeFactor();
        for (int i = 2; i <= maxPrimeFactor; i++) {
            if (notCrossed(i)) {
                crossOutMultiplesOf(i);
            }
        }
    }

    private static int calcMaxPrimeFactor() {
        // We cross out all multiples of p;where p is prime.
        // Thus,all crossed out multiples have p and q for
        // factors. If p > sqrt of the size of the array,then
        // q will never be greater than 1. Thus p is the
        // largest prime factor in the array,and is also
        // the iteration limit.
        // 我们划掉p的所有倍数；其中p是素数。
        // 因此，所有被划掉的倍数都有 p 和 q 的因子。
        // 如果数组大小的 p > sqrt，则 q 永远不会大于 1。
        // 因此 p 是数组中最大的素数因子，也是迭代限制。
        double maxPrimeFactor = Math.sqrt(isCrossed.length) + 1;
        return (int) maxPrimeFactor;
    }

    private static void crossOutMultiplesOf(int i) {
        for (int multiple = 2 * i;
             multiple < isCrossed.length;
             multiple += i)
            isCrossed[multiple] = true;
    }

    private static boolean notCrossed(int i) {
        return isCrossed[i] == false;
    }

    private static void putUncrossedIntegersIntoResult() {
        int i;
        int j;

        // how many primes are there?
        int count = 0;
        for (i = 2; i < isCrossed.length; i++) {
            if (notCrossed(i))
                count++; // bump count.
        }

        result = new int[count];

        // move the primes into the result
        for (i = 2, j = 0; i < isCrossed.length; i++) {
            if (notCrossed(i))             // if prime
                result[j++] = i;
        }
    }
}