#include <conio.h>
#include <iomanip>
#include <iostream>

#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"

std::vector<Course*> Course::_List;

Course::Course(const std::string& name, const double& full_score) :Name(name), Full_Score(full_score) {}

Course* const Course::_New(std::string name, double full_score)
{
	std::string full_score_input; // 从控制台输入课程满分
	bool flag = false; // 标记：从控制台新建
	if (name.empty()) // 从控制台新建，使用缺省形参
		flag = true;

	if (flag)
	{
		// 设置课程名
		std::cout << "新增课程 -> 课程名：";
		getline(std::cin, name);
	}

	// 检查重复项
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_Name() == name)
		{
			std::cerr << "新增课程 -> error（课程已存在）\n";
			return (*iter);
		}

	if (flag)
	{
		// 设置课程满分
		std::cout << "新增课程 -> 课程满分（按 Enter 自动填充 100）：";
		getline(std::cin, full_score_input);
		if (full_score_input.empty()) // 输入了 Enter
			full_score = 100; // 使用默认课程满分
		else
			full_score = atof(full_score_input.c_str()); // 使用输入的课程满分
	}
	Course* course_ptr = new Course(name, full_score);
	_List.push_back(course_ptr); // 添加到课程列表
	std::cout << "新增课程 -> 已新增课程 " << name << "，满分 " << full_score << std::endl;
	return course_ptr;
}

const size_t Course::Get_Serial_Number() const
{
	return std::find(_List.begin(), _List.end(), this) - _List.begin() + 1;
}

const std::string& Course::Get_Name() const
{
	return Name;
}

const double Course::Get_Full_Score() const
{
	return Full_Score;
}

const size_t Course::Get_Class_Size() const
{
	return Class_List.size();
}

Class* const Course::Get_Class_ptr(const unsigned long long& n) const
{
	if (n < 0 || n >= Class_List.size())
	{
		std::cerr << "in function Class* const Course::Get_Class_ptr(const int& n) const:\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=Class_List.size()\n";
		return nullptr;
	}
	else
		return Class_List[n];
}

