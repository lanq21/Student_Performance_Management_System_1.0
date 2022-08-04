#include <conio.h>
#include <iomanip>
#include <iostream>

#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "Teaching_Assistant.h"

std::vector<Student*> Student::_List;

Student::Student(const std::string& name, const std::string& id, const std::string& faculty, const Grade_Type& grade, bool is_ta) :
	Person(name, id, faculty), Grade(grade), Is_TA(is_ta) {}

Student* const Student::_New(std::string name, std::string id, std::string faculty, Grade_Type grade, bool is_ta)
{
	static std::string default_faculty = "电子系"; // 默认院系
	static Grade_Type default_grade = undergraduate_1; // 默认年级
	std::string grade_input; // 输入年级
	bool flag = false; // 标记：从控制台构造
	if (name.empty())
		flag = true;
	if (flag)
	{
		// 设置姓名
		std::cout << "新增学生 -> 学生姓名：";
		std::cin >> name;

		// 设置学号
		std::cout << "新增学生 -> 学号：";
		std::cin >> id;
		std::cin.ignore();
	}
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "新增学生 -> error（学生已存在）\n";
			return (*iter);
		}
	if (flag)
	{
		// 设置院系
		std::cout << "新增学生 -> 院系（按 Enter 自动填充 " << default_faculty << "）：";
		getline(std::cin, faculty);
		if (faculty.empty()) // 输入 Enter
			faculty = default_faculty; // 使用默认院系
		else
			default_faculty = faculty; // 更新默认院系

		// 设置年级
		std::cout << "新增学生 -> 年级代码：本科一年级 输入 11，二年级 输入 12 ...\n"
			<< "\t\t      硕士研究生一年级 输入 21，二年级 输入 22 ...\n"
			<< "\t\t      博士研究生一年级 输入 31，二年级 输入 32 ...\n"
			<< "新增学生 -> 年级（按 Enter 自动填充 " << default_grade << "）：";
		getline(std::cin, grade_input);
		if (grade_input.empty()) // 输入 Enter
			grade = default_grade; // 使用默认年级
		else
		{
			grade = Grade_Type(atoi(grade_input.c_str())); // 使用输入年级
			default_grade = grade; // 更新默认年级
		}
	}
	Student* student_ptr;
	if (flag) // 在控制台选择是否为助教
	{
		std::cout << "新增学生 -> 按 E/e 设置为助教，按其他键取消：";
		char input = _getch();
		std::cout << std::endl;
		if (input == 'E' || input == 'e')
			is_ta = true;
		else is_ta = false;
	}

	if (is_ta == true) // 是助教
	{
		Teaching_Assistant* teaching_assistant_ptr = Teaching_Assistant::_New(name, id, faculty, grade);
		student_ptr = teaching_assistant_ptr;
	}
	else // 不是助教
	{
		student_ptr = new Student(name, id, faculty, grade, false);
		_List.push_back(student_ptr);
		std::cout << "新增学生 -> 已新增学生 " << name << "，学号：" << id << " 院系：" << faculty << " 年级：";
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
	}
	return student_ptr;
}

const Grade_Type Student::Get_Grade() const
{
	return Grade;
}

const bool Student::Get_is_TA() const
{
	return Is_TA;
}

