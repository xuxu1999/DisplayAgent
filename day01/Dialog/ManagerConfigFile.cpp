#include "ManagerConfigFile.h"
ManagerConfigFile::ManagerConfigFile(){}

ManagerConfigFile::~ManagerConfigFile(){}

/// <summary>
/// 设置配置文件路径
/// </summary>
/// <param name="filePath">文件路径</param>
void ManagerConfigFile::SetFilePath(const string& filePath) {
	m_filePath = filePath;
}
/// <summary>
/// 获取文件路径
/// </summary>
/// <returns>文件路径</returns>
string ManagerConfigFile::GetFilePath() {
	return this->m_filePath;
}
/// <summary>
/// 打开配置文件
/// </summary>
/// <returns>成功true ，失败false</returns>
bool ManagerConfigFile::OpenFile() {
	if (m_fin.is_open() == true) {
		m_fin.close();
	}

	m_fin.open(m_filePath.c_str());
	if (!m_fin.is_open()) {
		m_error = "open file fail:" + m_filePath;
		return false;
	}
	return true;
}

/// <summary>
/// 找节名
/// </summary>
/// <param name="sectionName">节名</param>
/// <returns>ture or false</returns>
bool ManagerConfigFile::FindSection(const string& sectionName)
{
	if (-1 != m_content.find('['))
	{
		string sTemp = m_content.substr(m_content.find('[') + 1, m_content.find(']') - m_content.find('[') - 1);
		if (0 == strcmp(sTemp.c_str(), sectionName.c_str()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
/// <summary>
/// 找键名
/// </summary>
/// <param name="key">键名</param>
/// <returns>true or false</returns>
bool ManagerConfigFile::FindKey(const string& key) {
	size_t iDelePlace = m_content.find((char)'//', 0);
	size_t iFindEqual = m_content.find((char)'=', 0);
	//被注释的行，或者是包含key但是已经被注视掉了，过滤
	if ((-1 != iDelePlace && iDelePlace < iFindEqual) || (-1 != iDelePlace && -1 == iFindEqual) || -1 == iFindEqual)
	{
		return false;
	}
	string sKey = m_content.substr(0, m_content.find('='));

	if (0 == strcmp(sKey.c_str(), key.c_str()))
	{
		m_value = m_content.substr(m_content.find('=') + 1, m_content.length() - m_content.find('=') - 1);
		return true;
	}
	return false;
}
/// <summary>
/// 读取节下Key对应的value值
/// </summary>
/// <param name="section">节名</param>
/// <param name="key">键名</param>
/// <param name="value">值</param>
/// <param name="error">错误信息</param>
/// <returns>true or false</returns>
bool ManagerConfigFile::GetValue(const string& section, const string& key, string& value, string& error)
{
	m_error = "";
	if (false == OpenFile())
	{
		error = m_error;
		return false;
	}
	char str[4096] = { 0 };
	bool bFindSection = false;
	while (m_fin.getline(str, sizeof(str)))
	{
		m_content = str;
		if (!bFindSection)
		{
			if (FindSection(section))
			{
				bFindSection = true;
			}
			else
			{
				m_error = "";
				m_error = "节点" + section + "不存在";
			}
		}
		else
		{
			if (FindKey(key))
			{
				m_fin.close();
				m_error = "";
				value = m_value;
				return true;
			}
			else
			{
				m_error = "";
				m_error = "键名" + key + "不存在";
			}
		}
		memset(str, 0, 4096);
	}
	error = m_error;
	m_fin.close();
	return false;
}
/// <summary>
/// 读的方式打开
/// </summary>
/// <returns></returns>
bool ManagerConfigFile::OpenFileRead()
{
	m_fout.close();
	//关闭后要在清空一下，否则下次打开会出错
	m_fout.clear();
	m_fout.open(m_filePath.c_str(), ios::in);
	if (!m_fout.is_open())
	{
		m_error = "open file fail:" + m_filePath;
		return false;
	}
	return true;
}
/// <summary>
/// 写的方式打开
/// </summary>
/// <returns></returns>
bool ManagerConfigFile::OpenFileWrite()
{
	m_fout.close();
	//关闭后要在清空一下，否则下次打开会出错
	m_fout.clear();
	m_fout.open(m_filePath.c_str(), ios::out | ios::trunc);
	if (!m_fout.is_open())
	{
		m_error = "can not open file " + m_filePath;
		return false;
	}
	return true;
}
/// <summary>
/// 找KEY，设置新值
/// </summary>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
bool ManagerConfigFile::SetValue(const string& key, const string& value)
{
	size_t iDelePlace = m_content.find((char)'//');
	size_t iFindEqual = m_content.find((char)'=');
	//被注释的行，或者是包含key但是已经被注视掉了，过滤
	if ((-1 != iDelePlace && iDelePlace < iFindEqual) || (-1 != iDelePlace && -1 == iFindEqual) || -1 == iFindEqual)
	{
		return false;
	}
	string sKey = m_content.substr(0, m_content.find('='));

	if (0 == strcmp(sKey.c_str(), key.c_str()))
	{
		m_content = m_content.substr(0, m_content.find('=') + 1) + value;
		return true;
	}

	return false;
}

/// <summary>
/// 修改key下value
/// </summary>
/// <param name="section"></param>
/// <param name="key"></param>
/// <param name="value"></param>
/// <param name="error"></param>
/// <returns></returns>
bool ManagerConfigFile::ModifyValue(const string& section, const string& key, const string& value, string& error)
{
	m_error = "";
	if (false == OpenFileRead())
	{
		error = m_error;
		return false;
	}

	char str[4096] = { 0 };
	vector<string> vContent;
	bool isModify = false;
	bool isFindSection = false;
	while ((m_fout.getline(str, sizeof(str))))
	{
		m_content = str;
		if (!isFindSection)
		{
			if (FindSection(section))
			{
				isFindSection = true;
			}
			else
			{
				m_error = "";
				m_error = "节点" + section + "不存在";
			}
		}
		else
		{
			if (!isModify)
			{
				if (SetValue(key, value))
				{
					isModify = true;
				}
				else
				{
					m_error = "";
					m_error = "键名" + key + "不存在";
				}
			}
		}
		vContent.push_back(m_content);
		m_content = "";
		memset(str, 0, 4096);
	}
	error = m_error;
	WriteFile(vContent);
	m_fout.flush();
	m_fout.close();
	return isModify;
}
/// <summary>
/// 写文件
/// </summary>
/// <param name="vContent"></param>
void ManagerConfigFile::WriteFile(vector<string>& vContent) {
	if (OpenFileWrite() == false) {
		m_fout.close();
		return;
	}

	for (size_t iIndex = 0; iIndex < vContent.size(); iIndex++)
	{
		m_fout << vContent[iIndex] << endl;
	}
	m_fout.close();
	vector<string>().swap(vContent);
}