#pragma once
#include <vector>
#include "Student.h"
#include "Teacher.h"

class Class;
class Teaching_Assistant : public Student, public Teacher
{
public:

	/// <summary>
	/// 构造函数，助教指针加入Student::Student_List
	/// </summary>
	/// <param name="name">姓名</param>
	/// <param name="id">学号</param>
	/// <param name="faculty">院系</param>
	/// <param name="grade">年级</param>
	Teaching_Assistant(const std::string& name, const std::string& id, const std::string& faculty, const Grade_Type grade);

	static Teaching_Assistant* const _New(std::string name = "", std::string id = "0", std::string faculty = "电子系", Grade_Type grade = undergraduate_1);

	/// <summary>
	/// 在控制台修改
	/// </summary>
	virtual void Edit();

	/// <summary>
	/// 在控制台打印
	/// </summary>
	virtual void Print() const;

	/// <returns>助教人数</returns>
	static const size_t _Get_Size();

	/// <summary>
	/// 在控制台打印全部助教辅导班级信息
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// 添加到助教列表
	/// </summary>
	static void _Add_Teaching_Assistant(Teaching_Assistant* const teaching_assistant_ptr);

	/// <summary>
	/// 清空成绩列表
	/// </summary>
	virtual ~Teaching_Assistant();

	/// <summary>
	/// 全部助教信息写入文件
	/// </summary>
	/// <param name="file">文件输出流对象</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// 从文件读入全部助教信息
	/// </summary>
	/// <param name="file">文件输入流对象</param>
	static void _Read_File(std::ifstream& file);

private:

	/// <summary>
	/// 编辑学号
	/// </summary>
	/// <param name="id">学号</param>
	virtual void Edit_ID(const std::string& id);

	/// <summary>
	/// 在控制台编辑辅导班级
	/// </summary>
	virtual void Edit_Class();

	static std::vector<Teaching_Assistant*> _List; // 全部助教指针列表

};
