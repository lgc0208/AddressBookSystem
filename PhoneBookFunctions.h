//PhoneBookFunctions.h

#ifndef PhoneBookFunctions
#define PhoneBookFunctions
#include<string>
#include<fstream>
#include<istream>
#include<windows.h>//获取各个系统的桌面路径(参考自csdn)
#include<shlobj.h>//获取各个系统的桌面路径(参考自csdn)
#include"PhoneBook.h"

//判断需要读入的数据个数是否合法
extern int ChooseNumberOfNewMember()
{
	int Num=1;
	cout << "输入需要创建的数据的个数(请控制在100条以内): ";
	do
	{
		cin >> Num;//读入数据
		if (Num > 100 || Num < 0)
		{
			cout << "输入的数据个数有误。请重新输入： ";
			cin >> Num;
		}
	} while (Num > 100 || Num < 0);
	return Num;
}

//输入功能函数
extern void InputMembersInformation(DataType &StartMembers )
{
	cin >> StartMembers.ID >> StartMembers.name >> StartMembers.ch >> StartMembers.phone >> StartMembers.addr;
}

//建立原始通信录（由DataType组成）
extern void FoundPhoneBook(DataType* StartMembers,int FirstNum)
{
	for (int temp = 0; temp < FirstNum; temp++)
	{
		InputMembersInformation(*(StartMembers + temp));
	}//输入界面
}

//屏幕展示通信录信息
extern void ShowAllMembers(PhoneBook MyPhoneBook)
{
	DevidedLine();
	cout << "目前所选菜单的内容为：" << endl;
	MyPhoneBook.PrintAllMember();
	DevidedLine();
}

//获取不同电脑的桌面路径(参考自CSDN：https://blog.csdn.net/CosmopolitanMe/article/details/80512721?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)
/*
	★有可能出现错误：C2208：“_RPC_SYNTAX_IDENTIFIER”: 没有使用此类型进行定义的成员
	但注释掉该段代码再取消注释后不再报错。原因尚未可知，尚未检索到类似的错误情况。在另一个工程文件中一切正常。
*/
extern string  GetDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[300];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {// 如果成功返回true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}
	return string(szDir);
}

//通信录输入转换(将string数组转换成char数组，char类型以及int类型)
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

//文件输入通信录信息
extern void BookIn( DataType* StartMembers, int &FirstNum)
{
	ifstream In;
	string Number;
	string FileName;
	string Information;
	cout << "请输入不带后缀的文件名: (若需要读取默认保存的通信录，请输入default)" << endl
		<< "请保证通信录文件符合格式，且保存于程序目录下" << endl;
	cin >> FileName;

	if (FileName != "default")
	{
		FileName += ".txt";//后缀名
	}
	else 
	{
		FileName = "MyPhoneBook.txt";
	}
	In.open(FileName);
	if (!In)
		cout << "该文件不存在，请检查。" << endl;
	else
	{
		getline(In, Number);//逐行读取文件
		getline(In, Information, '!');//感叹号作为读取的终止条件
		//Information += " !";//作为转换的终止条件
		FirstNum = atoi(Number.c_str());//转换为int类型

		int s = 0;
		string* EachInformation = new string[1000];//动态申请空间
		for (int i = 0; i < Information.length(); i++) { //将字符串分割成字符串数组
			if ((Information[i] == ' ') || (Information[i] == '\n')) {                 //以空格或者换行符作为分隔符
				s++;
				continue;
			}
			else EachInformation[s] += Information[i];  //将分割好的字符串放到EachInformation数组里
		}
		for (int temp = 0, loop = 0; temp < FirstNum; temp++, loop += 5)
		{
			InputBookInInformation(*(StartMembers + temp), EachInformation, loop);
		}
		delete[] EachInformation;
	}
	In.close();
	}

//默认形式保存通信录
extern void SavePhoneBook(PhoneBook BookText)
{
	int Number = BookText.StatisticNumber();
	string Name = "MyPhoneBook.txt";
	Node* p = BookText.ReturnFront();
	ofstream Out(Name);//在当前目录下输出文件
	Out << Number << endl;//第一行输出成员个数
	while (p->next)//当下一条信息不为空时，持续输出
	{
		Out << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
		p = p->next;
	}
	Out << "!" << endl;
	Out.close();
	cout << "保存成功！" << endl;
}

