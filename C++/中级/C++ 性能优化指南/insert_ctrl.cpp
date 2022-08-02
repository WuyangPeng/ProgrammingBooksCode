
# include <string>

std::string insert_ctrl(std::string& s) {
	char buf[10000];
	char* dest = buf;
	char* end = buf + sizeof(buf) - 4;
	char const* src = s.data();
	size_t count = s.length();
	while (count > 0 && dest < end) {
		if (*src < 0x20 && dest < end) {
			*dest++ = '\\';
			*dest++ = 'x';
			*dest++ = "0123456789ABCDEF"[*src >> 4];
			*dest++ = "0123456789ABCDEF"[*src & 0xf];
			++src;
		}
		else if (dest < buf + sizeof(buf)) {
			*dest++ = *src++;
		}
		else throw std::logic_error("string too long");
		--count;
	}
	return std::move(std::string(buf, dest));
}

int test_insert_ctrl(int test_no, unsigned long) {
	bool rc = true;
	switch (test_no) {
	default: return -1;
	case 0:  return 1;
	case 1: {
		rc &= (insert_ctrl(std::string("test")) == std::string("test"));
		rc &= (insert_ctrl(std::string("test\07")) == "test\\x07");
		rc &= (insert_ctrl(std::string("x\01test\07")) == "x\\x01test\\x07");
	}
			break;
	}
	return rc ? 1 : 0;
}
