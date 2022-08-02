package effectivejava.chapter2.item8;

// Well-behaved client of resource with cleaner safety-net (Page 33)
// 行为规范的客户使用更安全的安全网
public class Adult {
    public static void main(String[] args) {
        try (Room myRoom = new Room(7)) {
            System.out.println("Goodbye");
        }
    }
}
