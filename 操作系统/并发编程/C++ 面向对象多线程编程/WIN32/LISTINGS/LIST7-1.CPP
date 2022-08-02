// Listing 7.1
// Declaration of the STL stack container class

       template <class Container>
       class stack {
       friend bool operator==(const stack<Container>& x, const stack<Container>& y);
       friend bool operator<(const stack<Container>& x, const stack<Container>& y);
       public:
           typedef Container::value_type value_type;
           typedef Container::size_type size_type;
       protected:
           Container c;
		 public:
          bool empty() const { return c.empty(); }
          size_type size() const { return c.size(); }
          value_type& top() { return c.back(); }
          const value_type& top() const { return c.back(); }
          void push(const value_type& x) { c.push_back(x); }
          void pop() { c.pop_back(); }
      };
