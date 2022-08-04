#pragma once
#include "Person.h"
#include <vector>
#include <fstream>

class Class;
class Teacher;

class Course
{
public:

	/// <summary>
	/// �ӿ���̨����
	/// </summary>
	static Course* const _New(std::string name = "", double full_score = 100);

	/// <returns>�γ����</returns>
	const size_t Get_Serial_Number() const;

	/// <returns>�γ���</returns>
	const std::string& Get_Name() const;

	/// <returns>�γ�����</returns>
	const double Get_Full_Score() const;

	/// <returns>���ΰ༶��</returns>
	const size_t Get_Class_Size() const;

	/// <returns>��n���༶ָ��</returns>
	Class* const Get_Class_ptr(const unsigned long long& n) const;

	/// <returns>�γ�ƽ����</returns>
	const double Get_Average_Score() const;

	/// <summary>
	/// ��ӵ��༶�б�
	/// </summary>
	/// <param name="class_ptr">�༶ָ��</param>
	void Add_Class(Class* const class_ptr);

	/// <summary>
	/// �ڿ���̨����ɼ�
	/// </summary>
	static void _Score_Manage();

	/// <summary>
	/// �ڿ���̨�༭ȫ���γ�
	/// </summary>
	static void _Edit_All();

	/// <summary>
	/// �ڿ���̨�༭
	/// </summary>
	void Edit();

	/// <summary>
	/// �ڿ���̨��ӡ���ΰ༶�γ̡���ʦ����ѧ������
	/// </summary>
	void Print_Class() const;

	/// <summary>
	/// �ڿ���̨��ӡ�γ��������ΰ༶
	/// </summary>
	void Print() const;

	/// <summary>
	/// �Ӱ༶�б�ɾ���༶
	/// </summary>
	/// <param name="class_ptr">�༶ָ��</param>
	void Delete_Class(Class* class_ptr);

	/// <returns>ȫ���γ���</returns>
	static const size_t _Get_Size();

	/// <returns>��n���γ�ָ��</returns>
	static Course* const _Get_ptr(const size_t& n);

	/// <summary>
	/// �ڿ���̨��ӡȫ���γ����ơ�����
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// ȫ���γ���Ϣд���ļ�
	/// </summary>
	/// <param name="file">�ļ����������</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// ���ļ�����ȫ���γ���Ϣ
	/// </summary>
	/// <param name="file">�ļ�����������</param>
	static void _Read_File(std::ifstream& file);

	~Course();

private:

	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="name">����</param>
	Course(const std::string& name, const double& full_score);

	/// <summary>
	/// �޸Ŀγ���
	/// </summary>
	/// <param name="name">�γ���</param>
	void Edit_Name(const std::string& name);

	/// <summary>
	/// �޸Ŀγ�����
	/// </summary>
	/// <param name="full_score">�γ�����</param>
	void Edit_Full_Score(const int& full_score);

	/// <summary>
	/// �ڿ���̨�޸İ༶
	/// </summary>
	void Edit_Class();

	std::string Name; // �γ���
	double Full_Score; // �γ�����
	std::vector<Class*> Class_List; // �༶ָ���б�
	static std::vector<Course*> _List; // ȫ���γ�ָ���б�

};