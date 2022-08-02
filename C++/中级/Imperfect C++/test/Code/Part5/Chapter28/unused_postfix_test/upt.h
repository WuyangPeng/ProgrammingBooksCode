template< typename V
        , typename M
        , typename R = V
        >
class unused_return_value_monitor
{
public:
  typedef unused_return_value_monitor<V, M, R>  class_type;

public:
  explicit unused_return_value_monitor(R value, M monitorFn = M())
    : m_value(value)
    , m_monitorFn(monitorFn)
    , m_bUsed(false)
  {}
  ~unused_return_value_monitor()
  {
    if(!m_bUsed)
    {
      m_monitorFn(this, m_value);
    }
  }

public:
  operator V() const
  {
    m_bUsed = true;

    return m_value;
  }

private:
  R             m_value;
  M             m_monitorFn;
  mutable bool  m_bUsed;
};
