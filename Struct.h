//Struct.h

//��Ŀ����Ҫ��
struct DataType
{
	int ID;
	char name[10];
	char ch;
	char phone[13];
	char addr[31];
};

//����������ṹ
struct Node
{
	DataType PersonData;
	struct Node* next;
};