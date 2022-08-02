class StockItem
{
public:
    StockItem();

    StockItem(std::string Name, short InStock, short Price, 
    std::string Distributor, std::string UPC);

    void Display();
    void Read(std::istream& is);

    bool CheckUPC(std::string ItemUPC);
    void DeductSaleFromInventory(short QuantitySold);
    short GetInventory();
    std::string GetName();
    bool IsNull();
    short GetPrice();
    std::string GetUPC();

private:
    short m_InStock;
    short m_Price;
    std::string m_Name;
    std::string m_Distributor;
    std::string m_UPC;
};
