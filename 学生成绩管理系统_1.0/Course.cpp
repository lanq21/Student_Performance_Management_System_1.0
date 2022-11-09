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
	std::string full_score_input; // �ӿ���̨����γ�����
	bool flag = false; // ��ǣ��ӿ���̨�½�
	if (name.empty()) // �ӿ���̨�½���ʹ��ȱʡ�β�
		flag = true;

	if (flag)
	{
		// ���ÿγ���
		std::cout << "�����γ� -> �γ�����";
		getline(std::cin, name);
	}

	// ����ظ���
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_Name() == name)
		{
			std::cerr << "�����γ� -> error���γ��Ѵ��ڣ�\n";
			return (*iter);
		}

	if (flag)
	{
		// ���ÿγ�����
		std::cout << "�����γ� -> �γ����֣��� Enter �Զ���� 100����";
		getline(std::cin, full_score_input);
		if (full_score_input.empty()) // ������ Enter
			full_score = 100; // ʹ��Ĭ�Ͽγ�����
		else
			full_score = atof(full_score_input.c_str()); // ʹ������Ŀγ�����
	}
	Course* course_ptr = new Course(name, full_score);
	_List.push_back(course_ptr); // ��ӵ��γ��б�
	std::cout << "�����γ� -> �������γ� " << name << "������ " << full_score << std::endl;
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
		std::cout << "�༭�γ� -> " << Get_Name() << " -> ѡ���޸��1.�γ�����2.�γ����֣�3.���ΰ༶����������ȡ��...";
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		// switch �ڽ�������
		std::string new_info;
		int new_num;

		switch (input)
		{
		case '1': // �޸Ŀγ���
			std::cout << "�༭�γ� -> " << Get_Name() << " -> �¿γ�����";
			getline(std::cin, new_info);
			Edit_Name(new_info);
			break;

		case '2': // �޸Ŀγ�����
			std::cout << "�༭�γ� -> " << Get_Name() << " -> �¿γ����֣�";
			std::cin >> new_num;
			std::cin.ignore();
			Edit_Full_Score(new_num);
			break;

		case '3': // �༭���ΰ༶
			Edit_Class();
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭�γ� -> " << Get_Name() << " -> ��E/e�����޸Ŀγ���Ϣ��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Course::Edit_Name(const std::string& name)
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_Name() == name)
		{
			std::cerr << "�༭�γ� -> error���γ��Ѵ��ڣ�\n";
			return;
		}
	Name = name;
	std::cout << "�༭�γ� -> ���޸Ŀγ���Ϊ " << name << std::endl;
}

