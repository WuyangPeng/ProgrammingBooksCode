
// Updated: 16th September 2005

#include <unixstl/exceptions.hpp>
#include <unixstl/filesystem_traits.hpp>
#include <unixstl/string_access.hpp>

#include <string>
#include <dirent.h>

namespace unixstl
{

class readdir_sequence_exception
    : public unix_exception
{
/// \name Types
/// @{
public:
    typedef unix_exception              parent_class_type;
    typedef readdir_sequence_exception  class_type;
/// @}

/// \name Construction
/// @{
public:
    readdir_sequence_exception(us_char_a_t const *message, us_int_t erno)
        : parent_class_type(message, erno)
    {}
/// @}
};



class readdir_sequence
{
public:
  typedef char							char_type;
public: // Types
  typedef char_type const				*value_type;
  typedef std::string					string_type;
  typedef filesystem_traits<char_type>	traits_type;
  class									const_iterator;
public: // Constants
  enum
  {
      includeDots = 0x0008  /*!< Requests that dots directories be included in the returned sequence */
    , directories = 0x0010  /*!< Causes the search to include directories */
    , files       = 0x0020  /*!< Causes the search to include files */
  };
public: // Construction
  template <typename S>  
  readdir_sequence(S const &dir, int flags = 0)
    : m_directory(validate_directory_(stlsoft::c_str_ptr(dir), flags))
    , m_flags(validate_flags_(flags))
  {}

public: // Iteration
  const_iterator  begin() const;
  const_iterator  end() const;
public: // Size
  bool empty() const;
private: // Implementation
  static int          validate_flags_(int flags);
  static string_type  validate_directory_(char_type const *directory, int flags);
private: // Members
  const int         m_flags;
  const string_type m_directory;
};


//#define NO_COPY_SEMANTICS
//#define SHOW_REF_RETURN

class readdir_sequence::const_iterator
{
public: // Types
  typedef readdir_sequence::char_type	char_type;
  typedef char_type const				*value_type;
  typedef const_iterator				class_type;
private: // Construction
  friend class readdir_sequence;
  const_iterator(DIR *dir, string_type const &directory, int flags);
public:
  const_iterator();
#ifndef NO_COPY_SEMANTICS
  const_iterator(class_type const &rhs);
#endif /* 0 */
  ~const_iterator() stlsoft_throw_0();
#ifndef NO_COPY_SEMANTICS
  class_type const &operator =(class_type const &rhs);
#endif /* 0 */
public: // Methods
  class_type &operator ++();
  class_type operator ++(int);
#ifdef SHOW_REF_RETURN
//  typedef char_type const *const &const_reference;
  typedef char_type const *&const_reference;

