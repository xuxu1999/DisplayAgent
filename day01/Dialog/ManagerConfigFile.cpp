#include "ManagerConfigFile.h"
ManagerConfigFile::ManagerConfigFile(){}

ManagerConfigFile::~ManagerConfigFile(){}

/// <summary>
/// ���������ļ�·��
/// </summary>
/// <param name="filePath">�ļ�·��</param>
void ManagerConfigFile::SetFilePath(const string& filePath) {
	m_filePath = filePath;
}
/// <summary>
/// ��ȡ�ļ�·��
/// </summary>
/// <returns>�ļ�·��</returns>
string ManagerConfigFile::GetFilePath() {
	return this->m_filePath;
}
/// <summary>
/// �������ļ�
/// </summary>
/// <returns>�ɹ�true ��ʧ��false</returns>
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
/// �ҽ���
/// </summary>
/// <param name="sectionName">����</param>
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
/// �Ҽ���
/// </summary>
/// <param name="key">����</param>
/// <returns>true or false</returns>
bool ManagerConfigFile::FindKey(const string& key) {
	size_t iDelePlace = m_content.find((char)'//', 0);
	size_t iFindEqual = m_content.find((char)'=', 0);
	//��ע�͵��У������ǰ���key�����Ѿ���ע�ӵ��ˣ�����
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
/// ��ȡ����Key��Ӧ��valueֵ
/// </summary>
/// <param name="section">����</param>
/// <param name="key">����</param>
/// <param name="value">ֵ</param>
/// <param name="error">������Ϣ</param>
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
				m_error = "�ڵ�" + section + "������";
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
				m_error = "����" + key + "������";
			}
		}
		memset(str, 0, 4096);
	}
	error = m_error;
	m_fin.close();
	return false;
}
/// <summary>
/// ���ķ�ʽ��
/// </summary>
/// <returns></returns>
bool ManagerConfigFile::OpenFileRead()
{
	m_fout.close();
	//�رպ�Ҫ�����һ�£������´δ򿪻����
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
/// д�ķ�ʽ��
/// </summary>
/// <returns></returns>
bool ManagerConfigFile::OpenFileWrite()
{
	m_fout.close();
	//�رպ�Ҫ�����һ�£������´δ򿪻����
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
/// ��KEY��������ֵ
/// </summary>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
bool ManagerConfigFile::SetValue(const string& key, const string& value)
{
	size_t iDelePlace = m_content.find((char)'//');
	size_t iFindEqual = m_content.find((char)'=');
	//��ע�͵��У������ǰ���key�����Ѿ���ע�ӵ��ˣ�����
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
/// �޸�key��value
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
				m_error = "�ڵ�" + section + "������";
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
					m_error = "����" + key + "������";
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
/// д�ļ�
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