
// Updated: 23rd February 2006

namespace
{
    template <ss_typename_param_k S>
    struct charset_comparator
    {
        typedef S                   delimiter_type;

        template <ss_typename_param_k const_iterator>
        static bool not_equal(delimiter_type const &delim, const_iterator &it)
        {
            return delim.end() == std::find(delim.begin(), delim.end(), *it);
        }

        static size_t length(delimiter_type const &delim)
        {
            return 1;
        }
    };

	inline std::basic_ostream<char, std::char_traits<char> > &flush(std::basic_ostream<char, std::char_traits<char> > &stm)
	{	
		stm.flush();
		return (stm);
	}

	struct Results
	{
		unsigned long		t1;			// Short string (str1), char delim, preserving
		size_t				n1;
		size_t				l1;
		unsigned long		t2;			// Medium string (str2), char delim, skipping
		size_t				n2;
		size_t				l2;
		unsigned long		t3;			// Medium string (str2), char delim, preserving
		size_t				n3;
		size_t				l3;
		unsigned long		t4;			// Long string (str3), char delim, skipping
		size_t				n4;
		size_t				l4;
		unsigned long		t5;			// Medium string (str4), string delim, skipping
		size_t				n5;
		size_t				l5;
		unsigned long		t6;			// Medium string (str4), string delim, preserving
		size_t				n6;
		size_t				l6;
		unsigned long		t7;			// Long string (str5), string delim, skipping
		size_t				n7;
		size_t				l7;
		unsigned long		t8;			// charset: Medium string (str4), ws delim, skipping
		size_t				n8;
		size_t				l8;
		unsigned long		t9;			// charset: Long string (str5), ws delim, skipping
		size_t				n9;
		size_t				l9;
		unsigned long		t10;		// 
		size_t				n10;
		size_t				l10;
		unsigned long		t11;		// 
		size_t				n11;
		size_t				l11;
		unsigned long		t12;		// 
		size_t				n12;
		size_t				l12;
		unsigned long		t13;		// 
		size_t				n13;
		size_t				l13;
		unsigned long		t14;		// 
		size_t				n14;
		size_t				l14;

		Results()
			: t1(~0)
			, n1(~0)
			, l1(~0)
			, t2(~0)
			, n2(~0)
			, l2(~0)
			, t3(~0)
			, n3(~0)
			, l3(~0)
			, t4(~0)
			, n4(~0)
			, l4(~0)
			, t5(~0)
			, n5(~0)
			, l5(~0)
			, t6(~0)
			, n6(~0)
			, l6(~0)
			, t7(~0)
			, n7(~0)
			, l7(~0)
			, t8(~0)
			, n8(~0)
			, l8(~0)
			, t9(~0)
			, n9(~0)
			, l9(~0)
			, t10(~0)
			, n10(~0)
			, l10(~0)
			, t11(~0)
			, n11(~0)
			, l11(~0)
			, t12(~0)
			, n12(~0)
			, l12(~0)
			, t13(~0)
			, n13(~0)
			, l13(~0)
			, t14(~0)
			, n14(~0)
			, l14(~0)
		{}
	};

	typedef std::pair<size_t, size_t>	num_pair_t;

	struct invoke_length
	{
	public:
		template <typename S>
		size_t operator ()(size_t n, S const &s) const
		{
			return n + s.length();
		}
	};

} // anonymous namespace

	extern "C" void consume(char const *s, size_t len);

namespace
{
	template <typename S>
	void consume(S const &s)
	{
		::consume(s.data(), s.size());
	}

	struct consumer
	{
		template <typename S>
		void operator ()(S const &s) const
		{
			::consume(s.data(), s.size());
		}
	};

	template<	typename T
			,	typename I
			>
	num_pair_t process_sequence(I from, I to)
	{
//		std::copy(from, to, stlsoft::null_output_iterator<T>());

		std::for_each(from, to, consumer());

		size_t	n1	=	std::distance(from, to);
		size_t	n2	=	std::accumulate(from, to, 0, invoke_length());

		return num_pair_t(n1, n2);
	}

} // anonymous namespace