void Course::Edit_Full_Score(const int& full_score)
{
	Full_Score = full_score;
	std::cout << "�༭�γ� -> ���޸Ŀγ�����Ϊ " << full_score << std::endl;
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
		unsigned long long serial; // �ӿ���̨�������

		if (_Get_Size()) // �γ��б�Ϊ��
		{
			std::cout << "�γ̳ɼ� -> ������Ų鿴�γ̳ɼ�ͳ�ƣ�\n\n";
			_Print_All();
			std::cout << "\n�� ���� 0 ȡ����";
			std::cin >> serial;
			std::cin.ignore();
			if (serial == 0)
				return;
			if (serial < 0 || serial > _Get_Size())
				std::cerr << "�γ̳ɼ� -> error����ų����б�Χ��\n";
			else
			{
				Course* course_ptr = Course::_Get_ptr(serial - 1);
				std::cout << course_ptr->Get_Name() << " -> �鿴�༶�ɼ�ͳ�ƣ�������ţ�\n\n";
				course_ptr->Print_Class(); // ��ӡ�༶�б������γ̡���ʦ����ѧ������
				std::cout << "\n�� ���� 0 ȡ����";
				std::cin >> serial;
				std::cin.ignore();
				if (serial)
				{
					if (serial > course_ptr->Get_Class_Size())
						std::cerr << course_ptr->Get_Name() << " -> error����ų����б�Χ��";
					else
					{
						Class* class_ptr = course_ptr->Get_Class_ptr(serial - 1);
						if (class_ptr->Get_Student_Size() == 0)
							std::cerr << course_ptr->Get_Name()
							<< " -> �༶���γ� " << course_ptr->Get_Name()
							<< "����ʦ " << class_ptr->Get_Teacher_ptr()->Get_Name()
							<< " -> �鿴�ɼ�ͳ�� -> error����ǰ�༶��ѧ����\n";
						else
						{
							std::cout << course_ptr->Get_Name()
								<< " -> �༶���γ� " << course_ptr->Get_Name()
								<< "����ʦ " << class_ptr->Get_Teacher_ptr()->Get_Name()
								<< " -> ѡ������ʽ��1.���� 2.ѧ�� 3.�ɼ�����������ȡ����";
							char input = _getch();
							std::cout << std::endl << std::endl;
							switch (input)
							{
							case '1':
								class_ptr->Rank(Rank_Name); // ��ѧ����������
								class_ptr->Print_Record();
								break;
							case '2':
								class_ptr->Rank(Rank_ID); // ��ѧ��ѧ������
								class_ptr->Print_Record();
								break;
							case '3':
								class_ptr->Rank(Rank_Score); // ��ѧ���ɼ�����
								class_ptr->Print_Record();
							}
							std::cout << std::endl;
						}
					}
				}
			}
		}
		else
			std::cerr << "�γ̳ɼ� -> error����ǰ�޿γ̣�\n";

		std::cout << "�γ̳ɼ� -> ��E/e�����鿴�γ̳ɼ�ͳ�ƣ�������������...";
		char input = _getch();
		std::cout << std::endl << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Course::_Edit_All()
{
	while (true)
	{
		system("cls");
		std::cout << "�༭�γ̣�\n";
		bool flag = false; // ��ǣ��γ��б�Ϊ�գ�2��3 ���� ����������
		if (_List.empty())
		{
			std::cout << "�༭�γ� -> ����ǰ�޿γ̣�\n"
				<< "�༭�γ� -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // ��ӡȫ���γ�
			std::cout << "\n�༭�γ� -> ѡ��༭��ʽ��1.������2.�޸ģ�3.ɾ������������ȡ��...";
		}

		unsigned long long new_num; // switch �ڽ�������
		Course* course_ptr;
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �����γ�
			course_ptr = Course::_New(); // �ڿ���̨�����γ�
			std::cout << "�����γ� -> �� Enter �༭���ΰ༶����������ȡ����";
			input = _getch();
			std::cout << std::endl;
			if (input == '\r')
				course_ptr->Edit_Class();
			break;

		case '2': // �޸Ŀγ�
			if (flag) // ��ǰ�޿γ�
				return;
			std::cout << "�༭�γ� -> ѡ��γ̣�������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "�༭�γ� -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				_List[new_num - 1]->Edit();
			break;

		case '3': // ɾ���γ�
			if (flag) // ��ǰ�޿γ�
				return;
			std::cout << "ɾ���γ̣�������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "ɾ���γ� -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭�γ� -> ��E/e�����༭�γ̣�������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Course::Edit_Class()
{
	while (true)
	{
		bool flag = false; // ��ǣ��༶Ϊ�գ�2 ���� ����������
		if (Class_List.empty())
		{
			std::cout << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> ����ǰ�ް༶��\n"
				<< "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			Print_Class(); // ��ӡ���ΰ༶
			std::cout << "\n�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> ѡ��༭��ʽ��1.������2.ɾ������������ȡ��...";
		}

		unsigned long long new_num; // switch �ڽ�������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �����༶
			if (Teacher::_Get_Size()) // ��ʦ�б�Ϊ��
			{
				std::cout << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> �����༶ -> ѡ���ʦ��������ţ���\n\n";
				Teacher::_Print_All();
				std::cout << "\n������ 0 ������ʦ��";
			}
			else
				std::cout << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> �����༶ -> ѡ���ʦ -> ��ǰ�޽�ʦ������ 0 ������ʦ��";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Teacher::_Get_Size())
				std::cerr << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> �����༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0) // �����༶
				Class::_New(this, Teacher::_Get_ptr(new_num - 1)); // �����༶
			else // ������ʦ�������༶
			{
				Teacher* new_teacher = Teacher::_New(); // �ڿ���̨������ʦ
				Class::_New(this, new_teacher); // ֱ�Ӵ����༶
			}
			break;

		case '2': // ɾ���༶
			if (flag) // ��ǰ�޽�ʦ
				return;
			std::cout << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> ɾ���༶ -> ѡ��༶��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Class_List.size())
				std::cerr << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> ɾ���༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				delete Class_List[new_num - 1];
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭�γ� -> " << Get_Name() << " -> �༭���ΰ༶ -> ��E/e�����༭���ΰ༶��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
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
		<< " -> �γ����֣�" << Get_Full_Score() << std::endl;
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
		std::cout << std::right << std::setw(3) << iter - _List.begin() + 1 << '.'  // ���
			<< std::setw(25) << std::left << (*iter)->Get_Name() // �γ���
			<< "�γ����֣�" << std::setw(5) << (*iter)->Get_Full_Score(); // �γ�����

		if ((*iter)->Class_List.size()) // �༶�б�Ϊ��
		{
			std::cout << "���ν�ʦ��";
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				std::cout << (*iter_2)->Get_Teacher_ptr()->Get_Name() << " "; // ��ʦ����
		}
		std::cout << std::endl;
	}
}

void Course::_Write_File(std::ofstream& file)
{
	file << "## �γ̣��ܼƣ�" << _List.size() << "��\n\n" // ����
		<< "| ��� | �γ��� | �ڿν�ʦ | �γ����� |\n" // ��ͷ
		<< "| - | - | - | - |\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // ���
			<< " | " << (*iter)->Get_Name() << " | "; // �γ���
		if ((*iter)->Class_List.size()) // �༶�б�Ϊ��
		{
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				file << (*iter_2)->Get_Teacher_ptr()->Get_Name() << "  "; // ��ʦ����
			file.seekp(-2, std::ios_base::cur); // ���������ո�
		}
		file << " | " << (*iter)->Get_Full_Score() << " |\n"; // �γ�����
	}
	file << std::endl;
}

