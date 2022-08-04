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
	// ����ظ���
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "�༭��ʦ -> error����ʦ�Ѵ��ڣ�\n";
			return;
		}
	ID = id;
	std::cout << "�༭��ʦ -> ���޸Ľ�ʦ���Ϊ " << id << std::endl;
}

Teacher* const Teacher::_New(std::string name, std::string id, std::string faculty)
{
	static std::string default_faculty = "����ϵ"; // Ĭ��Ժϵ
	bool flag = false; // ��ǣ��ӿ���̨�½�
	if (name.empty()) // �ӿ���̨�½���ʹ��ȱʡ�β�
		flag = true;

	if (flag)
	{
		// ��������
		std::cout << "������ʦ -> ��ʦ������";
		std::cin >> name;

		// ���ý�ʦ���
		std::cout << "������ʦ -> ��ʦ��ţ�";
		std::cin >> id;
		std::cin.ignore();
	}

	// ����ظ���
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "������ʦ -> error����ʦ�Ѵ��ڣ�\n";
			return (*iter);
		}
	if (flag)
	{
		// ����Ժϵ
		std::cout << "������ʦ -> Ժϵ���� Enter �Զ���� " << default_faculty << "����";
		getline(std::cin, faculty);
		if (faculty.empty()) // ������ Enter
			faculty = default_faculty; // ʹ��Ĭ��Ժϵ
		else
			default_faculty = faculty; // ����Ĭ��Ժϵ
	}
	Teacher* teacher_ptr = new Teacher(name, id, faculty,false);
	_List.push_back(teacher_ptr); // ��ӵ���ʦ�б�
	std::cout << "������ʦ -> ��������ʦ " << name << "����ţ�" << id << " Ժϵ��" << faculty << std::endl;

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
		bool flag = false; // ��ǣ���ʦ�б�Ϊ�գ�2��3 ���� ����������
		if (_List.empty())
		{
			std::cout << "�༭��ʦ -> ����ǰ�޽�ʦ��\n"
				<< "�༭��ʦ -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // ��ӡȫ����ʦ
			std::cout << "\n�༭��ʦ -> ѡ��༭��ʽ��1.������2.�޸ģ�3.ɾ������������ȡ��...";
		}

		unsigned long long new_num; // switch �ڽ�������
		Teacher* teacher_ptr;
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // ������ʦ
			teacher_ptr = Teacher::_New(); // �ڿ���̨�����γ�
			std::cout << "������ʦ -> �� Enter �༭���ΰ༶����������ȡ����";
			input = _getch();
			std::cout << std::endl;
			if (input == '\r')
				teacher_ptr->Edit_Class();
			break;

		case '2': // �޸Ľ�ʦ
			if (flag) // ��ǰ�޽�ʦ
				return;
			std::cout << "�༭��ʦ  -> ѡ���ʦ��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "�༭��ʦ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				_List[new_num - 1]->Edit();
			break;

		case '3': // ɾ����ʦ
			if (flag) // ��ǰ�޽�ʦ
				return;
			std::cout << "ɾ����ʦ��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > _List.size())
				std::cerr << "ɾ����ʦ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭��ʦ -> ��E/e�����༭��ʦ��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
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
		Class::Delete(this); // ɾ����ذ༶
		_List.erase(std::find(_List.begin(), _List.end(), this)); // �ӽ�ʦ�б���ɾ��
		std::cout << "ɾ����ʦ -> ��ɾ����ʦ " << Get_Name() << std::endl;
	}
}

