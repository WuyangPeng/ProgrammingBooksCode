package effectivejava.chapter2.item3.field;

// Singleton with public final field  (Page 17)
public class Elvis {
    public static final Elvis INSTANCE = new Elvis();

    private Elvis() {
    }

    public void leaveTheBuilding() {
        System.out.println("Whoa baby, I'm outta here!");
    }

    // This code would normally appear outside the class!
    // 该代码通常会出现在类之外！
    public static void main(String[] args) {
        Elvis elvis = Elvis.INSTANCE;
        elvis.leaveTheBuilding();
    }
}