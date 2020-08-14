//Interface.h

#ifndef Interface
#define Interface
#include<iostream>
using namespace std;

//分割线
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

//初始运行提示框
extern void StartPrompt()
{
	DevidedLine();
	cout << "读取通信录，请输入1" << endl
		<<  "创建通信录，请输入2" << endl;
	DevidedLine();
}

//起始操作界面提示框
extern void Start()
{
	DevidedLine();
	cout << "请输入操作前的数字，选择你需要进行的操作" << endl
		<< "1.通信录操作" << endl
		<< "2.好友簿操作" << endl
		<< "3.班级簿操作" << endl
		<< "4.黑名单操作" << endl;
	DevidedLine();
}

//通信录操作界面提示框
extern void StartForPhoneBook()
{
	DevidedLine();
	cout << "请输入操作前的数字，选择你需要进行的操作" << endl
		<< "1.重建初始通信录" << endl
		<< "2.增添通信录成员" << endl
		<< "3.删除通信录成员" << endl
		<< "4.修改通信录成员" << endl
		<< "5.查看所有通信录成员" << endl
		<< "6.查找通信录成员" << endl
		<< "7.保存通信录成员" << endl
		<< "8.以文件形式输出通信录成员" << endl;
	DevidedLine();
}

//好友簿操作界面提示框
extern void StartForGoodFriendsBook()
{
	DevidedLine();
	cout << "请输入操作前的数字，选择你需要进行的操作" << endl
		<< "1.建立好友簿" << endl
		<< "2.增添好友簿成员" << endl
		<< "3.删除好友簿成员" << endl
		<< "4.查看所有好友簿成员" << endl
		<< "5.查找好友簿成员" << endl
		<< "6.以文件形式输出通信录成员" << endl;
	DevidedLine();
}

//班级簿操作界面提示框
extern void StartForClassmates()
{
	DevidedLine();
	cout << "请输入操作前的数字，选择你需要进行的操作" << endl
		<< "1.建立班级簿" << endl
		<< "2.增添班级簿成员" << endl
		<< "3.删除班级簿成员" << endl
		<< "4.查看所有班级簿成员" << endl
		<< "5.查找班级簿成员" << endl
		<< "6.以文件形式输出通信录成员" << endl;
	DevidedLine();
}

//黑名单操作界面提示框
extern void StartForBlackBook()
{
	DevidedLine();
	cout << "请输入操作前的数字，选择你需要进行的操作" << endl
		<< "1.建立黑名单" << endl
		<< "2.增添黑名单成员" << endl
		<< "3.删除黑名单成员" << endl
		<< "4.查看所有黑名单成员" << endl
		<< "5.查找黑名单成员" << endl
		<< "6.以文件形式输出通信录成员" << endl;
	DevidedLine();
}

//文件输出界面提示框
extern void PromptForBookOut()
{
	DevidedLine();
	cout << "若需要将输出到程序当前目录，请输入1" << endl
		<< "若输入到桌面，请输入2" << endl;
	cout << "你的选择是： ";
}

//退出界面提示框
extern char ChoiceToEnd(char Judge)
{
	DevidedLine();
	cout << "如需要退出当前界面，请输入0。如继续操作，请输入除0外的任意字符" << endl;
	cin >> Judge;
	DevidedLine();
	return Judge;
}

//输入成员信息提示框
extern void PromptForInput()
{
	cout << "请依次输入通信录成员的ID，姓名，性别（m/w）,电话，地址" << endl;
}

//错误提示框
extern void Error()
{
	DevidedLine();
	cout << "您输入的数据有误，请检查后重新输入" << endl;
	DevidedLine();
}

//退出程序提示框
extern void PromptToEnd()
{
	DevidedLine();
	cout << "如需要退出程序，请输入0；如要继续其他操作，请输入除0外任意字符" << endl;
	DevidedLine();
}
#endif // !Interface