class StockItem
{
public:
    StockItem();

    StockItem(std::string Name, short InStock, short Price, 
    std::string Distributor, std::string UPC);

    void Display();

private:
    short m_InStock;
    short m_Price;
    std::string m_Name;
    std::string m_Distributor;
    std::string m_UPC;
};
