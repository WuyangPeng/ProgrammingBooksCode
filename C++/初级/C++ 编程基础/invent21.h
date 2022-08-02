class Inventory
{
public:
  Inventory();

  short LoadInventory(std::ifstream& is);

// the following function was added for inventory update
  void StoreInventory(std::ofstream& OutputStream);

  DatedStockItem FindItem(std::string UPC);
  bool UpdateItem(DatedStockItem Item);
  void ReorderItems(std::ofstream &OutputStream);

private:
  Vec<DatedStockItem> m_Stock;
  short m_StockCount;
};
