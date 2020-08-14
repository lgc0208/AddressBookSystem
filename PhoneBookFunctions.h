//PhoneBookFunctions.h

#ifndef PhoneBookFunctions
#define PhoneBookFunctions
#include<string>
#include<fstream>
#include<istream>
#include<windows.h>//��ȡ����ϵͳ������·��(�ο���csdn)
#include<shlobj.h>//��ȡ����ϵͳ������·��(�ο���csdn)
#include"PhoneBook.h"

//�ж���Ҫ��������ݸ����Ƿ�Ϸ�
extern int ChooseNumberOfNewMember()
{
	int Num=1;
	cout << "������Ҫ���������ݵĸ���(�������100������): ";
	do
	{
		cin >> Num;//��������
		if (Num > 100 || Num < 0)
		{
			cout << "��������ݸ����������������룺 ";
			cin >> Num;
		}
	} while (Num > 100 || Num < 0);
	return Num;
}

//���빦�ܺ���
extern void InputMembersInformation(DataType &StartMembers )
{
	cin >> StartMembers.ID >> StartMembers.name >> StartMembers.ch >> StartMembers.phone >> StartMembers.addr;
}

//����ԭʼͨ��¼����DataType��ɣ�
extern void FoundPhoneBook(DataType* StartMembers,int FirstNum)
{
	for (int temp = 0; temp < FirstNum; temp++)
	{
		InputMembersInformation(*(StartMembers + temp));
	}//�������
}

//��Ļչʾͨ��¼��Ϣ
extern void ShowAllMembers(PhoneBook MyPhoneBook)
{
	DevidedLine();
	cout << "Ŀǰ��ѡ�˵�������Ϊ��" << endl;
	MyPhoneBook.PrintAllMember();
	DevidedLine();
}

//��ȡ��ͬ���Ե�����·��(�ο���CSDN��https://blog.csdn.net/CosmopolitanMe/article/details/80512721?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)
/*
	���п��ܳ��ִ���C2208����_RPC_SYNTAX_IDENTIFIER��: û��ʹ�ô����ͽ��ж���ĳ�Ա
	��ע�͵��öδ�����ȡ��ע�ͺ��ٱ���ԭ����δ��֪����δ���������ƵĴ������������һ�������ļ���һ��������
*/
extern string  GetDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[300];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {// ����ɹ�����true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}
	return string(szDir);
}

//ͨ��¼����ת��(��string����ת����char���飬char�����Լ�int����)
extern void InputBookInInformation(DataType &StartMembers,string EachInformation[],int loop)
{
	if (EachInformation[loop] != "!")
	{
		StartMembers.ID = stoi(EachInformation[loop]);
		strcpy_s(StartMembers.name, EachInformation[loop + 1].c_str());//https://blog.csdn.net/ggbody/article/details/84674055
		strcpy_s(&StartMembers.ch, strlen(EachInformation[loop + 2].c_str())+1, EachInformation[loop + 2].c_str());
		strcpy_s(StartMembers.phone,  EachInformation[loop + 3].c_str());
		strcpy_s(StartMembers.addr, EachInformation[loop + 4].c_str());
	}
}

//�ļ�����ͨ��¼��Ϣ
extern void BookIn( DataType* StartMembers, int &FirstNum)
{
	ifstream In;
	string Number;
	string FileName;
	string Information;
	cout << "�����벻����׺���ļ���: (����Ҫ��ȡĬ�ϱ����ͨ��¼��������default)" << endl
		<< "�뱣֤ͨ��¼�ļ����ϸ�ʽ���ұ����ڳ���Ŀ¼��" << endl;
	cin >> FileName;

	if (FileName != "default")
	{
		FileName += ".txt";//��׺��
	}
	else 
	{
		FileName = "MyPhoneBook.txt";
	}
	In.open(FileName);
	if (!In)
		cout << "���ļ������ڣ����顣" << endl;
	else
	{
		getline(In, Number);//���ж�ȡ�ļ�
		getline(In, Information, '!');//��̾����Ϊ��ȡ����ֹ����
		//Information += " !";//��Ϊת������ֹ����
		FirstNum = atoi(Number.c_str());//ת��Ϊint����

		int s = 0;
		string* EachInformation = new string[1000];//��̬����ռ�
		for (int i = 0; i < Information.length(); i++) { //���ַ����ָ���ַ�������
			if ((Information[i] == ' ') || (Information[i] == '\n')) {                 //�Կո���߻��з���Ϊ�ָ���
				s++;
				continue;
			}
			else EachInformation[s] += Information[i];  //���ָ�õ��ַ����ŵ�EachInformation������
		}
		for (int temp = 0, loop = 0; temp < FirstNum; temp++, loop += 5)
		{
			InputBookInInformation(*(StartMembers + temp), EachInformation, loop);
		}
		delete[] EachInformation;
	}
	In.close();
	}

