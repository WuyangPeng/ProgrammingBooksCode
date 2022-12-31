package com.tcre;

public class Product {
    private int itsPrice;

    public Product(String name, int price) {
        itsPrice = price;
    }

    public int getPrice() {
        return itsPrice;
    }
}