void Student::_Edit_All()
{
	while (true)
	{
		bool flag = false; // 标记：学生列表为空，2、3 属于 “其他键”
		if (_List.empty())
		{
			std::cout << "编辑学生 -> （当前无学生）\n"
				<< "编辑学生 -> 选择编辑方式：1.新增，按其他键取消...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // 打印全部学生
			std::cout << "\n编辑学生 -> 选择编辑方式：1.新增，2.修改，3.删除，按其他键取消...";
		}

		Student* student_ptr;
		unsigned long long new_num; // switch 内接受输入
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 新增学生
			student_ptr = Student::_New();
			if (student_ptr != nullptr)
			{
				std::cout << "按 Enter 添加成绩信息，按其他键取消...";
				input = _getch();
				std::cout << std::endl;
				if (input == '\r')
					student_ptr->Edit_Record();
			}
			break;

		case '2': // 修改学生
			if (flag) // 当前无学生
				return;
			std::cout << "编辑学生  -> 选择学生（输入序号）或 输入 0 取消：";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > _List.size())
				std::cerr << "编辑学生 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				_List[new_num - 1]->Edit();
			break;

		case '3': // 删除学生
			if (flag) // 当前无学生
				return;
			std::cout << "删除学生（输入序号）或 输入 0 取消：\n";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > _List.size())
				std::cerr << "删除学生 -> error（序号超出列表范围）\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // 取消
			return;
		}
		std::cout << "编辑学生 -> 按 E/e 继续编辑学生，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Student::Add_Record(Class* const class_ptr, const double& score)
{
	if (class_ptr == nullptr)
	{
		std::cerr << "in function void Student::Add_Record(Class* const class_ptr, const double& score):\n"
			<< "\tadd record failed.\n"
			<< "\tcause: class_ptr == nullptr\n";
		return;
	}
	else
	{
		Record_List.push_back(Record(class_ptr, score)); // 添加成绩记录
		class_ptr->Add_Student(this); // 对应班级添加学生
		std::cout << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> "
			<< class_ptr->Get_Course_ptr()->Get_Name() << "成绩已添加\n";
	}
}

void Student::Add_Record(Course* const course_ptr)
{
	if (course_ptr == nullptr)
	{
		std::cerr << "in function void Student::Add_Record(Course* const course_ptr):\n"
			<< "\tadd record failed.\n"
			<< "\tcause: course_ptr == nullptr\n";
		return;
	}
	else
	{
		unsigned long long class_serial; // 班级序号
		double score; // 成绩

		if (course_ptr->Get_Class_Size()) // 班级列表不为空
		{
			std::cout << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> "
				<< course_ptr->Get_Name() << " -> 选择班级（输入序号）：\n\n";
			course_ptr->Print_Class();
			std::cout << "\n或 输入 0 取消：";
			std::cin >> class_serial;
			std::cin.ignore();

			if (class_serial > course_ptr->Get_Class_Size())
				std::cerr << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> "
				<< course_ptr->Get_Name() << " -> 选择班级 -> error（序号超出列表范围）\n";
			else if (class_serial > 0)
			{
				std::cout << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> "
					<< course_ptr->Get_Name() << " 成绩：";
				std::cin >> score;
				std::cin.ignore();
				Add_Record(course_ptr->Get_Class_ptr(class_serial - 1), score); // 添加成绩记录
			}
		}
		else
			std::cout << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> "
			<< course_ptr->Get_Name() << " -> error（当前无班级）\n";
	}
}

void Student::Edit_ID(const std::string& id)
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "编辑学生 -> error（学生已存在）\n";
			return;
		}
	ID = id;
	std::cout << "编辑学生 -> 已修改学号为 " << id << std::endl;
}

