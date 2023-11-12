#include<iostream>
#include<list>
#include<vector>
#include<array>
#include<Windows.h>
#include<string>
#include<fstream>
#include<algorithm>
#include<iomanip>
using namespace std;

class Documentation {
private:
	int Number;
	float coast;
	string Information;
	string Date;
	string WorkerName;
public:

	Documentation() : Number(12), coast(12.3), Information("Default Information"), WorkerName("Vlad"),Date("15/04(17:46)") {}

	Documentation(int Number, float coast, string Information, string WorkerName) {
		this->Number = Number;
		this->coast = coast;
		this->Information = Information;
		setDate();
		this->WorkerName = WorkerName;
	}

	int GetNumber() {
		return Number;
	}

	float GetCoast() {
		return coast;
	}

	string GetInformation() {
		return Information;
	}

	string GetDate() {
		return Date;
	}

	string GetWorkerName() {
		return WorkerName;
	}

	void setNumber(int Number) {
		this->Number = Number;
	}
	void setInformation(string Information) {
		this->Information = Information;
	}

	void setCoast(float coast) {
		this->coast = coast;
	}

	void  setDate() {
		int day, month, hour, minuts;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		struct tm localtime;
		time_t now = time(NULL);
		localtime_s(&localtime, &now);
		day = localtime.tm_mday;
		month = 1 + localtime.tm_mon;
		hour = localtime.tm_hour;
		minuts = localtime.tm_min;

		string strDay = std::to_string(day);
		string strMonth = std::to_string(month);
		string strHour = std::to_string(hour);
		string strMinutes = std::to_string(minuts);

		this->Date = strDay + "/" + strMonth + "(" + strHour + ":" + strMinutes + ")";
	}

	void ViewDocument() {
		cout << "| " << setw(5) << GetNumber() << " | " << setw(28) << GetInformation() << " |  "<<setw(11)<< GetDate() << fixed << setprecision(2) << "| "
		<< setw(7) << GetCoast()<<"   |" << endl;
		cout << "|_______|______________________________|______________|___________|" << endl;
		
	}

	void SetWorkerName(string WorkerName) {
		this->WorkerName = WorkerName;
	}

	friend ostream& operator <<(ostream& os, Documentation document) {
		os << document.Number << " " << document.Information << " " << document.Date << " " << document.WorkerName << endl;
		return os;
	}
};


void ViewHeadLine() {
	cout << "__________________________________________________________________" << endl;
	cout << "| Номер |          Информация          |     Дата     |    Цена   |" << endl;
	cout << "|_______|______________________________|______________|___________|" << endl;
}

bool CompareByNumber(Documentation document1, Documentation document2) {
	return document1.GetNumber() < document2.GetNumber();
}

bool CompareByInf(Documentation document1, Documentation document2) {
	return document1.GetInformation() > document2.GetInformation();
}

int main() {
	list<Documentation> listDocumentation;
	vector<Documentation> vectorDocumentation;
	array<Documentation, 4> arrayDocumentation {Documentation(),Documentation(13,15.5,"Information2","Саша"),
	Documentation(16,67.4,"Information3","Вадим"),Documentation(19,23.4,"27/03","Света")};


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1) {
		cout << "1. Добавление (list,vector,array) (Также запись в файл)" << endl;
		cout << "2. Редактирование (list,vector,array)" << endl;
		cout << "3. Удаление (list,vector)" << endl;
		cout << "4. Просмотр (list,vector,array)" << endl;
		cout << "5. Сортировка (list,vector)" << endl;
		cout << "6. Выйти" << endl;
		int choice;
		try {
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				throw runtime_error("Ошибка ввода");
			}
		}
		catch(runtime_error e){
			cout  << e.what() << endl;
			continue;
		}
		switch (choice) {
		case 1: {
			int Number;
			float coast;
			string Inf, date, name;
			cout << "Введите номер заказа : ";
			cin >> Number;
			cout << "Введите цену : ";
			cin >> coast;
			cout << "Введите Информацию : ";
			cin.ignore();
			getline(cin, Inf);
			cout << "Введите имя работника : ";
			cin >> name;
			Documentation document(Number, coast, Inf, name);
			listDocumentation.push_back(document);
			vectorDocumentation.push_back(document);
			ofstream file("DocumentFile.txt", ios::app);
			file << document;
			cout << "Документ был добавлен" << endl;
			break;
		}
		case 2:
		{
			cout << "Всего Документов " << listDocumentation.size() << endl;
			cout << " Введите номер документа для изменения : ";
			int n;
			cin >> n;
			if (n <= 0 || n > listDocumentation.size()) {
				cout << "Неверно введен номер" << endl;
				break;
			}
			int Number;
			float coast;
			string Inf, date, name;
			cout << "Введите номер заказа : ";
			cin >> Number;
			cout << "Введите цену : ";
			cin >> coast;
			cout << "Введите Информацию : ";
			cin.ignore();
			getline(cin, Inf);
			cout << "Введите имя работника : ";
			cin >> name;
			Documentation document(Number, coast, Inf, name);
			vectorDocumentation[n - 1] = document;
			list<Documentation>::iterator ListIterator = listDocumentation.begin();
		
			for (int i = 1; i < n; ++i) {
				++ListIterator;
			}
			*ListIterator = document;
			cout << "Документ был отредактирован" << endl;
			break;
		}
		case 3:
		{
			cout << "Всего документов " << listDocumentation.size() << endl;
			cout << " Введите номер документа для удаления : ";
			int n;
			cin >> n;
			if (n <= 0 || n > listDocumentation.size()) {
				cout << "Екверно введен номер" << endl;
				break;
			}
			list<Documentation>::iterator ListIterator = listDocumentation.begin();
			vector<Documentation>::iterator VectorIterator = vectorDocumentation.begin();

			for (int i = 1; i < n; ++i) {
				++ListIterator;
				++VectorIterator;
			}
			listDocumentation.erase(ListIterator);
			vectorDocumentation.erase(VectorIterator);
			cout << "Документ был удалён" << endl;
			break;
		}
		case 4:
		{
			list<Documentation>::iterator ListIterator = listDocumentation.begin();
			vector<Documentation>::iterator VectorIterator = vectorDocumentation.begin();
			cout << "Вывод list" << endl;
			ViewHeadLine();
			while (ListIterator != listDocumentation.end()) {
				ListIterator->ViewDocument();
				ListIterator++;
			}
			cout << "Вывод vector" << endl;
			ViewHeadLine();
			while (VectorIterator != vectorDocumentation.end()) {
				VectorIterator->ViewDocument();
				VectorIterator++;
			}
			
			cout << "Вывод array" << endl;
			ViewHeadLine();
			for (int i{}; i < arrayDocumentation.size(); i++) {
				arrayDocumentation.at(i).ViewDocument();
			}
			break;
		}
		case 5:
		{
			cout << "Сортировать по " << endl;
			cout << "1. Номер" << endl;
			cout << "2. Информация" << endl;
			int SortChoice;
			cin >> SortChoice;
			if (SortChoice != 1 && SortChoice != 2) {
				cout << "Непрвильный номер операции " << endl;
				break;
			}
			if (SortChoice) {
				listDocumentation.sort(CompareByNumber);
				sort(vectorDocumentation.begin(), vectorDocumentation.end(), CompareByNumber);
			}
			else if (SortChoice == 2) {
				listDocumentation.sort(CompareByInf);
				sort(vectorDocumentation.begin(), vectorDocumentation.end(), CompareByInf);
			}
			break;
		}
		case 6:return 0; break;
		default: cout << "Неправильно введён номер операции" << endl;
		}
	}
}