void Course::Edit()
{
	while (true)
	{
		std::cout << "编辑课程 -> " << Get_Name() << " -> 选择修改项：1.课程名，2.课程满分，3.开课班级，按其他键取消...";
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		// switch 内接受输入
		std::string new_info;
		int new_num;

		switch (input)
		{
		case '1': // 修改课程名
			std::cout << "编辑课程 -> " << Get_Name() << " -> 新课程名：";
			getline(std::cin, new_info);
			Edit_Name(new_info);
			break;

		case '2': // 修改课程满分
			std::cout << "编辑课程 -> " << Get_Name() << " -> 新课程满分：";
			std::cin >> new_num;
			std::cin.ignore();
			Edit_Full_Score(new_num);
			break;

		case '3': // 编辑开课班级
			Edit_Class();
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑课程 -> " << Get_Name() << " -> 按E/e继续修改课程信息，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Course::Edit_Name(const std::string& name)
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_Name() == name)
		{
			std::cerr << "编辑课程 -> error（课程已存在）\n";
			return;
		}
	Name = name;
	std::cout << "编辑课程 -> 已修改课程名为 " << name << std::endl;
}

void Course::Edit_Full_Score(const int& full_score)
{
	Full_Score = full_score;
	std::cout << "编辑课程 -> 已修改课程满分为 " << full_score << std::endl;
}

void Course::Add_Class(Class* const class_ptr)
{
	if (class_ptr == nullptr)
	{
		std::cerr << "in function void Course::Add_Class(Class* const class_ptr):\n"
			<< "\tadd class failed.\n"
			<< "\tcause: class_ptr == nullptr\n";
		return;
	}
	else
		Class_List.push_back(class_ptr);
}

void Course::_Score_Manage()
{
	while (true)
	{
		system("cls");
		unsigned long long serial; // 从控制台输入序号

		if (_Get_Size()) // 课程列表不为空
		{
			std::cout << "课程成绩 -> 输入序号查看课程成绩统计：\n\n";
			_Print_All();
			std::cout << "\n或 输入 0 取消：";
			std::cin >> serial;
			std::cin.ignore();
			if (serial == 0)
				return;
			if (serial < 0 || serial > _Get_Size())
				std::cerr << "课程成绩 -> error（序号超出列表范围）\n";
			else
			{
				Course* course_ptr = Course::_Get_ptr(serial - 1);
				std::cout << course_ptr->Get_Name() << " -> 查看班级成绩统计（输入序号）\n\n";
				course_ptr->Print_Class(); // 打印班级列表，包括课程、教师名，学生人数
				std::cout << "\n或 输入 0 取消：";
				std::cin >> serial;
				std::cin.ignore();
				if (serial)
				{
					if (serial > course_ptr->Get_Class_Size())
						std::cerr << course_ptr->Get_Name() << " -> error（序号超出列表范围）";
					else
					{
						Class* class_ptr = course_ptr->Get_Class_ptr(serial - 1);
						if (class_ptr->Get_Student_Size() == 0)
							std::cerr << course_ptr->Get_Name()
							<< " -> 班级：课程 " << course_ptr->Get_Name()
							<< "，教师 " << class_ptr->Get_Teacher_ptr()->Get_Name()
							<< " -> 查看成绩统计 -> error（当前班级无学生）\n";
						else
						{
							std::cout << course_ptr->Get_Name()
								<< " -> 班级：课程 " << course_ptr->Get_Name()
								<< "，教师 " << class_ptr->Get_Teacher_ptr()->Get_Name()
								<< " -> 选择排序方式：1.姓名 2.学号 3.成绩，或按其他键取消：";
							char input = _getch();
							std::cout << std::endl << std::endl;
							switch (input)
							{
							case '1':
								class_ptr->Rank(Rank_Name); // 按学生姓名排序
								class_ptr->Print_Record();
								break;
							case '2':
								class_ptr->Rank(Rank_ID); // 按学生学号排序
								class_ptr->Print_Record();
								break;
							case '3':
								class_ptr->Rank(Rank_Score); // 按学生成绩排序
								class_ptr->Print_Record();
							}
							std::cout << std::endl;
						}
					}
				}
			}
		}
		else
			std::cerr << "课程成绩 -> error（当前无课程）\n";

		std::cout << "课程成绩 -> 按E/e继续查看课程成绩统计，按其他键结束...";
		char input = _getch();
		std::cout << std::endl << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Course::_Edit_All()
{
	while (true)
	{
		system("cls");
		std::cout << "编辑课程：\n";
		bool flag = false; // 标记：课程列表为空，2、3 属于 “其他键”
		if (_List.empty())
		{
			std::cout << "编辑课程 -> （当前无课程）\n"
				<< "编辑课程 -> 选择编辑方式：1.新增，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // 打印全部课程
			std::cout << "\n编辑课程 -> 选择编辑方式：1.新增，2.修改，3.删除，按其他键取消...";
		}

		unsigned long long new_num; // switch 内接受输入
		Course* course_ptr;
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增课程
			course_ptr = Course::_New(); // 在控制台新增课程
			std::cout << "新增课程 -> 按 Enter 编辑开课班级，按其他键取消：";
			input = _getch();
			std::cout << std::endl;
			if (input == '\r')
				course_ptr->Edit_Class();
			break;

		case '2': // 修改课程
			if (flag) // 当前无课程
				return;
			std::cout << "编辑课程 -> 选择课程（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "编辑课程 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				_List[new_num - 1]->Edit();
			break;

		case '3': // 删除课程
			if (flag) // 当前无课程
				return;
			std::cout << "删除课程（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "删除课程 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑课程 -> 按E/e继续编辑课程，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Course::Edit_Class()
{
	while (true)
	{
		bool flag = false; // 标记：班级为空，2 属于 “其他键”
		if (Class_List.empty())
		{
			std::cout << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> （当前无班级）\n"
				<< "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 选择编辑方式：1.新增，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			Print_Class(); // 打印开课班级
			std::cout << "\n编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 选择编辑方式：1.新增，2.删除，按其他键取消...";
		}

		unsigned long long new_num; // switch 内接受输入
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增班级
			if (Teacher::_Get_Size()) // 教师列表不为空
			{
				std::cout << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 新增班级 -> 选择教师（输入序号）：\n\n";
				Teacher::_Print_All();
				std::cout << "\n或输入 0 新增教师：";
			}
			else
				std::cout << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 新增班级 -> 选择教师 -> 当前无教师，输入 0 新增教师：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Teacher::_Get_Size())
				std::cerr << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 新增班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0) // 创建班级
				Class::_New(this, Teacher::_Get_ptr(new_num - 1)); // 新增班级
			else // 新增教师并创建班级
			{
				Teacher* new_teacher = Teacher::_New(); // 在控制台新增教师
				Class::_New(this, new_teacher); // 直接创建班级
			}
			break;

		case '2': // 删除班级
			if (flag) // 当前无教师
				return;
			std::cout << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 删除班级 -> 选择班级（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Class_List.size())
				std::cerr << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 删除班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				delete Class_List[new_num - 1];
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑课程 -> " << Get_Name() << " -> 编辑开课班级 -> 按E/e继续编辑开课班级，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Course::Print_Class() const
{
	for (auto iter = Class_List.begin(); iter != Class_List.end(); iter++)
	{
		std::cout << iter - Class_List.begin() + 1 << '.';
		(*iter)->Print();
	}
}

void Course::Print() const
{
	std::cout << Get_Name()
		<< " -> 课程满分：" << Get_Full_Score() << std::endl;
	Print_Class();
}

void Course::Delete_Class(Class* class_ptr)
{
	Class_List.erase(std::find(class_ptr->Get_Course_ptr()->Class_List.begin(), class_ptr->Get_Course_ptr()->Class_List.end(), class_ptr));
}

const size_t Course::_Get_Size()
{
	return _List.size();
}

Course* const Course::_Get_ptr(const size_t& n)
{
	if (n < 0 || n >= _List.size())
	{
		std::cerr << "in function Course* const Course::_Get_ptr(const size_t& n):\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=_List.size()\n";
		return nullptr;
	}
	else
		return _List[n];
}

void Course::_Print_All()
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		std::cout << std::right << std::setw(3) << iter - _List.begin() + 1 << '.'  // 序号
			<< std::setw(25) << std::left << (*iter)->Get_Name() // 课程名
			<< "课程满分：" << std::setw(5) << (*iter)->Get_Full_Score(); // 课程满分

		if ((*iter)->Class_List.size()) // 班级列表不为空
		{
			std::cout << "开课教师：";
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				std::cout << (*iter_2)->Get_Teacher_ptr()->Get_Name() << " "; // 教师姓名
		}
		std::cout << std::endl;
	}
}

void Course::_Write_File(std::ofstream& file)
{
	file << "## 课程（总计：" << _List.size() << "）\n\n" // 标题
		<< "| 序号 | 课程名 | 授课教师 | 课程满分 |\n" // 表头
		<< "| - | - | - | - |\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // 序号
			<< " | " << (*iter)->Get_Name() << " | "; // 课程名
		if ((*iter)->Class_List.size()) // 班级列表不为空
		{
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				file << (*iter_2)->Get_Teacher_ptr()->Get_Name() << "  "; // 教师姓名
			file.seekp(-2, std::ios_base::cur); // 覆盖两个空格
		}
		file << " | " << (*iter)->Get_Full_Score() << " |\n"; // 课程满分
	}
	file << std::endl;
}

void Course::_Read_File(std::ifstream& file)
{
	int serial; // 序号
	char delimiter; // 分隔符
	std::string name; // 课程名
	double full_score; // 课程满分

	// 移动读指针到课程列表
	file.seekg(std::ios_base::beg); // 定位到文件头
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到标题
	if (file.peek() != '#')
		file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到课程列表标题
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "## 课程"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过空行
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| 序号 | 课程名 | 授课教师 | 课程满分 |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| - | - | - | - |"

	delimiter = file.get(); // 读入第一行首字符
	while (delimiter == '|')
	{
		file >> serial // 序号
			>> delimiter; // '|'
		file.get(); // ' '
		getline(file, name, '|'); // 姓名
		name.pop_back();
		file >> delimiter; // '|'
		file.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // 忽略教师名
		file >> full_score >> delimiter; // 读入课程满分
		file.get(); // 读入 '\n'
		delimiter = file.get(); // 读入下一行首字符
		Course::_New(name, full_score); // 创建课程
	}
}

Course::~Course()
{
	for (size_t i = Get_Class_Size(); i > 0; i--)
		delete Get_Class_ptr(i - 1); // 删除相关班级
	_List.erase(std::find(_List.begin(), _List.end(), this)); // 从课程列表中删除
	std::cout << "删除课程 -> 已删除课程 " << Get_Name() << std::endl;
}

std::ostream& operator<<(std::ostream& output, const Course& course_obj)
{
	output<< course_obj.Get_Name()
		<< " -> 课程满分：" << course_obj.Get_Full_Score() << std::endl;
	for (auto iter = course_obj.Class_List.begin(); iter != course_obj.Class_List.end(); iter++)
		output << iter - course_obj.Class_List.begin() + 1 << '.'<<(*iter);
	return output;
}