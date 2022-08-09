#include <conio.h>
#include <iomanip>
#include <iostream>

#include "Class.h"
#include "Course.h"
#include "Teaching_Assistant.h"

std::vector<Teaching_Assistant*> Teaching_Assistant::_List;

Teaching_Assistant::Teaching_Assistant(const std::string& name, const std::string& id, const std::string& faculty, const Grade_Type grade) :
	Person(name, id, faculty), Student(name, id, faculty, grade, true), Teacher(name, id, faculty,true) {}

Teaching_Assistant* const Teaching_Assistant::_New(std::string name, std::string id, std::string faculty, Grade_Type grade)
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "新增助教 -> error（学生已存在）\n";
			std::cerr << "(warning) in function Teaching_Assistant* const Teaching_Assistant::_New(std::string name, std::string id, std::string faculty, Grade_Type grade):\n"
				<< "\tduplicate id already exists in student list, a nullptr has been returned.\n"
				<< "\tcause: (*iter)->Get_ID() == id\n";
			return nullptr;
		}

	Teaching_Assistant* teaching_assistant_ptr = new Teaching_Assistant(name, id, faculty, grade);
	_List.push_back(teaching_assistant_ptr); // 添加到助教列表
	Student::_List.push_back(teaching_assistant_ptr); // 添加到学生列表
	std::cout << "新增助教 -> 已新增助教 " << name << "，学号：" << id << " 院系：" << faculty << " 年级：";
	switch (grade)
	{
	case undergraduate_1:
		std::cout << "本科一年级\n";
		break;
	case undergraduate_2:
		std::cout << "本科二年级\n";
		break;
	case undergraduate_3:
		std::cout << "本科三年级\n";
		break;
	case undergraduate_4:
		std::cout << "本科四年级\n";
		break;
	case master_1:
		std::cout << "硕士研究生一年级\n";
		break;
	case master_2:
		std::cout << "硕士研究生二年级\n";
		break;
	case master_3:
		std::cout << "硕士研究生三年级\n";
		break;
	case PhD_1:
		std::cout << "博士研究生一年级\n";
		break;
	case PhD_2:
		std::cout << "博士研究生二年级\n";
		break;
	case PhD_3:
		std::cout << "博士研究生三年级\n";
	}
	return teaching_assistant_ptr;
}

void Teaching_Assistant::Edit()
{
	while (true)
	{
		std::cout << Get_Name() << " -> 选择修改项：1.姓名，2.学号，3.院系，4.成绩记录，5.辅导班级，按其他键取消...";
		std::string new_info; // switch 内接受输入
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 修改姓名
			std::cout << "\n新姓名：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Name(new_info);
			break;

		case '2': // 修改学号
			std::cout << "\n新学号：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_ID(new_info);
			break;

		case '3': // 修改院系
			std::cout << "\n新院系：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Faculty(new_info);
			break;

		case '4': // 修改成绩记录
			Student::Edit_Record();
			break;

		case '5': // 修改辅导班级
			Edit_Class();
			break;

		default: // 取消
			return;
		}
		std::cout << Get_Name() << " -> 按E/e继续修改助教信息，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Teaching_Assistant::Print() const
{
	Person::Print();
	Student::Print_Record();
	std::cout << "该学生为助教，辅导班级列表：\n";
	Teacher::Print_Class();
}

const size_t Teaching_Assistant::_Get_Size()
{
	return _List.size();
}

void Teaching_Assistant::_Print_All()
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		std::cout << iter - _List.begin() + 1 << '.'  // 序号
			<< std::setw(10) << std::left << (*iter)->Get_Name() // 助教姓名
			<< "学号：" << std::setw(15) << std::left << (*iter)->Get_ID() // 助教学号
			<< "院系：" << std::setw(10) << std::left << (*iter)->Get_Faculty(); // 院系

		if ((*iter)->Class_List.size()) // 班级列表不为空
		{
			std::cout << "辅导班级：\n";
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				std::cout <<"\t\t\t\t\t\t\t" << iter_2 - (*iter)->Class_List.begin() + 1 << '.' // 序号
				<< "课程 " << (*iter_2)->Get_Course_ptr()->Get_Name()// 课程名
				<< "，教师 " << (*iter_2)->Get_Teacher_ptr()->Get_Name()// 教师名
				<< std::endl;
		}
	}
}

