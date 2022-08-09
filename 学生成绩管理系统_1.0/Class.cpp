#include <algorithm>
#include <conio.h>
#include <functional>
#include <iomanip>
#include <iostream>

#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"

using std::placeholders::_1;
using std::placeholders::_2;

std::vector<Class*> Class::_List;

Class::Class(Course* const course_ptr, Teacher* const teacher_ptr) :
	Course_ptr(course_ptr), Teacher_ptr(teacher_ptr), Order_by_Name(true), Order_by_ID(true), Order_by_Score(true) {}

void Class::Edit_Course(Course* const course_ptr)
{
	if (course_ptr == nullptr)
	{
		std::cerr << "in function void Class::Edit_Course(Course* const course_ptr):\n"
			<< "\tedit course failed.\n"
			<< "\tcause：course_ptr == nullptr\n";
		return;
	}
	else
		Course_ptr = course_ptr;
}

void Class::Edit_Teacher(Teacher* const teacher_ptr)
{
	if (teacher_ptr == nullptr)
	{
		std::cerr << "in function void Class::Edit_Teacher(Teacher* const teacher_ptr):\n"
			<< "\tedit teacher failed.\n"
			<< "\tcause：teacher_ptr == nullptr\n";
		return;
	}
	else
		Teacher_ptr = teacher_ptr;
}

Class* const Class::_New(Course* course_ptr, Teacher* teacher_ptr)
{
	unsigned long long serial; // 输入序号

	if (course_ptr == nullptr) // 课程指针 course_ptr 为缺省值或无效值
	{
		std::cout << "新增班级 -> ";
		if (Course::_Get_Size()) // 课程列表不为空
		{
			std::cout << "选择课程（输入序号）：\n\n";
			Course::_Print_All();
			std::cout << "\n或输入 0 新增课程：";
		}
		else
			std::cout << "选择课程 -> 当前无课程，输入 0 新增课程：";
		std::cin >> serial;
		std::cin.ignore();

		if (serial>Course::_Get_Size())
		{
			std::cerr << "新增班级 -> error（序号超出列表范围）\n";
			return nullptr;
		}
		else if (serial > 0)
			course_ptr = Course::_Get_ptr(serial - 1); // 用第 serial 个课程指针更新 course_ptr
		else
			course_ptr = Course::_New(); // 在控制台新增课程
	}

	if (teacher_ptr == nullptr) // 教师指针 teacher_ptr 为缺省值或无效值
	{
		std::cout <<course_ptr->Get_Name() << " -> 新增班级 -> ";
		if (Teacher::_Get_Size()) // 教师列表不为空
		{
			std::cout << "选择教师（输入序号）：\n\n";
			Teacher::_Print_All();
			std::cout << "\n或输入 0 新增教师：";
		}
		else
			std::cout << "选择教师 -> 当前无教师，输入 0 新增教师：";
		std::cin >> serial;
		std::cin.ignore();

		if (serial>Teacher::_Get_Size())
		{
			std::cerr << "新增班级 -> error（序号超出列表范围）\n";
			return nullptr;
		}
		else if (serial > 0)
			teacher_ptr = Teacher::_Get_ptr(serial - 1); // 用第 serial 个教师指针更新 teacher_ptr
		else
			teacher_ptr = Teacher::_New(); // 在控制台新增教师
	}

	// 检查重复项
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		if ((*iter)->Get_Course_ptr()->Get_Name() == course_ptr->Get_Name() && (*iter)->Get_Teacher_ptr()->Get_ID() == teacher_ptr->Get_ID())
		{
			std::cerr << "新增班级 -> error（班级已存在）\n";
			return (*iter); // 返回已有班级指针
		}
	}

	if (course_ptr == nullptr || teacher_ptr == nullptr) // 确定课程和教师失败
	{
		std::cerr << "in function Class* const Class::_New(Course* course_ptr, Teacher* teacher_ptr):\n"
			<< "\t construct class failed\n"
			<< "\tcause: course_ptr == nullptr || teacher_ptr == nullptr\n";
		return nullptr;
	}
	else
	{
		Class* class_ptr = new Class(course_ptr, teacher_ptr);
		course_ptr->Add_Class(class_ptr); // 添加班级到对应课程
		teacher_ptr->Add_Class(class_ptr); // 添加班级到对应教师
		_List.push_back(class_ptr); // 添加班级到班级列表
		std::cout << "新增班级 -> 已新增班级：课程 " << course_ptr->Get_Name()
			<< "，教师 " << teacher_ptr->Get_Name() << std::endl;
		return class_ptr; // 返回创建的班级指针
	}
}

