# include <fstream>     //  for ifstream
# include <ostream>
# include <string>      //  std::string functions, not <strstream>
# include <sstream>
# include <iostream>    //  for cout
# include <memory>
# include "stopwatch03.h"
# include "test_driver.h"

// returns -1 on fail
std::streamoff stream_size(std::istream& f) {
	std::istream::pos_type current_pos = f.tellg();
	if (-1 == current_pos)
		return -1;
	f.seekg(0,std::istream::end);
	std::istream::pos_type end_pos = f.tellg();
    f.seekg(current_pos);
	return end_pos - current_pos;
}

void stream_read_streambuf(std::istream& f, std::string& result) {
    std::stringstream s;
	s << f.rdbuf();
    std::swap(result, s.str());
}

std::string stream_read_streambuf_stringstream_noarg(std::istream& f) {
    std::stringstream s;
    std::copy(std::istreambuf_iterator<char>(f.rdbuf()), 
              std::istreambuf_iterator<char>(), 
              std::ostreambuf_iterator<char>(s) );
    return s.str();
}

void stream_read_streambuf_stringstream(std::istream& f, std::string& result) {
    std::stringstream s;
    std::copy(std::istreambuf_iterator<char>(f.rdbuf()), 
              std::istreambuf_iterator<char>(), 
              std::ostreambuf_iterator<char>(s) );
    std::swap(result, s.str());
}

void stream_read_streambuf_string(std::istream& f, std::string& result) {
    result.assign(std::istreambuf_iterator<char>(f.rdbuf()), 
                  std::istreambuf_iterator<char>());
}

void stream_read_streambuf_string_reserve(std::istream& f, std::string& result) {

	f.seekg(0,std::istream::end);
    std::streamoff len = f.tellg();
    f.seekg(0);

	if (len > 0)
		result.reserve(static_cast<std::string::size_type>(len));

    result.assign(std::istreambuf_iterator<char>(f.rdbuf()), 
                  std::istreambuf_iterator<char>());
}

void stream_read_streambuf_string_2(std::istream& f, std::string& result, std::streamoff len = 0) {
	if (len > 0)
		result.reserve(static_cast<std::string::size_type>(len));

    result.assign(std::istreambuf_iterator<char>(f.rdbuf()), 
                  std::istreambuf_iterator<char>());
}

void stream_read_getline(std::istream& f, std::string& result) {
    std::string line;
	result.clear();

	while (getline(f, line))
		(result += line) += "\n";
}

void stream_read_getline_2(std::ifstream& f, std::string& result, std::streamoff len = 0) {
    std::string line;

	result.clear();

    if (len > 0)
	    result.reserve(static_cast<std::string::size_type>(len));

	while (getline(f, line))
		(result += line) += "\n";
}

bool stream_read_sgetn(std::istream& f, std::string& result) {
	
	std::streamoff len = stream_size(f);
	if (len == -1)
		return false;

    result.resize (static_cast<std::string::size_type>(len));

    f.rdbuf()->sgetn(&result[0], len);
	return true;
}

bool stream_read_array(std::istream& f, std::string& result) {
	std::streamoff len = stream_size(f);
	if (len == -1)
		return false;

    std::unique_ptr<char> data(new char[static_cast<size_t>(len)]);

    f.read(data.get(), static_cast<std::streamsize>(len));
    result.assign(data.get(), static_cast<std::string::size_type>(len));
	return true;
}

bool stream_read_string(std::istream& f, std::string& result) {
	std::streamoff len = stream_size(f);
	if (len == -1)
		return false;

    result.resize (static_cast<std::string::size_type>(len));

    f.read(&result[0], result.length());
	return true;
}

// from: http://stackoverflow.com/questions/8736862
// This was a dreadful failure; very slow
class custombuf : public std::streambuf
{
public:
    custombuf(std::string& target): target_(target) {
        this->setp(this->buffer_, this->buffer_ + bufsize - 1);
    }

private:
    std::string& target_;
    enum { bufsize = 8192 };
    char buffer_[bufsize];
    int overflow(int c) {
        if (!traits_type::eq_int_type(c, traits_type::eof()))
        {
            *this->pptr() = traits_type::to_char_type(c);
            this->pbump(1);
        }
        this->target_.append(this->pbase(), this->pptr() - this->pbase());
        this->setp(this->buffer_, this->buffer_ + bufsize - 1);
        return traits_type::not_eof(c);
    }
    int sync() { this->overflow(traits_type::eof()); return 0; }
};

