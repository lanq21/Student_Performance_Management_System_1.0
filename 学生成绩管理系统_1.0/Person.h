#pragma once
#include <string>

class Person
{
public:

	/// <returns>名称</returns>
	const std::string& Get_Name() const;

	/// <returns>编号</returns>
	const std::string& Get_ID() const;

	/// <returns>院系</returns>
	const std::string& Get_Faculty() const;

	/// <returns>人员编号相同</returns>
	const bool operator==(const Person& person);

	/// <summary>
	/// 纯虚函数，在控制台编辑
	/// </summary>
	virtual void Edit() = 0;

	/// <summary>
	/// 虚函数，在控制台打印
	/// </summary>
	virtual void Print() const;

	virtual ~Person();

protected:

	std::string ID; // 编号

	/// <summary>
	/// 带缺省参数的构造函数
	/// name默认初始化为" "
	/// id默认初始化为"0"
	/// faculty默认初始化为"电子系"
	/// </summary>
	/// <param name="name">姓名</param>
	/// <param name="id">编号</param>
	/// <param name="faculty">院系</param>
	Person(const std::string& name = " ", const std::string& id = "0", const std::string& faculty = "电子系");

	/// <summary>
	/// 编辑对象名称
	/// </summary>
	/// <param name="name">姓名</param>
	void Edit_Name(const std::string& name);

	/// <summary>
	/// 纯虚函数，编辑对象编号
	/// </summary>
	/// <param name="id">编号</param>
	virtual void Edit_ID(const std::string& id) = 0;

	/// <summary>
	/// 编辑对象院系
	/// </summary>
	/// <param name="faculty">院系</param>
	void Edit_Faculty(const std::string& faculty);

private:

	std::string Name; // 姓名
	std::string Faculty; // 院系

};