Course* const Class::Get_Course_ptr() const
{
	return Course_ptr;
}

Teacher* const Class::Get_Teacher_ptr() const
{
	return Teacher_ptr;
}

const size_t Class::Get_Student_Size() const
{
	return Student_List.size();
}

const size_t Class::Get_Serial_Number() const
{
	return std::find(_List.begin(), _List.end(), this) - _List.begin() + 1;
}

const _int64 Class::Get_Rank(const Student* const student_ptr)
{
	if (student_ptr == nullptr)
	{
		std::cerr << "in function const int Class::Get_Rank(Student* const student_ptr):\n"
			<< "can not find the student.\n"
			<< "cause: student_ptr == nullptr\n";
		return 0;
	}
	Rank(Rank_Score); // 按照成绩排序
	auto iter = Student_List.begin();
	for (; iter != Student_List.end(); iter++)
	{
		if ((*iter)==student_ptr) // 找到该学生
			break;
	}
	if (iter == Student_List.end()) // 未找到成绩
	{
		std::cerr << student_ptr->Get_Name() << " -> 班级排名 -> error（找不到该学生）\n";
		return 0;
	}
	else
		return iter - Student_List.begin() + 1;
}

void Class::Add_Student(Student* const student_ptr)
{
	if (student_ptr == nullptr)
	{
		std::cerr << "in function void Class::Add_Student(Student* const student_ptr):\n"
			<< "\tadd student failed.\n"
			<< "\tcause：class_ptr == nullptr\n";
		return;
	}
	else
	{
		Student_List.push_back(student_ptr);
		std::cout << "班级：课程 " << Course_ptr->Get_Name()
			<< "，教师 " << Teacher_ptr->Get_Name()
			<< " -> 添加学生：已添加学生 " << student_ptr->Get_Name()
			<< std::endl;
		Order_by_Name = false;
		Order_by_ID = false;
		Order_by_Score = false;
	}
}

void Class::Delete_Student(Student* const student_ptr)
{
	auto iter = std::find(Student_List.begin(), Student_List.end(), student_ptr);
	if (iter != Student_List.end()) // 查找到学生
	{
		Student_List.erase(iter);
		std::cout << "班级：课程 " << Course_ptr->Get_Name()
			<< "，教师 " << Teacher_ptr->Get_Name()
			<< " -> 删除学生：已删除学生 " << student_ptr->Get_Name()
			<< std::endl;
	}
}

const double Class::Get_Average_Score() const
{
	if (Student_List.empty())
	{
		std::cerr << "班级：课程 " << Get_Course_ptr()->Get_Name()
			<< "，教师 " << Get_Teacher_ptr()->Get_Name()
			<< " -> 平均分 -> error（班级无学生）\n";
		return 0;
	}
	else
	{
		double total_score = 0;
		for (auto iter = Student_List.begin(); iter != Student_List.end(); iter++)
			total_score += (*iter)->Get_Score(this); // 学生该课程成绩求和
		return total_score / Student_List.size();
	}

}

void Class::Rank(const Sort_Condition& sort_condition)
{
	switch (sort_condition)
	{
	case Rank_Name: // 按照学生姓名排序
		if (Order_by_Name == false)
		{
			std::sort(Student_List.begin(), Student_List.end(), compare_name);
			Order_by_Name = true;
		}
		break;
	case Rank_ID: // 按照学生学号排序
		if (Order_by_ID == false)
		{
			std::sort(Student_List.begin(), Student_List.end(), compare_id);
			Order_by_ID = true;
		}
		break;
	case Rank_Score: // 按照学生成绩排序
		if (Order_by_Score == false)
		{
			std::sort(Student_List.begin(), Student_List.end(), bind(&Class::compare_score, this, _1, _2));
			Order_by_Score = true;
		}
		/*
				bind(&Class::compare_score, this, _1, _2))	参考了如下内容：

				using namespace std;
				using placeholders::_1;
				using placeholders::_2;
				class Solution {
				public:
					string minNumber(vector<int> &nums) {
						sort(nums.begin(), nums.end(), bind(&Solution::comp, this, _1, _2));
						string ans;
						for (const auto &c : nums) ans += to_string(c);
						return ans;
					}

					bool comp(int &a, int &b) {
						string sa = to_string(a), sb = to_string(b);
						return sa + sb < sb + sa;
					}
				};

				————————————————
				版权声明：本文为CSDN博主「孤独的拉普拉斯」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
				原文链接：https://blog.csdn.net/qq_33551749/article/details/108247630

		*/
	}
}

