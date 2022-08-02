// Updated: 24th October 2003

template< typename V              /* The actual property value type */
        , typename R              /* The reference type */
        , typename C              /* The enclosing class */
        , ptrdiff_t (*PFnOff)()   /* Pointer to function providing offset of property within container */
        , R (C::*PFnGet)() const  /* Pointer to a const member function returning R */
        >
class method_property_get
{
public:
  typedef method_property_get<V, R, C, PFnOff, PFnGet>  class_type;

private:
  method_property_get()
  {}
  explicit method_property_get(R value)
    : m_value(value)
  {}

  DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

// Accessors
public:
  /// Provides read-only access to the property
  operator R() const
  {
    ptrdiff_t  offset  = (*PFnOff)();
    C          *pC     = (C*)((byte_t*)this - offset);

    return (pC->*PFnGet)();
  }

// Members
private:
  V m_value;

/// Not to be implemented
private:
  /// This method is hidden in order to prevent users of this class from
  /// becoming familiar with using operator = on the property instances
  /// from within the containing class, since doing so with 
  /// method_property_getset<> would result in an infinite loop.
  class_type &operator =(R value);
};


/// \brief This class provides method-based write-only property access
///
/// The containing class defines a set method. It also defines a static method
/// that contains the offset of the given property from within the container.
/// Then the template is parameterised with the value type, the reference type,
/// the container type, the member function and the offset function.
template< typename V            /* The actual property value type */
        , typename R            /* The reference type */
        , typename C            /* The enclosing class */
        , ptrdiff_t (*PFnOff)() /* Pointer to function providing offset of property within container */
        , void (C::*PFnSet)(R ) /* Pointer to a member function taking R */
        >
class method_property_set
{
  typedef method_property_set<V, R, C, PFnOff, PFnSet>  class_type;

private:
  method_property_set()
  {}
  explicit method_property_set(R value)
    : m_value(value)
  {}

  DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

// Accessors
public:
  /// Provides write-only access to the property
  class_type &operator =(R value)
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    (pC->*PFnSet)(value);

    return *this;
  }

// Members
private:
  V m_value;
};


/// \brief This class provides method-based read/write property access
///
/// The containing class defines get and set methods. It also defines a static 
/// method that contains the offset of the given property from within the container.
/// Then the template is parameterised with the value type, the set reference type,
/// the get reference type, the container type, the member functions and the offset
/// function.
template< typename V              /* The actual property value type */
        , typename RG             /* The get reference type */
        , typename RS             /* The set reference type */
        , typename C              /* The enclosing class */
        , ptrdiff_t (*PFnOff)()   /* Pointer to function providing offset of property within container */
        , RG (C::*PFnGet)() const /* Pointer to a const member function returning R */
        , void (C::*PFnSet)(RS)   /* Pointer to a member function taking R */
        >
class method_property_getset
{
  typedef method_property_getset<V, RG, RS, C, PFnOff, PFnGet, PFnSet>  class_type;

private:
  method_property_getset()
  {}
  explicit method_property_getset(RS value)
    : m_value(value)
  {}

  DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

// Accessors
public:
  /// Provides read-only access to the property
  operator RG () const
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    return (pC->*PFnGet)();
  }

  /// Provides write-only access to the property
  class_type &operator =(RS value)
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    (pC->*PFnSet)(value);

    return *this;
  }

// Members
private:
  V m_value;
};

#define METHOD_PROPERTY_GET(V, R, C, GM, P)         \
                                                    \
  static ptrdiff_t P##_offset##__LINE__()           \
  {                                                 \
    return offsetof(C, P);                          \
  }                                                 \
                                                    \
  method_property_get<  V                           \
                      , R                           \
                      , C                           \
                      , &C::P##_offset##__LINE__    \
                      , &C::GM                      \
                      >         P

#define METHOD_PROPERTY_SET(V, R, C, SM, P)         \
                                                    \
  static ptrdiff_t P##_offset##__LINE__()           \
  {                                                 \
    return offsetof(C, P);                          \
  }                                                 \
                                                    \
  method_property_set< V                            \
                      , R                           \
                      , C                           \
                      , &C::P##_offset##__LINE__    \
                      , &C::SM                      \
                      >         P