//Ĭ����ʽ����ͨ��¼
extern void SavePhoneBook(PhoneBook BookText)
{
	int Number = BookText.StatisticNumber();
	string Name = "MyPhoneBook.txt";
	Node* p = BookText.ReturnFront();
	ofstream Out(Name);//�ڵ�ǰĿ¼������ļ�
	Out << Number << endl;//��һ�������Ա����
	while (p->next)//����һ����Ϣ��Ϊ��ʱ���������
	{
		Out << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
		p = p->next;
	}
	Out << "!" << endl;
	Out.close();
	cout << "����ɹ���" << endl;
}

//�ļ�����ò���Ϣ
extern void BookOut(PhoneBook BookText)
{
	int Choice;
	PromptForBookOut();
	cin >> Choice;
	switch (Choice)
	{
		case 1://���������ǰĿ¼
		{
			int Number = BookText.StatisticNumber();
			cout << "���Զ����ļ�����" << endl;
			string Name;
			cin >> Name;
			Name += ".txt";
			Node* p = BookText.ReturnFront();
			ofstream Out(Name);//�ڵ�ǰĿ¼������ļ�
			Out << Number << endl;//��һ�������Ա����
			while (p->next)//����һ����Ϣ��Ϊ��ʱ���������
			{
				Out << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
				p = p->next;
			}
			Out << "!" << endl;
			Out.close();
			cout << "�ѱ������ļ�Ŀ¼��" << endl;
			break;
		}
		case 2://�������������
			{
				int Number = BookText.StatisticNumber();
				cout << "���Զ����ļ�����" << endl;
				string Name;
				string ToDesktop = GetDesktopPath();//��ȡ����ϵͳ������·��
				ToDesktop += "\\";
				cin >> Name;
				Name += ".txt";
				ToDesktop += Name;
				Node* p = BookText.ReturnFront();
				ofstream Out(ToDesktop);//�Ծ���·������ļ�
				Out << Number<< endl;//��һ�������Ա����
				while (p->next)//����һ����Ϣ��Ϊ��ʱ���������
				{
					Out << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
					p = p->next;
				}
				Out << "!" << endl;
				Out.close();
				cout << "�ѱ������ļ�Ŀ¼��" << endl;
				break;
			}
		default:
			{
				Error();
				break;
			}
	}
	
}

//����ͨ��¼��Ա�ĸ�������
extern DataType CinDataType()
{
	DataType Information;
	PromptForInput();
	cin >> Information.ID >> Information.name >> Information.ch >> Information.phone >> Information.addr;
	return Information;
}

//�ؽ�ͨ��¼
extern void RebuildPhoneBook(DataType *StartMembers)
{
	PromptForInput();
	int NumTest;
	NumTest = ChooseNumberOfNewMember();
	for (int temp = 0; temp < NumTest; temp++)
	{
		PromptForInput();
		InputMembersInformation(*(StartMembers + temp));
	}//����ĳ�ʼ����
	PhoneBook MyPhoneBook(StartMembers, NumTest);//���캯��
	ShowAllMembers(MyPhoneBook);//չʾ��Ϣ
}

