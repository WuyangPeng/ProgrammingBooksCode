// hmiti7.h

class HomeItemBasic : public HomeItem
{

public:
  HomeItemBasic();

  HomeItemBasic(const xstring& Name, double PurchasePrice, 
  long PurchaseDate, const xstring& Description, 
  const xstring& Category);

virtual xstring GetName();
virtual xstring GetDescription();
virtual bool IsNull();
virtual void Read(std::istream& is);
virtual void Edit();

virtual void Write(std::ostream& os);
virtual xstring GetType();
virtual short FormattedDisplay(std::ostream& os);

virtual short ReadInteractive();
virtual short ReadFromFile(std::istream &is);
virtual bool EditField(short FieldNumber);

protected:
  enum FieldNum {e_Name = 1, e_PurchasePrice, 
  e_PurchaseDate, e_Description, e_Category};

  xstring GetFieldName(short FieldNumber);
virtual HomeItem* CopyData();

protected:
  xstring m_Name;
  double m_PurchasePrice;
  long m_PurchaseDate;
  xstring m_Description;
  xstring m_Category;
};

class HomeItemMusic : public HomeItemBasic
{
public:

  HomeItemMusic(const xstring& Name, double PurchasePrice, 
  long PurchaseDate, const xstring& Description, 
  const xstring& Category, const xstring& Artist, 
  const Vec<xstring>& Track);

HomeItemMusic& operator = (const HomeItemMusic& Item);

virtual void Write(std::ostream& os);
virtual xstring GetType();
virtual short FormattedDisplay(std::ostream& os);

virtual short ReadInteractive();
virtual short ReadFromFile(std::istream &is);
virtual bool EditField(short FieldNumber);

protected:
  enum FieldNum {e_Artist = HomeItemBasic::e_Category + 1,
  e_TrackCount, e_TrackNumber};

  xstring GetFieldName(short FieldNumber);
virtual HomeItem* CopyData();

protected:
  xstring m_Artist;
  Vec<xstring> m_Track;
};
