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
	cout << "��ѡ�������\n" << "'A'=add 'O'=output  'Q'=quit" << endl;
	cin >> s;
	while (s != "Q") {

		if (s == "A")
		{

			string name;
			char gender, hand;
			int ID = 0, age;
			cout << "������������Ϣ��\n������";
			cin >> name;
			cout << "�Ա�('M'��ʾ���ԣ�'F'��ʾŮ��)��";
			cin >> gender;
			cout << "���䣺";
			cin >> age;
			cout << "����('L'��ʾ���֣�'R'��ʾ����)��";
			cin >> hand;
			EXAMINEE e(ID, name, gender, age, hand);
			E.push_back(e);
			cout << "��ѡ�������\n" << "'A'=add 'O'=output  'Q'=quit" << endl;
		}
		if (s == "O")
		{
			cout << endl;
			for (int i = 0; i <= E.size() - 1; ++i)
			{
				E[i].ID = i+1;
				cout << "#"<<i+1<<"#\n"<<"������" << E[i].name << endl;
				cout << "�Ա�";
				if (E[i].gender == 'M')
				{
					cout  << "��" << endl;
				}
				else { cout  << "Ů" << endl; }
				cout << "����:"  << E[i].age << endl;
				cout << "����:";
				if (E[i].hand == 'L')
				{
					cout  << "������" << endl;
				}
				else { cout  << "������" << endl; }
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
