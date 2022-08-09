#include <algorithm>
#include <conio.h>
#include <functional>
#include <iomanip>
#include <iostream>

#include "Class.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"

using std::placeholders::_1;
using std::placeholders::_2;

std::vector<Class*> Class::_List;

Class::Class(Course* const course_ptr, Teacher* const teacher_ptr) :
	Course_ptr(course_ptr), Teacher_ptr(teacher_ptr), Order_by_Name(true), Order_by_ID(true), Order_by_Score(true) {}

void Class::Edit_Course(Course* const course_ptr)
{
	if (course_ptr == nullptr)
	{
		std::cerr << "in function void Class::Edit_Course(Course* const course_ptr):\n"
			<< "\tedit course failed.\n"
			<< "\tcause��course_ptr == nullptr\n";
		return;
	}
	else
		Course_ptr = course_ptr;
}

void Class::Edit_Teacher(Teacher* const teacher_ptr)
{
	if (teacher_ptr == nullptr)
	{
		std::cerr << "in function void Class::Edit_Teacher(Teacher* const teacher_ptr):\n"
			<< "\tedit teacher failed.\n"
			<< "\tcause��teacher_ptr == nullptr\n";
		return;
	}
	else
		Teacher_ptr = teacher_ptr;
}

Class* const Class::_New(Course* course_ptr, Teacher* teacher_ptr)
{
	unsigned long long serial; // �������

	if (course_ptr == nullptr) // �γ�ָ�� course_ptr Ϊȱʡֵ����Чֵ
	{
		std::cout << "�����༶ -> ";
		if (Course::_Get_Size()) // �γ��б�Ϊ��
		{
			std::cout << "ѡ��γ̣�������ţ���\n\n";
			Course::_Print_All();
			std::cout << "\n������ 0 �����γ̣�";
		}
		else
			std::cout << "ѡ��γ� -> ��ǰ�޿γ̣����� 0 �����γ̣�";
		std::cin >> serial;
		std::cin.ignore();

		if (serial>Course::_Get_Size())
		{
			std::cerr << "�����༶ -> error����ų����б�Χ��\n";
			return nullptr;
		}
		else if (serial > 0)
			course_ptr = Course::_Get_ptr(serial - 1); // �õ� serial ���γ�ָ����� course_ptr
		else
			course_ptr = Course::_New(); // �ڿ���̨�����γ�
	}

	if (teacher_ptr == nullptr) // ��ʦָ�� teacher_ptr Ϊȱʡֵ����Чֵ
	{
		std::cout <<course_ptr->Get_Name() << " -> �����༶ -> ";
		if (Teacher::_Get_Size()) // ��ʦ�б�Ϊ��
		{
			std::cout << "ѡ���ʦ��������ţ���\n\n";
			Teacher::_Print_All();
			std::cout << "\n������ 0 ������ʦ��";
		}
		else
			std::cout << "ѡ���ʦ -> ��ǰ�޽�ʦ������ 0 ������ʦ��";
		std::cin >> serial;
		std::cin.ignore();

		if (serial>Teacher::_Get_Size())
		{
			std::cerr << "�����༶ -> error����ų����б�Χ��\n";
			return nullptr;
		}
		else if (serial > 0)
			teacher_ptr = Teacher::_Get_ptr(serial - 1); // �õ� serial ����ʦָ����� teacher_ptr
		else
			teacher_ptr = Teacher::_New(); // �ڿ���̨������ʦ
	}

	// ����ظ���
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		if ((*iter)->Get_Course_ptr()->Get_Name() == course_ptr->Get_Name() && (*iter)->Get_Teacher_ptr()->Get_ID() == teacher_ptr->Get_ID())
		{
			std::cerr << "�����༶ -> error���༶�Ѵ��ڣ�\n";
			return (*iter); // �������а༶ָ��
		}
	}

	if (course_ptr == nullptr || teacher_ptr == nullptr) // ȷ���γ̺ͽ�ʦʧ��
	{
		std::cerr << "in function Class* const Class::_New(Course* course_ptr, Teacher* teacher_ptr):\n"
			<< "\t construct class failed\n"
			<< "\tcause: course_ptr == nullptr || teacher_ptr == nullptr\n";
		return nullptr;
	}
	else
	{
		Class* class_ptr = new Class(course_ptr, teacher_ptr);
		course_ptr->Add_Class(class_ptr); // ��Ӱ༶����Ӧ�γ�
		teacher_ptr->Add_Class(class_ptr); // ��Ӱ༶����Ӧ��ʦ
		_List.push_back(class_ptr); // ��Ӱ༶���༶�б�
		std::cout << "�����༶ -> �������༶���γ� " << course_ptr->Get_Name()
			<< "����ʦ " << teacher_ptr->Get_Name() << std::endl;
		return class_ptr; // ���ش����İ༶ָ��
	}
}

