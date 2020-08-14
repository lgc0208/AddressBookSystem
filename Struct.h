//Struct.h

//题目基础要求
struct DataType
{
	int ID;
	char name[10];
	char ch;
	char phone[13];
	char addr[31];
};

//设置链表结点结构
struct Node
{
	DataType PersonData;
	struct Node* next;
};