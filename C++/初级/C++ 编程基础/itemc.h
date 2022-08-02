class StockItem
{
friend std::ostream& operator << (std::ostream& os, StockItem* Item);
friend std::istream& operator >> (std::istream& is, StockItem*& Item);

public:
    StockItem(std::string Name, short InStock, short MinimumStock);
virtual ~StockItem();

virtual void Reorder(std::ostream& os);
virtual void Write(std::ostream& os);

protected:
    std::string m_Name;
    short m_InStock;
    short m_MinimumStock;
};

class DatedStockItem: public StockItem
{
public:
    DatedStockItem(std::string Name, short InStock, 
      short MinimumStock, std::string Expires);

virtual void Reorder(std::ostream& os);
virtual void Write(std::ostream& os);

protected:
static std::string Today();

protected:
    std::string m_Expires;
};