void Teaching_Assistant::_Add_Teaching_Assistant(Teaching_Assistant* const teaching_assistant_ptr)
{
	if (teaching_assistant_ptr == nullptr)
		std::cerr << "in function void Teaching_Assistant::_Add_Teaching_Assistant(const Teaching_Assistant* const teaching_assistant_ptr):\n"
		<< "\tadd teaching assistant failed.\n"
		<< "\tcause: teaching_assistant_ptr == nullptr\n";
	else
		_List.push_back(teaching_assistant_ptr);
}

Teaching_Assistant::~Teaching_Assistant()
{
	_List.erase(std::find(_List.begin(), _List.end(), this)); // 从助教列表中删除
	std::cout << "删除助教 -> 已删除助教 " << Get_Name() << std::endl;
}

void Teaching_Assistant::_Write_File(std::ofstream& file)
{
	file << "## 助教（总计：" << _List.size() << "）\n\n" // 标题
		<< "| 序号 | 姓名 | 学号 | 院系 | 年级 | 辅导班级（序号） |\n" // 表头
		<< "| - | - | - | - | - | - |\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // 学生序号
			<< " | " << (*iter)->Get_Name() // 学生姓名
			<< " | " << (*iter)->Get_ID() // 学号
			<< " | " << (*iter)->Get_Faculty() // 院系
			<< " | ";
		switch ((*iter)->Get_Grade()) // 年级代码和年级名称
		{
		case undergraduate_1:
			file << "` 11 `  本科一年级";
			break;
		case undergraduate_2:
			file << "` 12 `  本科二年级";
			break;
		case undergraduate_3:
			file << "` 13 `  本科三年级";
			break;
		case undergraduate_4:
			file << "` 14 `  本科四年级";
			break;
		case master_1:
			file << "` 21 `  硕士研究生一年级";
			break;
		case master_2:
			file << "` 22 `  硕士研究生二年级";
			break;
		case master_3:
			file << "` 23 `  硕士研究生三年级";
			break;
		case PhD_1:
			file << "` 31 `  博士研究生一年级";
			break;
		case PhD_2:
			file << "` 32 `  博士研究生二年级";
			break;
		case PhD_3:
			file << "` 33 `  博士研究生三年级";
		}

		if (!(*iter)->Class_List.empty()) // 辅导班级列表不为空
		{
			auto iter_2 = (*iter)->Class_List.begin();
			file << " | ` "<< (*iter_2)->Get_Serial_Number(); // 写入第一个序号
			iter_2++;
			for (; iter_2 != (*iter)->Class_List.end(); iter_2++)
				file << " ` 、 ` "<<(*iter_2)->Get_Serial_Number() ;
			file << " ` |\n";
		}
		else
			file << " | |\n";
	}
	file << std::endl;
}