std::string stream_read_custombuf(std::istream& f) {
	std::string data;
	custombuf sbuf(data);
	std::ostream(&sbuf) << f.rdbuf() << std::flush;
	return data;
}

void file_writer(std::ostream& f, int nlines) {
//  construct a file with 10,000 100 character lines (plus line endings)
    std::string line;
    for (int i = 0; i < 20; ++i)
        line += "blah ";    //  make 100 character lines
	line += "\n";
    for (int i = 0; i < nlines; ++i)
        f << line;
	f.flush();
}

void stream_write_line(std::ostream& f, std::string const& line) {
	f << line << std::endl;
}

void stream_write_line_noflush(std::ostream& f, std::string const& line) {
	f << line << "\n";
}

int test_read_stream(int testno, unsigned long multiplier) {
    bool rc = true;
    char const filename[] = "file_optimization_tester.txt";
    const unsigned long iterations = multiplier;
	std::string s;

    std::ofstream out(filename);
    if (!out) {
        std::cout << "Can't open " << filename 
                  << " for writing" << std::endl;
        return 0;
    }

    unsigned nlines = (testno > 1) ? 10000 : 10;
	size_t   flen   = 101*nlines;

    file_writer(out, nlines);
	out.close();

	std::ifstream in;
	in.open(filename);
	if (!in) {
		std::cout << "Can't open " << filename 
					<< " for reading" << std::endl;
		return 0;
	}
	std::ifstream in8k;
	in8k.open(filename);
	if (!in8k) {
		std::cout << "Can't open " << filename 
				  << " buffered stream for reading" << std::endl;
		return 0;
	}
	char buf[8192];	// set fat static buffer
	in8k.rdbuf()->pubsetbuf(buf, sizeof(buf));

    switch (testno) {
    case 1: {
            s = stream_read_streambuf_stringstream_noarg(in);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

            stream_read_streambuf_stringstream(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

            stream_read_streambuf_string(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

            stream_read_streambuf_string_reserve(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

            stream_read_streambuf_string_2(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

			stream_read_streambuf(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

			stream_read_streambuf(in8k, s);
			in8k.clear(); in8k.seekg(0); 
            rc &= (s.length() == flen);
			
			stream_read_streambuf(in8k, s);

            stream_read_getline(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

            stream_read_getline_2(in, s, 100);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);

            stream_read_sgetn(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen+nlines);

            stream_read_array(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen+nlines);

            stream_read_string(in, s);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen+nlines);

            s = stream_read_custombuf(in);
			in.clear();	in.seekg(0); 
            rc &= (s.length() == flen);
        }
		{//	verify behavior of stream_size()
			std::ifstream f;
			std::streamsize len1 = stream_size(f);
			rc &= (len1 == -1);
			f.open(filename);
			std::streamsize len2 = stream_size(f);
			rc &= (len2 > 100);
			std::getline(f, s);
			std::streamsize len3 = stream_size(f);
			rc &= (len2 > len3);
			std::stringstream ins;
			ins.str(s);
			std::streamsize len4 = stream_size(ins);
			rc &= (len4 == s.length());
		}
        break;

    case 2: 
		{
    		Stopwatch sw("stream_read_streambuf_stringstream_noarg()");
			for (unsigned long i = 0; i < iterations; ++i) {
				s = stream_read_streambuf_stringstream_noarg(in);
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
    		Stopwatch sw("stream_read_streambuf_stringstream()");
			for (unsigned long i = 0; i < iterations; ++i) {
				stream_read_streambuf_stringstream(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
    		Stopwatch sw("stream_read_streambuf_string()");
			for (unsigned long i = 0; i < iterations; ++i) {
				stream_read_streambuf_string(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
    		Stopwatch sw("stream_read_streambuf_string_reserve()");
			for (unsigned long i = 0; i < iterations; ++i) {
				stream_read_streambuf_string_reserve(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
    		Stopwatch sw("stream_read_streambuf_string_2()");
			for (unsigned long i = 0; i < iterations; ++i) {
				stream_read_streambuf_string_2(in, s, stream_size(in));
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
    		Stopwatch sw("stream_read_streambuf_string_2(in8k)");
			for (unsigned long i = 0; i < iterations; ++i) {
				stream_read_streambuf_string_2(in8k, s, stream_size(in8k));
				in8k.clear(); in8k.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
            Stopwatch sw("stream_read_streambuf()");
            for (unsigned long i = 0; i < iterations; ++i) {
                stream_read_streambuf(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
            Stopwatch sw("stream_read_streambuf(8k buffer)");
            for (unsigned long i = 0; i < iterations; ++i) {
                stream_read_streambuf(in8k, s);
				in8k.clear(); in8k.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
        break;

    case 3: 
		{
            Stopwatch sw("stream_read_getline()");
            for (unsigned long i = 0; i < iterations; ++i) {
                stream_read_getline(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
            Stopwatch sw("stream_read_getline_2()");
            for (unsigned long i = 0; i < iterations; ++i) {
                stream_read_getline_2(in, s, stream_size(in));
				in.clear();	in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
		{
            Stopwatch sw("stream_read_getline_2(in8k)");
            for (unsigned long i = 0; i < iterations; ++i) {
                stream_read_getline_2(in8k, s, stream_size(in8k));
				in8k.clear(); in8k.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
        break;

    case 4: 
		{
            Stopwatch sw("stream_read_sgetn()");
			bool err = true;
            for (unsigned long i = 0; i < iterations; ++i) {
                err &= stream_read_sgetn(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (err == true && s.length() == flen+nlines);
        }
		{
            Stopwatch sw("stream_read_sgetn(in8k)");
			bool err = true;
            for (unsigned long i = 0; i < iterations; ++i) {
                err &= stream_read_sgetn(in8k, s);
				in8k.clear(); in8k.seekg(0); 
			}
            rc &= (err == true && s.length() == flen+nlines);
        }
        break;

    case 5: 
		{
            Stopwatch sw("stream_read_array()");
			bool err = true;
            for (unsigned long i = 0; i < iterations; ++i) {
                err &= stream_read_array(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (err == true && s.length() == flen+nlines);
        }
		{
            Stopwatch sw("stream_read_string()");
			bool err = true;
            for (unsigned long i = 0; i < iterations; ++i) {
                err &= stream_read_string(in, s);
				in.clear();	in.seekg(0); 
			}
            rc &= (err == true && s.length() == flen+nlines);
        }
		{
            Stopwatch sw("stream_read_string(in8k)");
			bool err = true;
            for (unsigned long i = 0; i < iterations; ++i) {
                err &= stream_read_string(in8k, s);
				in8k.clear(); in8k.seekg(0); 
			}
            rc &= (err == true && s.length() == flen+nlines);
        }
        break;

	case 6:
		{
            Stopwatch sw("stream_read_custombuf()");
            for (unsigned long i = 0; i < iterations; ++i) {
                s = stream_read_custombuf(in);
				in.clear(); in.seekg(0); 
			}
            rc &= (s.length() == flen);
        }
        break;

	case 7: 
		std::remove(filename);
		out.open(filename);
		{
			std::string line;
			for (unsigned i = 0; i < 20; ++i)
				line += "blah ";
            Stopwatch sw("stream_write_line()");
            for (unsigned long i = 0; i < iterations; ++i) {
				out.seekp(0);
				for (unsigned j = 0; j < nlines; ++j) {
					stream_write_line(out, line);
				}
			}
		}
		out.close();
		std::remove(filename);
		out.open(filename);
		{
			std::string line;
			for (unsigned i = 0; i < 20; ++i)
				line += "blah ";
            Stopwatch sw("stream_write_line_noflush()");
            for (unsigned long i = 0; i < iterations; ++i) {
				out.seekp(0);
				for (unsigned j = 0; j < nlines; ++j) {
					stream_write_line_noflush(out, line);
				}
				out.flush();
			}
		}
		out.close();
		std::remove(filename);
		out.open(filename);
		{
			std::string line;
			for (unsigned i = 0; i < 20; ++i)
				line += "blah ";
			std::string file;
			for (unsigned j = 0; j < nlines; ++j) 
				file += line;

            Stopwatch sw("stream_write_line_noflush(file)");
            for (unsigned long i = 0; i < iterations; ++i) {
				out.seekp(0);
				stream_write_line_noflush(out, file);
				out.flush();
			}
		}
		out.close();
		break;

    case 0: return 7;
    default:return -1;
    }
    std::remove(filename);
    return rc ? 1 : 0;
}

int main(int argc, char** argv) {
	test_driver(test_read_stream, argc, argv);
	return 0;
}    