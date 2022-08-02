/**
   @file invoice.cpp
   @author Cay Horstmann
*/

/**
   Describes an invoice for a set of purchased products.
*/
class Invoice
{
public:
   /**
      Adds a charge for a product to this invoice.
      @param aProduct the product that the customer ordered
      @param quantity the quantity of the product
   */
   void add(Product p, int quantity);
   /**
      Prints the invoice.
   */
   void print() const;
};

/**
   Describes a quantity of an article to purchase and its price.
*/
class Item
{  
public:  
   /**
      Computes the total cost of this item.
      @return the total price
   */
   double get_total_price() const;
  
   /**
      Prints this item.
   */
   void print() const;
};

/**
   Describes a product with a description and a price.
*/
class Product
{  
public:  
   /**
      Gets the product description.
      @return the description
   */
   string get_description() const;

   /**
      Gets the product price.
      @return the unit price
   */
   double get_price() const;
};

/**
   Describes a mailing address.
*/
class Address
{  
public:  
   /**
      Prints the address.
   */
   void print() const;
};


