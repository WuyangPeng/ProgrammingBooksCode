template< typename V   /* The actual property value type */
        , typename R   /* The reference type */
        , typename C   /* The enclosing class */
    >
class field_property_get
{
public:
  typedef field_property_get<V, R, C> class_type;

private:
  // Does not initialise m_value
  field_property_get()
  {}
  // Initialises m_value to given value
  explicit field_property_get(R value)
    : m_value(value)
  {}

  DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

public:
  /// Provides read-only access to the property
  operator R () const
  {
    return m_value;
  }

private:
  V m_value;

// Not to be implemented
private:
  field_property_get(class_type const &);
  class_type &operator =(class_type const &);
};


template< typename V   /* The actual property value type */
        , typename R   /* The reference type */
        , typename C   /* The enclosing class */
    >
class field_property_set
{
public:
  typedef field_property_set<V, R, C> class_type;

private:
  field_property_set()
  {}
  explicit field_property_set(R value)
    : m_value(value)
  {}

  DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

public:
  /// Provides write-only access to the property
  class_type &operator =(R value)
  {
    m_value = value;

    return *this;
  }

private:
  V  m_value;

// Not to be implemented
private:
  field_property_set(class_type const &);
  class_type &operator =(class_type const &);
};


template< typename V   /* The actual property value type */
        , typename R   /* The reference type */
    >
class field_property_get_external
{
public:
  field_property_get_external(V &value)
    : m_value(value)
  {}

// Accessors
public:
  /// Provides read-only access to the property
  operator R() const
  {
    return m_value;
  }

// Members
private:
  V  &m_value;
};


template< typename V   /* The actual property value type */
        , typename R   /* The reference type */
    >
class field_property_set_external
{
public:
  field_property_set_external(V &value)
    : m_value(value)
  {}

// Accessors
public:
  /// Provides write-only access to the property
  field_property_set_external &operator =(R value)
  {
    m_value = value;

    return *this;
  }

// Members
private:
  V  &m_value;
};
