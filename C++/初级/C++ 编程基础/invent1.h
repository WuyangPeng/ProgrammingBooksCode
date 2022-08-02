class Inventory
{
public:
    Inventory();

    short LoadInventory(std::ifstream& is);
    StockItem FindItem(std::string UPC);
    bool UpdateItem(StockItem Item);

private:
    Vec<StockItem> m_Stock;
    short m_StockCount;
};
