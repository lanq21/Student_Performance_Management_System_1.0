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
	static std::string default_faculty = "����ϵ"; // Ĭ��Ժϵ
	static Grade_Type default_grade = undergraduate_1; // Ĭ���꼶
	std::string grade_input; // �����꼶
	bool flag = false; // ��ǣ��ӿ���̨����
	if (name.empty())
		flag = true;
	if (flag)
	{
		// ��������
		std::cout << "����ѧ�� -> ѧ��������";
		std::cin >> name;

		// ����ѧ��
		std::cout << "����ѧ�� -> ѧ�ţ�";
		std::cin >> id;
		std::cin.ignore();
	}
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "����ѧ�� -> error��ѧ���Ѵ��ڣ�\n";
			return (*iter);
		}
	if (flag)
	{
		// ����Ժϵ
		std::cout << "����ѧ�� -> Ժϵ���� Enter �Զ���� " << default_faculty << "����";
		getline(std::cin, faculty);
		if (faculty.empty()) // ���� Enter
			faculty = default_faculty; // ʹ��Ĭ��Ժϵ
		else
			default_faculty = faculty; // ����Ĭ��Ժϵ

		// �����꼶
		std::cout << "����ѧ�� -> �꼶���룺����һ�꼶 ���� 11�����꼶 ���� 12 ...\n"
			<< "\t\t      ˶ʿ�о���һ�꼶 ���� 21�����꼶 ���� 22 ...\n"
			<< "\t\t      ��ʿ�о���һ�꼶 ���� 31�����꼶 ���� 32 ...\n"
			<< "����ѧ�� -> �꼶���� Enter �Զ���� " << default_grade << "����";
		getline(std::cin, grade_input);
		if (grade_input.empty()) // ���� Enter
			grade = default_grade; // ʹ��Ĭ���꼶
		else
		{
			grade = Grade_Type(atoi(grade_input.c_str())); // ʹ�������꼶
			default_grade = grade; // ����Ĭ���꼶
		}
	}
	Student* student_ptr;
	if (flag) // �ڿ���̨ѡ���Ƿ�Ϊ����
	{
		std::cout << "����ѧ�� -> �� E/e ����Ϊ���̣���������ȡ����";
		char input = _getch();
		std::cout << std::endl;
		if (input == 'E' || input == 'e')
			is_ta = true;
		else is_ta = false;
	}

	if (is_ta == true) // ������
	{
		Teaching_Assistant* teaching_assistant_ptr = Teaching_Assistant::_New(name, id, faculty, grade);
		student_ptr = teaching_assistant_ptr;
	}
	else // ��������
	{
		student_ptr = new Student(name, id, faculty, grade, false);
		_List.push_back(student_ptr);
		std::cout << "����ѧ�� -> ������ѧ�� " << name << "��ѧ�ţ�" << id << " Ժϵ��" << faculty << " �꼶��";
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
		bool flag = false; // ��ǣ�ѧ���б�Ϊ�գ�2��3 ���� ����������
		if (_List.empty())
		{
			std::cout << "�༭ѧ�� -> ����ǰ��ѧ����\n"
				<< "�༭ѧ�� -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // ��ӡȫ��ѧ��
			std::cout << "\n�༭ѧ�� -> ѡ��༭��ʽ��1.������2.�޸ģ�3.ɾ������������ȡ��...";
		}

		Student* student_ptr;
		unsigned long long new_num; // switch �ڽ�������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // ����ѧ��
			student_ptr = Student::_New();
			if (student_ptr != nullptr)
			{
				std::cout << "�� Enter ��ӳɼ���Ϣ����������ȡ��...";
				input = _getch();
				std::cout << std::endl;
				if (input == '\r')
					student_ptr->Edit_Record();
			}
			break;

		case '2': // �޸�ѧ��
			if (flag) // ��ǰ��ѧ��
				return;
			std::cout << "�༭ѧ��  -> ѡ��ѧ����������ţ��� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > _List.size())
				std::cerr << "�༭ѧ�� -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				_List[new_num - 1]->Edit();
			break;

		case '3': // ɾ��ѧ��
			if (flag) // ��ǰ��ѧ��
				return;
			std::cout << "ɾ��ѧ����������ţ��� ���� 0 ȡ����\n";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num > _List.size())
				std::cerr << "ɾ��ѧ�� -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭ѧ�� -> �� E/e �����༭ѧ����������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
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
		Record_List.push_back(Record(class_ptr, score)); // ��ӳɼ���¼
		class_ptr->Add_Student(this); // ��Ӧ�༶���ѧ��
		std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> "
			<< class_ptr->Get_Course_ptr()->Get_Name() << "�ɼ������\n";
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
		unsigned long long class_serial; // �༶���
		double score; // �ɼ�

		if (course_ptr->Get_Class_Size()) // �༶�б�Ϊ��
		{
			std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> "
				<< course_ptr->Get_Name() << " -> ѡ��༶��������ţ���\n\n";
			course_ptr->Print_Class();
			std::cout << "\n�� ���� 0 ȡ����";
			std::cin >> class_serial;
			std::cin.ignore();

			if (class_serial > course_ptr->Get_Class_Size())
				std::cerr << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> "
				<< course_ptr->Get_Name() << " -> ѡ��༶ -> error����ų����б�Χ��\n";
			else if (class_serial > 0)
			{
				std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> "
					<< course_ptr->Get_Name() << " �ɼ���";
				std::cin >> score;
				std::cin.ignore();
				Add_Record(course_ptr->Get_Class_ptr(class_serial - 1), score); // ��ӳɼ���¼
			}
		}
		else
			std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> "
			<< course_ptr->Get_Name() << " -> error����ǰ�ް༶��\n";
	}
}

