// itemp.h

class StockItem
{
friend std::ostream& operator << (std::ostream& os, 
  const StockItem& Item);

friend std::istream& operator >> (std::istream& is, StockItem& Item);

public:
  StockItem();
  StockItem(const StockItem& Item);
  StockItem& operator = (const StockItem& Item);
virtual ~StockItem();

  StockItem(std::string Name, short InStock,
  short Price, short MinimumStock,
  short MinimumReorder, std::string Distributor, std::string UPC);

  StockItem(std::string Name, short InStock,
  short Price, short MinimumStock,
  short MinimumReorder, std::string Distributor, std::string UPC,
  std::string Expires);

virtual bool CheckUPC(std::string UPC);
virtual void DeductSaleFromInventory(short QuantitySold);
virtual short GetInventory();
virtual std::string GetName();

virtual void Reorder(std::ostream& os);
virtual void FormattedDisplay(std::ostream& os);
virtual std::ostream& Write(std::ostream& os);

protected:
  StockItem(int);

protected:
  StockItem* m_Worker;
  short m_Count;
};
