#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// название файла
const string Name = "data.dat";
class Student;
// множество
template<class T>
class Array {
	int size; // размер множества
	T* elements; // элементы множества
public:
	// конструктор (elements) - принимаемое множество, (size - размермножества)
	Array(T* elements, int size) :elements(elements), size(size) {}
	template<class T>
	friend istream& operator>>(istream& in, Array<T>& arr); // перегрузкаввода
		template<class T>
	friend ostream& operator<<(ostream& out, const Array<T>& arr); // перегрузка вывода
		// Конструктор копирования
		Array(const Array& source)
	{
		this->size = source.size;
		this->elements = new T[source.size];
		for (int t = 0; t < source.size; t++)
		{
			this->elements[t] = source.elements[t];
		}
	}
	void DelElement()
	{
		T value;
		cout << "Что удалить> "; cin >> value;
		int counter = 0;
		for (int t = 0; t < size; t++)
		{
			if (value != elements[t]) {
				counter++;
			}
		}
		T* temp = new T[counter];
		counter = 0;
		for (int t = 0; t < size; t++)
		{
			if (is_same<T, Student>::value)
			{
				if (value != elements[t]) // проверяем равны ли типы данных и равны ли данные
				{
				temp[counter++] = elements[t];
				}
			}
			else
			{
				if (value != elements[t])
				{
					temp[counter++] = elements[t];
				}
			}
		}
		elements = temp;
		this->size = counter;
	}
	void AddElement()
	{
		// добавление элемента
		T value;
		cout << "Добавление> "; cin >> value;
		T* ArrayOne = new T[size + 1];
		for (int i = 0; i < size; i++)
		{
			ArrayOne[i] = elements[i];
		}
		ArrayOne[size] = value;
		elements = ArrayOne;
		size++;
	}
	// вывод массива
	void print() const
	{
		for (int t = 0; t < size; t++)
		{
			cout << elements[t] << " ";
		}
		cout << endl;
	}
	// сохранение в файл
	void save()
	{
		ofstream out(Name, ios::out | ios::binary);
		for (int i = 0; i < size; i++)
		{
			out.write((char*)&elements[i], sizeof(elements[i]));
		}
		out.close();
	}
	// восстановление из файла
	void restore()
	{
		ifstream in(Name, ios::in | ios::binary);
		// 0 - отступ , ios::end - от конца файла
		in.seekg(0, ios::end);
		// размер файла = позиции указателя чтения-записи
		int filesize = in.tellg();
		// количество єлементов массива в файле
		size = filesize / sizeof(T);
		// освобождаем старій массив
		delete[]elements;
		// вbIделяем место для нового массива
		elements = new T[size];
		// читаем
		in.seekg(0, ios::beg);
		in.read((char*)elements, size * sizeof(T));
		in.close();
	}
	~Array() { delete[]elements; }
};
class Student {

	char name[30] = {}; // имя
	char group[30] = {}; // группа

public:
	Student() {};

	// Конструктор копирования
	Student(const Student& source)
	{
		strcpy(name, source.name);
		strcpy(group, source.group);
	}

	friend istream& operator>>(istream& in, Student& source) // вводданных о студенте
	{
		cout << " Name: ";
		cin >> source.name;
		cout << " Group: ";
		cin >> source.group;
		return in;
	}

	friend bool operator!=(const Student& source, const Student&source2)
	{
		return (strcmp(source.name, source2.name) && strcmp(source.group,
			source2.group)); // сравниваем поля классов
	}

	friend ostream& operator<<(ostream& out, Student& source) // вывод данных о студенте
	{
		cout << " Имя: " << source.name;
		cout << " Группа: " << source.group << endl;
		return out;
	}
};
// перегрузка вывода
template<class T>
ostream& operator<<(ostream& out, const Array<T>& arr)
{
	arr.print();
	return out;
}
// перегрузка ввода
template<class T>
istream& operator>>(istream& in, Array<T>& arr)
{
	for (int t = 0; t < arr.size; t++)
	{
		system("cls");
		cout << "Элемент No" << t + 1 << " > ";
		cin >> arr.elements[t];
	}
	return in;
}
const void PrintMenu()
{
	cout << "----------------------------------" << endl;
	cout << "1| Выход " << endl;
	cout << "2| Ввести данные " << endl;
	cout << "3| Сохранить данные " << endl;
	cout << "4| Восстановить данные " << endl;
	cout << "5| Удалить элемент " << endl;
	cout << "6| Добавить элемент " << endl;
	cout << "----------------------------------" << endl;
}
int main()
{
	srand(time(nullptr));
	setlocale(LC_ALL, "rus");
	// ввод размера множеств
	int size = 0;
	cout << "Введите размер множеств (1-15) > "; cin >> size;
	// проверка ввода
	if (!cin.good() || size > 15 || size <= 0)
	{
		exit(0);
	}
	// множество
	Student* ArrayOne = new Student[size];
	// передача множеств классу
	Array<Student> ArrOne(ArrayOne, size);
	//// проверка на другом типе данных
	//float* ArrayOne = new float[size];
	//
	//// передача множеств классу
	//Array<float> ArrOne(ArrayOne, size);
	int choice = 0;
	while (true)
	{
		system("cls");
		cout << ArrOne << endl;
		PrintMenu();
		cout << "Выберите пункт> "; cin >> choice;
		switch (choice)
		{
		case 1: exit(0);
		case 2: cin >> ArrOne; break;
		case 3: cout << "Данные сохранены!" << endl; ArrOne.save();
			break;
		case 4: cout << "Данные восстановлены!" << endl;
			ArrOne.restore(); break;
		case 5:ArrOne.DelElement(); break;
		case 6:ArrOne.AddElement(); break;
		}
	}
}