void Teacher::Edit_Class()
{
	while (true)
	{
		bool flag = false; // ��ǣ��༶Ϊ�գ�2 ���� ����������
		if (Class_List.empty())
		{
			std::cout << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> ����ǰ�ް༶��\n"
				<< "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			Print_Class(); // ��ӡ�ڿΰ༶
			std::cout << "\n�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> ѡ��༭��ʽ��1.������2.ɾ������������ȡ��...";
		}

		unsigned long long new_num; // switch �ڽ�������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �����༶
			if (Course::_Get_Size()) // �γ��б�Ϊ��
			{
				std::cout << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> �����༶ -> ѡ��γ̣�������ţ���\n\n";
				Course::_Print_All();
				std::cout << "\n������ 0 �����γ̣�";
			}
			std::cout << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> �����༶ -> ѡ��γ� -> ��ǰ�޿γ̣����� 0 �����γ̣�";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Course::_Get_Size())
				std::cerr << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> �����༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0) // �����༶
				Class::_New(Course::_Get_ptr(new_num - 1), this);
			else
			{
				Course* new_course = Course::_New(); // �ڿ���̨�½��γ�
				Class::_New(new_course, this); // ֱ���½��༶
			}
			break;

		case '2': // ɾ���༶
			if (flag) // ��ǰ�޿γ�
				return;
			std::cout << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> ɾ���༶ -> ѡ��༶��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Class_List.size())
				std::cerr << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> ɾ���༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				delete Class_List[new_num - 1];
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭��ʦ -> " << Get_Name() << " -> �༭�ڿΰ༶��Ϣ -> ��E/e�����༭�ڿΰ༶��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Teacher::Edit()
{
	while (true)
	{
		std::cout << "�༭��ʦ -> " << Get_Name() << " -> ѡ���޸��1.������2.��ʦ��ţ�3.Ժϵ��4.�ڿΰ༶����������ȡ��...";
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		std::string new_info; // �� switch �ڽ�������

		switch (input)
		{
		case '1': // �޸�����
			std::cout << "�༭��ʦ -> " << Get_Name() << " -> ��������";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Name(new_info);
			break;

		case '2': // �޸Ľ�ʦ���
			std::cout << "�༭��ʦ -> " << Get_Name() << " -> �±�ţ�";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_ID(new_info);
			break;

		case '3': // �޸�Ժϵ
			std::cout << "�༭��ʦ -> " << Get_Name() << " -> ��Ժϵ��";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Faculty(new_info);
			break;

		case '4': // �༭�༶
			Edit_Class();
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭��ʦ -> " << Get_Name() << " -> ��E/e�����޸Ľ�ʦ��Ϣ��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
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
		std::cout << iter - _List.begin() + 1 << '.'  // ���
			<< std::setw(10) << std::left << (*iter)->Get_Name() // ��ʦ����
			<< "��ţ�" << std::setw(15) << std::left << (*iter)->Get_ID() // ��ʦ���
			<< "Ժϵ��" << std::setw(10) << std::left << (*iter)->Get_Faculty(); // Ժϵ

		if ((*iter)->Class_List.size()) // �༶�б�Ϊ��
		{
			std::cout << "���ڿγ̣�";
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				std::cout << (*iter_2)->Get_Course_ptr()->Get_Name() << " "; // ���ڿγ�
		}
		std::cout << std::endl;
	}
}

void Teacher::_Write_File(std::ofstream& file)
{
	file << "## ��ʦ���ܼƣ�" << _List.size() << "��\n\n" // ����
		<< "| ��� | ���� | ��ʦ��� | Ժϵ | ���ڿγ� |\n" // ��ͷ
		<< "| - | - | - | - | - |\n";
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // ���
			<< " | " << (*iter)->Get_Name() // ��ʦ��
			<< " | " << (*iter)->Get_ID() // ��ʦ���
			<< " | " << (*iter)->Get_Faculty() << " | "; // Ժϵ
		for (int j = 0; j < (*iter)->Class_List.size(); j++)
			file << (*iter)->Class_List[j]->Get_Course_ptr()->Get_Name() << "  "; // ���ڿγ�
		file.seekp(-2, std::ios_base::cur); // ���������ո�
		file << " |\n";
	}
	file << std::endl;
}

void Teacher::_Read_File(std::ifstream& file)
{
	int serial; // ���
	char delimiter; // �ָ���
	std::string name; // ��ʦ����
	std::string id; // ��ʦ���
	std::string faculty; // Ժϵ

	// �ƶ���ָ�뵽�γ��б�
	file.seekg(std::ios_base::beg); // ��λ���ļ�ͷ
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���γ��б����
	file.get(); // ����ڶ��� '#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ����ʦ�б����
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� '## ��ʦ'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ��������
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� '| ��� | ���� | ��ʦ��� | Ժϵ | ���ڿγ� |'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� '| - | - | - | - | - |'

	delimiter = file.get(); // �����һ�����ַ�
	while (delimiter == '|')
	{
		file >> serial // ���
			>> delimiter // '|'
			>> name // ��ʦ����
			>> delimiter // '|'
			>> id // ��ʦ���
			>> delimiter // '|'
			>> faculty // Ժϵ
			>> delimiter; // '|'
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���Խ��ڿγ�
		delimiter = file.get(); // ������һ�����ַ�
		Teacher::_New(name, id, faculty);
	}
}
