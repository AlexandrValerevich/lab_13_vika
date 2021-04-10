/*������������ ������ �� �����, ���������� �������� � ����������� ���������. ����������� ��� �������� ����:
������� �����������, �������� ������, ��� ��������, ���� ������, ���������, �����. �������� ���������,
������� �������� � ����� � ������� �� �����:
-������ ����������� ����������� �������� �� ����������� ���� � ��������� ����� ������;
-������� ����, ���������� � ������ X (X ������ � ����������)*/

#include <vector>
#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
#include <list>
#include <memory>

using namespace std;

class Institute
{
public:
	string surname;
	string department;
	string birth_date;
	int    expirience;
	string position;
	double salary;
public:
		Institute() {
			surname    = "";
			department = "";
			birth_date = "";
			expirience = 0;
			position   = "";
			salary     = 0;
		}
		Institute(const Institute& pers) {
			surname    = pers.surname;
			department = pers.department;
			birth_date = pers.birth_date;
			expirience = pers.expirience;
			position   = pers.position;
			salary     = pers.salary;
		}
		Institute operator=(const Institute& pers) {
			surname    = pers.surname;
			department = pers.department;
			birth_date = pers.birth_date;
			expirience = pers.expirience;
			position   = pers.position;
			salary     = pers.salary;
		}
};

/*�������� ����� ���������*/
shared_ptr<Institute> InputStructure()
{
	Institute* person = new Institute();

	cout << "������� ������� ����������" << endl;
	getline(cin, person->surname);
	cout << "������� �����" << endl;
	getline(cin, person->department);
	cout << "������� ���� �������� ����������" << endl;
	getline(cin, person->birth_date);
	cout << "������� ��������� ����������" << endl;
	getline(cin, person->position);
	cout << "������� ���� ������ ����������" << endl;
	cin >> person->expirience;
	cout << "������� ����� ����������" << endl;
	cin >> person->salary;

	/*shared_ptr<> ��� ����� ���������, �.�. �� �������� ������ � ���� �� ��� ���������� ������� � ������� 
	� shared_ptr<> ������ ��� �� ��� �������� � ��� ��� �� ��� � � ������� ����������*/
	return shared_ptr<Institute>(person);
}

/*���������� �  ���� ��� ��������� �� list*/
void InputList(list<shared_ptr<Institute>>& persons)
{

	ofstream file;
	file.open("file.txt", ios::binary | ios::trunc);

	if (!file.is_open())
	{
		cout << "������ �������� �����" << endl;
		return;
	}

	for(const auto& it : persons) {
		file.write((char*)it.get(), sizeof(Institute));
	}


	file.close();
	return;
}

/*������� ��������� � �������*/
void PrintStructure(const shared_ptr<Institute>& person)
{
	cout << person->surname << endl;
	cout << person->department << endl;
	cout << person->position << endl;
	cout << person->birth_date << endl;
	cout << person->expirience << endl;
	cout << person->salary << endl;
	cout << endl;
}


/*���������� ��������� �� �����*/
list<shared_ptr<Institute>> OutputStructure()
{
	list<shared_ptr<Institute>> persons;
	

	ifstream file("file.txt",   ios::binary);
	if (!file.is_open())
	{
		cout << "������ �������� �����" << endl;
		exit(0);
	}

	/*����� get() � shared_ptr<> ��������� ��������� ����� �� ������*/
	while (file.good())
	{
		shared_ptr<Institute> person = shared_ptr<Institute>(new Institute);
		file.read((char*)person.get(), sizeof(Institute));
		persons.push_back(person);
	}

	file.close();
	persons.pop_back();
	return persons;
}

void avarageStage(list<shared_ptr<Institute>>& persons) {
	string temp;
	int count = 0;
	int	sum = 0;
	cout << "������� �����: ";
	/*cin.get(); ������� ����� �����... �� ��� ������ ������� */
	cin.get();
	getline(cin,temp);

	for (const auto& it : persons) 
		if (temp == it->department) {
			count++;
			sum += it->expirience;
		}
	if (!count) {

	}
	cout << "������� ���� ������ �����������: " << sum / count << endl;
}



int main()
{
	setlocale(LC_ALL, "rus");
	
	list<shared_ptr<Institute>> plist = OutputStructure();;
	plist.push_back(InputStructure());


	for (const auto& it : plist)
	{
		PrintStructure(it);
	}

	avarageStage(plist);

	InputList(plist);
	exit (0);
}