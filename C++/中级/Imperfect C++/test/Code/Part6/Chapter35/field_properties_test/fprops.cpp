
#include <stdio.h>

#if defined(__MWERKS__)
# define    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)     friend class T
#elif defined(__BORLANDC__) || \
      defined(__COMO__) || \
      defined(__DMC__) || \
      ( defined(__GNUC__) && \
        __GNUC__ < 3) || \
      defined(__INTEL_COMPILER) || \
      defined(_MSC_VER) || \
      defined(__VECTORC) || \
      defined(__WATCOMC__)
# define    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)     friend T
#elif defined(__GNUC__) && \
      __GNUC__ >= 3

# define    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(T)     \
                                                            \
    struct friend_maker                                     \
    {                                                       \
        typedef T T2;                                       \
    };                                                      \
                                                            \
    typedef typename friend_maker::T2 friend_type;          \
                                                            \
    friend friend_type

#else
# error Compiler not discriminated
#endif /* compiler */

template<   typename V   /* The actual property value type */
        ,   typename R   /* The reference type */
        ,   typename C   /* The enclosing class */
        >
class field_property_get
{
public:
    typedef V                           value_type;
    typedef R                           reference_type;
    typedef C                           container_type;
    typedef field_property_get<V, R, C> class_type;

# if defined(__DMC__)
public:
# else
private:
# endif /* __DMC__ */
    field_property_get()
    {}
private:
    explicit field_property_get(reference_type value)
        : m_value(value)
    {}

    class_type &operator =(reference_type value)
    {
        m_value = value;

        return *this;
    }

    STLSOFT_DECLARE_TEMPLATE_PARAM_AS_FRIEND(C);

public:
    /// Provides read-only access to the property
    operator reference_type () const
    {
        return m_value;
    }

// Members
private:
    value_type  m_value;

// Not to be implemented
private:
    field_property_get(class_type const &);
    class_type &operator =(class_type const &);
};

class PropTester
{
public:
    field_property_get<int, int, PropTester>    Prop;

public:
    void SetPropValue(int i)
    {
        Prop.m_value = i;
    }
};

int main()
{
    PropTester  tester;
    int         i;

    i = tester.Prop;

    printf("%d\n", i);

    tester.SetPropValue(100);

    i = tester.Prop;

    printf("%d\n", i);

    return 0;
}
