package effectivejava.chapter2.item6;

import java.util.Comparator;

// Hideously slow program! Can you spot the object creation? (Page 24)
// 程序太慢了！ 您可以发现对象的创建吗？
public class Sum {
    private static long sum() {
        Long sum = 0L;
        for (long i = 0; i <= Integer.MAX_VALUE; i++)
            sum += i;
        return sum;
    }

    public static void main(String[] args) {
        int numSets = Integer.parseInt(args[0]);
        long x = 0;

        for (int i = 0; i < numSets; i++) {
            long start = System.nanoTime();
            x += sum();
            long end = System.nanoTime();
            System.out.println((end - start) / 1_000_000. + " ms.");
        }

        // Prevents VM from optimizing away everything.
        // 防止VM优化所有内容。
        if (x == 42)
            System.out.println();
    }
}