//���ӳ�Ա
extern void AddPhoneBook(PhoneBook PhoneBook)
{
	DataType AddInformation;
	AddInformation = CinDataType();
	PhoneBook.AddMember(AddInformation);//���ú���
}

//���ڳ�ͨ��¼���Book�����Ա��ʹ������ĳ�Աʼ�մ���ͨ��¼��
extern void AddToOtherBook(PhoneBook NewBook,PhoneBook MyPhoneBook)
{
	int IDtoNewBook;
	char JudgeToNewBook = '1';
	DataType MemberToNewBook;
	do {
		DevidedLine();
		cout << "����������Ҫ�����ID:";
		cin >> IDtoNewBook;
		MemberToNewBook = MyPhoneBook.FindMemberAndReturn(IDtoNewBook);
		if (MemberToNewBook.ch != 0)//�������ʱ��������ID���󣬲����ٴ������һ������
			NewBook.AddMember(MemberToNewBook);
		DevidedLine();
		cout << "��Ҫ������ӣ��������0��������ַ���" << endl
			<< "��Ҫ���أ�������0." << endl;
		DevidedLine();
		cin >> JudgeToNewBook;
	} while (JudgeToNewBook != '0');
}

//ɾ����Ա
extern void DeleteAMember(PhoneBook PhoneBook)
{
	int IDtoDelete;
	cout << "��������Ҫɾ����ID" << endl;
	cin >> IDtoDelete;
	Node* tmp = PhoneBook.ReturnFront();
	int temp = 0;//�ж��Ƿ���ڸ�ID
	if (!tmp->next)//����ǰĿ¼Ϊ��ʱ����ʾ�쳣
		Error();
	while (tmp->next)//ȷ��ָ��ǿ�
	{
		tmp = tmp->next;//��tmp����
		if (tmp->PersonData.ID == IDtoDelete)//��������ʱ��temp����
		{
			temp++;
			PhoneBook.DeleteMember(IDtoDelete);
		}
		else if (tmp->next == NULL && temp == 0)
			cout << "��ID�����ڣ��������롣" << endl;//ID�Ƿ�����ʾ������
	}
}

//�޸ĳ�Ա
extern void ChangeAMember(PhoneBook PhoneBook)
{
	int IDtoChange;
	DataType ChangeInformation;
	cout << "��������Ҫ�޸ĵĳ�ԱID�� " << endl;
	cin >> IDtoChange;
	cout << "�������޸ĺ�ĳ�Ա��Ϣ��" << endl;
	ChangeInformation = CinDataType();
	PhoneBook.ChangeMember(IDtoChange, ChangeInformation);//���ú���
}

//���ҳ�Ա
extern void FindAMember(PhoneBook PhoneBook)
{
	int IDtoFind;
	cout << "����������Ҫ���ҵ�ID�� ";
	cin >> IDtoFind;
	PhoneBook.ToFindMember(IDtoFind);//���ú���
}

//�����²�
extern void FoundNewBook(PhoneBook MyPhoneBook, PhoneBook NewBook)
{
	int IDtoNewBook;
	char JudgeToNewBook = '1';
	DataType MemberToNewBook;
	do {
		DevidedLine();
		cout << "����������Ҫ�����ID:";
		cin >> IDtoNewBook;
		MemberToNewBook = MyPhoneBook.FindMemberAndReturn(IDtoNewBook);
		if (MemberToNewBook.ch != 0)//�������ʱ��������ID���󣬲����ٴ������һ������
			NewBook.AddMember(MemberToNewBook);
		DevidedLine();
		cout << "��Ҫ������ӣ��������0��������ַ���" << endl
			<< "��Ҫ���أ�������0." << endl;
		DevidedLine();
		cin >> JudgeToNewBook;
	} while (JudgeToNewBook != '0');
}

