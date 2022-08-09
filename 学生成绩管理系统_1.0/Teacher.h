#pragma once
#include "Person.h"
#include <vector>

class Class;
class Course;

class Teacher : virtual public Person
{
public:

	/// <summary>
	/// 从控制台构造
	/// </summary>
	static Teacher* const _New(std::string name="", std::string id="0", std::string faculty="电子系");

	/// <returns>教师序号</returns>
	const size_t Get_Serial_Number() const;

	/// <summary>
	/// 在控制台编辑全部教师
	/// </summary>
	static void Edit_All();

	/// <summary>
	/// 在控制台编辑
	/// </summary>
	virtual void Edit();

	/// <summary>
	/// 在控制台打印
	/// </summary>
	virtual void Print() const;

	/// <summary>
	/// 重载运算符 << 用于在控制台打印
	/// </summary>
	friend std::ostream& operator<<(std::ostream& output, const Teacher& teacher_obj);

	/// <summary>
	/// 从班级列表删除班级
	/// </summary>
	/// <param name="class_ptr"></param>
	void Delete_Class(Class* class_ptr);

	/// <returns>班级数</returns>
	size_t Get_Class_Size() const;

	/// <returns>第n个班级指针</returns>
	Class* const Get_Class_ptr(const int& n);

	/// <returns>全部教师数</returns>
	static const size_t _Get_Size();

	/// <returns>第n个教师指针</returns>
	static Teacher* const _Get_ptr(const size_t& n);

	/// <summary>
	/// 在控制台打印全部教师名称、编号、院系
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// 全部教师信息写入文件
	/// </summary>
	/// <param name="file">文件输出流对象</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// 从文件读入全部教师信息
	/// </summary>
	/// <param name="file">文件输入流对象</param>
	static void _Read_File(std::ifstream& file);

	/// <summary>
	/// 添加班级到列表
	/// </summary>
	/// <param name="class_ptr">班级指针</param>
	void Add_Class(Class* const class_ptr);

	virtual ~Teacher();

protected:

	/// <summary>
	/// 在控制台打印授课班级
	/// </summary>
	void Print_Class() const;

	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="name">姓名</param>
	/// <param name="id">编号</param>
	/// <param name="faculty">院系</param>
	Teacher(const std::string& name, const std::string& id, const std::string faculty,const bool& is_ta);

	std::vector<Class*> Class_List; // 班级指针列表

private:

	/// <summary>
	/// 修改教师编号
	/// </summary>
	/// <param name="id">教师编号</param>
	virtual void Edit_ID(const std::string& id);

	/// <summary>
	/// 在控制台修改班级
	/// </summary>
	virtual void Edit_Class();

	bool is_TA; // 是否为助教
	static std::vector<Teacher*> _List; // 全部教师指针列表
};