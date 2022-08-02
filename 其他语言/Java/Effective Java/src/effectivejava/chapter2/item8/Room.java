package effectivejava.chapter2.item8;

import java.lang.ref.Cleaner;

// An autocloseable class using a cleaner as a safety net (Page 32)
// 使用autocloseable作为安全网的自动关闭类
public class Room implements AutoCloseable {
    private static final Cleaner cleaner = Cleaner.create();

    // Resource that requires cleaning. Must not refer to Room!
    // 需要清洁的资源。 绝对不能指Room！
    private static class State implements Runnable {
        int numJunkPiles; // Number of junk piles in this room（这个房间里的垃圾堆数）

        State(int numJunkPiles) {
            this.numJunkPiles = numJunkPiles;
        }

        // Invoked by close method or cleaner
        // 通过close方法或cleaner调用
        @Override public void run() {
            System.out.println("Cleaning room");
            numJunkPiles = 0;
        }
    }

    // The state of this room, shared with our cleanable
    //房间的状态，与我们的cleanable共享
    private final State state;

    // Our cleanable. Cleans the room when it’s eligible for gc
    // 我们可清洗。 清理房间时，它的资格GC
    private final Cleaner.Cleanable cleanable;

    public Room(int numJunkPiles) {
        state = new State(numJunkPiles);
        cleanable = cleaner.register(this, state);
    }

    @Override public void close() {
        cleanable.clean();
    }
}
