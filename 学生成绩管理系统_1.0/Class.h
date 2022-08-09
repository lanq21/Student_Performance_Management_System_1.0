#pragma once
#include <vector>
#include <string>

enum Sort_Condition // 排序依据
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
	/// 在控制台构造
	/// </summary>
	static Class* const _New(Course* course_ptr = nullptr, Teacher* teacher_ptr = nullptr);

	/// <returns>课程指针</returns>
	Course* const Get_Course_ptr() const;

	/// <returns>教师指针</returns>
	Teacher* const Get_Teacher_ptr() const;

	/// <returns>学生数</returns>
	const size_t Get_Student_Size() const;

	/// <returns>班级序号</returns>
	const size_t Get_Serial_Number() const;

	/// <param name="student_ptr">学生指针</param>
	/// <returns>班级排名</returns>
	const _int64 Get_Rank(const Student* const student_ptr);

	/// <summary>
	/// 在学生指针列表中添加学生
	/// c</summary>
	/// <param name="student_ptr">学生指针</param>
	void Add_Student(Student* const student_ptr);

	/// <summary>
	/// 在学生指针列表中删除学生
	/// </summary>
	/// <param name="student_ptr">学生指针</param>
	void Delete_Student(Student* const student_ptr);

	/// <returns>班级平均分</returns>
	const double Get_Average_Score() const;

	/// <summary>
	/// 学生列表排序
	/// </summary>
	/// <param name="sort_condition">排序依据</param>
	void Rank(const Sort_Condition& sort_condition);

	/// <summary>
	/// 在控制台打印成绩记录
	/// </summary>
	void Print_Record() const;

	/// <summary>
	/// 在控制台打印班级课程、教师名称和学生人数
	/// </summary>
	void Print() const;

	/// <summary>
	/// 重载运算符 << 用于在控制台打印
	/// </summary>
	friend std::ostream& operator<<(std::ostream& output, const Class& class_obj);

	/// <summary>
	/// 在控制台打印所有班级课程名、教师名
	/// </summary>
	static void _Print_All();

	/// <summary>
	/// 在控制台编辑全部班级
	/// </summary>
	static void _Edit_All();

	/// <returns>全部班级数</returns>
	static const size_t _Get_Size();

	/// <returns>第n个班级指针</returns>
	static Class* const _Get_ptr(const size_t& n);

	/// <summary>
	/// 全部班级信息写入文件
	/// </summary>
	/// <param name="file">文件输出流对象</param>
	static void _Write_File(std::ofstream& file);

	/// <summary>
	/// 从文件读入全部班级信息
	/// </summary>
	/// <param name="file">文件输入流对象</param>
	static void _Read_File(std::ifstream& file);

	/// <summary>
	/// 因析构课程导致的班级析构
	/// </summary>
	/// <param name="course_ptr"课程指针></param>
	static void Delete(Course* const course_ptr);

	/// <summary>
	/// 因析构教师导致的班级析构
	/// </summary>
	/// <param name="teacher_ptr">教师指针</param>
	static void Delete(Teacher* const teacher_ptr);

	~Class();

private:


	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="course">课程指针</param>
	/// <param name="teacher">教师指针</param>
	Class(Course* const course_ptr, Teacher* const teacher_ptr);

	/// <summary>
	/// 按照姓名排序
	/// </summary>
	/// <param name="student_ptr_1">学生一指针</param>
	/// <param name="student_ptr_2">学生二指针</param>
	static bool compare_name(Student* const student_ptr_1, Student* const student_ptr_2);

	/// <summary>
	/// 按照学号排序
	/// </summary>
	/// <param name="student_ptr_1">学生一指针</param>
	/// <param name="student_ptr_2">学生二指针</param>
	static bool compare_id(Student* const student_ptr_1, Student* const student_ptr_2);

	/// <summary>
	/// 按照成绩排序
	/// </summary>
	/// <param name="student_ptr_1">学生一指针</param>
	/// <param name="student_ptr_2">学生二指针</param>
	bool compare_score(Student* const student_ptr_1, Student* const student_ptr_2) const;

	/// <summary>
	/// 修改课程指针
	/// </summary>
	/// <param name="course_ptr">课程指针</param>
	void Edit_Course(Course* const course_ptr);

	/// <summary>
	/// 修改教师指针
	/// </summary>
	/// <param name="teacher_ptr">教师指针</param>
	void Edit_Teacher(Teacher* const teacher_ptr);

	Course* Course_ptr; // 课程指针
	Teacher* Teacher_ptr; // 教师指针
	static std::vector<Class*> _List; // 全部班级指针列表
	std::vector<Student*> Student_List; // 学生列表
	bool Order_by_Name; // 标记：按照学生姓名有序
	bool Order_by_ID; // 标记：按照学生学号有序
	bool Order_by_Score; // 标记：按照学生成绩有序
};