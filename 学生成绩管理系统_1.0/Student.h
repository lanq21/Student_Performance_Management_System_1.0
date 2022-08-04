#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

enum Grade_Type // �꼶����
{
	undergraduate_1 = 11, undergraduate_2, undergraduate_3, undergraduate_4,
	master_1 = 21, master_2, master_3,
	PhD_1 = 31, PhD_2, PhD_3
};
class Class;
class Course;

class Student : virtual public Person
{
public:

	/// <summary>
	/// �ӿ���̨����
	/// </summary>
	/// <param name="is_ta">�Ƿ�Ϊ���� -> 0�������� 1������ 2���ڿ���̨ȷ��</param>
	static Student* const _New(std::string name = "", std::string id = "0", std::string faculty = "����ϵ", Grade_Type grade = undergraduate_1, bool is_ta = false);

	/// <returns>�꼶</returns>
	const Grade_Type Get_Grade() const;

	/// <returns>�Ƿ�Ϊ����</returns>
	const bool Get_is_TA() const;

	/// <summary>
	/// �ڿ���̨�༭ȫ��ѧ��
	/// </summary>
	static void _Edit_All();

	/// <summary>
	/// �ڿ���̨�༭
	/// </summary>
	virtual void Edit();

	/// <summary>
	/// �ڿ���̨��ӡ�ɼ���¼
	/// </summary>
	void Print_Record() const;

	void Delete_Record(Class* const class_ptr);

	/// <summary>
	/// �ڿ���̨��ӡ��Ϣ�ͳɼ�
	/// </summary>
	virtual void Print() const;

	/// <param name="class_ptr">�༶ָ��</param>
	/// <returns>ѧ���ɼ�</returns>
	const double Get_Score(const Class* const class_ptr);


	/// <param name="class_ptr">�γ�ָ��</param>
	/// <returns>ѧ���ɼ�</returns>
	const double Get_Score(const Course* const course_ptr);

	/// <returns>ȫ��ѧ����</returns>
	static const size_t _Get_Size();

	/// <returns>��n��ѧ��ָ��</returns>
	static Student* const _Get_ptr(const size_t& n);

	/// <summary>
	/// �ڿ���̨��ӡȫ��ѧ����Ϣ
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// �ڿ���̨����ɼ�
	/// </summary>
	static void _Score_Manage();

	/// <summary>
	/// ȫ��ѧ����Ϣд���ļ�
	/// </summary>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// ���ļ�����ȫ��ѧ����Ϣ
	/// </summary>
	/// <param name="file">�ļ�����������</param>
	static void _Read_File(std::ifstream& file);

	virtual ~Student();

protected:

	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="name">����</param>
	/// <param name="id">ѧ��</param>
	/// <param name="faculty">Ժϵ</param>
	/// <param name="grade">�꼶</param>
	Student(const std::string& name, const std::string& id, const std::string& faculty, const Grade_Type& grade, bool is_ta);

	/// <summary>
	/// �޸�ѧ��
	/// </summary>
	/// <param name="id">ѧ��</param>
	virtual void Edit_ID(const std::string& id);

	/// <summary>
	/// �ڿ���̨�޸ĳɼ���¼
	/// </summary>
	void Edit_Record();

	/// <summary>
	/// ɾ����n��ɼ���¼
	/// </summary>
	void Delete_Record(const unsigned long long& n);

	/// <summary>
	/// ��ӳɼ���¼
	/// </summary>
	/// <param name="class_ptr">�༶ָ��</param>
	/// <param name="score">�ɼ�</param>
	void Add_Record(Class* const class_ptr, const double& score);

	/// <summary>
	/// �ڿ���̨��ӳɼ���¼
	/// </summary>
	void Add_Record(Course* const course_ptr);

	class Record
	{
	public:

		/// <summary>
		/// ���캯��
		/// </summary>
		/// <param name="class_ptr">�༶ָ��</param>
		/// <param name="score">�ɼ�</param>
		Record(Class* const class_ptr, const double& score);

		/// <returns>�γ�ָ��</returns>
		Class* const Get_Class_ptr() const;

		/// <returns>�ɼ�</returns>
		const double Get_Score() const;

		/// <summary>
		/// �޸ĳɼ�
		/// </summary>
		/// <param name="score">�ɼ�</param>
		void Edit_Score(const double& score);

	private:

		Class* Class_ptr; // �༶ָ��
		double Score; // �ɼ�

	};

	bool Is_TA; // �Ƿ�Ϊ����
	Grade_Type Grade; // �꼶
	std::vector<Record> Record_List; // ѧ���ɼ���¼�б�ÿ������༶ָ�롢�ɼ�
	static std::vector<Student*> _List; // ȫ��ѧ��ָ���б�
};