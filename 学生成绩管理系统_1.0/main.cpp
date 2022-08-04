#include <conio.h>
#include <fstream>

#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "Teaching_Assistant.h"

/// <summary>
/// �ӿ���̨�������
/// </summary>
void Console()
{
	char input; // ����ѡ��
	while (true)
	{
		std::cout << "��    �� -> 1.�γ��б�    2.��ʦ�б�    3.�༶�б�    4.ѧ���б�\n"
			<< "��    �� -> 5.�γ���Ϣ    6.��ʦ��Ϣ    7.�༶��Ϣ    8.ѧ����Ϣ\n"
			<< "�ɼ���¼ -> 9.�γ̳ɼ���  0.ѧ���ɼ���"
			<< "    �� ��������ȡ��...";
		input = _getch();
		std::cout << std::endl << std::endl;

		// switch �ڽ�������
		std::string new_info;

		switch (input)
		{
		case '1':
			std::cout << "�鿴�γ̣�\n";
			if (Course::_Get_Size() == 0)
				std::cerr << "�鿴�γ� -> ����ǰ�޿γ̣�\n";
			else
				Course::_Print_All();
			std::cout << std::endl;
			break;
		case '2':
			std::cout << "�鿴��ʦ��\n";
			if (Teacher::_Get_Size() == 0)
				std::cerr << "�鿴��ʦ -> ����ǰ�޽�ʦ��\n";
			else
			Teacher::_Print_All();
			std::cout << std::endl;
			break;
		case '3':
			std::cout << "�鿴�༶��\n";
			if (Class::_Get_Size() == 0)
				std::cerr << "�鿴�༶ -> ����ǰ�ް༶��\n";
			else
			Class::_Print_All();
			std::cout << std::endl;
			break;
		case '4':
			std::cout << "�鿴ѧ����\n";
			if (Student::_Get_Size() == 0)
				std::cerr << "�鿴ѧ�� -> ����ǰ��ѧ����\n";
			else
			Student::_Print_All();
			if (Teaching_Assistant::_Get_Size())
			{
				std::cout << "�鿴ѧ�� -> �����б�\n";
				Teaching_Assistant::_Print_All();
			}
			std::cout << std::endl;
			break;
		case '5':
			std::cout << "�༭�γ̣�\n";
			Course::_Edit_All();
			std::cout << std::endl;
			break;
		case '6':
			std::cout << "�༭��ʦ��\n";
			Teacher::Edit_All();
			std::cout << std::endl;
			break;
		case '7':
			std::cout << "�༭�༶��\n";
			Class::_Edit_All();
			std::cout << std::endl;
			break;
		case '8':
			std::cout << "�༭ѧ����\n";
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
	std::cout << "\n\n\n\t\t\t\tѧ���ɼ�����ϵͳ v1.0\n\n\n";
	char input; // ����ѡ��
	std::string file_name; // �ļ���
	std::ifstream file_in; // �����ļ�
	std::ofstream file_out; // ����ļ�
	while (true)
	{
		std::cout << "��ʼ���� -> 1.�ӿ���̨������ݣ�C/c��    2.���ļ��������ݣ�F/f��    3.�˳���Eec)\n";
		input = _getch();
		switch (input)
		{
		case '2':
		case 'F':
		case 'f': // ���ļ���������
			std::cout << "�ļ�������֧�� ANSI���룬����ģ���ʽ�� .md �ļ�����";
			std::cin >> file_name;
			std::cin.ignore(); // �������뻺�������� Enter �Խ��ܵ��ַ��ͽ��� Enter ��ΪĬ�������־��Ӱ��
			file_in.open(file_name, std::ios_base::in);
			if (file_in.is_open())
			{
				// ��ȡ�ļ�
				Course::_Read_File(file_in);
				Teacher::_Read_File(file_in);
				Class::_Read_File(file_in);
				Student::_Read_File(file_in);
				Teaching_Assistant::_Read_File(file_in);
				file_in.close();

				// �ڿ���̨��ӡ��Ϣ
				std::cout << "\n����γ̣�\n";
				Course::_Print_All();
				std::cout << "\n�����ʦ��\n";
				Teacher::_Print_All();
				std::cout << "\n����༶��\n";
				Class::_Print_All();
				std::cout << "\n����ѧ����\n";
				Student::_Print_All();
				std::cout << "\n�������̣�\n";
				Teaching_Assistant::_Print_All();
				std::cout << std::endl;
			}
			else
			{
				std::cerr << "error���ļ�δ�򿪣�\n";
				break;
			}
		case '1':
		case 'C':
		case 'c': // �ӿ���̨�༭����
			std::cout << std::endl;
			Console();
			std::cout << "�����ļ��������ļ�����ֱ�Ӱ� Enter ȡ����";
			getline(std::cin, file_name);
			if (!file_name.empty()) // ���벻�� Enter
			{
				file_out.open(file_name, std::ios_base::trunc);
				if (file_out.is_open()) // д���ļ�
				{
					Course::_Write_File(file_out);
					Teacher::_Write_File(file_out);
					Class::_Write_File(file_out);
					Student::_Write_File(file_out);
					Teaching_Assistant::_Write_File(file_out);
					std::cout << "�ļ��ѱ�������" << file_name << std::endl;
					file_out.close();
				}
				else
					std::cerr << "error���ļ�δ�򿪣�\n";
			}
			break;
		case '3':
		case 27: // �˳�
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