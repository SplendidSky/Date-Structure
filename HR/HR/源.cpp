#include<iostream>
#include<vector>
#include<string>
#include<ios>
using namespace std;
struct EXAMINEE
{
	int ID;
	string name;
	char gender;
	int age;
	char hand;
	EXAMINEE(int ID_, string name_, char gender_, int age_, char hand_)
	{
		ID = ID_;
		name = name_;
		gender = gender_;
		age = age_;
		hand = hand_;
	}
};
int main()
{
	vector<EXAMINEE> E;
	string s;
	cout << "请选择操作：\n" << "'A'=add 'O'=output  'Q'=quit" << endl;
	cin >> s;
	while (s != "Q") {

		if (s == "A")
		{

			string name;
			char gender, hand;
			int ID = 0, age;
			cout << "请输入您的信息：\n姓名：";
			cin >> name;
			cout << "性别('M'表示男性，'F'表示女性)：";
			cin >> gender;
			cout << "年龄：";
			cin >> age;
			cout << "利手('L'表示左手，'R'表示右手)：";
			cin >> hand;
			EXAMINEE e(ID, name, gender, age, hand);
			E.push_back(e);
			cout << "请选择操作：\n" << "'A'=add 'O'=output  'Q'=quit" << endl;
		}
		if (s == "O")
		{
			cout << endl;
			for (int i = 0; i <= E.size() - 1; ++i)
			{
				E[i].ID = i+1;
				cout << "#"<<i+1<<"#\n"<<"姓名：" << E[i].name << endl;
				cout << "性别：";
				if (E[i].gender == 'M')
				{
					cout  << "男" << endl;
				}
				else { cout  << "女" << endl; }
				cout << "年龄:"  << E[i].age << endl;
				cout << "利手:";
				if (E[i].hand == 'L')
				{
					cout  << "左利手" << endl;
				}
				else { cout  << "右利手" << endl; }
				cout << endl;
			}
		}
		if (s != "A"&&s != "O"&&s != "Q")
		{
			cout << "Wrong input ! Please input 'A' or 'O' or 'Q'.\n";
		}
		cin >> s;
	}
	return 0;
}