void Student::Edit_ID(const std::string& id)
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		if ((*iter)->Get_ID() == id)
		{
			std::cerr << "�༭ѧ�� -> error��ѧ���Ѵ��ڣ�\n";
			return;
		}
	ID = id;
	std::cout << "�༭ѧ�� -> ���޸�ѧ��Ϊ " << id << std::endl;
}

void Student::Edit_Record()
{
	bool flag_all = false; // ��ǣ���ʹ�� Enter ���ȫ���γ�
	if (Record_List.empty())
		flag_all = true;

	while (true)
	{
		bool flag_empty = false; // ��ǣ��ɼ���¼Ϊ�գ�2��3 ���� ����������
		if (Record_List.empty()) // �ɼ���¼Ϊ��
		{
			std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �����޳ɼ���¼��\n"
				<< Get_Name() << " -> �༭�ɼ���¼ -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag_empty = true;
		}
		else
		{
			std::cout << std::endl;
			Print_Record();
			std::cout << std::endl << Get_Name() << " -> �༭�ɼ���¼ -> ѡ��༭��ʽ��1.������2.�޸ģ�3.ɾ������������ȡ��...";
		}

		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		// switch �ڽ�������
		unsigned long long new_num_1;
		int new_num_2;
		std::string new_string;

		switch (input)
		{
		case '1': // �����ɼ���¼
			if (Course::_Get_Size()) // �γ��б�Ϊ��
			{
				std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> ѡ��γ̣�������ţ���\n\n";
				Course::_Print_All();
				std::cout << "\n��";
				if (flag_all)
					std::cout << "�� Enter ���ȫ���γ̣�";
				std::cout << "���� 0 ȡ����";

				if (flag_all)
				{
					getline(std::cin, new_string);
					if (new_string.empty()) // Ϊȫ���п��ΰ༶�Ŀγ���ӳɼ�
					{
						for (int i = 0; i < Course::_Get_Size(); i++)
							if (Course::_Get_ptr(i)->Get_Class_Size()) // �п��ΰ༶
								Add_Record(Course::_Get_ptr(i)); // �ڿ���̨��ӳɼ���¼
						flag_all = false;
						break;
					}
					else
						new_num_1 = atoi(new_string.c_str()); // ���ܿγ����
				}
				else
				{
					std::cin >> new_num_1; // �γ����
					std::cin.ignore();
				}

				if (new_num_1 > Course::_Get_Size())
					std::cerr << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> ѡ��γ� -> error����ų����б�Χ��\n";
				else if (new_num_1 > 0)
					Add_Record(Course::_Get_ptr(new_num_1 - 1)); // �ڿ���̨��ӳɼ���¼
			}
			else
				std::cerr << Get_Name() << " -> �༭�ɼ���¼ -> �����ɼ���¼ -> ����ǰ�޿γ̣�\n";
			break;

		case '2': // �޸ĳɼ���¼
			if (flag_empty)
				return;
			std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �޸ĳɼ���¼ -> ѡ���¼��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num_1;
			std::cin.ignore();

			if (new_num_1 > Record_List.size())
				std::cerr << Get_Name() << " -> �༭�ɼ���¼ -> �޸ĳɼ���¼ -> error����ų����б�Χ��\n";
			else if (new_num_1 > 0)
			{
				std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �޸ĳɼ���¼ -> �³ɼ���";
				std::cin >> new_num_2;
				std::cin.ignore();
				if (new_num_2 > Record_List[new_num_1 - 1].Get_Class_ptr()->Get_Course_ptr()->Get_Full_Score())
					std::cerr << Get_Name() << " -> �༭�ɼ���¼ -> �޸ĳɼ���¼ -> error������ɼ����ڿγ����֣�\n";
				else
					Record_List[new_num_1 - 1].Edit_Score(new_num_2);
				std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �޸ĳɼ���¼ -> �ɼ����޸�Ϊ " << new_num_2 << std::endl;
			}
			break;

		case '3': // ɾ���ɼ���¼
			if (flag_empty)
				return;
			std::cout << Get_Name() << " -> �༭�ɼ���¼ -> ɾ���ɼ���¼ -> ѡ���¼��������ţ��� ���� 0 ȡ����";
			std::cin >> new_num_1;
			std::cin.ignore();

			if (new_num_1 > Record_List.size())
				std::cerr << Get_Name() << " -> �༭�ɼ���¼ -> ɾ���ɼ���¼ -> error����ų����б�Χ��\n";
			else if (new_num_1 > 0)
			{
				Delete_Record(new_num_1); // ɾ���ɼ���¼
				std::cout << Get_Name() << " -> �༭�ɼ���¼ -> ɾ���ɼ���¼ -> ��¼��ɾ��\n";
			}
			break;

		default: // ȡ��
			return;
		}
		std::cout << Get_Name() << " -> �༭�ɼ���¼ -> �� E/e �����༭�ɼ���¼��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Student::Delete_Record(const unsigned long long& n)
{
	Record_List[n - 1].Get_Class_ptr()->Delete_Student(this); // �Ӱ༶��ɾ��
	Record_List.erase(Record_List.begin() + n - 1); // �ӳɼ���¼�б���ɾ��
}

void Student::Edit()
{
	while (true)
	{
		std::cout << Get_Name() << " -> ѡ���޸��1.������2.ѧ�ţ�3.Ժϵ��4.�ɼ���¼����������ȡ��...";
		std::string new_info; // switch �ڽ�������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �޸�ѧ������
			std::cout << Get_Name() << " -> ��������";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Name(new_info);
			break;

		case '2': // �޸�ѧ��
			std::cout << Get_Name() << " -> ��ѧ�ţ�";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_ID(new_info);
			break;

		case '3': // �޸�Ժϵ
			std::cout << Get_Name() << " -> ��Ժϵ��";
			std::cin >> new_info;
			std::cin.ignore();
			Edit_Faculty(new_info);
			break;

		case '4': // �༭�ɼ���¼
			Edit_Record();
			break;

		default: // ȡ��
			return;
		}
		std::cout << Get_Name() << " -> ��E/e�����޸�ѧ����Ϣ��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Student::Print() const
{
	Person::Print(); // ��ӡ������ѧ�š�Ժϵ
	Print_Record(); // ��ӡ�ɼ���¼
}

const double Student::Get_Score(const Class* const class_ptr)
{
	auto iter = Record_List.begin();
	for (; iter != Record_List.end(); iter++)
		if ((*iter).Get_Class_ptr() == class_ptr)
			break;
	if (iter == Record_List.end()) // δ�ҵ���¼
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
	if (iter == Record_List.end()) // δ�ҵ���¼
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
		std::cout << iter - _List.begin() + 1 << '.'; // ��ӡ���
		if ((*iter)->Get_is_TA() == true)
			std::cout << std::setw(15) << "�����̣�" + (*iter)->Get_Name();
		else
			std::cout << std::setw(10) << (*iter)->Get_Name(); // ��ӡ����
		std::cout << "ѧ�ţ�" << std::setw(15) << std::left << (*iter)->Get_ID() // ��ӡѧ��
			<< "Ժϵ��" << std::setw(8) << std::left << (*iter)->Get_Faculty(); // ��ӡԺϵ
		switch ((*iter)->Get_Grade()) // ��ӡ�꼶
		{
		case undergraduate_1:
			std::cout << "�꼶��" << std::setw(16) << std::left << "����һ�꼶";
			break;
		case undergraduate_2:
			std::cout << "�꼶��" << std::setw(16) << std::left << "���ƶ��꼶";
			break;
		case undergraduate_3:
			std::cout << "�꼶��" << std::setw(16) << std::left << "�������꼶";
			break;
		case undergraduate_4:
			std::cout << "�꼶��" << std::setw(16) << std::left << "�������꼶";
			break;
		case master_1:
			std::cout << "�꼶��" << std::setw(16) << std::left << "˶ʿ�о���һ�꼶";
			break;
		case master_2:
			std::cout << "�꼶��" << std::setw(16) << std::left << "˶ʿ�о������꼶";
			break;
		case master_3:
			std::cout << "�꼶��" << std::setw(16) << std::left << "˶ʿ�о������꼶";
			break;
		case PhD_1:
			std::cout << "�꼶��" << std::setw(16) << std::left << "��ʿ�о���һ�꼶";
			break;
		case PhD_2:
			std::cout << "�꼶��" << std::setw(16) << std::left << "��ʿ�о������꼶";
			break;
		case PhD_3:
			std::cout << "�꼶��" << std::setw(16) << std::left << "��ʿ�о������꼶";
		}
		if (!(*iter)->Record_List.empty())
		{
			std::cout << "\n  �ɼ���";
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
		std::cout << "ѧ���ɼ� -> ����ѧ�Ų�ѯ�ɼ����� Enter ȡ����";
		getline(std::cin, id);
		if (id.empty()) // ������ Enter
			return;
		else
		{
			auto iter = _List.begin();
			for (; iter != _List.end(); iter++)
				if ((*iter)->Get_ID() == id)
					break;
			if (iter == _List.end()) // δ���ҵ�ѧ��
				std::cerr << "ѧ���ɼ� -> error��ѧ�������ڣ�\n";
			else
			{
				std::cout << std::endl;
				(*iter)->Print(); // ��ӡ��Ϣ�ͳɼ�
				std::cout << std::endl;
			}
		}
		std::cout << "ѧ���ɼ� -> �� E/e ������ѯ�ɼ�����������ȡ����";
		char input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

void Student::_Write_File(std::ofstream& file)
{
	size_t course_num = Course::_Get_Size(); // �γ�ָ��
	double* grade_list = new double[course_num]; // ���տγ�˳��ĳɼ��б�
	size_t* class_serial_list = new size_t[course_num]{ 0 }; // ���տγ�˳��İ༶����б�0 ��ʾ�޸ÿγɼ�

	file << "## ѧ�����ܼƣ�" << _List.size() << "��\n\n" // ����
		<< "| ��� | ���� | ѧ�� | Ժϵ | �꼶 | "; // ��ͷ
	for (int i = 0; i < course_num; i++)
		file << Course::_Get_ptr(i)->Get_Name() << " | ";
	file.seekp(-1, std::ios_base::cur); // ����һ���ո�
	file << std::endl;

	for (int i = 0; i < course_num + 5; i++)
		file << "| - ";
	file << "|\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1; // ѧ�����
		if ((*iter)->Is_TA == true)
			file << " | ` ���� ` ";
		else
			file << " | ";
		file << (*iter)->Get_Name() // ѧ������
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
		for (auto iter_2 = (*iter)->Record_List.begin(); iter_2 != (*iter)->Record_List.end(); iter_2++)
		{
			// ���γ�˳�����༶���
			class_serial_list[(*iter_2).Get_Class_ptr()->Get_Course_ptr()->Get_Serial_Number() - 1] = (*iter_2).Get_Class_ptr()->Get_Serial_Number();
			// ���γ�˳�����ɼ�
			grade_list[(*iter_2).Get_Class_ptr()->Get_Course_ptr()->Get_Serial_Number() - 1] = (*iter_2).Get_Score();
		}
		for (int j = 0; j < course_num; j++)
		{
			if (class_serial_list[j] > 0) // ��Ӧ�γ̳ɼ���Ϊ��
				file << " | ` " << class_serial_list[j] << " ` " << grade_list[j]; // �༶��źͳɼ�
			else
				file << " |";
		}
		file << " |\n";
		for (int j = 0; j < course_num; j++)
			class_serial_list[j] = 0; // ���ð༶����б�
	}
	file << std::endl;

	delete[] class_serial_list;
	delete[] grade_list;
}

void Student::_Read_File(std::ifstream& file)
{
	int serial; // ѧ�����
	char delimiter; // �ָ���
	std::string name; // ����
	std::string id; // ѧ��
	std::string faculty; // Ժϵ
	int grade; // �꼶
	bool is_ta = false; // �Ƿ�Ϊ����
	unsigned long long num_class; // �༶���
	double score; // �ɼ�
	size_t course_num = Course::_Get_Size(); // �γ���

	// �ƶ���ָ�뵽ѧ���б�
	file.seekg(std::ios_base::beg); // ��λ���ļ�ͷ
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���γ��б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ����ʦ�б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���༶�б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ��ѧ���б����
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "## ѧ��"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ��������
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| ��� | ���� | ѧ�� | Ժϵ | �꼶 |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| - | - | - | - | - |"

	delimiter = file.get(); // �����һ�����ַ�
	while (delimiter == '|')
	{
		file >> serial // ���
			>> delimiter; // '|'

		delimiter = file.get(); // ���� '|' ��Ŀո�
		delimiter = file.peek(); // �鿴 '`' �� ���������ַ�
		if (delimiter == '`')
		{
			file.get(); // ���� '`'
			file.ignore(std::numeric_limits<std::streamsize>::max(), '`'); // ��λ������
			is_ta = true;
		}
		file >> name // ѧ������
			>> delimiter // '|'
			>> id // ѧ��
			>> delimiter // '|'
			>> faculty // Ժϵ
			>> delimiter // '|'
			>> delimiter // '`'
			>> grade; // �꼶����
		Student* student = Student::_New(name, id, faculty, Grade_Type(grade), is_ta); // ����ѧ��
		file.ignore(std::numeric_limits<std::streamsize>::max(), '|'); // ��λ���׸��γ̵ĳɼ���¼
		for (int i = 0; i < course_num; i++)
		{
			delimiter = file.get(); // ���� '|' ��� ' ' �� '\n'
			delimiter = file.get(); // ���� '`' �� '|'
			if (delimiter == '|') // �ÿγ��޳ɼ�
				continue;
			else
				file >> num_class // �༶���
				>> delimiter // '`'
				>> score // �ɼ�
				>> delimiter; // '|'
			student->Add_Record(Class::_Get_ptr(num_class - 1), score);
		}
		file.get(); // ���� '\n'
		delimiter = file.get(); // ������һ�����ַ�
	}
}

Student::~Student()
{
	for (int i = 0; i < Record_List.size(); i++)
		Record_List[i].Get_Class_ptr()->Delete_Student(this); // �Ӱ༶��ѧ���б���ɾ��
	Record_List.clear(); // ��ճɼ��б�
	_List.erase(std::find(_List.begin(), _List.end(), this)); // ��ѧ���б���ɾ��
	std::cout << "ɾ��ѧ�� -> ��ɾ��ѧ�� " << Get_Name() << std::endl;
}

void Student::Print_Record() const
{
	if (Record_List.empty()) // �ɼ��б�Ϊ��
		return;
	else
	{
		std::cout << Get_Name() << " �ɼ���¼��" << std::endl;
		for (auto iter = Record_List.begin(); iter != Record_List.end(); iter++)
		{
			std::cout << (iter - Record_List.begin() + 1) << '.' // ���
				<< (*iter).Get_Class_ptr()->Get_Course_ptr()->Get_Name() // �γ���
				<< "\t�ڿν�ʦ��" << (*iter).Get_Class_ptr()->Get_Teacher_ptr()->Get_Name() // ��ʦ��
				<< "\t�ɼ���" << (*iter).Get_Score() // �ɼ�
				<< "\t�༶������" << (*iter).Get_Class_ptr()->Get_Rank(this) // �༶����
				<< std::endl;
		}
	}
}

void Student::Delete_Record(Class* const class_ptr)
{
	for (int i = 0; i < Record_List.size(); i++)
		if (Record_List[i].Get_Class_ptr() == class_ptr) // ���ҵ��ɼ���¼
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
