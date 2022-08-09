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
			std::cerr << "�������� -> error��ѧ���Ѵ��ڣ�\n";
			std::cerr << "(warning) in function Teaching_Assistant* const Teaching_Assistant::_New(std::string name, std::string id, std::string faculty, Grade_Type grade):\n"
				<< "\tduplicate id already exists in student list, a nullptr has been returned.\n"
				<< "\tcause: (*iter)->Get_ID() == id\n";
			return nullptr;
		}

	Teaching_Assistant* teaching_assistant_ptr = new Teaching_Assistant(name, id, faculty, grade);
	_List.push_back(teaching_assistant_ptr); // ��ӵ������б�
	Student::_List.push_back(teaching_assistant_ptr); // ��ӵ�ѧ���б�
	std::cout << "�������� -> ���������� " << name << "��ѧ�ţ�" << id << " Ժϵ��" << faculty << " �꼶��";
	switch (grade)
	{
	case undergraduate_1:
		std::cout << "����һ�꼶\n";
		break;
	case undergraduate_2:
		std::cout << "���ƶ��꼶\n";
		break;
	case undergraduate_3:
		std::cout << "�������꼶\n";
		break;
	case undergraduate_4:
		std::cout << "�������꼶\n";
		break;
	case master_1:
		std::cout << "˶ʿ�о���һ�꼶\n";
		break;
	case master_2:
		std::cout << "˶ʿ�о������꼶\n";
		break;
	case master_3:
		std::cout << "˶ʿ�о������꼶\n";
		break;
	case PhD_1:
		std::cout << "��ʿ�о���һ�꼶\n";
		break;
	case PhD_2:
		std::cout << "��ʿ�о������꼶\n";
		break;
	case PhD_3:
		std::cout << "��ʿ�о������꼶\n";
	}
	return teaching_assistant_ptr;
}

