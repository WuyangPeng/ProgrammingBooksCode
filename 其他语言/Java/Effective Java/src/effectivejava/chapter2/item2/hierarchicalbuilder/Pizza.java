package effectivejava.chapter2.item2.hierarchicalbuilder;

import java.util.*;

// Builder pattern for class hierarchies (Page 14)
// 类层次结构的构建器模式

// Note that the underlying "simulated self-type" idiom  allows for arbitrary fluid hierarchies, not just builders
// 请注意，底层的“模拟的自我类型”惯用法允许任意的流体层次结构，而不仅仅是构建器

public abstract class Pizza {
    public enum Topping {HAM, MUSHROOM, ONION, PEPPER, SAUSAGE}

    final Set<Topping> toppings;

    abstract static class Builder<T extends Builder<T>> {
        EnumSet<Topping> toppings = EnumSet.noneOf(Topping.class);

        public T addTopping(Topping topping) {
            toppings.add(Objects.requireNonNull(topping));
            return self();
        }

        abstract Pizza build();

        // Subclasses must override this method to return "this"
        // 子类必须重写此方法以返回“this”
        protected abstract T self();
    }

    Pizza(Builder<?> builder) {
        toppings = builder.toppings.clone(); // See Item 50
    }
}
