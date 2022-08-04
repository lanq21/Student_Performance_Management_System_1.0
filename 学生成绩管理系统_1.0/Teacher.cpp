#include <conio.h>
#include <iomanip>
#include <iostream>

#include "Class.h"
#include "Course.h"
#include "Teacher.h"

std::vector<Teacher*> Teacher::_List;

Teacher::Teacher(const std::string& name, const std::string& id, const std::string faculty, const bool& is_ta) :
	Person(name, id, faculty), is_TA(is_ta) {}

void Teacher::Edit_ID(const std::string& id)
{
	// 检查重复项
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "编辑教师 -> error（教师已存在）\n";
			return;
		}
	ID = id;
	std::cout << "编辑教师 -> 已修改教师编号为 " << id << std::endl;
}

Teacher* const Teacher::_New(std::string name, std::string id, std::string faculty)
{
	static std::string default_faculty = "电子系"; // 默认院系
	bool flag = false; // 标记：从控制台新建
	if (name.empty()) // 从控制台新建，使用缺省形参
		flag = true;

	if (flag)
	{
		// 设置姓名
		std::cout << "新增教师 -> 教师姓名：";
		std::cin >> name;

		// 设置教师编号
		std::cout << "新增教师 -> 教师编号：";
		std::cin >> id;
		std::cin.ignore();
	}

	// 检查重复项
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "新增教师 -> error（教师已存在）\n";
			return (*iter);
		}
	if (flag)
	{
		// 设置院系
		std::cout << "新增教师 -> 院系（按 Enter 自动填充 " << default_faculty << "）：";
		getline(std::cin, faculty);
		if (faculty.empty()) // 输入了 Enter
			faculty = default_faculty; // 使用默认院系
		else
			default_faculty = faculty; // 更新默认院系
	}
	Teacher* teacher_ptr = new Teacher(name, id, faculty,false);
	_List.push_back(teacher_ptr); // 添加到教师列表
	std::cout << "新增教师 -> 已新增教师 " << name << "，编号：" << id << " 院系：" << faculty << std::endl;

	return teacher_ptr;
}

const size_t Teacher::Get_Serial_Number() const
{
	return std::find(_List.begin(), _List.end(), this) - _List.begin() + 1;
}

