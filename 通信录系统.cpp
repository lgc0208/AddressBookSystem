// 通信录系统.cpp

#include"PhoneBookFunctions.h"
#include <cstdlib>

int main()
{
	DataType *StartMembers = new DataType [100];
	char Judge = '1';//程序循环条件
	StartPrompt();//初始提示信息
	int ChoiceForStart;
	PhoneBook MyGoodFriends, MyClassmates, MyBlackBook;
	cin >> ChoiceForStart;
	int FirstNum;
	switch (ChoiceForStart)
		{
		case 1://读取默认保存的通信录
		{
			BookIn(StartMembers,FirstNum);
			break;
		}
		case 2:
		{
			PromptForInput();//输入成员信息的提示信息
			FirstNum = ChooseNumberOfNewMember();//添加成员的个数
			FoundPhoneBook(StartMembers, FirstNum);
			break;
		}
		default:
		{
			Error();
			break;
		}
	}
	PhoneBook MyPhoneBook(StartMembers, FirstNum);
	do {
		Start();//调用初始界面
		cin >> ChoiceForStart;
		switch (ChoiceForStart)
		{
			case 1://通信录操作
			{
				AllPhoneBookFunctions(MyPhoneBook,StartMembers,ChoiceForStart,Judge);
				break;
			}
			case 2://好友簿操作
			{
				AllGoodFriendsBookFunctions(MyGoodFriends, MyPhoneBook, StartMembers, ChoiceForStart, Judge);
				break;
			}
			case 3://班级簿操作
			{
				AllClassmatesFunctions(MyClassmates, MyPhoneBook, StartMembers, ChoiceForStart, Judge);
				break;
			}
			case 4://黑名单操作
			{
				AllBlaceBookFunctions(MyBlackBook, MyPhoneBook, StartMembers, ChoiceForStart, Judge);
				break;
			}
			default://容错
			{
				Error();
				break;
			}
		}//交互界面
		PromptToEnd();
		cin>>Judge;//判断是否需要退出程序
	} while (Judge!= '0');//当Judge为0时，退出循环
	delete[] StartMembers;
	cout << "通信录程序已关闭" << endl;
	system("pause");
	return 0;
}
