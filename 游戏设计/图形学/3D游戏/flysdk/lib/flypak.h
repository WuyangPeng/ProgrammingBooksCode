#define MAXP 256

class FLY_API fly_pak
{
public:
	char *buf;
	unsigned long pos, len;

	void seek(long offset);
	bool open(char *filename);
	void close();
	int read(void *dest, int size);
	void get_profile_string(char *section, char *key, char *dest);
	void get_string(char *dest);
	int get_int();
	float get_float();
	FILE *get_fp(char *filename);
	fly_pak();
	~fly_pak();

protected:
	FILE *pakfile;
	char fldrname[MAXP];

	bool seek_file(char *);
	bool open_pak(char *);
	bool proc_section(char *);
	bool proc_key(char *);
	bool same_pak(char *);
};

struct fileinfo
{
	char filename[MAXP];
	unsigned long size;
};

class FLY_API fly_pak_util
{
public:
	bool implode(char *);
	bool explode(char *);

protected:
	char folder[MAXP];
	bool add_data();
	bool add_header();
	unsigned long currsize;
	unsigned long totalsize;
	void add_filelist(char *, unsigned long);
	unsigned int lenfilelist;
	virtual void update_status(char *, unsigned long);
	struct fileinfo *filelist;
	FILE *fpk;
	bool add(int);
	bool browse(char *);
	void create_dir(char *, char *);
	bool extract(char *, unsigned long);
};
