package effectivejava.chapter2.item4;

// Noninstantiable utility class (Page 19)
// 不可实例化的实用程序类
public class UtilityClass {
    // Suppress default constructor for noninstantiability
    // 抑制默认构造函数的不稳定性
    private UtilityClass() {
        throw new AssertionError();
    }

    // Remainder omitted
    // 其余省略
}