void Teacher::Edit_All()
{
	while (true)
	{
		bool flag = false; // 标记：教师列表为空，2、3 属于 “其他键”
		if (_List.empty())
		{
			std::cout << "编辑教师 -> （当前无教师）\n"
				<< "编辑教师 -> 选择编辑方式：1.新增，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // 打印全部教师
			std::cout << "\n编辑教师 -> 选择编辑方式：1.新增，2.修改，3.删除，按其他键取消...";
		}

		unsigned long long new_num; // switch 内接受输入
		Teacher* teacher_ptr;
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增教师
			teacher_ptr = Teacher::_New(); // 在控制台新增课程
			std::cout << "新增教师 -> 按 Enter 编辑开课班级，按其他键取消：";
			input = _getch();
			std::cout << std::endl;
			if (input == '\r')
				teacher_ptr->Edit_Class();
			break;

		case '2': // 修改教师
			if (flag) // 当前无教师
				return;
			std::cout << "编辑教师  -> 选择教师（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "编辑教师 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				_List[new_num - 1]->Edit();
			break;

		case '3': // 删除教师
			if (flag) // 当前无教师
				return;
			std::cout << "删除教师（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "删除教师 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑教师 -> 按E/e继续编辑教师，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Teacher::Add_Class(Class* const class_ptr)
{
	if (class_ptr == nullptr)
	{
		std::cerr << "in function void Teacher::Add_Class(Class* const class_ptr):\n"
			<< "\tadd class failed.\n"
			<< "\tcause: class_ptr == nullptr\n";
		return;
	}
	else
		Class_List.push_back(class_ptr);
}

Teacher::~Teacher()
{
	if (!is_TA)
	{
		Class::Delete(this); // 删除相关班级
		_List.erase(std::find(_List.begin(), _List.end(), this)); // 从教师列表中删除
		std::cout << "删除教师 -> 已删除教师 " << Get_Name() << std::endl;
	}
}

void Teacher::Edit_Class()
{
	while (true)
	{
		bool flag = false; // 标记：班级为空，2 属于 “其他键”
		if (Class_List.empty())
		{
			std::cout << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> （当前无班级）\n"
				<< "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 选择编辑方式：1.新增，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			Print_Class(); // 打印授课班级
			std::cout << "\n编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 选择编辑方式：1.新增，2.删除，按其他键取消...";
		}

		unsigned long long new_num; // switch 内接受输入
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增班级
			if (Course::_Get_Size()) // 课程列表不为空
			{
				std::cout << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 新增班级 -> 选择课程（输入序号）：\n\n";
				Course::_Print_All();
				std::cout << "\n或输入 0 新增课程：";
			}
			std::cout << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 新增班级 -> 选择课程 -> 当前无课程，输入 0 新增课程：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Course::_Get_Size())
				std::cerr << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 新增班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0) // 创建班级
				Class::_New(Course::_Get_ptr(new_num - 1), this);
			else
			{
				Course* new_course = Course::_New(); // 在控制台新建课程
				Class::_New(new_course, this); // 直接新建班级
			}
			break;

		case '2': // 删除班级
			if (flag) // 当前无课程
				return;
			std::cout << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 删除班级 -> 选择班级（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Class_List.size())
				std::cerr << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 删除班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				delete Class_List[new_num - 1];
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑教师 -> " << Get_Name() << " -> 编辑授课班级信息 -> 按E/e继续编辑授课班级，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Teacher::Edit()
{
	while (true)
	{
		std::cout << "编辑教师 -> " << Get_Name() << " -> 选择修改项：1.姓名，2.教师编号，3.院系，4.授课班级，按其他键取消...";
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		std::string new_info; // 在 switch 内接受输入

		switch (input)
		{
		case '1': // 修改姓名
			std::cout << "编辑教师 -> " << Get_Name() << " -> 新姓名：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Name(new_info);
			break;

		case '2': // 修改教师编号
			std::cout << "编辑教师 -> " << Get_Name() << " -> 新编号：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_ID(new_info);
			break;

		case '3': // 修改院系
			std::cout << "编辑教师 -> " << Get_Name() << " -> 新院系：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Faculty(new_info);
			break;

		case '4': // 编辑班级
			Edit_Class();
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑教师 -> " << Get_Name() << " -> 按E/e继续修改教师信息，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Teacher::Print_Class() const
{
	for (auto iter = Class_List.begin(); iter != Class_List.end(); iter++)
	{
		std::cout << iter - Class_List.begin() + 1 << '.';
		(*iter)->Print();
	}
}

void Teacher::Print() const
{
	Person::Print();
	Print_Class();
}

Teacher* const Teacher::_Get_ptr(const size_t& n)
{
	if (n < 0 || n >= _Get_Size())
	{
		std::cerr << "in function Teacher* const Teacher::_Get_ptr(const size_t& n):\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=_Get_Size()\n";
		return nullptr;
	}
	else
		return _List[n];
}

void Teacher::Delete_Class(Class* class_ptr)
{
	Class_List.erase(std::find(class_ptr->Get_Teacher_ptr()->Class_List.begin(), class_ptr->Get_Teacher_ptr()->Class_List.end(), class_ptr));
}

size_t Teacher::Get_Class_Size() const
{
	return Class_List.size();
}

Class* const Teacher::Get_Class_ptr(const int& n)
{
	if (n < 0 || n >= Class_List.size())
	{
		std::cerr << "in function Class* const Teacher::Get_Class_ptr(const int& n):\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=Class_List.size()\n";
		return nullptr;
	}
	else
		return Class_List[n];
}

const size_t Teacher::_Get_Size()
{
	return _List.size();
}

void Teacher::_Print_All()
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		std::cout << iter - _List.begin() + 1 << '.'  // 序号
			<< std::setw(10) << std::left << (*iter)->Get_Name() // 教师姓名
			<< "编号：" << std::setw(15) << std::left << (*iter)->Get_ID() // 教师编号
			<< "院系：" << std::setw(10) << std::left << (*iter)->Get_Faculty(); // 院系

		if ((*iter)->Class_List.size()) // 班级列表不为空
		{
			std::cout << "教授课程：";
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				std::cout << (*iter_2)->Get_Course_ptr()->Get_Name() << " "; // 教授课程
		}
		std::cout << std::endl;
	}
}

void Teacher::_Write_File(std::ofstream& file)
{
	file << "## 教师（总计：" << _List.size() << "）\n\n" // 标题
		<< "| 序号 | 姓名 | 教师编号 | 院系 | 教授课程 |\n" // 表头
		<< "| - | - | - | - | - |\n";
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // 序号
			<< " | " << (*iter)->Get_Name() // 教师名
			<< " | " << (*iter)->Get_ID() // 教师编号
			<< " | " << (*iter)->Get_Faculty() << " | "; // 院系
		for (int j = 0; j < (*iter)->Class_List.size(); j++)
			file << (*iter)->Class_List[j]->Get_Course_ptr()->Get_Name() << "  "; // 教授课程
		file.seekp(-2, std::ios_base::cur); // 覆盖两个空格
		file << " |\n";
	}
	file << std::endl;
}

void Teacher::_Read_File(std::ifstream& file)
{
	int serial; // 序号
	char delimiter; // 分隔符
	std::string name; // 教师姓名
	std::string id; // 教师编号
	std::string faculty; // 院系

	// 移动读指针到课程列表
	file.seekg(std::ios_base::beg); // 定位到文件头
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到课程列表标题
	file.get(); // 读入第二个 '#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到教师列表标题
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 '## 教师'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过空行
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 '| 序号 | 姓名 | 教师编号 | 院系 | 教授课程 |'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 '| - | - | - | - | - |'

	delimiter = file.get(); // 读入第一行首字符
	while (delimiter == '|')
	{
		file >> serial // 序号
			>> delimiter // '|'
			>> name // 教师姓名
			>> delimiter // '|'
			>> id // 教师编号
			>> delimiter // '|'
			>> faculty // 院系
			>> delimiter; // '|'
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略教授课程
		delimiter = file.get(); // 读入下一行首字符
		Teacher::_New(name, id, faculty);
	}
}
