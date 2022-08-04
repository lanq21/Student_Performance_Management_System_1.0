#pragma once
#include <string>

class Person
{
public:

	/// <returns>����</returns>
	const std::string& Get_Name() const;

	/// <returns>���</returns>
	const std::string& Get_ID() const;

	/// <returns>Ժϵ</returns>
	const std::string& Get_Faculty() const;

	/// <returns>��Ա�����ͬ</returns>
	const bool operator==(const Person& person);

	/// <summary>
	/// ���麯�����ڿ���̨�༭
	/// </summary>
	virtual void Edit() = 0;

	/// <summary>
	/// �麯�����ڿ���̨��ӡ
	/// </summary>
	virtual void Print() const;

	virtual ~Person();

protected:

	std::string ID; // ���

	/// <summary>
	/// ��ȱʡ�����Ĺ��캯��
	/// nameĬ�ϳ�ʼ��Ϊ" "
	/// idĬ�ϳ�ʼ��Ϊ"0"
	/// facultyĬ�ϳ�ʼ��Ϊ"����ϵ"
	/// </summary>
	/// <param name="name">����</param>
	/// <param name="id">���</param>
	/// <param name="faculty">Ժϵ</param>
	Person(const std::string& name = " ", const std::string& id = "0", const std::string& faculty = "����ϵ");

	/// <summary>
	/// �༭��������
	/// </summary>
	/// <param name="name">����</param>
	void Edit_Name(const std::string& name);

	/// <summary>
	/// ���麯�����༭������
	/// </summary>
	/// <param name="id">���</param>
	virtual void Edit_ID(const std::string& id) = 0;

	/// <summary>
	/// �༭����Ժϵ
	/// </summary>
	/// <param name="faculty">Ժϵ</param>
	void Edit_Faculty(const std::string& faculty);

private:

	std::string Name; // ����
	std::string Faculty; // Ժϵ

};