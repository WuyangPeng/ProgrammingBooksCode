
// Updated: 23rd February 2006

	create_test_strings(str1, str2, str3, str4, str5);

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		size_t	n	=	0;
		size_t	l	=	0;

		// 1.
		//
		//  - short string
		//  - char delimiter
		//  - keep blanks
		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&str	=	str1;
			static const char				SEP[]	=	";";

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
//					if(p0 != p1)
					{
						consume(p0, static_cast<size_t>(p1 - p0));
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(n = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
//					if(p0 != p1)
					{
						++n;
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(l = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
//					if(p0 != p1)
					{
						l += p1 - p0;
					}
				}
			}
		}}
		counter.stop();
		if(1 == WARMUPS)
		{
			results.t1	=	static_cast<unsigned long>(counter.get_milliseconds());
			results.n1	=	n;
			results.l1	=	l;
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+pres (small):\t: %lu\t(%lu, %lu)\n", results.t1, results.n1, results.l1);
		}

	}}

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		size_t	n	=	0;
		size_t	l	=	0;

		// 2.
		//
		//  - medium string
		//  - char delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&str	=	str2;
			static const char				SEP[]	=	";";

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
					if(p0 != p1)
					{
						consume(p0, static_cast<size_t>(p1 - p0));
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(n = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
					if(p0 != p1)
					{
						++n;
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(l = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
					if(p0 != p1)
					{
						l += p1 - p0;
					}
				}
			}
		}}
		counter.stop();
		if(1 == WARMUPS)
		{
			results.t2	=	static_cast<unsigned long>(counter.get_milliseconds());
			results.n2	=	n;
			results.l2	=	l;
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+skip (medium):\t: %lu\t(%lu, %lu)\n", results.t2, results.n2, results.l2);
		}
	}}

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		size_t	n	=	0;
		size_t	l	=	0;

		// 3.
		//
		//  - medium string
		//  - char delimiter
		//  - keep blanks
		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&str	=	str2;
			static const char				SEP[]	=	";";

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
//					if(p0 != p1)
					{
						consume(p0, static_cast<size_t>(p1 - p0));
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(n = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
//					if(p0 != p1)
					{
						++n;
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(l = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
//					if(p0 != p1)
					{
						l += p1 - p0;
					}
				}
			}
		}}
		counter.stop();
		if(1 == WARMUPS)
		{
			results.t3	=	static_cast<unsigned long>(counter.get_milliseconds());
			results.n3	=	n;
			results.l3	=	l;
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+pres (medium):\t: %lu\t(%lu, %lu)\n", results.t3, results.n3, results.l3);
		}

	}}

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		size_t	n	=	0;
		size_t	l	=	0;

		// 4.
		//
		//  - medium string
		//  - char delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&str	=	str3;
			static const char				SEP[]	=	";";

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
					if(p0 != p1)
					{
						consume(p0, static_cast<size_t>(p1 - p0));
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(n = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
					if(p0 != p1)
					{
						++n;
					}
				}
			}

			{
				char const			*p0	=	str.data();
				char const			*p1	=	p0;
				char const *const	end	=	p0 + str.length();

				for(l = 0; end != stlsoft::find_next_token(p0, p1, end, ';'); )
				{
					if(p0 != p1)
					{
						l += p1 - p0;
					}
				}
			}
		}}
		counter.stop();
		if(1 == WARMUPS)
		{
			results.t4	=	static_cast<unsigned long>(counter.get_milliseconds());
			results.n4	=	n;
			results.l4	=	l;
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+skip (large):\t: %lu\t(%lu, %lu)\n", results.t4, results.n4, results.l4);
		}

		// 5.
		//
		//  - medium string
		//  - string delimiter
		//  - skip blanks
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+string+skip (medium):\n");
		}

		// 6.
		//
		//  - medium string
		//  - string delimiter
		//  - preserve blanks
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+string+pres (medium):\n");
		}

		// 7.
		//
		//  - long string
		//  - string delimiter
		//  - preserve blanks
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+string+pres (long):\n");
		}

		// 8.
		//
		//  - medium string
		//  - char delimiter
		//  - skip blanks
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  char-set delim (medium):\n");
		}

		// 9.
		//
		//  - long string
		//  - char delimiter
		//  - skip blanks
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  char-set delim (long):\n");
		}

	}}

