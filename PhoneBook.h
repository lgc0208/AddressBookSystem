//PhoneBook.h

#include"Struct.h"
#include"Interface.h"

class PhoneBook
{
public:
	PhoneBook(); //无参构造函数
	PhoneBook(DataType Member[], int SumNumber);//含参构造函数，即通信录的创建
	~PhoneBook();//析构函数
	void PrintAllMember();//打印通信录
	void AddMember(DataType MemberInformation);//增加成员
	void DeleteMember(int ID);//根据ID删除成员
	void ChangeMember(int ID, DataType MemberInformation);//修改成员
	void ToFindMember(int ID);//根据ID寻找成员
	int StatisticNumber();//统计成员个数
	DataType FindMemberAndReturn(int ID);//返回成员信息
	Node* ReturnFront();//返回front成员
	Node* ReturnBack();//返回back成员
private:
	Node* front;
	Node* back;
};

//无参构造函数
PhoneBook::PhoneBook()
{
	front = new Node;
	back = new Node;
	front->next = NULL;//没有参数时，让front结点指向空
	back = front;//让back结点从front开始
}

//通信录的创建
PhoneBook::PhoneBook(DataType Member[], int SumNumber)
{
	front = new Node;
	back = new Node;
	back = front;//开始时结点重合
	for (int temp = 0; temp < SumNumber; temp++)//读入通信录的数据
	{
		Node* tmp = new Node;
		tmp->PersonData = Member[temp];//成员数据
		back->next = tmp;//在back前插入该成员数据
		back = tmp;//准备对back重复进行下一轮的操作
	}
	back->next = NULL;//令其最后一个元素的next指向空
}

//析构函数
PhoneBook::~PhoneBook()
{
	Node* tmp = front;//将tmp指向front
	Node* NeedToDelete = NULL;//用以储存需要delete的指针
	while (tmp)
	{
		tmp = tmp->next;//tmp移到下一个信息的位置
		delete NeedToDelete;//释放
	}
}

//在通信录的最尾部添加信息 
void PhoneBook::AddMember(DataType MemberInformation)
{
	Node* tmp = new Node;
	tmp->PersonData = MemberInformation;//储存成员数据
	back->next = tmp;//尾部插入新的数据
	back = tmp;
	back->next = NULL;//处理tmp
	cout << "你已经成功添加ID： " << MemberInformation.ID << "的成员" << endl;
}

//根据ID删除通讯录中的指定数据
void PhoneBook::DeleteMember(int ID)
{
	Node* tmp = front;//定义一个用来处理数据的tmp指针
	do {
		if (tmp->next->PersonData.ID == ID)//找到所要删除的数据，tmp->next指向要删除的数据
			break;
		tmp = tmp->next;
	} while (tmp->next);//一直循环知道最后一项，tmp->next=NULL前
	if (tmp->next)//确保删除的数据是可被操作的
	{
		tmp->next = tmp->next->next;//将要删除的数据的前一个数据与要删除的数据的后一项数据链接
		cout << "你成功删除了一条信息(ID:" << ID << ")" << endl;
	}
	else cout << "该ID非法，请检查输入。" << endl;//如若查找不到对应ID，提示操作者
}

//输出通信录内容
void PhoneBook::PrintAllMember()
{
	Node* p = front;//寻找头结点
	cout << "所有的成员信息为:" << endl;
	while (p->next)//当下一条信息不为空时，持续输出
	{
		cout << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
		p = p->next;
	}
}

//修改指定ID的内容
void PhoneBook::ChangeMember(int ID, DataType MemberInformation)
{
	Node* tmp = front;
	while (tmp->next)//当指针不为空时
	{
		int Temp = 0;
		tmp = tmp->next;//将tmp下移一位
		if (ID == tmp->PersonData.ID)//寻找对应ID
		{
			tmp->PersonData = MemberInformation;//替换信息
			Temp += 1;
		}
		if (Temp == 0 && tmp == NULL)//当无法查找指定ID时，提示输入者
			cout << "无法找到该ID对应的成员" << endl;
		else if (Temp) //提示置换的信息个数
			cout << "你成功修改了 " << Temp << " 个成员的信息" << endl;
	}
}

//查找指定ID对应的联系人信息
void PhoneBook::ToFindMember(int ID)
{
	Node* tmp = front;
	int temp = 0;
	while (tmp->next)//确保指针非空
	{
		tmp = tmp->next;//将tmp后移
		if (tmp->PersonData.ID == ID)//符合条件时，输出所查询的ID对应的信息
		{
			cout << "ID:" << tmp->PersonData.ID << " Name:" << tmp->PersonData.name << " Ch:" << tmp->PersonData.ch
				<< " Phone:" << tmp->PersonData.phone << " Address:" << tmp->PersonData.addr << endl;
			temp++;
		}
		else if (tmp->next == NULL && temp == 0)
			cout << "该ID不存在，请检查输入。" << endl;//ID非法，提示操作者
	}
}

//寻找成员并返回成员信息
DataType PhoneBook::FindMemberAndReturn(int ID)
{
	Node* tmp = front;
	int temp = 0;//用于判断是否读取到了数据
	while (tmp->next)//确保指针非空
	{
		tmp = tmp->next;//将tmp后移
		if (tmp->PersonData.ID == ID)//符合条件时，输出所查询的ID对应的信息
		{
			return tmp->PersonData;
			temp++;
		}
		if (tmp->next == NULL && temp == 0)
		{
			cout << "该ID不存在，请检查输入。" << endl;//ID非法，提示操作者
			return { 0 };
		}
	}
}
	
//统计成员个数
int PhoneBook::StatisticNumber()
{
	Node* p = front;
	int Number = 0;
	while (p != NULL)
	{
		p = p->next;
		Number++;
	}
	Number -= 1;
	return Number;
}

//返回front成员
Node* PhoneBook::ReturnFront()
{
	return front;
}

//返回back成员
Node* PhoneBook::ReturnBack()
{
	return back;
}