
// Updated: 11th November 2006

#include <iostream>
#include <list>
#include <vector>

#include <stlsoft/smartptr/shared_ptr.hpp>

template<typename I>
struct an_iter
{
	I m_it;
	an_iter(I i) : m_it(i) { }
	I operator->() const
	{
		return m_it;
	}
};

struct S
{
	int i;

	S(int i)
		: i(i)
	{}
};

typedef stlsoft::shared_ptr<S>	S_ptr;

struct an_iter_c
{
	an_iter_c()
		: m_s(NULL)
	{}
	an_iter_c(S const *s)
		: m_s(s)
	{}

	S const *operator ->() const
	{
		return m_s;
	}

	S const	*m_s;
};

int main(int argc, char* argv[])
{
	S a[] = { 10, 20 };

	{
		std::vector<S> v(a, a + 2);
		an_iter<std::vector<S>::iterator> it(v.begin());
		std::cout << it->i;

		std::list<S> l(a, a + 2);
		an_iter<std::list<S>::reverse_iterator> it2(l.rbegin());
		std::cout << it2->i;
	}

#if 1
	{
		std::vector<an_iter_c>	v(2);

		v[0] = an_iter_c(new S(10));
		v[1] = an_iter_c(new S(20));

		std::cout << v.begin()->i;
	}

#else /* ? 0 */
	{
		std::vector<S*>	v(2);

		v[0] = new S(10);
		v[1] = new S(20);

		std::cout << v.begin()->i;
	}

	{
		std::vector<S_ptr>	v(2);

		v[0] = S_ptr(new S(10));
		v[1] = S_ptr(new S(20));

		std::cout << v.begin()->i;
	}
#endif /* 0 */

	return 0;
}
