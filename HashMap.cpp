#include <iostream>
#include "windows.h"
#include <string>
using namespace std;

// класс узла хэш-таблицы
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

// класс хэш-таблицы
class HashMap {

	HashNode** arr;   // масссив хэш-таблицы
	int capacity;      // максимальная вместимость хэш-таблицы
	int size;          //текущий размер хэш-таблицы
	HashNode* dummy;    //фиктивный узел

public:
	HashMap()
	{
		capacity = 100;    //макс размер хэш-таблицы
		size = 0;
		arr = new HashNode*[capacity];

		// инициализация всех элементов таблицы значением NULL
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

		dummy = new HashNode(-1,"0", "0");
	}
	// хэш-функция - остаток от деления ключа на макс вместимость хэш-таблицы
	int hashCode(int key)
	{
		return key % capacity;
	}

	// функция вставки
	bool insertNode(int key, string fio, string adress)
	{
		HashNode* temp = new HashNode(key, fio, adress);
		int hashIndex = hashCode(key);
		int c = 0;
		// поиск свободного места
		while (arr[hashIndex] != NULL   //если в позиции массива уже находится что-то
			&& arr[hashIndex]->key != key     
			&& arr[hashIndex]->key != -1) {    
			c++;
			hashIndex++;         //увеличиваем индекс на константу - единицу (адрес=h(x)+ci)
			hashIndex %= capacity;   //идём в начало массива при выходе за пределы индексации
			//если прошли все ячейки и не нашлось свободного места
			if (c == capacity) { return false; }  //условие выхода из цикла while
		}

		// =если найдено свободное место, то оно заполняется
		if (arr[hashIndex] == NULL
			|| arr[hashIndex]->key == -1) {
			size++;
			arr[hashIndex] = temp;
			return true;
		}	
	}
	//функция, удаляющая узел хэш-таблицы
	bool deleteNode(int key)
	{
		int hashIndex = hashCode(key);
		// поиск узла с заданным ключом
		while (arr[hashIndex] != NULL) {   //проверяем, есть ли элемент по индексу

			if (arr[hashIndex]->key == key) {     //если узел найден
	// заносим в элемент узел с ключом -1, чтобы в дальнейшем ячейка могла заполниться другим узлом
				arr[hashIndex] = dummy;    
				// уменьшаем размер
				size--;
				return true;
			}
			//смещаем для дальнейшего поиска, если узел не найден
			hashIndex++;
			hashIndex %= capacity;
		}
		return false;
	}

	// функция поиска по ключу
	HashNode* get(int key)
	{
		int hashIndex = hashCode(key);
		int counter = 0;

		// поиск узла с заданным ключом
		while (arr[hashIndex] != NULL) { // проверяем, есть ли элемент по индексу

			if (counter++ > capacity) // для избежания бесконечного цикла
				return NULL;

			// если узел найден, он возвращается
			if (arr[hashIndex]->key == key) {
				return arr[hashIndex];
			}
			hashIndex++;      //продолжаем сдвиги по индексу, если не найден
			hashIndex %= capacity;
		}
		// если не найден - возвращается NULL
		return NULL;
	}

	// Функция возврата размера хэш-таблицы
	int sizeofMap() { return size; }

	// функция, отображающая хэш-таблицу
	void display()
	{
		for (int i = 0; i < capacity; i++) {
			if (arr[i] != NULL && arr[i]->key != -1)
				cout << " Номер счета в банке: " << arr[i]->key
				<< ", ФИО: "
				<< arr[i]->fio << ", Адрес: " << arr[i]->adress << endl;
		}
	}
};
// интерфэйс
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	HashMap* h = new HashMap;
	cout << "Таблица заполнена начальными значениями: " << endl;
	h->insertNode(1639767, "Крыжовников Андрей Сергеевич", "Реутов, Гагарина 21");
	h->insertNode(2642867, "Панкратов Василий Никитич", "Москва, Проспект Вернандского 43");
	h->insertNode(2429101, "Фурземонов Максим Валерьевич", "Ногинск, Советская 38");
	h->insertNode(1234567, "Иванов Иван Иванович", "Рязань, ул. Пушкина, 10");
	h->insertNode(2345678, "Петров Петр Петрович", "Ульяновск, ул. Ленина, 20");
	h->insertNode(5678901, "Семенов Семен Семенович", "Казань, ул. Маяковского, 8");
	h->display();
	cout << "Список доступных команд";
	cout << "\n" << "1. Вставить запись" << endl;
	cout << "2. Найти запись по ключу" << endl;
	cout << "3. Удалить запись по ключу" << endl;
	cout << "4. Вывести все записи" << endl;
	cout << "5. Выход" << endl;
	while (true) {
		cout << "Нажмите номер команды для выполнения: ";
		int choice;
		cin >> choice;

		switch (choice) {
		case 1: {
			int key;
			string fio, address;
			cout << "Введите номер счета-ключ (целое семизначное число): ";
			cin >> key;
			while (to_string(key).length() != 7 || key < 0) {
				if (to_string(key).length() != 7 || key < 0)
				{
					cout << "Номер должен быть целым семизначным числом: ";
				}
				cin >> key;
			}
			cin.ignore(); 
			cout << "Введите ФИО: ";
			getline(cin, fio);
			cout << "Введите адрес: ";
			getline(cin, address);
			h->insertNode(key, fio, address);
			break;
		}
		case 2: {
			int key;
			std::cout << "Введите номер счета-ключ для поиска: ";
			std::cin >> key;
			HashNode *result = h->get(key);
			if (result) {
				cout << "Найдена запись: Номер счета: " << result->key << ", ФИО: "
					<< result->fio << ", Адрес: " << result->adress << endl;
			}
			else {
				cout << "Запись не найдена." << endl;
			}
			break;
		}
		case 3: {
			int key;
			cout << "Введите номер счета-ключ для удаления: ";
			cin >> key;
			while (h->deleteNode(key) != 1) { 
				if (h->deleteNode(key) == 0)
				{
					cout << "Номер не найден, введите ещё раз: ";
				}
				cin >> key;
			}
			cout << "Запись удалена." << endl;
			break;
		}
		case 4:
			h->display();
			break;
		case 5:
			return 0;
		default: 
			cout << "Неверный выбор. Попробуйте снова." << endl;
			break;
		}
	}
	return 0;
}


