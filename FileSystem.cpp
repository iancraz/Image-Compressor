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

void createfile(string path, string name) {
	boost::filesystem::path dir(path + "\\"+ name);
	boost::filesystem::create_directory(dir);
}

ofstream ocreatefile(string path, string name) {
	boost::filesystem::path dir(path + "\\" + name);
	boost::filesystem::create_directory(dir);
	ofstream dest(path + "\\" + name);
	return dest;
}

ostream& operator<<(ostream& o, vector<string> c) {
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