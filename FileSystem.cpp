#include "FileSystem.h"


vector<string> FileSystem(string path, string extension) {
	boost::filesystem::path dir(path);
	boost::filesystem::directory_iterator itr(dir);
	vector<string> str;
	string s;
	bool b = 0;
	string test = extension;
	for (itr; itr != boost::filesystem::directory_iterator(); itr++)
	{
		s = itr->path().filename().string();
		for (int i = 0;i < extension.size(); i++)
		{
			if (s[s.size() - extension.size() + i] != test[i])
			{
				b = 1;
			}
		}
		if (b == 0)
		{
			str.push_back(s);
		}
		b = 0;
	}
	return str;
}

ofstream createfile(string pos, string name) {
	boost::filesystem::path dir(pos);
	boost::filesystem::create_directory(dir);
	/*string pos1 = pos;
	string name1 = name;*/
	ofstream dest(pos + "\\" + name);
	return dest;
}

ostream& operator<<(ostream& o, vector<char> c) {
	for (int i = 0; i < c.size(); i++) {
		o << c[i] << endl;
	}
	return o;
}

char* Convert2CharPointer(string s) {
	char* pointer = new char[s.size()+1];
	for (int i = 0; i < s.size(); i++)
		pointer[i] = s[i];
	pointer[s.size()] = '\0';
	return pointer;
}