void Teaching_Assistant::Edit()
{
	while (true)
	{
		std::cout << Get_Name() << " -> ѡ���޸��1.������2.ѧ�ţ�3.Ժϵ��4.�ɼ���¼��5.�����༶����������ȡ��...";
		std::string new_info; // switch �ڽ�������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �޸�����
			std::cout << "\n��������";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Name(new_info);
			break;

		case '2': // �޸�ѧ��
			std::cout << "\n��ѧ�ţ�";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_ID(new_info);
			break;

		case '3': // �޸�Ժϵ
			std::cout << "\n��Ժϵ��";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Faculty(new_info);
			break;

		case '4': // �޸ĳɼ���¼
			Student::Edit_Record();
			break;

		case '5': // �޸ĸ����༶
			Edit_Class();
			break;

		default: // ȡ��
			return;
		}
		std::cout << Get_Name() << " -> ��E/e�����޸�������Ϣ��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Teaching_Assistant::Print() const
{
	Person::Print();
	Student::Print_Record();
	std::cout << "��ѧ��Ϊ���̣������༶�б�\n";
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
		std::cout << iter - _List.begin() + 1 << '.'  // ���
			<< std::setw(10) << std::left << (*iter)->Get_Name() // ��������
			<< "ѧ�ţ�" << std::setw(15) << std::left << (*iter)->Get_ID() // ����ѧ��
			<< "Ժϵ��" << std::setw(10) << std::left << (*iter)->Get_Faculty(); // Ժϵ

		if ((*iter)->Class_List.size()) // �༶�б�Ϊ��
		{
			std::cout << "�����༶��\n";
			for (auto iter_2 = (*iter)->Class_List.begin(); iter_2 != (*iter)->Class_List.end(); iter_2++)
				std::cout <<"\t\t\t\t\t\t\t" << iter_2 - (*iter)->Class_List.begin() + 1 << '.' // ���
				<< "�γ� " << (*iter_2)->Get_Course_ptr()->Get_Name()// �γ���
				<< "����ʦ " << (*iter_2)->Get_Teacher_ptr()->Get_Name()// ��ʦ��
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
	_List.erase(std::find(_List.begin(), _List.end(), this)); // �������б���ɾ��
	std::cout << "ɾ������ -> ��ɾ������ " << Get_Name() << std::endl;
}

void Teaching_Assistant::_Write_File(std::ofstream& file)
{
	file << "## ���̣��ܼƣ�" << _List.size() << "��\n\n" // ����
		<< "| ��� | ���� | ѧ�� | Ժϵ | �꼶 | �����༶����ţ� |\n" // ��ͷ
		<< "| - | - | - | - | - | - |\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // ѧ�����
			<< " | " << (*iter)->Get_Name() // ѧ������
			<< " | " << (*iter)->Get_ID() // ѧ��
			<< " | " << (*iter)->Get_Faculty() // Ժϵ
			<< " | ";
		switch ((*iter)->Get_Grade()) // �꼶������꼶����
		{
		case undergraduate_1:
			file << "` 11 `  ����һ�꼶";
			break;
		case undergraduate_2:
			file << "` 12 `  ���ƶ��꼶";
			break;
		case undergraduate_3:
			file << "` 13 `  �������꼶";
			break;
		case undergraduate_4:
			file << "` 14 `  �������꼶";
			break;
		case master_1:
			file << "` 21 `  ˶ʿ�о���һ�꼶";
			break;
		case master_2:
			file << "` 22 `  ˶ʿ�о������꼶";
			break;
		case master_3:
			file << "` 23 `  ˶ʿ�о������꼶";
			break;
		case PhD_1:
			file << "` 31 `  ��ʿ�о���һ�꼶";
			break;
		case PhD_2:
			file << "` 32 `  ��ʿ�о������꼶";
			break;
		case PhD_3:
			file << "` 33 `  ��ʿ�о������꼶";
		}

		if (!(*iter)->Class_List.empty()) // �����༶�б�Ϊ��
		{
			auto iter_2 = (*iter)->Class_List.begin();
			file << " | ` "<< (*iter_2)->Get_Serial_Number(); // д���һ�����
			iter_2++;
			for (; iter_2 != (*iter)->Class_List.end(); iter_2++)
				file << " ` �� ` "<<(*iter_2)->Get_Serial_Number() ;
			file << " ` |\n";
		}
		else
			file << " | |\n";
	}
	file << std::endl;
}

void Teaching_Assistant::_Read_File(std::ifstream& file)
{
	int serial; // ѧ�����
	char delimiter; // �ָ���
	std::string name; // ����
	std::string id; // ѧ��
	std::string faculty; // Ժϵ
	int grade; // �꼶
	unsigned long long num_class; // �༶���

	// �ƶ���ָ�뵽ѧ���б�
	file.seekg(std::ios_base::beg); // ��λ���ļ�ͷ
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ������
	if (file.peek() != '#')
		file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���γ��б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ����ʦ�б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���༶�б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ��ѧ���б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ�������б����
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "## ����"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ��������
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| ��� | ���� | ѧ�� | Ժϵ | �꼶 |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| - | - | - | - | - |"

	delimiter = file.get(); // �����һ�����ַ�
	while (delimiter == '|')
	{
		file >> serial // ���
			>> delimiter // '|'
			>> name // ѧ������
			>> delimiter // '|'
			>> id // ѧ��
			>> delimiter // '|'
			>> faculty // Ժϵ
			>> delimiter // '|'
			>> delimiter // '`'
			>> grade; // �꼶����
		auto iter = _List.begin();
		for (; iter != _List.end(); iter++)
			if ((*iter)->Get_ID() == id) // �ҵ�����
				break;
		if (iter == _List.end()) // δ�ҵ�����
		{
			std::cerr << "���ļ��������� -> error������ " << name << " ����ѧ���б��У�\n";
			getline(file, name); // �л�����һ��
			break;
		}

		file.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // ��λ�������༶�б�
		file >> delimiter; // ���� '`' �� '|'
		while(delimiter=='`')
		{
			file >> num_class // �༶���
				>> delimiter; // '`'
			(*iter)->Add_Class(Class::_Get_ptr(num_class - 1));
			file.get(); // ���� ' '
			if (file.peek() == '|')
			{
				file.get(); // '|'
				break;
			}
			else
			{
				getline(file, name, ' '); // ���� '��'
				delimiter = file.get(); // ���� '`' 
			}
		}
		file.get(); // ���� '\n'
		delimiter = file.get(); // ������һ�����ַ�
	}
}

void Teaching_Assistant::Edit_ID(const std::string& id)
{
	for (auto iter = Student::_List.begin(); iter != Student::_List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "�༭���� -> error��ѧ���Ѵ��ڣ�\n";
			return;
		}
	ID = id;
	std::cout << "�༭���� -> ���޸�ѧ��Ϊ " << id << std::endl;
}

void Teaching_Assistant::Edit_Class()
{
	if (Class::_Get_Size() == 0)
	{
		std::cerr << "�༭����-> " << Get_Name() << " -> �༭�����༶��Ϣ -> error����ǰ�ް༶��";
		return;
	}
	while (true)
	{
		bool flag = false; // ��ǣ��༶Ϊ�գ�2 ���� ����������
		if (Teacher::Class_List.empty())
		{
			std::cout << "�༭����-> " << Get_Name() << " -> �༭�����༶��Ϣ -> ����ǰ�ް༶��\n"
				<< "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ѡ��༭��ʽ��1.��ӣ���������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			Teacher::Print_Class(); // ��ӡ�����༶
			std::cout << "\n�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ѡ��༭��ʽ��1.��ӣ�2.ɾ������������ȡ��...";
		}
		unsigned long long new_num; // switch �ڽ�������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �����༶
			std::cout << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ��Ӱ༶��������ţ���\n\n";
			Class::_Print_All(); // ��ӡ���а༶�Ŀγ̡���ʦ��
			std::cout << "\n�� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();
			if (new_num > Class::_Get_Size())
				std::cerr << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ��Ӱ༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
			{
				Class* class_ptr = Class::_Get_ptr(new_num - 1);
				Teacher::Class_List.push_back(class_ptr);
				std::cerr << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ��Ӱ༶ -> ����Ӱ༶���γ� "
					<< class_ptr->Get_Course_ptr()->Get_Name()
					<< "����ʦ " << class_ptr->Get_Teacher_ptr()->Get_Name()
					<< std::endl;
			}
			break;

		case '2': // ɾ���༶
			if (flag) // ��ǰ�޿γ�
				return;
			std::cout << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ɾ���༶ -> ��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > Teacher::Class_List.size())
				std::cerr << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ɾ���༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
			{
				auto iter = Teacher::Class_List.begin() + new_num - 1;
				std::cout << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ɾ���༶ -> ��ɾ���༶���γ� "
					<< (*iter)->Get_Course_ptr()->Get_Name()
					<< "����ʦ " << (*iter)->Get_Teacher_ptr()->Get_Name()
					<< std::endl;
				Teacher::Class_List.erase(iter); // �����б����Ƴ�
			}
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭���� -> " << Get_Name() << " -> �༭�����༶��Ϣ -> ��E/e�����༭�����༶��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}

}