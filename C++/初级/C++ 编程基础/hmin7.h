//hmin7.h

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

    void DisplayNames(std::ostream& os);
    short LocateItemByPartialName(const xstring& Partial);
    HomeItem EditItem(short Index);
    void PrintNames(std::ostream &os);
    void PrintAll(std::ostream &os);
    void StoreInventory(std::ofstream& OutputStream);
    void DisplayItem(short Index);
    
private:
    Vec<HomeItem> m_Home;
};
