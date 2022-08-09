#pragma once
#include <vector>
#include <string>

enum Sort_Condition // ��������
{
	Rank_Name, Rank_ID, Rank_Score
};
class Student;
class Course;
class Teacher;

class Class
{
public:


	/// <summary>
	/// �ڿ���̨����
	/// </summary>
	static Class* const _New(Course* course_ptr = nullptr, Teacher* teacher_ptr = nullptr);

	/// <returns>�γ�ָ��</returns>
	Course* const Get_Course_ptr() const;

	/// <returns>��ʦָ��</returns>
	Teacher* const Get_Teacher_ptr() const;

	/// <returns>ѧ����</returns>
	const size_t Get_Student_Size() const;

	/// <returns>�༶���</returns>
	const size_t Get_Serial_Number() const;

	/// <param name="student_ptr">ѧ��ָ��</param>
	/// <returns>�༶����</returns>
	const _int64 Get_Rank(const Student* const student_ptr);

	/// <summary>
	/// ��ѧ��ָ���б������ѧ��
	/// c</summary>
	/// <param name="student_ptr">ѧ��ָ��</param>
	void Add_Student(Student* const student_ptr);

	/// <summary>
	/// ��ѧ��ָ���б���ɾ��ѧ��
	/// </summary>
	/// <param name="student_ptr">ѧ��ָ��</param>
	void Delete_Student(Student* const student_ptr);

	/// <returns>�༶ƽ����</returns>
	const double Get_Average_Score() const;

	/// <summary>
	/// ѧ���б�����
	/// </summary>
	/// <param name="sort_condition">��������</param>
	void Rank(const Sort_Condition& sort_condition);

	/// <summary>
	/// �ڿ���̨��ӡ�ɼ���¼
	/// </summary>
	void Print_Record() const;

	/// <summary>
	/// �ڿ���̨��ӡ�༶�γ̡���ʦ���ƺ�ѧ������
	/// </summary>
	void Print() const;

	/// <summary>
	/// ��������� << �����ڿ���̨��ӡ
	/// </summary>
	friend std::ostream& operator<<(std::ostream& output, const Class& class_obj);

	/// <summary>
	/// �ڿ���̨��ӡ���а༶�γ�������ʦ��
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// �ڿ���̨�༭ȫ���༶
	/// </summary>
	static void _Edit_All();

	/// <returns>ȫ���༶��</returns>
	static const size_t _Get_Size();

	/// <returns>��n���༶ָ��</returns>
	static Class* const _Get_ptr(const size_t& n);

	/// <summary>
	/// ȫ���༶��Ϣд���ļ�
	/// </summary>
	/// <param name="file">�ļ����������</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// ���ļ�����ȫ���༶��Ϣ
	/// </summary>
	/// <param name="file">�ļ�����������</param>
	static void _Read_File(std::ifstream& file);

	/// <summary>
	/// �������γ̵��µİ༶����
	/// </summary>
	/// <param name="course_ptr"�γ�ָ��></param>
	static void Delete(Course* const course_ptr);

	/// <summary>
	/// ��������ʦ���µİ༶����
	/// </summary>
	/// <param name="teacher_ptr">��ʦָ��</param>
	static void Delete(Teacher* const teacher_ptr);

	~Class();

private:


	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="course">�γ�ָ��</param>
	/// <param name="teacher">��ʦָ��</param>
	Class(Course* const course_ptr, Teacher* const teacher_ptr);

	/// <summary>
	/// ������������
	/// </summary>
	/// <param name="student_ptr_1">ѧ��һָ��</param>
	/// <param name="student_ptr_2">ѧ����ָ��</param>
	static bool compare_name(Student* const student_ptr_1, Student* const student_ptr_2);

	/// <summary>
	/// ����ѧ������
	/// </summary>
	/// <param name="student_ptr_1">ѧ��һָ��</param>
	/// <param name="student_ptr_2">ѧ����ָ��</param>
	static bool compare_id(Student* const student_ptr_1, Student* const student_ptr_2);

	/// <summary>
	/// ���ճɼ�����
	/// </summary>
	/// <param name="student_ptr_1">ѧ��һָ��</param>
	/// <param name="student_ptr_2">ѧ����ָ��</param>
	bool compare_score(Student* const student_ptr_1, Student* const student_ptr_2) const;

	/// <summary>
	/// �޸Ŀγ�ָ��
	/// </summary>
	/// <param name="course_ptr">�γ�ָ��</param>
	void Edit_Course(Course* const course_ptr);

	/// <summary>
	/// �޸Ľ�ʦָ��
	/// </summary>
	/// <param name="teacher_ptr">��ʦָ��</param>
	void Edit_Teacher(Teacher* const teacher_ptr);

	Course* Course_ptr; // �γ�ָ��
	Teacher* Teacher_ptr; // ��ʦָ��
	static std::vector<Class*> _List; // ȫ���༶ָ���б�
	std::vector<Student*> Student_List; // ѧ���б�
	bool Order_by_Name; // ��ǣ�����ѧ����������
	bool Order_by_ID; // ��ǣ�����ѧ��ѧ������
	bool Order_by_Score; // ��ǣ�����ѧ���ɼ�����
};