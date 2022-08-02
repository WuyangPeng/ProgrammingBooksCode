class enum_scene : public scene_max, public ITreeEnumProc
{
public:
	TimeValue time;

	void AddLight(GenLight *, Matrix3);
	int FindMtl(char *);
	void Save3DS(Mesh *, char *, int, Matrix3, Point3, Matrix3);
	void SaveFAO(Mesh *, char *, int, Matrix3, Point3, Matrix3);
	void AddMesh(Mesh *, char *, int, Matrix3);
	int AddMtl(Mtl *);
	int callback(INode *);
};

class enum_scene_count : public ITreeEnumProc
{
public:
	TimeValue time;
	
	int callback(INode *);
};
