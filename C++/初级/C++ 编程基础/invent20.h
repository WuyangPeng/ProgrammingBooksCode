class Inventory
{
public:
    Inventory();

    short LoadInventory(std::istream& is);

    void StoreInventory(std::ostream& os);

    StockItem FindItem(std::string UPC);
    bool UpdateItem(StockItem Item);
    void ReorderItems(std::ostream& os);

private:
    Vec<StockItem> m_Stock;
    short m_StockCount;
};
