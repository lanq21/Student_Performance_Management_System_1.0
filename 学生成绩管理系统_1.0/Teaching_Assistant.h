#pragma once
#include <vector>
#include "Student.h"
#include "Teacher.h"

class Class;
class Teaching_Assistant : public Student, public Teacher
{
public:

	/// <summary>
	/// ���캯��������ָ�����Student::Student_List
	/// </summary>
	/// <param name="name">����</param>
	/// <param name="id">ѧ��</param>
	/// <param name="faculty">Ժϵ</param>
	/// <param name="grade">�꼶</param>
	Teaching_Assistant(const std::string& name, const std::string& id, const std::string& faculty, const Grade_Type grade);

	static Teaching_Assistant* const _New(std::string name = "", std::string id = "0", std::string faculty = "����ϵ", Grade_Type grade = undergraduate_1);

	/// <summary>
	/// �ڿ���̨�޸�
	/// </summary>
	virtual void Edit();

	/// <summary>
	/// �ڿ���̨��ӡ
	/// </summary>
	virtual void Print() const;

	/// <returns>��������</returns>
	static const size_t _Get_Size();

	/// <summary>
	/// �ڿ���̨��ӡȫ�����̸����༶��Ϣ
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// ��ӵ������б�
	/// </summary>
	static void _Add_Teaching_Assistant(Teaching_Assistant* const teaching_assistant_ptr);

	/// <summary>
	/// ��ճɼ��б�
	/// </summary>
	virtual ~Teaching_Assistant();

	/// <summary>
	/// ȫ��������Ϣд���ļ�
	/// </summary>
	/// <param name="file">�ļ����������</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// ���ļ�����ȫ��������Ϣ
	/// </summary>
	/// <param name="file">�ļ�����������</param>
	static void _Read_File(std::ifstream& file);

private:

	/// <summary>
	/// �༭ѧ��
	/// </summary>
	/// <param name="id">ѧ��</param>
	virtual void Edit_ID(const std::string& id);

	/// <summary>
	/// �ڿ���̨�༭�����༶
	/// </summary>
	virtual void Edit_Class();

	static std::vector<Teaching_Assistant*> _List; // ȫ������ָ���б�

};
