#pragma once
#include "Person.h"
#include <vector>

class Class;
class Course;

class Teacher : virtual public Person
{
public:

	/// <summary>
	/// �ӿ���̨����
	/// </summary>
	static Teacher* const _New(std::string name="", std::string id="0", std::string faculty="����ϵ");

	/// <returns>��ʦ���</returns>
	const size_t Get_Serial_Number() const;

	/// <summary>
	/// �ڿ���̨�༭ȫ����ʦ
	/// </summary>
	static void Edit_All();

	/// <summary>
	/// �ڿ���̨�༭
	/// </summary>
	virtual void Edit();

	/// <summary>
	/// �ڿ���̨��ӡ
	/// </summary>
	virtual void Print() const;

	/// <summary>
	/// ��������� << �����ڿ���̨��ӡ
	/// </summary>
	friend std::ostream& operator<<(std::ostream& output, const Teacher& teacher_obj);

	/// <summary>
	/// �Ӱ༶�б�ɾ���༶
	/// </summary>
	/// <param name="class_ptr"></param>
	void Delete_Class(Class* class_ptr);

	/// <returns>�༶��</returns>
	size_t Get_Class_Size() const;

	/// <returns>��n���༶ָ��</returns>
	Class* const Get_Class_ptr(const int& n);

	/// <returns>ȫ����ʦ��</returns>
	static const size_t _Get_Size();

	/// <returns>��n����ʦָ��</returns>
	static Teacher* const _Get_ptr(const size_t& n);

	/// <summary>
	/// �ڿ���̨��ӡȫ����ʦ���ơ���š�Ժϵ
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// ȫ����ʦ��Ϣд���ļ�
	/// </summary>
	/// <param name="file">�ļ����������</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// ���ļ�����ȫ����ʦ��Ϣ
	/// </summary>
	/// <param name="file">�ļ�����������</param>
	static void _Read_File(std::ifstream& file);

	/// <summary>
	/// ��Ӱ༶���б�
	/// </summary>
	/// <param name="class_ptr">�༶ָ��</param>
	void Add_Class(Class* const class_ptr);

	virtual ~Teacher();

protected:

	/// <summary>
	/// �ڿ���̨��ӡ�ڿΰ༶
	/// </summary>
	void Print_Class() const;

	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="name">����</param>
	/// <param name="id">���</param>
	/// <param name="faculty">Ժϵ</param>
	Teacher(const std::string& name, const std::string& id, const std::string faculty,const bool& is_ta);

	std::vector<Class*> Class_List; // �༶ָ���б�

private:

	/// <summary>
	/// �޸Ľ�ʦ���
	/// </summary>
	/// <param name="id">��ʦ���</param>
	virtual void Edit_ID(const std::string& id);

	/// <summary>
	/// �ڿ���̨�޸İ༶
	/// </summary>
	virtual void Edit_Class();

	bool is_TA; // �Ƿ�Ϊ����
	static std::vector<Teacher*> _List; // ȫ����ʦָ���б�
};