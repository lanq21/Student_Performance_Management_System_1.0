#include <conio.h>
#include <fstream>

#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "Teaching_Assistant.h"

/// <summary>
/// 从控制台添加数据
/// </summary>
void Console()
{
	char input; // 功能选项
	while (true)
	{
		std::cout << "查    看 -> 1.课程列表    2.教师列表    3.班级列表    4.学生列表\n"
			<< "编    辑 -> 5.课程信息    6.教师信息    7.班级信息    8.学生信息\n"
			<< "成绩记录 -> 9.课程成绩表  0.学生成绩单"
			<< "    或 按其他键取消...";
		input = _getch();
		std::cout << std::endl << std::endl;

		// switch 内接受输入
		std::string new_info;

		switch (input)
		{
		case '1':
			std::cout << "查看课程：\n";
			if (Course::_Get_Size() == 0)
				std::cerr << "查看课程 -> （当前无课程）\n";
			else
				Course::_Print_All();
			std::cout << std::endl;
			break;
		case '2':
			std::cout << "查看教师：\n";
			if (Teacher::_Get_Size() == 0)
				std::cerr << "查看教师 -> （当前无教师）\n";
			else
			Teacher::_Print_All();
			std::cout << std::endl;
			break;
		case '3':
			std::cout << "查看班级：\n";
			if (Class::_Get_Size() == 0)
				std::cerr << "查看班级 -> （当前无班级）\n";
			else
			Class::_Print_All();
			std::cout << std::endl;
			break;
		case '4':
			std::cout << "查看学生：\n";
			if (Student::_Get_Size() == 0)
				std::cerr << "查看学生 -> （当前无学生）\n";
			else
			Student::_Print_All();
			if (Teaching_Assistant::_Get_Size())
			{
				std::cout << "查看学生 -> 助教列表：\n";
				Teaching_Assistant::_Print_All();
			}
			std::cout << std::endl;
			break;
		case '5':
			std::cout << "编辑课程：\n";
			Course::_Edit_All();
			std::cout << std::endl;
			break;
		case '6':
			std::cout << "编辑教师：\n";
			Teacher::Edit_All();
			std::cout << std::endl;
			break;
		case '7':
			std::cout << "编辑班级：\n";
			Class::_Edit_All();
			std::cout << std::endl;
			break;
		case '8':
			std::cout << "编辑学生：\n";
			Student::_Edit_All();
			std::cout << std::endl;
			break;
		case '9':
			Course::_Score_Manage();
			std::cout << std::endl;
			break;
		case '0':
			Student::_Score_Manage();
			std::cout << std::endl;
			break;
		default:
			return;
		}
	}
}

int main()
{
	std::cout << "\n\n\n\t\t\t\t学生成绩管理系统 v1.0\n\n\n";
	char input; // 功能选项
	std::string file_name; // 文件名
	std::ifstream file_in; // 输入文件
	std::ofstream file_out; // 输出文件
	while (true)
	{
		std::cout << "开始工作 -> 1.从控制台添加数据（C/c）    2.从文件导入数据（F/f）    3.退出（Eec)\n";
		input = _getch();
		switch (input)
		{
		case '2':
		case 'F':
		case 'f': // 从文件导入数据
			std::cout << "文件名（仅支持 ANSI编码，带有模板格式的 .md 文件）：";
			std::cin >> file_name;
			std::cin.ignore(); // 避免输入缓冲区残留 Enter 对接受单字符和接受 Enter 作为默认输入标志的影响
			file_in.open(file_name, std::ios_base::in);
			if (file_in.is_open())
			{
				// 读取文件
				Course::_Read_File(file_in);
				Teacher::_Read_File(file_in);
				Class::_Read_File(file_in);
				Student::_Read_File(file_in);
				Teaching_Assistant::_Read_File(file_in);
				file_in.close();

				// 在控制台打印信息
				std::cout << "\n导入课程：\n";
				Course::_Print_All();
				std::cout << "\n导入教师：\n";
				Teacher::_Print_All();
				std::cout << "\n导入班级：\n";
				Class::_Print_All();
				std::cout << "\n导入学生：\n";
				Student::_Print_All();
				std::cout << "\n导入助教：\n";
				Teaching_Assistant::_Print_All();
				std::cout << std::endl;
			}
			else
			{
				std::cerr << "error（文件未打开）\n";
				break;
			}
		case '1':
		case 'C':
		case 'c': // 从控制台编辑数据
			std::cout << std::endl;
			Console();
			std::cout << "输入文件名保存文件，或直接按 Enter 取消：";
			getline(std::cin, file_name);
			if (!file_name.empty()) // 输入不是 Enter
			{
				file_out.open(file_name, std::ios_base::trunc);
				if (file_out.is_open()) // 写入文件
				{
					Course::_Write_File(file_out);
					Teacher::_Write_File(file_out);
					Class::_Write_File(file_out);
					Student::_Write_File(file_out);
					Teaching_Assistant::_Write_File(file_out);
					std::cout << "文件已保存至：" << file_name << std::endl;
					file_out.close();
				}
				else
					std::cerr << "error（文件未打开）\n";
			}
			break;
		case '3':
		case 27: // 退出
			for (size_t i = Class::_Get_Size(); i > 0; i--)
				delete Class::_Get_ptr(i - 1);
			for (size_t i = Course::_Get_Size(); i > 0; i--)
				delete Course::_Get_ptr(i - 1);
			for (size_t i = Teacher::_Get_Size(); i > 0; i--)
				delete Teacher::_Get_ptr(i - 1);
			for (size_t i = Student::_Get_Size(); i > 0; i--)
				delete Student::_Get_ptr(i - 1);
			return 0;
		default:
			break;
		}
	}
}