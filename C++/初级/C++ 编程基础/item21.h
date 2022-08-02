class StockItem
{
friend std::ostream& operator << (std::ostream& os, 
  const StockItem& Item);

friend std::istream& operator >> (std::istream& is, StockItem& Item);

public:
  StockItem();
  StockItem(std::string Name, short InStock, 
  short Price, short MinimumStock,
  short MinimumReorder, std::string Distributor, std::string UPC);
  bool CheckUPC(std::string ItemUPC);
  void DeductSaleFromInventory(short QuantitySold);
  short GetInventory();
  std::string GetName();
  std::string GetUPC();
  bool IsNull();
  short GetPrice();
  void Reorder(std::ostream& os);
  void FormattedDisplay(std::ostream& os);

protected:
  short m_InStock;
  short m_Price;
  short m_MinimumStock;
  short m_MinimumReorder;
  std::string m_Name;
  std::string m_Distributor;
  std::string m_UPC;
};

class DatedStockItem: public StockItem 
{
friend std::ostream& operator << (std::ostream& os, 
  const DatedStockItem& Item);

friend std::istream& operator >> (std::istream& is, DatedStockItem& Item);

public:
  DatedStockItem();
  DatedStockItem(std::string Name, short InStock, short Price, 
  short MinimumStock, short MinimumReorder,
  std::string Distributor, std::string UPC, std::string Expires);
  void FormattedDisplay(std::ostream& os);
  void Reorder(std::ostream& os);

protected:
static std::string Today();

protected:
  std::string m_Expires;
};
