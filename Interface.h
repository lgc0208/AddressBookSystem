//Interface.h

#ifndef Interface
#define Interface
#include<iostream>
using namespace std;

//�ָ���
extern void DevidedLine()
{
	cout << endl;
	for (int Times = 0; Times < 50; Times++)
	{
		cout << "-";
		if (Times == 49)
			cout << endl;
	}
	cout << endl;
}

//��ʼ������ʾ��
extern void StartPrompt()
{
	DevidedLine();
	cout << "��ȡͨ��¼��������1" << endl
		<<  "����ͨ��¼��������2" << endl;
	DevidedLine();
}

//��ʼ����������ʾ��
extern void Start()
{
	DevidedLine();
	cout << "���������ǰ�����֣�ѡ������Ҫ���еĲ���" << endl
		<< "1.ͨ��¼����" << endl
		<< "2.���Ѳ�����" << endl
		<< "3.�༶������" << endl
		<< "4.����������" << endl;
	DevidedLine();
}

//ͨ��¼����������ʾ��
extern void StartForPhoneBook()
{
	DevidedLine();
	cout << "���������ǰ�����֣�ѡ������Ҫ���еĲ���" << endl
		<< "1.�ؽ���ʼͨ��¼" << endl
		<< "2.����ͨ��¼��Ա" << endl
		<< "3.ɾ��ͨ��¼��Ա" << endl
		<< "4.�޸�ͨ��¼��Ա" << endl
		<< "5.�鿴����ͨ��¼��Ա" << endl
		<< "6.����ͨ��¼��Ա" << endl
		<< "7.����ͨ��¼��Ա" << endl
		<< "8.���ļ���ʽ���ͨ��¼��Ա" << endl;
	DevidedLine();
}

//���Ѳ�����������ʾ��
extern void StartForGoodFriendsBook()
{
	DevidedLine();
	cout << "���������ǰ�����֣�ѡ������Ҫ���еĲ���" << endl
		<< "1.�������Ѳ�" << endl
		<< "2.������Ѳ���Ա" << endl
		<< "3.ɾ�����Ѳ���Ա" << endl
		<< "4.�鿴���к��Ѳ���Ա" << endl
		<< "5.���Һ��Ѳ���Ա" << endl
		<< "6.���ļ���ʽ���ͨ��¼��Ա" << endl;
	DevidedLine();
}

//�༶������������ʾ��
extern void StartForClassmates()
{
	DevidedLine();
	cout << "���������ǰ�����֣�ѡ������Ҫ���еĲ���" << endl
		<< "1.�����༶��" << endl
		<< "2.����༶����Ա" << endl
		<< "3.ɾ���༶����Ա" << endl
		<< "4.�鿴���а༶����Ա" << endl
		<< "5.���Ұ༶����Ա" << endl
		<< "6.���ļ���ʽ���ͨ��¼��Ա" << endl;
	DevidedLine();
}

//����������������ʾ��
extern void StartForBlackBook()
{
	DevidedLine();
	cout << "���������ǰ�����֣�ѡ������Ҫ���еĲ���" << endl
		<< "1.����������" << endl
		<< "2.�����������Ա" << endl
		<< "3.ɾ����������Ա" << endl
		<< "4.�鿴���к�������Ա" << endl
		<< "5.���Һ�������Ա" << endl
		<< "6.���ļ���ʽ���ͨ��¼��Ա" << endl;
	DevidedLine();
}

//�ļ����������ʾ��
extern void PromptForBookOut()
{
	DevidedLine();
	cout << "����Ҫ�����������ǰĿ¼��������1" << endl
		<< "�����뵽���棬������2" << endl;
	cout << "���ѡ���ǣ� ";
}

//�˳�������ʾ��
extern char ChoiceToEnd(char Judge)
{
	DevidedLine();
	cout << "����Ҫ�˳���ǰ���棬������0��������������������0��������ַ�" << endl;
	cin >> Judge;
	DevidedLine();
	return Judge;
}

//�����Ա��Ϣ��ʾ��
extern void PromptForInput()
{
	cout << "����������ͨ��¼��Ա��ID���������Ա�m/w��,�绰����ַ" << endl;
}

//������ʾ��
extern void Error()
{
	DevidedLine();
	cout << "����������������������������" << endl;
	DevidedLine();
}

//�˳�������ʾ��
extern void PromptToEnd()
{
	DevidedLine();
	cout << "����Ҫ�˳�����������0����Ҫ���������������������0�������ַ�" << endl;
	DevidedLine();
}
#endif // !Interface