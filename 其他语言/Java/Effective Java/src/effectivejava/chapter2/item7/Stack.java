package effectivejava.chapter2.item7;

import java.util.*;

// Can you spot the "memory leak"?  (Pages 26-27)
// 您可以发现“内存泄漏”吗？
public class Stack {
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;

    public Stack() {
        elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }

    public void push(Object e) {
        ensureCapacity();
        elements[size++] = e;
    }

    public Object pop() {
        if (size == 0)
            throw new EmptyStackException();
        return elements[--size];
    }

    /**
     * Ensure space for at least one more element, roughly
     * doubling the capacity each time the array needs to grow.
     * 确保至少再增加一个元素的空间，每次阵列需要增长时，容量大约都会增加一倍。
     */
    private void ensureCapacity() {
        if (elements.length == size)
            elements = Arrays.copyOf(elements, 2 * size + 1);
    }

//    // Corrected version of pop method (Page 27)
    // 更正了弹出方法的版本
//    public Object pop() {
//        if (size == 0)
//            throw new EmptyStackException();
//        Object result = elements[--size];
//        elements[size] = null; // Eliminate obsolete reference（消除过时的引用）
//        return result;
//    }

    public static void main(String[] args) {
        Stack stack = new Stack();
        for (String arg : args)
            stack.push(arg);

        while (true)
            System.err.println(stack.pop());
    }
}
