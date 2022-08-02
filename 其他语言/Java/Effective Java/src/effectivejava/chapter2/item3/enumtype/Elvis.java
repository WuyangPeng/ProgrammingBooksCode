package effectivejava.chapter2.item3.enumtype;

// Enum singleton - the preferred approach (Page 18)
// 枚举单例——首选方法
public enum Elvis {
    INSTANCE;

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