//文件输出该簿信息
extern void BookOut(PhoneBook BookText)
{
	int Choice;
	PromptForBookOut();
	cin >> Choice;
	switch (Choice)
	{
		case 1://输出到程序当前目录
		{
			int Number = BookText.StatisticNumber();
			cout << "请自定义文件名：" << endl;
			string Name;
			cin >> Name;
			Name += ".txt";
			Node* p = BookText.ReturnFront();
			ofstream Out(Name);//在当前目录下输出文件
			Out << Number << endl;//第一行输出成员个数
			while (p->next)//当下一条信息不为空时，持续输出
			{
				Out << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
				p = p->next;
			}
			Out << "!" << endl;
			Out.close();
			cout << "已保存至文件目录下" << endl;
			break;
		}
		case 2://输出到电脑桌面
			{
				int Number = BookText.StatisticNumber();
				cout << "请自定义文件名：" << endl;
				string Name;
				string ToDesktop = GetDesktopPath();//获取各个系统的桌面路径
				ToDesktop += "\\";
				cin >> Name;
				Name += ".txt";
				ToDesktop += Name;
				Node* p = BookText.ReturnFront();
				ofstream Out(ToDesktop);//以绝对路径输出文件
				Out << Number<< endl;//第一行输出成员个数
				while (p->next)//当下一条信息不为空时，持续输出
				{
					Out << p->next->PersonData.ID << " " << p->next->PersonData.name << " " << p->next->PersonData.ch << " " << p->next->PersonData.phone << " " << p->next->PersonData.addr << endl;
					p = p->next;
				}
				Out << "!" << endl;
				Out.close();
				cout << "已保存至文件目录下" << endl;
				break;
			}
		default:
			{
				Error();
				break;
			}
	}
	
}

//输入通信录成员的各项内容
extern DataType CinDataType()
{
	DataType Information;
	PromptForInput();
	cin >> Information.ID >> Information.name >> Information.ch >> Information.phone >> Information.addr;
	return Information;
}

//重建通信录
extern void RebuildPhoneBook(DataType *StartMembers)
{
	PromptForInput();
	int NumTest;
	NumTest = ChooseNumberOfNewMember();
	for (int temp = 0; temp < NumTest; temp++)
	{
		PromptForInput();
		InputMembersInformation(*(StartMembers + temp));
	}//输入的初始界面
	PhoneBook MyPhoneBook(StartMembers, NumTest);//构造函数
	ShowAllMembers(MyPhoneBook);//展示信息
}

//增加成员
extern void AddPhoneBook(PhoneBook PhoneBook)
{
	DataType AddInformation;
	AddInformation = CinDataType();
	PhoneBook.AddMember(AddInformation);//调用函数
}

//用于除通信录外的Book增添成员，使得增添的成员始终处在通信录内
extern void AddToOtherBook(PhoneBook NewBook,PhoneBook MyPhoneBook)
{
	int IDtoNewBook;
	char JudgeToNewBook = '1';
	DataType MemberToNewBook;
	do {
		DevidedLine();
		cout << "请输入你需要加入的ID:";
		cin >> IDtoNewBook;
		MemberToNewBook = MyPhoneBook.FindMemberAndReturn(IDtoNewBook);
		if (MemberToNewBook.ch != 0)//多次输入时，若输入ID有误，不会再次添加上一个数据
			NewBook.AddMember(MemberToNewBook);
		DevidedLine();
		cout << "若要继续添加，请输入除0外的其他字符；" << endl
			<< "若要返回，请输入0." << endl;
		DevidedLine();
		cin >> JudgeToNewBook;
	} while (JudgeToNewBook != '0');
}

//删除成员
extern void DeleteAMember(PhoneBook PhoneBook)
{
	int IDtoDelete;
	cout << "请输入需要删除的ID" << endl;
	cin >> IDtoDelete;
	Node* tmp = PhoneBook.ReturnFront();
	int temp = 0;//判断是否存在该ID
	if (!tmp->next)//当当前目录为空时，显示异常
		Error();
	while (tmp->next)//确保指针非空
	{
		tmp = tmp->next;//将tmp后移
		if (tmp->PersonData.ID == IDtoDelete)//符合条件时，temp增加
		{
			temp++;
			PhoneBook.DeleteMember(IDtoDelete);
		}
		else if (tmp->next == NULL && temp == 0)
			cout << "该ID不存在，请检查输入。" << endl;//ID非法，提示操作者
	}
}

//修改成员
extern void ChangeAMember(PhoneBook PhoneBook)
{
	int IDtoChange;
	DataType ChangeInformation;
	cout << "请输入需要修改的成员ID： " << endl;
	cin >> IDtoChange;
	cout << "请输入修改后的成员信息：" << endl;
	ChangeInformation = CinDataType();
	PhoneBook.ChangeMember(IDtoChange, ChangeInformation);//调用函数
}

//查找成员
extern void FindAMember(PhoneBook PhoneBook)
{
	int IDtoFind;
	cout << "请输入你需要查找的ID： ";
	cin >> IDtoFind;
	PhoneBook.ToFindMember(IDtoFind);//调用函数
}

