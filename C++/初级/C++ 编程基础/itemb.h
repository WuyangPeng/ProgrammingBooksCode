// itemb.h

class StockItem
{
public:
  StockItem(std::string Name, short InStock, short MinimumStock);
virtual void Reorder(std::ostream& os);

protected:
  std::string m_Name;
  short m_InStock;
  short m_MinimumStock;
};

class DatedStockItem: public StockItem // deriving a new class
{
public:
  DatedStockItem(std::string Name, short InStock, short MinimumStock, 
  std::string Expires);

virtual void Reorder(std::ostream& os);

protected:
static std::string Today();

protected:
  std::string m_Expires;
};
