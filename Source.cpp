#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// �������� �����
const string Name = "data.dat";
class Student;
// ���������
template<class T>
class Array {
	int size; // ������ ���������
	T* elements; // �������� ���������
public:
	// ����������� (elements) - ����������� ���������, (size - ���������������)
	Array(T* elements, int size) :elements(elements), size(size) {}
	template<class T>
	friend istream& operator>>(istream& in, Array<T>& arr); // ���������������
		template<class T>
	friend ostream& operator<<(ostream& out, const Array<T>& arr); // ���������� ������
		// ����������� �����������
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
		cout << "��� �������> "; cin >> value;
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
				if (value != elements[t]) // ��������� ����� �� ���� ������ � ����� �� ������
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
		// ���������� ��������
		T value;
		cout << "����������> "; cin >> value;
		T* ArrayOne = new T[size + 1];
		for (int i = 0; i < size; i++)
		{
			ArrayOne[i] = elements[i];
		}
		ArrayOne[size] = value;
		elements = ArrayOne;
		size++;
	}
	// ����� �������
	void print() const
	{
		for (int t = 0; t < size; t++)
		{
			cout << elements[t] << " ";
		}
		cout << endl;
	}
	// ���������� � ����
	void save()
	{
		ofstream out(Name, ios::out | ios::binary);
		for (int i = 0; i < size; i++)
		{
			out.write((char*)&elements[i], sizeof(elements[i]));
		}
		out.close();
	}
	// �������������� �� �����
	void restore()
	{
		ifstream in(Name, ios::in | ios::binary);
		// 0 - ������ , ios::end - �� ����� �����
		in.seekg(0, ios::end);
		// ������ ����� = ������� ��������� ������-������
		int filesize = in.tellg();
		// ���������� ��������� ������� � �����
		size = filesize / sizeof(T);
		// ����������� ����� ������
		delete[]elements;
		// �bI������ ����� ��� ������ �������
		elements = new T[size];
		// ������
		in.seekg(0, ios::beg);
		in.read((char*)elements, size * sizeof(T));
		in.close();
	}
	~Array() { delete[]elements; }
};
class Student {

	char name[30] = {}; // ���
	char group[30] = {}; // ������

public:
	Student() {};

	// ����������� �����������
	Student(const Student& source)
	{
		strcpy(name, source.name);
		strcpy(group, source.group);
	}

	friend istream& operator>>(istream& in, Student& source) // ���������� � ��������
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
			source2.group)); // ���������� ���� �������
	}

	friend ostream& operator<<(ostream& out, Student& source) // ����� ������ � ��������
	{
		cout << " ���: " << source.name;
		cout << " ������: " << source.group << endl;
		return out;
	}
};
// ���������� ������
template<class T>
ostream& operator<<(ostream& out, const Array<T>& arr)
{
	arr.print();
	return out;
}
// ���������� �����
template<class T>
istream& operator>>(istream& in, Array<T>& arr)
{
	for (int t = 0; t < arr.size; t++)
	{
		system("cls");
		cout << "������� No" << t + 1 << " > ";
		cin >> arr.elements[t];
	}
	return in;
}
const void PrintMenu()
{
	cout << "----------------------------------" << endl;
	cout << "1| ����� " << endl;
	cout << "2| ������ ������ " << endl;
	cout << "3| ��������� ������ " << endl;
	cout << "4| ������������ ������ " << endl;
	cout << "5| ������� ������� " << endl;
	cout << "6| �������� ������� " << endl;
	cout << "----------------------------------" << endl;
}
int main()
{
	srand(time(nullptr));
	setlocale(LC_ALL, "rus");
	// ���� ������� ��������
	int size = 0;
	cout << "������� ������ �������� (1-15) > "; cin >> size;
	// �������� �����
	if (!cin.good() || size > 15 || size <= 0)
	{
		exit(0);
	}
	// ���������
	Student* ArrayOne = new Student[size];
	// �������� �������� ������
	Array<Student> ArrOne(ArrayOne, size);
	//// �������� �� ������ ���� ������
	//float* ArrayOne = new float[size];
	//
	//// �������� �������� ������
	//Array<float> ArrOne(ArrayOne, size);
	int choice = 0;
	while (true)
	{
		system("cls");
		cout << ArrOne << endl;
		PrintMenu();
		cout << "�������� �����> "; cin >> choice;
		switch (choice)
		{
		case 1: exit(0);
		case 2: cin >> ArrOne; break;
		case 3: cout << "������ ���������!" << endl; ArrOne.save();
			break;
		case 4: cout << "������ �������������!" << endl;
			ArrOne.restore(); break;
		case 5:ArrOne.DelElement(); break;
		case 6:ArrOne.AddElement(); break;
		}
	}
}