#define METHOD_PROPERTY_GETSET(V, RG, RS, C, GM, SM, P) \
                                                        \
  static ptrdiff_t P##_offset##__LINE__()               \
  {                                                     \
    return offsetof(C, P);                              \
  }                                                     \
                                                        \
  method_property_getset< V                             \
                        , RG                            \
                        , RS                            \
                        , C                             \
                        , &C::P##_offset##__LINE__      \
                        , &C::GM                        \
                        , &C::SM                        \
                        >       P

/* ////////////////////////////////////////////////////////////////////////////
 * Indirect method property classes
 */

/// \brief This class provides indirect method-based read-only property access
///
/// The containing class defines a get method. It also defines a static method
/// that contains the offset of the given property from within the container.
/// Then the template is parameterised with the the reference type, the
/// container type, the member function and the offset function.
template< typename R              /* The reference type */
        , typename C              /* The enclosing class */
        , ptrdiff_t (*PFnOff)()   /* Pointer to function providing offset of property within container */
        , R (C::*PFnGet)() const  /* Pointer to a const member function returning R */
        >
class method_property_get_external
{
public:
  typedef method_property_get_external<R, C, PFnOff, PFnGet>  class_type;

public:
  /// Provides read-only access to the property
  operator R () const
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    return (pC->*PFnGet)();
  }

/// Not to be implemented
private:
  /// This method is hidden in order to prevent users of this class from
  /// becoming familiar with using operator = on the property instances
  /// from within the containing class, since doing so with 
  /// method_property_getset<> would result in an infinite loop.
  class_type &operator =(R value);
};


/// \brief This class provides indirect method-based write-only property access
///
/// The containing class defines a set method. It also defines a static method
/// that contains the offset of the given property from within the container.
/// Then the template is parameterised with the reference type, the container 
/// type, the member function and the offset function.
template< typename R            /* The reference type */
        , typename C            /* The enclosing class */
        , ptrdiff_t (*PFnOff)() /* Pointer to function providing offset of property within container */
        , void (C::*PFnSet)(R ) /* Pointer to a member function taking R */
        >
class method_property_set_external
{
public:
  typedef method_property_set_external<R, C, PFnOff, PFnSet>  class_type;

public:
  /// Provides read-only access to the property
  method_property_set_external &operator =(R value)
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    (pC->*PFnSet)(value);

    return *this;
  }
};



/// \brief This class provides indirect method-based read/write property access
///
/// The containing class defines get and set methods. It also defines a static 
/// method that contains the offset of the given property from within the container.
/// Then the template is parameterised with the set reference type, the get
/// reference type, the container type, the member functions and the offset function.
template< typename RG             /* The reference type */
        , typename RS             /* The reference type */
        , typename C              /* The enclosing class */
        , ptrdiff_t (*PFnOff)()   /* Pointer to function providing offset of property within container */
        , RG (C::*PFnGet)() const /* Pointer to a const member function returning R */
        , void (C::*PFnSet)(RS )  /* Pointer to a member function taking R */
        >
class method_property_getset_external
{
public:
  typedef method_property_getset_external<RG, RS, C, PFnOff, PFnGet, PFnSet>  class_type;

public:
  /// Provides read-only access to the property
  operator RG () const
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    return (pC->*PFnGet)();
  }

  /// Provides read-only access to the property
  class_type &operator =(RS value)
  {
    ptrdiff_t offset  = (*PFnOff)();
    C         *pC     = (C*)((byte_t*)this - offset);

    (pC->*PFnSet)(value);

    return *this;
  }
};











template< typename V
        , typename RG
        , typename RS
        , typename C
        , RG (*PFnGet)(void)
        , void (*PFnSet)(RS )
        >
class static_method_property_getset
{
public:
  static_method_property_getset()
  {}
  explicit static_method_property_getset(RS value)
    : m_value(value)
  {}

// Accessors
public:
  operator RG() const
  {
    return (*PFnGet)();
  }
  static_method_property_getset &operator =(RS value)
  {
    (*PFnSet)(value);

    return *this;
  }

// Members
private:
  value_type  m_value;
};


template< typename RG
        , typename RS
        , RG (*PFnGet)(void)
        , void (*PFnSet)(RS )
        >
class static_method_property_getset_external
{
// Accessors
public:
  operator RG() const
  {
    return (*PFnGet)();
  }
  static_method_property_getset_external &operator =(RS value)
  {
    (*PFnSet)(value);

    return *this;
  }
};