  const_reference operator *() const;
#else /* ? SHOW_REF_RETURN */
  char_type const *operator *() const;
#endif /* SHOW_REF_RETURN */

public: // Comparison
  bool equal(class_type const &rhs) const;

private: // Members
  string_type const &m_directory;
  DIR               *m_dir;
  struct dirent     *m_entry;
  int               m_flags;
private: // Proscribed (for now)
#ifdef NO_COPY_SEMANTICS
  const_iterator(class_type const &rhs);
  class_type const &operator =(class_type const &rhs);
#endif /* 0 */
};

#if 1
inline bool operator ==(readdir_sequence::const_iterator const &lhs, readdir_sequence::const_iterator const &rhs)
{
  return lhs.equal(rhs);
}

inline bool operator !=(readdir_sequence::const_iterator const &lhs, readdir_sequence::const_iterator const &rhs)
{
  return !lhs.equal(rhs);
}
#endif /* 0 */


// readdir_sequence

inline /* static */ us_int_t readdir_sequence::validate_flags_(us_int_t flags)
{
  if(0 == (flags & (directories | files)))
  {
    flags |= (directories | files);
  }

  return flags;
}

inline /* static */ readdir_sequence::string_type readdir_sequence::validate_directory_(char_type const *directory, int flags)
{
	if(	NULL == directory ||
		'\0' == *directory)
	{
		directory = ".";
	}

	string_type	dir(directory);

	if('/' != dir[dir.size() - 1])
	{
		dir += "/";
	}

	return dir;
}

inline bool readdir_sequence::empty() const
{
	return begin() == end();
}

inline readdir_sequence::const_iterator readdir_sequence::begin() const
{
  DIR *dir = ::opendir(m_directory.c_str());

  if(NULL == dir)
  {
    throw readdir_sequence_exception("Failed to enumerate directory", errno);
  }

  return const_iterator(dir, m_directory, m_flags);
}

inline readdir_sequence::const_iterator readdir_sequence::end() const
{
	return const_iterator();
}


// readdir_sequence::const_iterator

inline readdir_sequence::const_iterator::const_iterator(DIR *dir, string_type const &directory, int flags)
  : m_directory(directory)
  , m_dir(dir)
  , m_entry(NULL)
  , m_flags(flags)
{
    if(NULL != m_dir)
    {
        operator ++();
    }
}


#ifndef NO_COPY_SEMANTICS
inline readdir_sequence::const_iterator::const_iterator(class_type const &rhs)
    : m_directory(rhs.m_directory)
    , m_dir(rhs.m_dir)
    , m_entry(rhs.m_entry)
	, m_flags(rhs.m_flags)
{
}
#endif /* 0 */

inline readdir_sequence::const_iterator::const_iterator()
    : m_directory(m_directory)
    , m_dir(NULL)
    , m_entry(NULL)
	, m_flags(0)
{}


inline readdir_sequence::const_iterator::~const_iterator()
{
  if(NULL != m_dir)
  {
    ::closedir(m_dir);
  }
}

#ifdef SHOW_REF_RETURN
inline readdir_sequence::const_iterator::const_reference readdir_sequence::const_iterator::operator *() const
#else /* ? SHOW_REF_RETURN */
inline readdir_sequence::const_iterator::char_type const *readdir_sequence::const_iterator::operator *() const
#endif /* SHOW_REF_RETURN */
{
	return m_entry->d_name;
}

inline readdir_sequence::const_iterator &readdir_sequence::const_iterator::operator ++()
{
  unixstl_message_assert( "Incrementing invalid iterator", NULL != m_dir);

  for(;;)
  {
    errno = 0;

    m_entry = ::readdir(m_dir);

    if(NULL == m_entry)
    {
      if(0 != errno)
      {
#ifdef __STLSOFT_CF_EXCEPTION_SUPPORT
        throw readdir_sequence_exception("Partial failure of directory enumeration", errno);
#endif /* __STLSOFT_CF_EXCEPTION_SUPPORT */
      }
    }
    else
    {
      unixstl_assert(NULL != m_entry->d_name);

      if(0 == (m_flags & includeDots))
      {
        if(traits_type::is_dots(m_entry->d_name))
        {
          continue; // Don't want dots; skip it
        }
      }

      // If either 
      //
      // - eliding files or directories, or
      // - requiring absolute path
      //
      // then need to construct it. 
      if((m_flags & (directories | files)) != (directories | files))
      {
        // Now need to process the file, by using stat
        traits_type::stat_data_type	st;
        string_type					scratch(m_directory);

        scratch += m_entry->d_name;

        if(!traits_type::stat(scratch.c_str(), &st))
        {
          // Failed to get info from entry. Must assume it is
          // dead, so skip it
          continue;
        }
        else
        {
          if(m_flags & directories) // Want directories
          {
            if(traits_type::is_directory(&st))
            {
              // It is a directory, so accept it
              break;
            }
          }
          if(m_flags & files) // Want files
          {
            if(traits_type::is_file(&st))
            {
              // It is a file, so accept it
              break;
            }
          }

          continue; // Not a match, so skip this entry
        }
      }
    }

    break;
  }

  if(NULL == m_entry)
  {
    ::closedir(m_dir);

    m_dir = NULL;
  }

  return *this;
}

inline bool readdir_sequence::const_iterator::equal(readdir_sequence::const_iterator const &rhs) const
{
  unixstl_assert(NULL == m_dir || NULL == rhs.m_dir || m_dir == rhs.m_dir);

  return m_entry == rhs.m_entry;
}


} // namespace unixstl