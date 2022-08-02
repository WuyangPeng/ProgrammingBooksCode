class HomeInventory
{
public:
    HomeInventory();

    short LoadInventory(std::ifstream& is);
    HomeItem FindItemByName(std::string Name);

private:
    Vec<HomeItem> m_Home;
};