Course* const Class::Get_Course_ptr() const
{
	return Course_ptr;
}

Teacher* const Class::Get_Teacher_ptr() const
{
	return Teacher_ptr;
}

const size_t Class::Get_Student_Size() const
{
	return Student_List.size();
}

const size_t Class::Get_Serial_Number() const
{
	return std::find(_List.begin(), _List.end(), this) - _List.begin() + 1;
}

const _int64 Class::Get_Rank(const Student* const student_ptr)
{
	if (student_ptr == nullptr)
	{
		std::cerr << "in function const int Class::Get_Rank(Student* const student_ptr):\n"
			<< "can not find the student.\n"
			<< "cause: student_ptr == nullptr\n";
		return 0;
	}
	Rank(Rank_Score); // ���ճɼ�����
	auto iter = Student_List.begin();
	for (; iter != Student_List.end(); iter++)
	{
		if ((*iter)==student_ptr) // �ҵ���ѧ��
			break;
	}
	if (iter == Student_List.end()) // δ�ҵ��ɼ�
	{
		std::cerr << student_ptr->Get_Name() << " -> �༶���� -> error���Ҳ�����ѧ����\n";
		return 0;
	}
	else
		return iter - Student_List.begin() + 1;
}

void Class::Add_Student(Student* const student_ptr)
{
	if (student_ptr == nullptr)
	{
		std::cerr << "in function void Class::Add_Student(Student* const student_ptr):\n"
			<< "\tadd student failed.\n"
			<< "\tcause��class_ptr == nullptr\n";
		return;
	}
	else
	{
		Student_List.push_back(student_ptr);
		std::cout << "�༶���γ� " << Course_ptr->Get_Name()
			<< "����ʦ " << Teacher_ptr->Get_Name()
			<< " -> ���ѧ���������ѧ�� " << student_ptr->Get_Name()
			<< std::endl;
		Order_by_Name = false;
		Order_by_ID = false;
		Order_by_Score = false;
	}
}

void Class::Delete_Student(Student* const student_ptr)
{
	auto iter = std::find(Student_List.begin(), Student_List.end(), student_ptr);
	if (iter != Student_List.end()) // ���ҵ�ѧ��
	{
		Student_List.erase(iter);
		std::cout << "�༶���γ� " << Course_ptr->Get_Name()
			<< "����ʦ " << Teacher_ptr->Get_Name()
			<< " -> ɾ��ѧ������ɾ��ѧ�� " << student_ptr->Get_Name()
			<< std::endl;
	}
}

const double Class::Get_Average_Score() const
{
	if (Student_List.empty())
	{
		std::cerr << "�༶���γ� " << Get_Course_ptr()->Get_Name()
			<< "����ʦ " << Get_Teacher_ptr()->Get_Name()
			<< " -> ƽ���� -> error���༶��ѧ����\n";
		return 0;
	}
	else
	{
		double total_score = 0;
		for (auto iter = Student_List.begin(); iter != Student_List.end(); iter++)
			total_score += (*iter)->Get_Score(this); // ѧ���ÿγ̳ɼ����
		return total_score / Student_List.size();
	}

}