void Student::Edit_Record()
{
	bool flag_all = false; // 标记：可使用 Enter 添加全部课程
	if (Record_List.empty())
		flag_all = true;

	while (true)
	{
		bool flag_empty = false; // 标记：成绩记录为空，2、3 属于 “其他键”
		if (Record_List.empty()) // 成绩记录为空
		{
			std::cout << Get_Name() << " -> 编辑成绩记录 -> （暂无成绩记录）\n"
				<< Get_Name() << " -> 编辑成绩记录 -> 选择编辑方式：1.新增，按其他键取消...";
			flag_empty = true;
		}
		else
		{
			std::cout << std::endl;
			Print_Record();
			std::cout << std::endl << Get_Name() << " -> 编辑成绩记录 -> 选择编辑方式：1.新增，2.修改，3.删除，按其他键取消...";
		}

		char input = _getch(); // 功能选项
		std::cout << std::endl;

		// switch 内接受输入
		unsigned long long new_num_1;
		int new_num_2;
		std::string new_string;

		switch (input)
		{
		case '1': // 新增成绩记录
			if (Course::_Get_Size()) // 课程列表不为空
			{
				std::cout << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> 选择课程（输入序号）：\n\n";
				Course::_Print_All();
				std::cout << "\n或";
				if (flag_all)
					std::cout << "按 Enter 添加全部课程，";
				std::cout << "输入 0 取消：";

				if (flag_all)
				{
					getline(std::cin, new_string);
					if (new_string.empty()) // 为全部有开课班级的课程添加成绩
					{
						for (int i = 0; i < Course::_Get_Size(); i++)
							if (Course::_Get_ptr(i)->Get_Class_Size()) // 有开课班级
								Add_Record(Course::_Get_ptr(i)); // 在控制台添加成绩记录
						flag_all = false;
						break;
					}
					else
						new_num_1 = atoi(new_string.c_str()); // 接受课程序号
				}
				else
				{
					std::cin >> new_num_1; // 课程序号
					std::cin.ignore();
				}

				if (new_num_1 > Course::_Get_Size())
					std::cerr << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> 选择课程 -> error（序号超出列表范围）\n";
				else if (new_num_1 > 0)
					Add_Record(Course::_Get_ptr(new_num_1 - 1)); // 在控制台添加成绩记录
			}
			else
				std::cerr << Get_Name() << " -> 编辑成绩记录 -> 新增成绩记录 -> （当前无课程）\n";
			break;

		case '2': // 修改成绩记录
			if (flag_empty)
				return;
			std::cout << Get_Name() << " -> 编辑成绩记录 -> 修改成绩记录 -> 选择记录（输入序号）或 输入 0 取消：";
			std::cin >> new_num_1;
			std::cin.ignore();

			if (new_num_1 > Record_List.size())
				std::cerr << Get_Name() << " -> 编辑成绩记录 -> 修改成绩记录 -> error（序号超出列表范围）\n";
			else if (new_num_1 > 0)
			{
				std::cout << Get_Name() << " -> 编辑成绩记录 -> 修改成绩记录 -> 新成绩：";
				std::cin >> new_num_2;
				std::cin.ignore();
				if (new_num_2 > Record_List[new_num_1 - 1].Get_Class_ptr()->Get_Course_ptr()->Get_Full_Score())
					std::cerr << Get_Name() << " -> 编辑成绩记录 -> 修改成绩记录 -> error（输入成绩大于课程满分）\n";
				else
					Record_List[new_num_1 - 1].Edit_Score(new_num_2);
				std::cout << Get_Name() << " -> 编辑成绩记录 -> 修改成绩记录 -> 成绩已修改为 " << new_num_2 << std::endl;
			}
			break;

		case '3': // 删除成绩记录
			if (flag_empty)
				return;
			std::cout << Get_Name() << " -> 编辑成绩记录 -> 删除成绩记录 -> 选择记录（输入序号）或 输入 0 取消：";
			std::cin >> new_num_1;
			std::cin.ignore();

			if (new_num_1 > Record_List.size())
				std::cerr << Get_Name() << " -> 编辑成绩记录 -> 删除成绩记录 -> error（序号超出列表范围）\n";
			else if (new_num_1 > 0)
			{
				Delete_Record(new_num_1); // 删除成绩记录
				std::cout << Get_Name() << " -> 编辑成绩记录 -> 删除成绩记录 -> 记录已删除\n";
			}
			break;

		default: // 取消
			return;
		}
		std::cout << Get_Name() << " -> 编辑成绩记录 -> 按 E/e 继续编辑成绩记录，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Student::Delete_Record(const unsigned long long& n)
{
	Record_List[n - 1].Get_Class_ptr()->Delete_Student(this); // 从班级中删除
	Record_List.erase(Record_List.begin() + n - 1); // 从成绩记录列表中删除
}

void Student::Edit()
{
	while (true)
	{
		std::cout << Get_Name() << " -> 选择修改项：1.姓名，2.学号，3.院系，4.成绩记录，按其他键取消...";
		std::string new_info; // switch 内接受输入
		char input = _getch(); // 功能选项
		std::cout << std::endl;

		switch (input)
		{
		case '1': // 修改学生姓名
			std::cout << Get_Name() << " -> 新姓名：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Name(new_info);
			break;

		case '2': // 修改学号
			std::cout << Get_Name() << " -> 新学号：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_ID(new_info);
			break;

		case '3': // 修改院系
			std::cout << Get_Name() << " -> 新院系：";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Faculty(new_info);
			break;

		case '4': // 编辑成绩记录
			Edit_Record();
			break;

		default: // 取消
			return;
		}
		std::cout << Get_Name() << " -> 按E/e继续修改学生信息，按其他键结束...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Student::Print() const
{
	Person::Print(); // 打印姓名、学号、院系
	Print_Record(); // 打印成绩记录
}

const double Student::Get_Score(const Class* const class_ptr)
{
	auto iter = Record_List.begin();
	for (; iter != Record_List.end(); iter++)
		if ((*iter).Get_Class_ptr() == class_ptr)
			break;
	if (iter == Record_List.end()) // 未找到记录
	{
		std::cerr << "in function const double Student::Get_Score(Class* const class_ptr):\n"
			<< "the record does not exist, a zero score has been returned.\n"
			<< "cause: iter == Record_List.end()\n";
		return 0;
	}
	else
		return (*iter).Get_Score();
}

const double Student::Get_Score(const Course* const course_ptr)
{
	auto iter = Record_List.begin();
	for (; iter != Record_List.end(); iter++)
		if ((*iter).Get_Class_ptr()->Get_Course_ptr() == course_ptr)
			break;
	if (iter == Record_List.end()) // 未找到记录
	{
		std::cerr << "in function const double Student::Get_Score(Course* const course_ptr):\n"
			<< "the record does not exist, a zero score has been returned.\n"
			<< "cause: iter == Record_List.end()\n";
		return 0;
	}
	else
		return (*iter).Get_Score();
}

const size_t Student::_Get_Size()
{
	return _List.size();
}

Student* const Student::_Get_ptr(const size_t& n)
{
	if (n < 0 || n >= _List.size())
	{
		std::cerr << "in function Student* const Student::Get_Student_ptr(const int& n):\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=_List.size()\n";
		return nullptr;
	}
	else
		return _List[n];
}

void Student::_Print_All()
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		std::cout << iter - _List.begin() + 1 << '.'; // 打印序号
		if ((*iter)->Get_is_TA() == true)
			std::cout << std::setw(15) << "（助教）" + (*iter)->Get_Name();
		else
			std::cout << std::setw(10) << (*iter)->Get_Name(); // 打印姓名
		std::cout << "学号：" << std::setw(15) << std::left << (*iter)->Get_ID() // 打印学号
			<< "院系：" << std::setw(8) << std::left << (*iter)->Get_Faculty(); // 打印院系
		switch ((*iter)->Get_Grade()) // 打印年级
		{
		case undergraduate_1:
			std::cout << "年级：" << std::setw(16) << std::left << "本科一年级";
			break;
		case undergraduate_2:
			std::cout << "年级：" << std::setw(16) << std::left << "本科二年级";
			break;
		case undergraduate_3:
			std::cout << "年级：" << std::setw(16) << std::left << "本科三年级";
			break;
		case undergraduate_4:
			std::cout << "年级：" << std::setw(16) << std::left << "本科四年级";
			break;
		case master_1:
			std::cout << "年级：" << std::setw(16) << std::left << "硕士研究生一年级";
			break;
		case master_2:
			std::cout << "年级：" << std::setw(16) << std::left << "硕士研究生二年级";
			break;
		case master_3:
			std::cout << "年级：" << std::setw(16) << std::left << "硕士研究生三年级";
			break;
		case PhD_1:
			std::cout << "年级：" << std::setw(16) << std::left << "博士研究生一年级";
			break;
		case PhD_2:
			std::cout << "年级：" << std::setw(16) << std::left << "博士研究生二年级";
			break;
		case PhD_3:
			std::cout << "年级：" << std::setw(16) << std::left << "博士研究生三年级";
		}
		if (!(*iter)->Record_List.empty())
		{
			std::cout << "\n  成绩：";
			for (auto iter_2 = (*iter)->Record_List.begin(); iter_2 != (*iter)->Record_List.end(); iter_2++)
				std::cout << (*iter_2).Get_Class_ptr()->Get_Course_ptr()->Get_Name()
				<< " "
				<< (*iter_2).Get_Score()
				<< "  ";
			std::cout << std::endl;
		}
	}
}

void Student::_Score_Manage()
{
	while (true)
	{
		std::string id;
		std::cout << "学生成绩 -> 输入学号查询成绩，或按 Enter 取消：";
		getline(std::cin, id);
		if (id.empty()) // 输入了 Enter
			return;
		else
		{
			auto iter = _List.begin();
			for (; iter != _List.end(); iter++)
				if ((*iter)->Get_ID() == id)
					break;
			if (iter == _List.end()) // 未查找到学生
				std::cerr << "学生成绩 -> error（学生不存在）\n";
			else
			{
				std::cout << std::endl;
				(*iter)->Print(); // 打印信息和成绩
				std::cout << std::endl;
			}
		}
		std::cout << "学生成绩 -> 按 E/e 继续查询成绩，按其他键取消：";
		char input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // 结束编辑
			break;
	}
}

void Student::_Write_File(std::ofstream& file)
{
	size_t course_num = Course::_Get_Size(); // 课程指针
	double* grade_list = new double[course_num]; // 按照课程顺序的成绩列表
	size_t* class_serial_list = new size_t[course_num]{ 0 }; // 按照课程顺序的班级序号列表，0 表示无该课成绩

	file << "## 学生（总计：" << _List.size() << "）\n\n" // 标题
		<< "| 序号 | 姓名 | 学号 | 院系 | 年级 | "; // 表头
	for (int i = 0; i < course_num; i++)
		file << Course::_Get_ptr(i)->Get_Name() << " | ";
	file.seekp(-1, std::ios_base::cur); // 覆盖一个空格
	file << std::endl;

	for (int i = 0; i < course_num + 5; i++)
		file << "| - ";
	file << "|\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1; // 学生序号
		if ((*iter)->Is_TA == true)
			file << " | ` 助教 ` ";
		else
			file << " | ";
		file << (*iter)->Get_Name() // 学生姓名
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
		for (auto iter_2 = (*iter)->Record_List.begin(); iter_2 != (*iter)->Record_List.end(); iter_2++)
		{
			// 按课程顺序填充班级序号
			class_serial_list[(*iter_2).Get_Class_ptr()->Get_Course_ptr()->Get_Serial_Number() - 1] = (*iter_2).Get_Class_ptr()->Get_Serial_Number();
			// 按课程顺序填充成绩
			grade_list[(*iter_2).Get_Class_ptr()->Get_Course_ptr()->Get_Serial_Number() - 1] = (*iter_2).Get_Score();
		}
		for (int j = 0; j < course_num; j++)
		{
			if (class_serial_list[j] > 0) // 对应课程成绩不为空
				file << " | ` " << class_serial_list[j] << " ` " << grade_list[j]; // 班级序号和成绩
			else
				file << " |";
		}
		file << " |\n";
		for (int j = 0; j < course_num; j++)
			class_serial_list[j] = 0; // 重置班级序号列表
	}
	file << std::endl;

	delete[] class_serial_list;
	delete[] grade_list;
}

void Student::_Read_File(std::ifstream& file)
{
	int serial; // 学生序号
	char delimiter; // 分隔符
	std::string name; // 姓名
	std::string id; // 学号
	std::string faculty; // 院系
	int grade; // 年级
	bool is_ta = false; // 是否为助教
	unsigned long long num_class; // 班级序号
	double score; // 成绩
	size_t course_num = Course::_Get_Size(); // 课程数

	// 移动读指针到学生列表
	file.seekg(std::ios_base::beg); // 定位到文件头
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到课程列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到教师列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到班级列表标题
	file.get(); // 读入第二个'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // 定位到学生列表标题
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "## 学生"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过空行
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| 序号 | 姓名 | 学号 | 院系 | 年级 |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 跳过 "| - | - | - | - | - |"

	delimiter = file.get(); // 读入第一行首字符
	while (delimiter == '|')
	{
		file >> serial // 序号
			>> delimiter; // '|'

		delimiter = file.get(); // 读入 '|' 后的空格
		delimiter = file.peek(); // 查看 '`' 或 姓名的首字符
		if (delimiter == '`')
		{
			file.get(); // 读入 '`'
			file.ignore(std::numeric_limits<std::streamsize>::max(), '`'); // 定位到姓名
			is_ta = true;
		}
		file >> name // 学生姓名
			>> delimiter // '|'
			>> id // 学号
			>> delimiter // '|'
			>> faculty // 院系
			>> delimiter // '|'
			>> delimiter // '`'
			>> grade; // 年级代码
		Student* student = Student::_New(name, id, faculty, Grade_Type(grade), is_ta); // 创建学生
		file.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // 定位到首个课程的成绩记录
		for (int i = 0; i < course_num; i++)
		{
			delimiter = file.get(); // 读入 '|' 后的 ' ' 或 '\n'
			delimiter = file.get(); // 读入 '`' 或 '|'
			if (delimiter == '|') // 该课程无成绩
				continue;
			else
				file >> num_class // 班级序号
				>> delimiter // '`'
				>> score // 成绩
				>> delimiter; // '|'
			student->Add_Record(Class::_Get_ptr(num_class - 1), score);
		}
		file.get(); // 读入 '\n'
		delimiter = file.get(); // 读入下一行首字符
	}
}

Student::~Student()
{
	for (int i = 0; i < Record_List.size(); i++)
		Record_List[i].Get_Class_ptr()->Delete_Student(this); // 从班级的学生列表中删除
	Record_List.clear(); // 清空成绩列表
	_List.erase(std::find(_List.begin(), _List.end(), this)); // 从学生列表中删除
	std::cout << "删除学生 -> 已删除学生 " << Get_Name() << std::endl;
}

void Student::Print_Record() const
{
	if (Record_List.empty()) // 成绩列表为空
		return;
	else
	{
		std::cout << Get_Name() << " 成绩记录：" << std::endl;
		for (auto iter = Record_List.begin(); iter != Record_List.end(); iter++)
		{
			std::cout << (iter - Record_List.begin() + 1) << '.' // 序号
				<< (*iter).Get_Class_ptr()->Get_Course_ptr()->Get_Name() // 课程名
				<< "\t授课教师：" << (*iter).Get_Class_ptr()->Get_Teacher_ptr()->Get_Name() // 教师名
				<< "\t成绩：" << (*iter).Get_Score() // 成绩
				<< "\t班级排名：" << (*iter).Get_Class_ptr()->Get_Rank(this) // 班级排名
				<< std::endl;
		}
	}
}

void Student::Delete_Record(Class* const class_ptr)
{
	for (int i = 0; i < Record_List.size(); i++)
		if (Record_List[i].Get_Class_ptr() == class_ptr) // 查找到成绩记录
		{
			Record_List.erase(Record_List.begin() + i);
			return;
		}
}

Student::Record::Record(Class* const class_ptr, const double& score) :
	Class_ptr(class_ptr), Score(score) {}

Class* const Student::Record::Get_Class_ptr() const
{
	return Class_ptr;
}

const double Student::Record::Get_Score() const
{
	return Score;
}

void Student::Record::Edit_Score(const double& score)
{
	Score = score;
}
