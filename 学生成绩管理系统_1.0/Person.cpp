#include <iostream>

#include "Person.h"

Person::Person(const std::string& name, const std::string& id, const std::string& faculty) :
	Name(name), ID(id), Faculty(faculty) {}

const std::string& Person::Get_Name() const
{
	return Name;
}

const std::string& Person::Get_ID() const
{
	return ID;
}

const std::string& Person::Get_Faculty() const
{
	return Faculty;
}

const bool Person::operator==(const Person& person)
{
	if (ID == person.ID)
		return true;
	else
		return false;
}

void Person::Edit_Name(const std::string& name)
{
	Name = name;
}

void Person::Edit_Faculty(const std::string& faculty)
{
	Faculty = faculty;
}

void Person::Print() const
{
	std::cout << "ÐÕÃû£º" << Get_Name() << std::endl
	 << "±àºÅ£º" << Get_ID() << std::endl
	 << "ÔºÏµ£º" << Get_Faculty() << std::endl;
}

Person::~Person() {}