void Class::Rank(const Sort_Condition& sort_condition)
{
	switch (sort_condition)
	{
	case Rank_Name: // ����ѧ����������
		if (Order_by_Name == false)
		{
			std::sort(Student_List.begin(), Student_List.end(), compare_name);
			Order_by_Name = true;
		}
		break;
	case Rank_ID: // ����ѧ��ѧ������
		if (Order_by_ID == false)
		{
			std::sort(Student_List.begin(), Student_List.end(), compare_id);
			Order_by_ID = true;
		}
		break;
	case Rank_Score: // ����ѧ���ɼ�����
		if (Order_by_Score == false)
		{
			std::sort(Student_List.begin(), Student_List.end(), bind(&Class::compare_score, this, _1, _2));
			Order_by_Score = true;
		}
		/*
				bind(&Class::compare_score, this, _1, _2))	�ο����������ݣ�

				using namespace std;
				using placeholders::_1;
				using placeholders::_2;
				class Solution {
				public:
					string minNumber(vector<int> &nums) {
						sort(nums.begin(), nums.end(), bind(&Solution::comp, this, _1, _2));
						string ans;
						for (const auto &c : nums) ans += to_string(c);
						return ans;
					}

					bool comp(int &a, int &b) {
						string sa = to_string(a), sb = to_string(b);
						return sa + sb < sb + sa;
					}
				};

				��������������������������������
				��Ȩ����������ΪCSDN�������¶���������˹����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
				ԭ�����ӣ�https://blog.csdn.net/qq_33551749/article/details/108247630

		*/
	}
}

bool Class::compare_name(Student* const student_ptr_1, Student* const student_ptr_2)
{
	if (student_ptr_1->Get_Name() < student_ptr_2->Get_Name())
		return true;
	else if (student_ptr_1->Get_Name() == student_ptr_2->Get_Name() && student_ptr_1->Get_ID() < student_ptr_2->Get_ID())
		return true; // ������ͬʱ�Ƚ�ѧ��
	else
		return false;

}

bool Class::compare_id(Student* const student_ptr_1, Student* const student_ptr_2)
{
	if (student_ptr_1->Get_ID() < student_ptr_2->Get_ID()) // ѧ�ű���Ϊ������ͬ
		return true;
	else
		return false;
}

bool Class::compare_score(Student* const student_ptr_1, Student* const student_ptr_2) const
{
	if (student_ptr_1->Get_Score(this) > student_ptr_2->Get_Score(this))
		return true;
	else if (student_ptr_1->Get_Score(this) == student_ptr_2->Get_Score(this) && student_ptr_1->Get_ID() < student_ptr_2->Get_ID())
		return true; // �ɼ���ͬʱ�Ƚ�ѧ��
	else
		return false;
}

void Class::Print_Record() const
{
	size_t student_num = Student_List.size(); // ѧ������
	if (student_num) // ѧ���б�Ϊ��
	{
		int Grade_Distribution[10] = { 0 }; // ����ͳ�Ƴɼ��ֲ���10 �������Ӧ 1 ��Ԫ��
		for (auto iter = Student_List.begin(); iter != Student_List.end(); iter++)
		{
			std::cout << iter - Student_List.begin() + 1 << '.' // ��ӡ���
				<< std::setw(10) << (*iter)->Get_Name() // ��ӡ����
				<< std::setw(15) << (*iter)->Get_ID() // ��ӡѧ��
				<< std::setw(10) << (*iter)->Get_Faculty() // ��ӡԺϵ
				<< std::setw(10) << (*iter)->Get_Score(this) // ��ӡ�ɼ�
				<< std::endl;

			// �÷�ת 10 ���ƣ��ضϵ���λ
			int ten_score = int((*iter)->Get_Score(this) / Get_Course_ptr()->Get_Full_Score() * 10);
			if (ten_score == 10)
				ten_score = 9; // ����ͳ���ڣ�90% ~ 100%����Χ��
			Grade_Distribution[ten_score]++;
		}
		if (student_num) // ��Ч�ɼ�����Ϊ 0
		{
			std::cout << "�༶�ɼ� -> �༶���γ� " << Get_Course_ptr()->Get_Name()
				<< "����ʦ " << Get_Teacher_ptr()->Get_Name()
				<< " -> ƽ���֣�" << Get_Average_Score()
				<< "\n�ɼ��ֲ���\n";
			for (int i = 0; i < 10; i++)
				if (Grade_Distribution[i]) // �ɼ��ֲ���Ϊ 0������ѧ���ɼ����ڷ�Χ��
					std::cout << "        �÷��ʣ�" << i * 10 << "% ~ " << (i + 1) * 10 << "%\tѧ��ռ�ȣ�"
					<< double(Grade_Distribution[i]) / student_num * 100 << "%\n";
		}
	}
	else
		std::cerr << "�༶�ɼ� -> �༶���γ� " << Get_Course_ptr()->Get_Name()
		<< "����ʦ " << Get_Teacher_ptr()->Get_Name()
		<< " -> error����ǰ�༶��ѧ����\n";
}

