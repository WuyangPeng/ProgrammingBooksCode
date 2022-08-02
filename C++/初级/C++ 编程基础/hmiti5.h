// hmiti5.h

class HomeItemBasic : public HomeItem
{

public:
  HomeItemBasic();

  HomeItemBasic(std::string Name, double PurchasePrice, 
  long PurchaseDate, std::string Description, std::string Category);

virtual std::string GetName();
virtual void Read(std::istream& is);
virtual void Edit();

virtual void Write(std::ostream& os);
virtual std::string GetType();
virtual short FormattedDisplay(std::ostream& os);

virtual short ReadInteractive();
virtual short ReadFromFile(std::istream &is);
virtual bool EditField(short FieldNumber);

protected:
  enum FieldNum {e_Name = 1, e_PurchasePrice, 
  e_PurchaseDate, e_Description, e_Category};

  std::string GetFieldName(short FieldNumber);
virtual HomeItem* CopyData();

protected:
  std::string m_Name;
  double m_PurchasePrice;
  long m_PurchaseDate;
  std::string m_Description;
  std::string m_Category;
};

class HomeItemMusic : public HomeItemBasic
{
public:
  HomeItemMusic(std::string Name, double PurchasePrice, 
  long PurchaseDate, std::string Description, std::string Category,
  std::string Artist, Vec<std::string> Track);

virtual void Write(std::ostream& os);
virtual std::string GetType();
virtual short FormattedDisplay(std::ostream& os);

virtual short ReadInteractive();
virtual short ReadFromFile(std::istream &is);
virtual bool EditField(short FieldNumber);

protected:
  enum FieldNum {e_Artist = HomeItemBasic::e_Category + 1,
  e_TrackCount, e_TrackNumber};

  std::string GetFieldName(short FieldNumber);
virtual HomeItem* CopyData();

protected:
  std::string m_Artist;
  Vec<std::string> m_Track;
};
