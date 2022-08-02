package effectivejava.chapter2.item8;

import java.util.concurrent.TimeUnit;

// Ill-behaved client of resource with cleaner safety-net (Page 33)
// 行为不端的客户使用更安全的网络
public class Teenager {
    public static void main(String[] args) {
        new Room(99);
        System.out.println("Peace out");

        // Uncomment next line and retest behavior, but note that you MUST NOT depend on this behavior!
        // 取消注释下一行并重新测试行为，但是请注意，您一定不要依赖此行为！
//      System.gc();
    }
}