void Teaching_Assistant::_Read_File(std::ifstream& file)
{
	int serial; // 学生序号
	char delimiter; // 分隔符
	std::string name; // 姓名
	std::string id; // 学号
	std::string faculty; // 院系
	int grade; // 年级
	unsigned long long num_class; // 班级序号

	// 移动读指针到学生列表
	file.seekg(std::ios_base::beg); // 定位到文件头
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到标题
	if (file.peek() != '#')
		file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到课程列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到教师列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到班级列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到学生列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到助教列表标题
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "## 助教"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过空行
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| 序号 | 姓名 | 学号 | 院系 | 年级 |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| - | - | - | - | - |"

	delimiter = file.get(); // 读入第一行首字符
	while (delimiter == '|')
	{
		file >> serial // 序号
			>> delimiter // '|'
			>> name // 学生姓名
			>> delimiter // '|'
			>> id // 学号
			>> delimiter // '|'
			>> faculty // 院系
			>> delimiter // '|'
			>> delimiter // '`'
			>> grade; // 年级代码
		auto iter = _List.begin();
		for (; iter != _List.end(); iter++)
			if ((*iter)->Get_ID() == id) // 找到助教
				break;
		if (iter == _List.end()) // 未找到助教
		{
			std::cerr << "从文件导入数据 -> error（助教 " << name << " 不在学生列表中）\n";
			getline(file, name); // 切换至下一行
			break;
		}

		file.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // 定位到辅导班级列表
		file >> delimiter; // 读入 '`' 或 '|'
		while(delimiter=='`')
		{
			file >> num_class // 班级序号
				>> delimiter; // '`'
			(*iter)->Add_Class(Class::_Get_ptr(num_class - 1));
			file.get(); // 读入 ' '
			if (file.peek() == '|')
			{
				file.get(); // '|'
				break;
			}
			else
			{
				getline(file, name, ' '); // 读入 '、'
				delimiter = file.get(); // 读入 '`' 
			}
		}
		file.get(); // 读入 '\n'
		delimiter = file.get(); // 读入下一行首字符
	}
}

void Teaching_Assistant::Edit_ID(const std::string& id)
{
	for (auto iter = Student::_List.begin(); iter != Student::_List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "编辑助教 -> error（学生已存在）\n";
			return;
		}
	ID = id;
	std::cout << "编辑助教 -> 已修改学号为 " << id << std::endl;
}

void Teaching_Assistant::Edit_Class()
{
	if (Class::_Get_Size() == 0)
	{
		std::cerr << "编辑助教-> " << Get_Name() << " -> 编辑辅导班级信息 -> error（当前无班级）";
		return;
	}
	while (true)
	{
		bool flag = false; // 标记：班级为空，2 属于 “其他键”
		if (Teacher::Class_List.empty())
		{
			std::cout << "编辑助教-> " << Get_Name() << " -> 编辑辅导班级信息 -> （当前无班级）\n"
				<< "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 选择编辑方式：1.添加，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			Teacher::Print_Class(); // 打印辅导班级
			std::cout << "\n编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 选择编辑方式：1.添加，2.删除，按其他键取消...";
		}
		unsigned long long new_num; // switch 内接受输入
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增班级
			std::cout << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 添加班级（输入序号）：\n\n";
			Class::_Print_All(); // 打印所有班级的课程、教师名
			std::cout << "\n或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > Class::_Get_Size())
				std::cerr << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 添加班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
			{
				Class* class_ptr = Class::_Get_ptr(new_num - 1);
				Teacher::Class_List.push_back(class_ptr);
				std::cerr << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 添加班级 -> 已添加班级：课程 "
					<< class_ptr->Get_Course_ptr()->Get_Name()
					<< "，教师 " << class_ptr->Get_Teacher_ptr()->Get_Name()
					<< std::endl;
			}
			break;

		case '2': // 删除班级
			if (flag) // 当前无课程
				return;
			std::cout << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 删除班级 -> （输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Teacher::Class_List.size())
				std::cerr << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 删除班级 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
			{
				auto iter = Teacher::Class_List.begin() + new_num - 1;
				std::cout << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 删除班级 -> 已删除班级：课程 "
					<< (*iter)->Get_Course_ptr()->Get_Name()
					<< "，教师 " << (*iter)->Get_Teacher_ptr()->Get_Name()
					<< std::endl;
				Teacher::Class_List.erase(iter); // 仅从列表中移除
			}
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑助教 -> " << Get_Name() << " -> 编辑辅导班级信息 -> 按E/e继续编辑辅导班级，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}

}