
// Updated: 23rd February 2006

	create_test_strings(str1, str2, str3, str4, str5);

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		num_pair_t		res;

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
			typedef boost::tokenizer<	boost::char_separator<char>
									,	stlsoft::simple_string::const_iterator
									,	stlsoft::simple_string
									>			tokeniser_t;

			tokeniser_t		tokens(str2, boost::char_separator<char>(";"));

			res	=	process_sequence<stlsoft::simple_string>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t2	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n2	=	res.first;
		results.l2	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+skip (medium):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
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

		// 4.
		//
		//  - long string
		//  - char delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef boost::tokenizer<	boost::char_separator<char>
									,	stlsoft::simple_string::const_iterator
									,	stlsoft::simple_string
									>			tokeniser_t;

			tokeniser_t		tokens(str3, boost::char_separator<char>(";"));

			res	=	process_sequence<stlsoft::simple_string>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t4	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n4	=	res.first;
		results.l4	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+skip (large):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
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
	}}


	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		num_pair_t		res;

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef boost::tokenizer<	boost::char_separator<char>
									,	stlsoft::simple_string::const_iterator
									,	stlsoft::simple_string
									>			tokeniser_t;

			tokeniser_t		tokens(str4, boost::char_separator<char>("\r\n \b\v\t"));

			res	=	process_sequence<stlsoft::simple_string>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t8	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n8	=	res.first;
		results.l8	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  char-set delim (medium):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
		}
	}}

	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		num_pair_t		res;

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef boost::tokenizer<	boost::char_separator<char>
									,	stlsoft::simple_string::const_iterator
									,	stlsoft::simple_string
									>			tokeniser_t;

			tokeniser_t		tokens(str5, boost::char_separator<char>("\r\n \b\v\t"));

			res	=	process_sequence<stlsoft::simple_string>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t9	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n9	=	res.first;
		results.l9	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  char-set delim (large):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
		}
	}}

