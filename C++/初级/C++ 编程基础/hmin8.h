//hmin8.h

class HomeInventory
{
public:
    HomeInventory();

    short LoadInventory(std::ifstream& is);
    void DumpInventory();
    HomeItem AddItem();
    HomeItem EditItem(short Index);
    Vec<short> LocateItemByDescription(const xstring& Partial);

    Vec<short> LocateItemByCategory(const xstring& Partial);
    Vec<short> LocateItemByPartialName(const xstring& Partial);
    void PrintNames(std::ostream &os);
    void PrintAll(std::ostream &os);
    void StoreInventory(std::ofstream& ofs);
    void DisplayItem(short Index);

    void SortInventoryByName();
    short GetCount();
    short SelectItemByPartialName(const xstring& Partial);
    short SelectItemFromNameList();
    short SelectItemFromDescriptionList(const xstring& Partial);
    short SelectItemFromCategoryList(const xstring& Partial);
    void DeleteItem(short Index);
    
private:
    Vec<HomeItem> m_Home;
};
