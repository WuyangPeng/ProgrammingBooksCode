//hmin6.h

class HomeInventory
{
public:
    HomeInventory();

    short LoadInventory(std::ifstream& is);
    void DumpInventory();
    HomeItem FindItemByName(const xstring& Name);
    HomeItem AddItem();
    short LocateItemByName(const xstring& Name);
    HomeItem EditItem(const xstring& Name);

    HomeItem FindItemByDescription(const xstring& Partial);
    short LocateItemByDescription(const xstring& Partial);
    
private:
    Vec<HomeItem> m_Home;
};
