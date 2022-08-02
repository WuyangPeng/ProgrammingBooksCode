// hmit8.h

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

// Basic: Art objects, furniture, jewelry, etc.
  HomeItem(const xstring& Name, double PurchasePrice, 
  long PurchaseDate, const xstring& Description, 
  const xstring& Category);

// Music: CDs, LPs, cassettes, etc.
  HomeItem(const xstring& Name, double PurchasePrice, 
  long PurchaseDate, const xstring& Description, 
  const xstring& Category, const xstring& Artist, 
  const Vec<xstring>& Track);

virtual void Write(std::ostream& os);
virtual short FormattedDisplay(std::ostream& os);
virtual xstring GetName();
virtual xstring GetDescription();
virtual xstring GetCategory();
virtual bool IsNull();
static HomeItem NewItem();

virtual void Read(std::istream& is);
virtual void Edit();

protected:
  HomeItem(int,int);
virtual HomeItem* CopyData();

protected:
  HomeItem* m_Worker;
  short m_Count;
};
