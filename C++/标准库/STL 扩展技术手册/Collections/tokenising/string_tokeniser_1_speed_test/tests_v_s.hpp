
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

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	char
											,	stlsoft::skip_blank_tokens<false>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str1, ';');

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t1	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n1	=	res.first;
		results.l1	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+pres (small):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
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
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	char
											,	stlsoft::skip_blank_tokens<true>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str2, ';');

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
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

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	char
											,	stlsoft::skip_blank_tokens<false>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str2, ';');

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t3	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n3	=	res.first;
		results.l3	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+char+pres (medium):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
		}

		// 3.
		//
		//  - long string
		//  - char delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	char
											,	stlsoft::skip_blank_tokens<true>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str3, ';');

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
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

	}}


	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		num_pair_t		res;

		// 2.
		//
		//  - medium string
		//  - string delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	stlsoft::simple_string
											,	stlsoft::skip_blank_tokens<true>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str4, "\r\n");

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t5	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n5	=	res.first;
		results.l5	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+string+skip (medium):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
		}

		// 3.
		//
		//  - medium string
		//  - string delimiter
		//  - keep blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	stlsoft::simple_string
											,	stlsoft::skip_blank_tokens<false>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str4, "\r\n");

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t6	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n6	=	res.first;
		results.l6	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+string+pres (medium):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
		}

		// 3.
		//
		//  - long string
		//  - string delimiter
		//  - skip blanks

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::string_tokeniser<	stlsoft::string_view
											,	stlsoft::simple_string
											,	stlsoft::skip_blank_tokens<true>
											,	stlsoft::simple_string
											>		tokeniser_t;

			tokeniser_t		tokens(str5, "\r\n");

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
		}}
		counter.stop();
		results.t7	=	static_cast<unsigned long>(counter.get_milliseconds());
		results.n7	=	res.first;
		results.l7	=	res.second;
		if(1 == WARMUPS)
		{
			printf("%s", stlsoft::simple_string(81, '\b').c_str());
			printf("  string+string+skip (long):\t: %lu\t(%2lu, %lu)\n", static_cast<unsigned long>(counter.get_milliseconds()), res.first, res.second);
		}


	}}


	{ for(size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
	{
		num_pair_t		res;

		printf("."); fflush(stdout);
		counter.start();
		{ for(size_t r = 0; r < nRepeats; ++r)
		{
			typedef stlsoft::charset_tokeniser<	stlsoft::string_view
											,	stlsoft::string_tokeniser_ignore_blanks<true>
											,	stlsoft::simple_string
											>           tokeniser_t;

			tokeniser_t		tokens(str4, "\r\n \b\v\t");

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
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
			typedef stlsoft::charset_tokeniser<	stlsoft::string_view
											,	stlsoft::string_tokeniser_ignore_blanks<true>
											,	stlsoft::simple_string
											>           tokeniser_t;

			tokeniser_t		tokens(str5, "\r\n \b\v\t");

			res	=	process_sequence<tokeniser_t::value_type>(tokens.begin(), tokens.end());
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

