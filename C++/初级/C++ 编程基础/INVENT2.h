class Inventory
{
public:
    Inventory();

    short LoadInventory(std::ifstream& is);

// the following function was added for inventory update
    void StoreInventory(std::ofstream& os);

    StockItem FindItem(std::string UPC);
    bool UpdateItem(StockItem Item);

private:
    Vec<StockItem> m_Stock;
    short m_StockCount;
};
