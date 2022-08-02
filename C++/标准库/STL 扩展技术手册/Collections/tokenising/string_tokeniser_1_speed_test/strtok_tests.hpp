
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
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+pres (small):\n");
		}

		// 2.
		//
		//  - medium string
		//  - char delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&srcStr	=	str2;
			static const char				SEP[]	=	";";

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					consume(token, ::strlen(token));
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(n = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					++n;
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(l = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					l += ::strlen(token);
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

		// 3.
		//
		//  - medium string
		//  - char delimiter
		//  - keep blanks
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+pres (medium):\n");
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
			stlsoft::simple_string const	&srcStr	=	str3;
			static const char				SEP[]	=	";";

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					consume(token, ::strlen(token));
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(n = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					++n;
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(l = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					l += ::strlen(token);
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

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&srcStr	=	str4;
			static const char				SEP[]	=	"\r\n \b\v\t";

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					consume(token, ::strlen(token));
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(n = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					++n;
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(l = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					l += ::strlen(token);
				}
			}
		}}
		counter.stop();
		if(1 == WARMUPS)
		{
			results.t8	=	static_cast<unsigned long>(counter.get_milliseconds());
			results.n8	=	n;
			results.l8	=	l;
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  char-set delim (medium):\t: %lu\t(%lu, %lu)\n", results.t8, results.n8, results.l8);
		}

	}}

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		size_t	n	=	0;
		size_t	l	=	0;

		// 9.
		//
		//  - long string
		//  - char delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			stlsoft::simple_string const	&srcStr	=	str5;
			static const char				SEP[]	=	"\r\n \b\v\t";

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					consume(token, ::strlen(token));
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(n = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					++n;
				}
			}

			{
				stlsoft::simple_string									str(srcStr);
				char *const												s      =   &str[0];
				char													*token;

				for(l = 0, token = ::strtok(s, SEP); NULL != token; token = ::strtok(NULL, SEP))
				{
					l += ::strlen(token);
				}
			}
		}}
		counter.stop();
		if(1 == WARMUPS)
		{
			results.t9	=	static_cast<unsigned long>(counter.get_milliseconds());
			results.n9	=	n;
			results.l9	=	l;
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  char-set delim (long):\t: %lu\t(%lu, %lu)\n", results.t9, results.n9, results.l9);
		}

	}}

