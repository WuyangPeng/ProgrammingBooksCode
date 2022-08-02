package effectivejava.chapter2.item3.staticfactory;

// Singleton with static factory (Page 17)
// 具有静态工厂的Singleton
public class Elvis {
    private static final Elvis INSTANCE = new Elvis();

    private Elvis() {
    }

    public static Elvis getInstance() {
        return INSTANCE;
    }

    public void leaveTheBuilding() {
        System.out.println("Whoa baby, I'm outta here!");
    }

    // This code would normally appear outside the class!
    // 该代码通常会出现在类之外！
    public static void main(String[] args) {
        Elvis elvis = Elvis.getInstance();
        elvis.leaveTheBuilding();
    }
}
