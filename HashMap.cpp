#include <iostream>
#include "windows.h"
#include <string>
using namespace std;

// ����� ���� ���-�������
class HashNode {
public:
	int key;
	string fio;
	string adress;
	HashNode(int key, string fio, string adress)
	{
		this->fio = fio;
		this->key = key;
		this->adress = adress;
	}
};

// ����� ���-�������
class HashMap {

	HashNode** arr;   // ������� ���-�������
	int capacity;      // ������������ ����������� ���-�������
	int size;          //������� ������ ���-�������
	HashNode* dummy;    //��������� ����

public:
	HashMap()
	{
		capacity = 100;    //���� ������ ���-�������
		size = 0;
		arr = new HashNode*[capacity];

		// ������������� ���� ��������� ������� ��������� NULL
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

		dummy = new HashNode(-1,"0", "0");
	}
	// ���-������� - ������� �� ������� ����� �� ���� ����������� ���-�������
	int hashCode(int key)
	{
		return key % capacity;
	}

	// ������� �������
	bool insertNode(int key, string fio, string adress)
	{
		HashNode* temp = new HashNode(key, fio, adress);
		int hashIndex = hashCode(key);
		int c = 0;
		// ����� ���������� �����
		while (arr[hashIndex] != NULL   //���� � ������� ������� ��� ��������� ���-��
			&& arr[hashIndex]->key != key     
			&& arr[hashIndex]->key != -1) {    
			c++;
			hashIndex++;         //����������� ������ �� ��������� - ������� (�����=h(x)+ci)
			hashIndex %= capacity;   //��� � ������ ������� ��� ������ �� ������� ����������
			//���� ������ ��� ������ � �� ������� ���������� �����
			if (c == capacity) { return false; }  //������� ������ �� ����� while
		}

		// =���� ������� ��������� �����, �� ��� �����������
		if (arr[hashIndex] == NULL
			|| arr[hashIndex]->key == -1) {
			size++;
			arr[hashIndex] = temp;
			return true;
		}	
	}
	//�������, ��������� ���� ���-�������
	bool deleteNode(int key)
	{
		int hashIndex = hashCode(key);
		// ����� ���� � �������� ������
		while (arr[hashIndex] != NULL) {   //���������, ���� �� ������� �� �������

			if (arr[hashIndex]->key == key) {     //���� ���� ������
	// ������� � ������� ���� � ������ -1, ����� � ���������� ������ ����� ����������� ������ �����
				arr[hashIndex] = dummy;    
				// ��������� ������
				size--;
				return true;
			}
			//������� ��� ����������� ������, ���� ���� �� ������
			hashIndex++;
			hashIndex %= capacity;
		}
		return false;
	}

	// ������� ������ �� �����
	HashNode* get(int key)
	{
		int hashIndex = hashCode(key);
		int counter = 0;

		// ����� ���� � �������� ������
		while (arr[hashIndex] != NULL) { // ���������, ���� �� ������� �� �������

			if (counter++ > capacity) // ��� ��������� ������������ �����
				return NULL;

			// ���� ���� ������, �� ������������
			if (arr[hashIndex]->key == key) {
				return arr[hashIndex];
			}
			hashIndex++;      //���������� ������ �� �������, ���� �� ������
			hashIndex %= capacity;
		}
		// ���� �� ������ - ������������ NULL
		return NULL;
	}

	// ������� �������� ������� ���-�������
	int sizeofMap() { return size; }

	// �������, ������������ ���-�������
	void display()
	{
		for (int i = 0; i < capacity; i++) {
			if (arr[i] != NULL && arr[i]->key != -1)
				cout << " ����� ����� � �����: " << arr[i]->key
				<< ", ���: "
				<< arr[i]->fio << ", �����: " << arr[i]->adress << endl;
		}
	}
};
// ���������
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	HashMap* h = new HashMap;
	cout << "������� ��������� ���������� ����������: " << endl;
	h->insertNode(1639767, "����������� ������ ���������", "������, �������� 21");
	h->insertNode(2642867, "��������� ������� �������", "������, �������� ������������ 43");
	h->insertNode(2429101, "���������� ������ ����������", "�������, ��������� 38");
	h->insertNode(1234567, "������ ���� ��������", "������, ��. �������, 10");
	h->insertNode(2345678, "������ ���� ��������", "���������, ��. ������, 20");
	h->insertNode(5678901, "������� ����� ���������", "������, ��. �����������, 8");
	h->display();
	cout << "������ ��������� ������";
	cout << "\n" << "1. �������� ������" << endl;
	cout << "2. ����� ������ �� �����" << endl;
	cout << "3. ������� ������ �� �����" << endl;
	cout << "4. ������� ��� ������" << endl;
	cout << "5. �����" << endl;
	while (true) {
		cout << "������� ����� ������� ��� ����������: ";
		int choice;
		cin >> choice;

		switch (choice) {
		case 1: {
			int key;
			string fio, address;
			cout << "������� ����� �����-���� (����� ����������� �����): ";
			cin >> key;
			while (to_string(key).length() != 7 || key < 0) {
				if (to_string(key).length() != 7 || key < 0)
				{
					cout << "����� ������ ���� ����� ����������� ������: ";
				}
				cin >> key;
			}
			cin.ignore(); 
			cout << "������� ���: ";
			getline(cin, fio);
			cout << "������� �����: ";
			getline(cin, address);
			h->insertNode(key, fio, address);
			break;
		}
		case 2: {
			int key;
			std::cout << "������� ����� �����-���� ��� ������: ";
			std::cin >> key;
			HashNode *result = h->get(key);
			if (result) {
				cout << "������� ������: ����� �����: " << result->key << ", ���: "
					<< result->fio << ", �����: " << result->adress << endl;
			}
			else {
				cout << "������ �� �������." << endl;
			}
			break;
		}
		case 3: {
			int key;
			cout << "������� ����� �����-���� ��� ��������: ";
			cin >> key;
			while (h->deleteNode(key) != 1) { 
				if (h->deleteNode(key) == 0)
				{
					cout << "����� �� ������, ������� ��� ���: ";
				}
				cin >> key;
			}
			cout << "������ �������." << endl;
			break;
		}
		case 4:
			h->display();
			break;
		case 5:
			return 0;
		default: 
			cout << "�������� �����. ���������� �����." << endl;
			break;
		}
	}
	return 0;
}


