//PhoneBook.h

#include"Struct.h"
#include"Interface.h"

class PhoneBook
{
public:
	PhoneBook(); //�޲ι��캯��
	PhoneBook(DataType Member[], int SumNumber);//���ι��캯������ͨ��¼�Ĵ���
	~PhoneBook();//��������
	void PrintAllMember();//��ӡͨ��¼
	void AddMember(DataType MemberInformation);//���ӳ�Ա
	void DeleteMember(int ID);//����IDɾ����Ա
	void ChangeMember(int ID, DataType MemberInformation);//�޸ĳ�Ա
	void ToFindMember(int ID);//����IDѰ�ҳ�Ա
	int StatisticNumber();//ͳ�Ƴ�Ա����
	DataType FindMemberAndReturn(int ID);//���س�Ա��Ϣ
	Node* ReturnFront();//����front��Ա
	Node* ReturnBack();//����back��Ա
private:
	Node* front;
	Node* back;
};

//�޲ι��캯��
PhoneBook::PhoneBook()
{
	front = new Node;
	back = new Node;
	front->next = NULL;//û�в���ʱ����front���ָ���
	back = front;//��back����front��ʼ
}

//ͨ��¼�Ĵ���
PhoneBook::PhoneBook(DataType Member[], int SumNumber)
{
	front = new Node;
	back = new Node;
	back = front;//��ʼʱ����غ�
	for (int temp = 0; temp < SumNumber; temp++)//����ͨ��¼������
	{
		Node* tmp = new Node;
		tmp->PersonData = Member[temp];//��Ա����
		back->next = tmp;//��backǰ����ó�Ա����
		back = tmp;//׼����back�ظ�������һ�ֵĲ���
	}
	back->next = NULL;//�������һ��Ԫ�ص�nextָ���
}

//��������
PhoneBook::~PhoneBook()
{
	Node* tmp = front;//��tmpָ��front
	Node* NeedToDelete = NULL;//���Դ�����Ҫdelete��ָ��
	while (tmp)
	{
		tmp = tmp->next;//tmp�Ƶ���һ����Ϣ��λ��
		delete NeedToDelete;//�ͷ�
	}
}

//��ͨ��¼����β�������Ϣ 
void PhoneBook::AddMember(DataType MemberInformation)
{
	Node* tmp = new Node;
	tmp->PersonData = MemberInformation;//�����Ա����
	back->next = tmp;//β�������µ�����
	back = tmp;
	back->next = NULL;//����tmp
	cout << "���Ѿ��ɹ����ID�� " << MemberInformation.ID << "�ĳ�Ա" << endl;
}

//����IDɾ��ͨѶ¼�е�ָ������
void PhoneBook::DeleteMember(int ID)
{
	Node* tmp = front;//����һ�������������ݵ�tmpָ��
	do {
		if (tmp->next->PersonData.ID == ID)//�ҵ���Ҫɾ�������ݣ�tmp->nextָ��Ҫɾ��������
			break;
		tmp = tmp->next;
	} while (tmp->next);//һֱѭ��֪�����һ�tmp->next=NULLǰ
	if (tmp->next)//ȷ��ɾ���������ǿɱ�������
	{
		tmp->next = tmp->next->next;//��Ҫɾ�������ݵ�ǰһ��������Ҫɾ�������ݵĺ�һ����������
		cout << "��ɹ�ɾ����һ����Ϣ(ID:" << ID << ")" << endl;
	}
	else cout << "��ID�Ƿ����������롣" << endl;//�������Ҳ�����ӦID����ʾ������
}

//���ͨ��¼����
void PhoneBook::PrintAllMember()
{
	Node* p = front;//Ѱ��ͷ���
	cout << "���еĳ�Ա��ϢΪ:" << endl;
	while (p->next)//����һ����Ϣ��Ϊ��ʱ���������
	{
		cout << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
		p = p->next;
	}
}

//�޸�ָ��ID������
void PhoneBook::ChangeMember(int ID, DataType MemberInformation)
{
	Node* tmp = front;
	while (tmp->next)//��ָ�벻Ϊ��ʱ
	{
		int Temp = 0;
		tmp = tmp->next;//��tmp����һλ
		if (ID == tmp->PersonData.ID)//Ѱ�Ҷ�ӦID
		{
			tmp->PersonData = MemberInformation;//�滻��Ϣ
			Temp += 1;
		}
		if (Temp == 0 && tmp == NULL)//���޷�����ָ��IDʱ����ʾ������
			cout << "�޷��ҵ���ID��Ӧ�ĳ�Ա" << endl;
		else if (Temp) //��ʾ�û�����Ϣ����
			cout << "��ɹ��޸��� " << Temp << " ����Ա����Ϣ" << endl;
	}
}

//����ָ��ID��Ӧ����ϵ����Ϣ
void PhoneBook::ToFindMember(int ID)
{
	Node* tmp = front;
	int temp = 0;
	while (tmp->next)//ȷ��ָ��ǿ�
	{
		tmp = tmp->next;//��tmp����
		if (tmp->PersonData.ID == ID)//��������ʱ���������ѯ��ID��Ӧ����Ϣ
		{
			cout << "ID:" << tmp->PersonData.ID << " Name:" << tmp->PersonData.name << " Ch:" << tmp->PersonData.ch
				<< " Phone:" << tmp->PersonData.phone << " Address:" << tmp->PersonData.addr << endl;
			temp++;
		}
		else if (tmp->next == NULL && temp == 0)
			cout << "��ID�����ڣ��������롣" << endl;//ID�Ƿ�����ʾ������
	}
}

//Ѱ�ҳ�Ա�����س�Ա��Ϣ
DataType PhoneBook::FindMemberAndReturn(int ID)
{
	Node* tmp = front;
	int temp = 0;//�����ж��Ƿ��ȡ��������
	while (tmp->next)//ȷ��ָ��ǿ�
	{
		tmp = tmp->next;//��tmp����
		if (tmp->PersonData.ID == ID)//��������ʱ���������ѯ��ID��Ӧ����Ϣ
		{
			return tmp->PersonData;
			temp++;
		}
		if (tmp->next == NULL && temp == 0)
		{
			cout << "��ID�����ڣ��������롣" << endl;//ID�Ƿ�����ʾ������
			return { 0 };
		}
	}
}
	
//ͳ�Ƴ�Ա����
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

//����front��Ա
Node* PhoneBook::ReturnFront()
{
	return front;
}

//����back��Ա
Node* PhoneBook::ReturnBack()
{
	return back;
}