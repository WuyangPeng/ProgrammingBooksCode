package com.tcre;

import java.util.Vector;

public class Order {
    private Vector itsItems = new Vector();


    public Order(String cusid) {

    }

    public void addItem(Product p, int qty) {
        Item item = new Item(p, qty);
        itsItems.add(item);
    }

    public int total() {

        int total = 0;
        for (int i = 0; i < itsItems.size(); i++) {
            Item item = (Item) itsItems.elementAt(i);
            Product p = item.getProduct();
            int qty = item.getQuantity();
            total += p.getPrice() * qty;
        }
        return total;
    }
}
