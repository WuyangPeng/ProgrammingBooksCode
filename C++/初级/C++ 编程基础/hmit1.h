// hmit1.h

class HomeItem
{
friend std::ostream& operator << (std::ostream& os, 
  const HomeItem& Item);

friend std::istream& operator >> (std::istream& is, HomeItem& Item);

public:
  HomeItem();
  HomeItem(const HomeItem& Item);
  HomeItem& operator = (const HomeItem& Item);
virtual ~HomeItem();

// Basic: Includes art objects, furniture, jewelry, etc.
  HomeItem(std::string Name, double PurchasePrice, 
  long PurchaseDate, std::string Description, std::string Category);

// Music: CDs, LPs, cassettes, etc.
  HomeItem(std::string Name, double PurchasePrice, 
  long PurchaseDate, std::string Description, std::string Category,
  std::string Artist, Vec<std::string> Track);

virtual void Write(std::ostream& os);

protected:
  HomeItem(int);

protected:
  HomeItem* m_Worker;
  short m_Count;
};