void Class::Print() const
{
	std::cout << "�༶���γ� " << Get_Course_ptr()->Get_Name() // �γ���
		<< "����ʦ " << Get_Teacher_ptr()->Get_Name() // ��ʦ��
		<< "��ѧ��������" << Student_List.size() // ѧ������
		<< std::endl;
}

void Class::_Print_All()
{
	for (auto iter = _List.begin(); iter != _List.end(); iter++)
		std::cout << iter - _List.begin() + 1 << '.' // ���
		<< "�༶���γ� " << (*iter)->Get_Course_ptr()->Get_Name()
		<< "����ʦ " << (*iter)->Get_Teacher_ptr()->Get_Name()
		<< "��ѧ��������" << (*iter)->Student_List.size()
		<< std::endl;
}

void Class::_Edit_All()
{
	while (true)
	{
		bool flag = false; // ��ǣ��༶�б�Ϊ�գ�2 ���� ����������
		if (_List.empty())
		{
			std::cout << "�༭�༶ -> ����ǰ�ް༶��\n"
				<< "�༭�༶ -> ѡ��༭��ʽ��1.��������������ȡ��...";
			flag = true;
		}
		else
		{
			std::cout << std::endl;
			_Print_All(); // ��ӡȫ���༶
			std::cout << "\n�༭�༶ -> ѡ��༭��ʽ��1.������2.ɾ������������ȡ��...";
		}

		int new_num; // switch ���������
		char input = _getch(); // ����ѡ��
		std::cout << std::endl;

		switch (input)
		{
		case '1': // �����༶
			Class::_New();
			break;

		case '2': // ɾ���༶
			if (flag) // ��ǰ�ް༶���� default ��ͬ����
				return;
			std::cout << "ɾ���༶ -> ������� �� ���� 0 ȡ����";
			std::cin >> new_num;
			std::cin.ignore();

			if (new_num>_List.size())
				std::cerr << "ɾ���༶ -> error����ų����б�Χ��\n";
			else if (new_num > 0)
				delete _List[new_num - 1];
			break;

		default: // ȡ��
			return;
		}
		std::cout << "�༭�༶ -> ��E/e�����༭�༶��������������...";
		input = _getch();
		std::cout << std::endl;
		if (input != 'E' && input != 'e') // �����༭
			break;
	}
}

const size_t Class::_Get_Size()
{
	return _List.size();
}

Class* const Class::_Get_ptr(const size_t& n)
{
	// n ȡֵ�� 0 ��ʼ
	if (n < 0 || n >= _List.size())
	{
		std::cerr << "in function Class* const Class::Get_Class_ptr(const int& n):\n"
			<< "\tThe " << n << " th record does not exist, a null pointer has been returned.\n"
			<< "\tcause: n<0 || n>=_List.size()\n";
		return nullptr;
	}
	else
		return _List[n];
}

