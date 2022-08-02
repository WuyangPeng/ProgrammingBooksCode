//hmin5.h

class HomeInventory
{
public:
    HomeInventory();

    short LoadInventory(std::ifstream& is);
    void DumpInventory();
    HomeItem FindItemByName(std::string Name);
    HomeItem AddItem();
    short LocateItemByName(std::string Name);
    HomeItem EditItem(std::string Name);

private:
    Vec<HomeItem> m_Home;
};
