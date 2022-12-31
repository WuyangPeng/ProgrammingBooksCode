package com.tcre;

import junit.framework.*;
import junit.swingui.TestRunner;

public class DBTest extends TestCase {
    public static void main(String[] args) {
        TestRunner.main(new String[]{"com.tcre.DBTest"});
    }

    public DBTest(String name) {
        super(name);
    }

    public void setUp() throws Exception {
        DB.init();
    }

    public void tearDown() throws Exception {
        DB.close();
    }

    public void testStoreProduct() throws Exception {
        ProductData storedProduct = new ProductData( );
        storedProduct.name = "MyProduct";
        storedProduct.price = 1234;
        storedProduct.sku = "999";
        DB.store(storedProduct);
        ProductData retrievedProduct = DB.getProductData("999");
        DB.deleteProductData("999");
        assertEquals(storedProduct, retrievedProduct);
    }

    public void testOrderKeyGeneration() throws Exception {
        OrderData o1 = DB.newOrder("Bob");
        OrderData o2 = DB.newOrder("Bill");
        int firstOrderId = o1.orderId;
        int secondOrderId = o2.orderId;
        assertEquals(firstOrderId + 1, secondOrderId);
    }

    public void testStoreItem() throws Exception {
        ItemData storedItem = new ItemData(1, 3, "sku");
        DB.store(storedItem);
        ItemData[] retrievedItems = DB.getItemsForOrder(1);
        assertEquals(1, retrievedItems.length);
        assertEquals(storedItem, retrievedItems[0]);
    }

    public void testNoItems() throws Exception {
        ItemData[] id = DB.getItemsForOrder(42);
        assertEquals(0, id.length);
    }
}
