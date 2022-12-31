package com.tcre;

import junit.framework.*;
public class TestShoppingCart extends TestCase
{
    public static void main(String[] args)
    {
        junit.swingui.TestRunner.main(new String[] {"com.tcre.TestShoppingCart"});
    }

    public TestShoppingCart(String name)
    {
        super(name);
    }

    public void testOrderPrice()
    {
        Order  o = new Order("Bob");
        Product toothpaste = new Product ( "Toothpaste", 129);
        o.addItem(toothpaste, 1);
        assertEquals(129, o.total());
        Product mouthwash = new Product( "Mouthwash", 342);
        o.addItem(mouthwash, 2);
        assertEquals(813, o.total());
    }
}
