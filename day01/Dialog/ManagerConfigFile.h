#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<vector>
using namespace std;
class ManagerConfigFile
{
	/*ManagerConfigFile();
	~ManagerConfigFile();*/
public:
	/*bool readFile(const string& file) {};
	bool writeFile(const string& file) {};*/

	void SetFilePath(const string& filePath) {};
	string GetFilePath();
	bool GetValue(const string& section, const string& key, string& value, string& error);
	bool ModifyValue(const string& section, const string& key, const string& value, string& error);

private:
	bool OpenFile();
	bool FindSection(const string& sectionName);
	bool FindKey(const string& key);
	bool OpenFileRead();
	bool OpenFileWrite();
	bool SetValue(const string& key, const string& value);
	void WriteFile(vector<string>& vContent);

	string m_filePath, m_content, m_value, m_error;
	fstream m_fout, m_fin;
};