bool Class::compare_name(Student* const student_ptr_1, Student* const student_ptr_2)
{
	if (student_ptr_1->Get_Name() < student_ptr_2->Get_Name())
		return true;
	else if (student_ptr_1->Get_Name() == student_ptr_2->Get_Name() && student_ptr_1->Get_ID() < student_ptr_2->Get_ID())
		return true; // 姓名相同时比较学号
	else
		return false;

}

bool Class::compare_id(Student* const student_ptr_1, Student* const student_ptr_2)
{
	if (student_ptr_1->Get_ID() < student_ptr_2->Get_ID()) // 学号被认为互不相同
		return true;
	else
		return false;
}

bool Class::compare_score(Student* const student_ptr_1, Student* const student_ptr_2) const
{
	if (student_ptr_1->Get_Score(this) > student_ptr_2->Get_Score(this))
		return true;
	else if (student_ptr_1->Get_Score(this) == student_ptr_2->Get_Score(this) && student_ptr_1->Get_ID() < student_ptr_2->Get_ID())
		return true; // 成绩相同时比较学号
	else
		return false;
}

void Class::Print_Record() const
{
	size_t student_num = Student_List.size(); // 学生人数
	if (student_num) // 学生列表不为空
	{
		int Grade_Distribution[10] = { 0 }; // 用于统计成绩分布，10 分区间对应 1 个元素
		for (auto iter = Student_List.begin(); iter != Student_List.end(); iter++)
		{
			std::cout << iter - Student_List.begin() + 1 << '.' // 打印序号
				<< std::setw(10) << (*iter)->Get_Name() // 打印姓名
				<< std::setw(15) << (*iter)->Get_ID() // 打印学号
				<< std::setw(10) << (*iter)->Get_Faculty() // 打印院系
				<< std::setw(10) << (*iter)->Get_Score(this) // 打印成绩
				<< std::endl;

			// 得分转 10 分制，截断到个位
			int ten_score = int((*iter)->Get_Score(this) / Get_Course_ptr()->Get_Full_Score() * 10);
			if (ten_score == 10)
				ten_score = 9; // 满分统计在（90% ~ 100%）范围内
			Grade_Distribution[ten_score]++;
		}
		if (student_num) // 有效成绩数不为 0
		{
			std::cout << "班级成绩 -> 班级：课程 " << Get_Course_ptr()->Get_Name()
				<< "，教师 " << Get_Teacher_ptr()->Get_Name()
				<< " -> 平均分：" << Get_Average_Score()
				<< "\n成绩分布：\n";
			for (int i = 0; i < 10; i++)
				if (Grade_Distribution[i]) // 成绩分布不为 0，即有学生成绩处在范围内
					std::cout << "        得分率：" << i * 10 << "% ~ " << (i + 1) * 10 << "%\t学生占比："
					<< double(Grade_Distribution[i]) / student_num * 100 << "%\n";
		}
	}
	else
		std::cerr << "班级成绩 -> 班级：课程 " << Get_Course_ptr()->Get_Name()
		<< "，教师 " << Get_Teacher_ptr()->Get_Name()
		<< " -> error（当前班级无学生）\n";
}

void Class::Print() const
{
	std::cout << "班级：课程 " << Get_Course_ptr()->Get_Name() // 课程名
		<< "，教师 " << Get_Teacher_ptr()->Get_Name() // 教师名
		<< "，学生人数：" << Student_List.size() // 学生人数
		<< std::endl;
}

void Class::_Print_All()
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		std::cout << iter - _List.begin() + 1 << '.' // 序号
		<< "班级：课程 " << (*iter)->Get_Course_ptr()->Get_Name()
		<< "，教师 " << (*iter)->Get_Teacher_ptr()->Get_Name()
		<< "，学生人数：" << (*iter)->Student_List.size()
		<< std::endl;
}

