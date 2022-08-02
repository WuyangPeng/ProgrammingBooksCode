// hmiti2.h

class HomeItemBasic : public HomeItem
{
public:
  HomeItemBasic();

  HomeItemBasic(std::string Name, double PurchasePrice, 
  long PurchaseDate, std::string Description, std::string Category);

virtual void Write(std::ostream& os);

virtual void FormattedDisplay(std::ostream& os);
virtual std::string GetName();

virtual std::string GetType();

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

virtual void FormattedDisplay(std::ostream& os);
virtual std::string GetName();

virtual std::string GetType();


protected:
  std::string m_Artist;
  Vec<std::string> m_Track;
};