//ͨ��¼�Ĺ�������
extern void AllPhoneBookFunctions(PhoneBook MyPhoneBook,DataType* StartMembers,int ChoiceForStart,char Judge)
{
	do {
		StartForPhoneBook();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://�ؽ�ͨ��¼
		{
			RebuildPhoneBook(StartMembers);
			break;
		}
		case 2://���ӳ�Ա
		{
			AddPhoneBook(MyPhoneBook);
			break;
		}
		case 3://ɾ����Ա
		{
			DeleteAMember(MyPhoneBook);
			break;
			//ShowAllMembers(MyPhoneBook);//չʾ���г�Ա
		}
		case 4://�޸ĳ�Ա
		{
			ChangeAMember(MyPhoneBook);
			break;
		}
		case 5://��ӡ��Ա
		{
			ShowAllMembers(MyPhoneBook);//չʾ��Ϣ
			break;
		}
		case 6://���ҳ�Ա
		{
			FindAMember(MyPhoneBook);
			break;
		}
		case 7://����ͨ��¼
		{
			SavePhoneBook(MyPhoneBook);
			break;
		}
		case 8://���ļ���ʽ�����Ա
		{
			BookOut(MyPhoneBook);
			break;
		}
		default://��ʾ�������
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}

//���Ѳ��Ĺ�������
extern void AllGoodFriendsBookFunctions(PhoneBook MyGoodFriends, PhoneBook MyPhoneBook, DataType* StartMembers, int ChoiceForStart, char Judge)
{
	do {
		StartForGoodFriendsBook();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://�������Ѳ�
		{
			FoundNewBook(MyPhoneBook, MyGoodFriends);
			break;
		}
		case 2://���ӳ�Ա
		{
			AddToOtherBook(MyGoodFriends, MyPhoneBook);
			break;
		}
		case 3://ɾ����Ա
		{
			DeleteAMember(MyGoodFriends);
			break;
		}
		case 4://��ӡ��Ա
		{
			ShowAllMembers(MyGoodFriends);//չʾ��Ϣ
			break;
		}
		case 5://���ҳ�Ա
		{
			FindAMember(MyGoodFriends);
			break;
		}
		case 6://���ļ���ʽ�����Ա��Ϣ
		{
			BookOut(MyGoodFriends);
			break;
		}
		default://��ʾ�������
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}

//�༶���Ĺ�������
extern void AllClassmatesFunctions(PhoneBook MyClassmates, PhoneBook MyPhoneBook, DataType* StartMembers, int ChoiceForStart, char Judge)
{
	do {
		StartForClassmates();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://�����༶��
		{
			FoundNewBook(MyPhoneBook, MyClassmates);
			break;
		}
		case 2://���ӳ�Ա
		{
			AddToOtherBook(MyClassmates, MyPhoneBook);
			break;
		}
		case 3://ɾ����Ա
		{
			DeleteAMember(MyClassmates);
			break;
		}
		case 4://��ӡ��Ա
		{
			ShowAllMembers(MyClassmates);//չʾ��Ϣ
			break;
		}
		case 5://���ҳ�Ա
		{
			FindAMember(MyClassmates);
			break;
		}
		case 6://���ļ���ʽ�����Ա��Ϣ
		{
			BookOut(MyClassmates);
			break;
		}
		default://��ʾ�������
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}

//�������Ĺ�������
extern void AllBlaceBookFunctions(PhoneBook MyBlackBook, PhoneBook MyPhoneBook, DataType* StartMembers, int ChoiceForStart, char Judge)
{
	do {
		StartForBlackBook();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://����������
		{
			FoundNewBook(MyPhoneBook, MyBlackBook);
			break;
		}
		case 2://���ӳ�Ա
		{
			AddToOtherBook(MyBlackBook, MyPhoneBook);
			break;
		}
		case 3://ɾ����Ա
		{
			DeleteAMember(MyBlackBook);
			break;
		}
		case 4://��ӡ��Ա
		{
			ShowAllMembers(MyBlackBook);//չʾ��Ϣ
			break;
		}
		case 5://���ҳ�Ա
		{
			FindAMember(MyBlackBook);
			break;
		}
		case 6://���ļ���ʽ�����Ա��Ϣ
		{
			BookOut(MyBlackBook);
			break;
		}
		default://��ʾ�������
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}
#endif