void Class::_Edit_All()
{
	while (true)
	{
		bool flag = false; // 标记：班级列表为空，2 属于 “其他键”
		if (_List.empty())
		{
			std::cout << "编辑班级 -> （当前无班级）\n"
				<< "编辑班级 -> 选择编辑方式：1.新增，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // 打印全部班级
			std::cout << "\n编辑班级 -> 选择编辑方式：1.新增，2.删除，按其他键取消...";
		}

		int new_num; // switch 内输入序号
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增班级
			Class::_New();
			break;

		case '2': // 删除班级
			if (flag) // 当前无班级，与 default 相同处理
				return;
			std::cout << "删除班级 -> 输入序号 或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num>_List.size())
				std::cerr << "删除班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑班级 -> 按E/e继续编辑班级，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

const size_t Class::_Get_Size()
{
	return _List.size();
}

Class* const Class::_Get_ptr(const size_t& n)
{
	// n 取值从 0 开始
	if (n < 0 || n >= _List.size())
	{
		std::cerr << "in function Class* const Class::Get_Class_ptr(const int& n):\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=_List.size()\n";
		return nullptr;
	}
	else
		return _List[n];
}

void Class::_Write_File(std::ofstream& file)
{
	file << "## 班级（总计：" << _Get_Size() << "）\n\n" // 标题
		<< "| 序号 | 课程 | 教师 |\n" // 表头
		<< "| - | - | - |\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // 班级序号
			<< " | ` " << (*iter)->Get_Course_ptr()->Get_Serial_Number() // 课程序号
			<< " `  " << (*iter)->Get_Course_ptr()->Get_Name() << " | ` " // 课程名
			<< (*iter)->Get_Teacher_ptr()->Get_Serial_Number() << " `  " // 教师序号
			<< (*iter)->Get_Teacher_ptr()->Get_Name() << " |\n"; // 教师姓名
	}
	file << std::endl;
}

void Class::_Read_File(std::ifstream& file)
{
	char delimiter; // 分隔符
	unsigned long long num_course; // 课程序号
	unsigned long long num_teacher; // 教师序号

	// 移动读指针到班级列表
	file.seekg(std::ios_base::beg); // 定位到文件头
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到标题
	if (file.peek() != '#')
		file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到课程列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到教师列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到班级列表标题
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "## 班级"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过空行
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| 序号 | 课程 | 教师 |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| - | - | - |"

	delimiter = file.get(); // 读入第一行首字符
	while (delimiter == '|')
	{
		file.ignore(std::numeric_limits<std::streamsize>::max(), '`'); // 移动读指针到课程序号
		file >> num_course; // 读入课程序号
		file.get(); // 读入 ' '
		file.get(); // 读入 '|'
		file.ignore(std::numeric_limits<std::streamsize>::max(), '`'); // 移动读指针到教师序号
		file >> num_teacher; // 读入教师序号
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 移动读指针到行尾
		delimiter = file.get(); // 读入下一行首字符
		Class::_New(Course::_Get_ptr(num_course - 1), Teacher::_Get_ptr(num_teacher - 1)); // 创建班级
	}
}

void Class::Delete(Course* const course_ptr)
{
	size_t class_num = course_ptr->Get_Class_Size();
	for (int i = 0; i < class_num; i++)
		delete course_ptr->Get_Class_ptr(i); // 在析构课程前析构课程的全部班级
}

void Class::Delete(Teacher* const teacher_ptr)
{
	size_t class_num = teacher_ptr->Get_Class_Size();
	for (int i = 0; i < class_num; i++)
		delete teacher_ptr->Get_Class_ptr(i); // 在析构教师前析构教师的全部班级
}

Class::~Class()
{
	// 从相关课程中删除班级
	this->Get_Course_ptr()->Delete_Class(this);
	// 从相关教师中删除教师
	this->Get_Teacher_ptr()->Delete_Class(this);
	// 从相关学生中删除成绩记录
	for (auto iter = this->Student_List.begin(); iter != this->Student_List.end(); iter++)
		(*iter)->Delete_Record(this);
	// 从班级列表中删除
	_List.erase(std::find(_List.begin(), _List.end(), this));

	std::cout << "删除班级 -> 已删除班级：课程 " << Get_Course_ptr()->Get_Name()
		<< "，教师 " << Get_Teacher_ptr()->Get_Name()
		<< std::endl;
}

std::ostream& operator<<(std::ostream& output, const Class& class_obj)
{
	output << "班级：课程 " << class_obj.Get_Course_ptr()->Get_Name() // 课程名
		<< "，教师 " << class_obj.Get_Teacher_ptr()->Get_Name() // 教师名
		<< "，学生人数：" << class_obj.Student_List.size() // 学生人数
		<< std::endl;
	return output;
}
