#include <memory>

// In namespace std
template <typename T,  // The container value type
          typename A = std::allocator<T>>
class vector
{
public:  // Member Types
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
};