void Course::_Read_File(std::ifstream& file)
{
	int serial; // ���
	char delimiter; // �ָ���
	std::string name; // �γ���
	double full_score; // �γ�����

	// �ƶ���ָ�뵽�γ��б�
	file.seekg(std::ios_base::beg); // ��λ���ļ�ͷ
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ������
	if (file.peek() != '#')
		file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���γ��б����
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "## �γ�"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ��������
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| ��� | �γ��� | �ڿν�ʦ | �γ����� |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| - | - | - | - |"

	delimiter = file.get(); // �����һ�����ַ�
	while (delimiter == '|')
	{
		file >> serial // ���
			>> delimiter; // '|'
		file.get(); // ' '
		getline(file, name, '|'); // ����
		name.pop_back();
		file >> delimiter; // '|'
		file.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // ���Խ�ʦ��
		file >> full_score >> delimiter; // ����γ�����
		file.get(); // ���� '\n'
		delimiter = file.get(); // ������һ�����ַ�
		Course::_New(name, full_score); // �����γ�
	}
}

Course::~Course()
{
	for (size_t i = Get_Class_Size(); i > 0; i--)
		delete Get_Class_ptr(i - 1); // ɾ����ذ༶
	_List.erase(std::find(_List.begin(), _List.end(), this)); // �ӿγ��б���ɾ��
	std::cout << "ɾ���γ� -> ��ɾ���γ� " << Get_Name() << std::endl;
}

std::ostream& operator<<(std::ostream& output, const Course& course_obj)
{
	output<< course_obj.Get_Name()
		<< " -> �γ����֣�" << course_obj.Get_Full_Score() << std::endl;
	for (auto iter = course_obj.Class_List.begin(); iter != course_obj.Class_List.end(); iter++)
		output << iter - course_obj.Class_List.begin() + 1 << '.'<<(*iter);
	return output;
}