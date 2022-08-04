#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

enum Grade_Type // 年级类型
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
	/// 从控制台构造
	/// </summary>
	/// <param name="is_ta">是否为助教 -> 0：非助教 1：助教 2：在控制台确定</param>
	static Student* const _New(std::string name = "", std::string id = "0", std::string faculty = "电子系", Grade_Type grade = undergraduate_1, bool is_ta = false);

	/// <returns>年级</returns>
	const Grade_Type Get_Grade() const;

	/// <returns>是否为助教</returns>
	const bool Get_is_TA() const;

	/// <summary>
	/// 在控制台编辑全部学生
	/// </summary>
	static void _Edit_All();

	/// <summary>
	/// 在控制台编辑
	/// </summary>
	virtual void Edit();

	/// <summary>
	/// 在控制台打印成绩记录
	/// </summary>
	void Print_Record() const;

	void Delete_Record(Class* const class_ptr);

	/// <summary>
	/// 在控制台打印信息和成绩
	/// </summary>
	virtual void Print() const;

	/// <param name="class_ptr">班级指针</param>
	/// <returns>学生成绩</returns>
	const double Get_Score(const Class* const class_ptr);


	/// <param name="class_ptr">课程指针</param>
	/// <returns>学生成绩</returns>
	const double Get_Score(const Course* const course_ptr);

	/// <returns>全部学生数</returns>
	static const size_t _Get_Size();

	/// <returns>第n个学生指针</returns>
	static Student* const _Get_ptr(const size_t& n);

	/// <summary>
	/// 在控制台打印全部学生信息
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// 在控制台管理成绩
	/// </summary>
	static void _Score_Manage();

	/// <summary>
	/// 全部学生信息写入文件
	/// </summary>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// 从文件读入全部学生信息
	/// </summary>
	/// <param name="file">文件输入流对象</param>
	static void _Read_File(std::ifstream& file);

	virtual ~Student();

protected:

	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="name">姓名</param>
	/// <param name="id">学号</param>
	/// <param name="faculty">院系</param>
	/// <param name="grade">年级</param>
	Student(const std::string& name, const std::string& id, const std::string& faculty, const Grade_Type& grade, bool is_ta);

	/// <summary>
	/// 修改学号
	/// </summary>
	/// <param name="id">学号</param>
	virtual void Edit_ID(const std::string& id);

	/// <summary>
	/// 在控制台修改成绩记录
	/// </summary>
	void Edit_Record();

	/// <summary>
	/// 删除第n项成绩记录
	/// </summary>
	void Delete_Record(const unsigned long long& n);

	/// <summary>
	/// 添加成绩记录
	/// </summary>
	/// <param name="class_ptr">班级指针</param>
	/// <param name="score">成绩</param>
	void Add_Record(Class* const class_ptr, const double& score);

	/// <summary>
	/// 在控制台添加成绩记录
	/// </summary>
	void Add_Record(Course* const course_ptr);

	class Record
	{
	public:

		/// <summary>
		/// 构造函数
		/// </summary>
		/// <param name="class_ptr">班级指针</param>
		/// <param name="score">成绩</param>
		Record(Class* const class_ptr, const double& score);

		/// <returns>课程指针</returns>
		Class* const Get_Class_ptr() const;

		/// <returns>成绩</returns>
		const double Get_Score() const;

		/// <summary>
		/// 修改成绩
		/// </summary>
		/// <param name="score">成绩</param>
		void Edit_Score(const double& score);

	private:

		Class* Class_ptr; // 班级指针
		double Score; // 成绩

	};

	bool Is_TA; // 是否为助教
	Grade_Type Grade; // 年级
	std::vector<Record> Record_List; // 学生成绩记录列表，每项包含班级指针、成绩
	static std::vector<Student*> _List; // 全部学生指针列表
};