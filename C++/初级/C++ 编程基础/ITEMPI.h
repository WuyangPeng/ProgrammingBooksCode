class UndatedStockItem : public StockItem
{
public:
  UndatedStockItem();

  UndatedStockItem(std::string Name, short InStock,
    short Price, short MinimumStock, short ReorderQuantity, 
    std::string Distributor, std::string UPC);

virtual bool CheckUPC(std::string UPC);
virtual void DeductSaleFromInventory(short QuantitySold);
virtual short GetInventory();
virtual std::string GetName();

virtual void Reorder(std::ostream& os);
virtual void FormattedDisplay(std::ostream& os);
virtual std::ostream& Write(std::ostream& os);

protected:
  short m_InStock;
  short m_Price;
  short m_MinimumStock;
  short m_MinimumReorder;
  std::string m_Name;
  std::string m_Distributor;
  std::string m_UPC;
};

class DatedStockItem : public UndatedStockItem
{
public:

  DatedStockItem(std::string Name, short InStock,
    short Price, short MinimumStock, short MinimumReorder, 
    std::string Distributor, std::string UPC, std::string Expires);

virtual void Reorder(std::ostream& os);
virtual void FormattedDisplay(std::ostream& os);
virtual std::ostream& Write(std::ostream& os);

protected:
static std::string Today();

protected:
  std::string m_Expires;
};