void Class::_Write_File(std::ofstream& file)
{
	file << "## �༶���ܼƣ�" << _Get_Size() << "��\n\n" // ����
		<< "| ��� | �γ� | ��ʦ |\n" // ��ͷ
		<< "| - | - | - |\n";

	for (auto iter = _List.begin(); iter != _List.end(); iter++)
	{
		file << "| " << iter - _List.begin() + 1 // �༶���
			<< " | ` " << (*iter)->Get_Course_ptr()->Get_Serial_Number() // �γ����
			<< " `  " << (*iter)->Get_Course_ptr()->Get_Name() << " | ` " // �γ���
			<< (*iter)->Get_Teacher_ptr()->Get_Serial_Number() << " `  " // ��ʦ���
			<< (*iter)->Get_Teacher_ptr()->Get_Name() << " |\n"; // ��ʦ����
	}
	file << std::endl;
}

void Class::_Read_File(std::ifstream& file)
{
	char delimiter; // �ָ���
	unsigned long long num_course; // �γ����
	unsigned long long num_teacher; // ��ʦ���

	// �ƶ���ָ�뵽�༶�б�
	file.seekg(std::ios_base::beg); // ��λ���ļ�ͷ
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ������
	if (file.peek() != '#')
		file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���γ��б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ����ʦ�б����
	file.get(); // ����ڶ���'#'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '#'); // ��λ���༶�б����
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "## �༶"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ��������
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| ��� | �γ� | ��ʦ |"
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� "| - | - | - |"

	delimiter = file.get(); // �����һ�����ַ�
	while (delimiter == '|')
	{
		file.ignore(std::numeric_limits<std::streamsize>::max(), '`'); // �ƶ���ָ�뵽�γ����
		file >> num_course; // ����γ����
		file.get(); // ���� ' '
		file.get(); // ���� '|'
		file.ignore(std::numeric_limits<std::streamsize>::max(), '`'); // �ƶ���ָ�뵽��ʦ���
		file >> num_teacher; // �����ʦ���
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �ƶ���ָ�뵽��β
		delimiter = file.get(); // ������һ�����ַ�
		Class::_New(Course::_Get_ptr(num_course - 1), Teacher::_Get_ptr(num_teacher - 1)); // �����༶
	}
}

void Class::Delete(Course* const course_ptr)
{
	size_t class_num = course_ptr->Get_Class_Size();
	for (int i = 0; i < class_num; i++)
		delete course_ptr->Get_Class_ptr(i); // �������γ�ǰ�����γ̵�ȫ���༶
}

void Class::Delete(Teacher* const teacher_ptr)
{
	size_t class_num = teacher_ptr->Get_Class_Size();
	for (int i = 0; i < class_num; i++)
		delete teacher_ptr->Get_Class_ptr(i); // ��������ʦǰ������ʦ��ȫ���༶
}

Class::~Class()
{
	// ����ؿγ���ɾ���༶
	this->Get_Course_ptr()->Delete_Class(this);
	// ����ؽ�ʦ��ɾ����ʦ
	this->Get_Teacher_ptr()->Delete_Class(this);
	// �����ѧ����ɾ���ɼ���¼
	for (auto iter = this->Student_List.begin(); iter != this->Student_List.end(); iter++)
		(*iter)->Delete_Record(this);
	// �Ӱ༶�б���ɾ��
	_List.erase(std::find(_List.begin(), _List.end(), this));

	std::cout << "ɾ���༶ -> ��ɾ���༶���γ� " << Get_Course_ptr()->Get_Name()
		<< "����ʦ " << Get_Teacher_ptr()->Get_Name()
		<< std::endl;
}

std::ostream& operator<<(std::ostream& output, const Class& class_obj)
{
	output << "�༶���γ� " << class_obj.Get_Course_ptr()->Get_Name() // �γ���
		<< "����ʦ " << class_obj.Get_Teacher_ptr()->Get_Name() // ��ʦ��
		<< "��ѧ��������" << class_obj.Student_List.size() // ѧ������
		<< std::endl;
	return output;
}