//建立新簿
extern void FoundNewBook(PhoneBook MyPhoneBook, PhoneBook NewBook)
{
	int IDtoNewBook;
	char JudgeToNewBook = '1';
	DataType MemberToNewBook;
	do {
		DevidedLine();
		cout << "请输入你需要加入的ID:";
		cin >> IDtoNewBook;
		MemberToNewBook = MyPhoneBook.FindMemberAndReturn(IDtoNewBook);
		if (MemberToNewBook.ch != 0)//多次输入时，若输入ID有误，不会再次添加上一个数据
			NewBook.AddMember(MemberToNewBook);
		DevidedLine();
		cout << "若要继续添加，请输入除0外的其他字符；" << endl
			<< "若要返回，请输入0." << endl;
		DevidedLine();
		cin >> JudgeToNewBook;
	} while (JudgeToNewBook != '0');
}

//通信录的功能整合
extern void AllPhoneBookFunctions(PhoneBook MyPhoneBook,DataType* StartMembers,int ChoiceForStart,char Judge)
{
	do {
		StartForPhoneBook();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://重建通信录
		{
			RebuildPhoneBook(StartMembers);
			break;
		}
		case 2://增加成员
		{
			AddPhoneBook(MyPhoneBook);
			break;
		}
		case 3://删除成员
		{
			DeleteAMember(MyPhoneBook);
			break;
			//ShowAllMembers(MyPhoneBook);//展示所有成员
		}
		case 4://修改成员
		{
			ChangeAMember(MyPhoneBook);
			break;
		}
		case 5://打印成员
		{
			ShowAllMembers(MyPhoneBook);//展示信息
			break;
		}
		case 6://查找成员
		{
			FindAMember(MyPhoneBook);
			break;
		}
		case 7://保存通信录
		{
			SavePhoneBook(MyPhoneBook);
			break;
		}
		case 8://以文件形式输出成员
		{
			BookOut(MyPhoneBook);
			break;
		}
		default://提示输入错误
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}

//好友簿的功能整合
extern void AllGoodFriendsBookFunctions(PhoneBook MyGoodFriends, PhoneBook MyPhoneBook, DataType* StartMembers, int ChoiceForStart, char Judge)
{
	do {
		StartForGoodFriendsBook();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://建立好友簿
		{
			FoundNewBook(MyPhoneBook, MyGoodFriends);
			break;
		}
		case 2://增加成员
		{
			AddToOtherBook(MyGoodFriends, MyPhoneBook);
			break;
		}
		case 3://删除成员
		{
			DeleteAMember(MyGoodFriends);
			break;
		}
		case 4://打印成员
		{
			ShowAllMembers(MyGoodFriends);//展示信息
			break;
		}
		case 5://查找成员
		{
			FindAMember(MyGoodFriends);
			break;
		}
		case 6://以文件形式输出成员信息
		{
			BookOut(MyGoodFriends);
			break;
		}
		default://提示输入错误
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}

//班级簿的功能整合
extern void AllClassmatesFunctions(PhoneBook MyClassmates, PhoneBook MyPhoneBook, DataType* StartMembers, int ChoiceForStart, char Judge)
{
	do {
		StartForClassmates();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://建立班级簿
		{
			FoundNewBook(MyPhoneBook, MyClassmates);
			break;
		}
		case 2://增加成员
		{
			AddToOtherBook(MyClassmates, MyPhoneBook);
			break;
		}
		case 3://删除成员
		{
			DeleteAMember(MyClassmates);
			break;
		}
		case 4://打印成员
		{
			ShowAllMembers(MyClassmates);//展示信息
			break;
		}
		case 5://查找成员
		{
			FindAMember(MyClassmates);
			break;
		}
		case 6://以文件形式输出成员信息
		{
			BookOut(MyClassmates);
			break;
		}
		default://提示输入错误
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}

//黑名单的功能整合
extern void AllBlaceBookFunctions(PhoneBook MyBlackBook, PhoneBook MyPhoneBook, DataType* StartMembers, int ChoiceForStart, char Judge)
{
	do {
		StartForBlackBook();
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
		case 1://建立黑名单
		{
			FoundNewBook(MyPhoneBook, MyBlackBook);
			break;
		}
		case 2://增加成员
		{
			AddToOtherBook(MyBlackBook, MyPhoneBook);
			break;
		}
		case 3://删除成员
		{
			DeleteAMember(MyBlackBook);
			break;
		}
		case 4://打印成员
		{
			ShowAllMembers(MyBlackBook);//展示信息
			break;
		}
		case 5://查找成员
		{
			FindAMember(MyBlackBook);
			break;
		}
		case 6://以文件形式输出成员信息
		{
			BookOut(MyBlackBook);
			break;
		}
		default://提示输入错误
		{
			Error();
			break;
		}
		}
		Judge = ChoiceToEnd(Judge);
	} while (Judge != '0');
}
#endif