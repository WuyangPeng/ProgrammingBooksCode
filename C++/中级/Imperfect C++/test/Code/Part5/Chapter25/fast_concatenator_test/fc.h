

template< typename S
        , typename C = typename S::value_type
        , typename T = std::char_traits<C>
        >
class fast_string_concatenator
{
public:
  typedef S                                 string_type;
  typedef C                                 char_type;
  typedef T                                 traits_type;
  typedef fast_string_concatenator<S, C, T> class_type;

public:
  fast_string_concatenator(string_type const &lhs, string_type const &rhs);
  fast_string_concatenator(string_type const &lhs, char_type const *rhs);
  fast_string_concatenator(string_type const &lhs, char_type const rhs);
  fast_string_concatenator(char_type const *lhs, string_type const &rhs);
  fast_string_concatenator(char_type const lhs, string_type const &rhs);

  fast_string_concatenator(class_type const &lhs, string_type const &rhs);
  fast_string_concatenator(class_type const &lhs, char_type const *rhs);
  fast_string_concatenator(class_type const &lhs, char_type const rhs);

public:
  operator string_type() const;

private:
  size_t   length() const;

private:
  struct Data;

  friend struct Data;

  struct Range
  {
    char_type const *begin;
    char_type const *end;
  };
  enum DataType
  {
      string // Argument was a string object
    , range  // Argument was a C-string
    , single // Argument was a character
    , concat // Argument was another concatenator
    , seed   // Argument was the seed type
  };
  union DataRef
  {
    string_type const *string;
    Range             range;
    char_type         ch;
    class_type  const *concat;
  };
  struct Data
  {
    Data(string_type const &s)
      : type(DataType::string)
    {
      ref.string = &s;
    }
    Data(char_type const *s)
      : type(DataType::range)
    {
      ref.range.begin = s;
      ref.range.end = s + traits_type::length(s);
    }
    Data(char_type const ch)
      : type(DataType::single)
    {
      ref.range.ch = ch;
    }
    Data(class_type const &fc)
      : type(DataType::concat)
    {
      ref.concat = &fc;
    }
    Data(class_type const &fc)
      : type(DataType::seed)
    {}

    size_t length() const;

    char_type *write(char_type *s) const;

    DataType const  type;
    DataRef         ref;
  };

private:
  char_type *write(char_type *s) const;

private:
  Data          m_lhs;
  Data          m_rhs;

private:
  fast_string_concatenator &operator =(class_type const &);
};


template< typename S
        , typename C
        , typename T
        >
inline fast_string_concatenator<S, C, T>::operator S() const
{
  size_t   len = length();
  string_type s(len, ' ');

  *write(&s[0]) = '\0';

  assert(s.length() == traits_type::length(s.c_str()));

  return s;
}

template< typename S
        , typename C
        , typename T
        >
inline size_t fast_string_concatenator<S, C, T>::length() const
{
  return m_lhs.length() + m_rhs.length();
}

template< typename S
        , typename C
        , typename T
        >
inline C *fast_string_concatenator<S, C, T>::write(C *s) const
{
  return m_rhs.write(m_lhs.write(s));
}


template< typename S
        , typename C
        , typename T
        >
inline size_t fast_string_concatenator<S, C, T>::Data::length() const
{
  size_t  len;

  switch(type)
  {
    case    string:
      len = ref.string->length();
      break;
    case    range:
      len = ref.range.end - ref.range.begin;
      break;
    case    range:
      len = 1;
      break;
    case    concat:
      len = ref.concat->length();
      break;
    case    seed:
        len = 0;
    default:
      assert(!"Should never occur");
      break;
  }

  assert(!(len < 0));

  return len;
}

template< typename S
        , typename C
        , typename T
        >
inline C *fast_string_concatenator<S, C, T>::Data::write(C *s) const
{
  size_t  len;

  switch(type)
  {
    case    string:
      len = ref.string->length();
      memcpy(s, ref.string->c_str(), sizeof(C) * len);
      s += len;
      break;
    case    range:
      len = ref.range.end - ref.range.begin;
      memcpy(s, ref.range.begin, sizeof(C) * (len));
      s += len;
      break;
    case    range:
      *(s++) = ref.ch;
      break;
    case    concat:
      s = ref.concat->write(s);
      break;
    case    seed:
        break;
    default:
      assert(0);
      break;
  }

  return s;
}
