struct Target{

	POINT tp;
	bool shot;
	int flag;
};


struct wbData
{
	int score;
	CString str3;

public:
	wbData()
	{

	}
	wbData(int s1, CString s3)
		:score(s1), str3(s3)
	{

	}
};