/*Сформировать массив на диске, содержащий сведения о сотрудниках института. Структурный тип содержит поля:
фамилия работающего, название отдела, год рождения, стаж работы, долдность, оклад. Написать программу,
которая выбирает с диска и выводит на экран:
-список сотрудников пенсионного возраста на сегодняшний день с указанием стажа работы;
-средний стаж, работающих в отделе X (X ввести с клавиатуры)*/

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

/*Созадает новую структуру*/
shared_ptr<Institute> InputStructure()
{
	Institute* person = new Institute();

	cout << "Введите фамилию сотрудника" << endl;
	getline(cin, person->surname);
	cout << "Введите отдел" << endl;
	getline(cin, person->department);
	cout << "Введите дату рождения сотрудника" << endl;
	getline(cin, person->birth_date);
	cout << "Введите должность сотрудника" << endl;
	getline(cin, person->position);
	cout << "Введите стаж работы сотрудника" << endl;
	cin >> person->expirience;
	cout << "Введите оклад сотрудника" << endl;
	cin >> person->salary;

	/*shared_ptr<> это умный указатель, т.к. мы выделяем память в куче за ней необходимо следить и очищать 
	и shared_ptr<> делает это за нас работать с ним так де как и с обычным указателем*/
	return shared_ptr<Institute>(person);
}

/*Записывает в  файл всю инфорацию из list*/
void InputList(list<shared_ptr<Institute>>& persons)
{

	ofstream file;
	file.open("file.txt", ios::binary | ios::trunc);

	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}

	for(const auto& it : persons) {
		file.write((char*)it.get(), sizeof(Institute));
	}


	file.close();
	return;
}

/*Выводит структуру в консоль*/
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


/*считывание структуры из файла*/
list<shared_ptr<Institute>> OutputStructure()
{
	list<shared_ptr<Institute>> persons;
	

	ifstream file("file.txt",   ios::binary);
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		exit(0);
	}

	/*метод get() у shared_ptr<> Возращает указатель котый он хранит*/
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
	cout << "Введите отдел: ";
	/*cin.get(); очищает поток ввода... но это просто костыль */
	cin.get();
	getline(cin,temp);

	for (const auto& it : persons) 
		if (temp == it->department) {
			count++;
			sum += it->expirience;
		}
	if (!count) {

	}
	cout << "Средний стаж работы сотрудников: " << sum / count << endl;
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