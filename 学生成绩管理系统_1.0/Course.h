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
	/// 从控制台构造
	/// </summary>
	static Course* const _New(std::string name = "", double full_score = 100);

	/// <returns>课程序号</returns>
	const size_t Get_Serial_Number() const;

	/// <returns>课程名</returns>
	const std::string& Get_Name() const;

	/// <returns>课程满分</returns>
	const double Get_Full_Score() const;

	/// <returns>开课班级数</returns>
	const size_t Get_Class_Size() const;

	/// <returns>第n个班级指针</returns>
	Class* const Get_Class_ptr(const unsigned long long& n) const;

	/// <returns>课程平均分</returns>
	const double Get_Average_Score() const;

	/// <summary>
	/// 添加到班级列表
	/// </summary>
	/// <param name="class_ptr">班级指针</param>
	void Add_Class(Class* const class_ptr);

	/// <summary>
	/// 在控制台管理成绩
	/// </summary>
	static void _Score_Manage();

	/// <summary>
	/// 在控制台编辑全部课程
	/// </summary>
	static void _Edit_All();

	/// <summary>
	/// 在控制台编辑
	/// </summary>
	void Edit();

	/// <summary>
	/// 在控制台打印开课班级课程、教师名和学生人数
	/// </summary>
	void Print_Class() const;

	/// <summary>
	/// 在控制台打印课程名、开课班级
	/// </summary>
	void Print() const;

	/// <summary>
	/// 从班级列表删除班级
	/// </summary>
	/// <param name="class_ptr">班级指针</param>
	void Delete_Class(Class* class_ptr);

	/// <returns>全部课程数</returns>
	static const size_t _Get_Size();

	/// <returns>第n个课程指针</returns>
	static Course* const _Get_ptr(const size_t& n);

	/// <summary>
	/// 在控制台打印全部课程名称、满分
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// 全部课程信息写入文件
	/// </summary>
	/// <param name="file">文件输出流对象</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// 从文件读入全部课程信息
	/// </summary>
	/// <param name="file">文件输入流对象</param>
	static void _Read_File(std::ifstream& file);

	~Course();

private:

	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="name">名称</param>
	Course(const std::string& name, const double& full_score);

	/// <summary>
	/// 修改课程名
	/// </summary>
	/// <param name="name">课程名</param>
	void Edit_Name(const std::string& name);

	/// <summary>
	/// 修改课程满分
	/// </summary>
	/// <param name="full_score">课程满分</param>
	void Edit_Full_Score(const int& full_score);

	/// <summary>
	/// 在控制台修改班级
	/// </summary>
	void Edit_Class();

	std::string Name; // 课程名
	double Full_Score; // 课程满分
	std::vector<Class*> Class_List; // 班级指针列表
	static std::vector<Course*> _List; // 全部课程指针列表

};