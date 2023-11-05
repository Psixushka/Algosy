#include <iostream>
#include <vector>
using namespace std;
const int RUN = 32;
class DynamicArray {
private:

	int* array = NULL;
	int size;
	int capacity;

public:
	DynamicArray()
	{
		capacity = 1;
		size = 0;
		array = new int[capacity];
	}

	DynamicArray(int capacity)
	{
		this->capacity = capacity;
		array = new int[capacity];
		size = 0;
	}

	int getSize() { return size; }

	int getCapacity() { return capacity; }

	void push_back(int value)
	{
		if (size == capacity) {

			growArray();
		}

		array[size] = value;
		size++;
	}

	void pop_back()
	{
		array[size - 1] = 0;

		size--;
		if (size == (capacity / 2)) {
			shrinkArray();
		}
	}

	void growArray()
	{
		int* temp = new int[capacity * 2];

		capacity = capacity * 2;
		for (int i = 0; i < size; i++) {
			temp[i] = array[i];
		}

		delete[] array;
		array = temp;
	}



	void shrinkArray()
	{

		capacity = size;
		int* temp = new int[capacity];

		for (int i = 0; i < size; i++) {
			temp[i] = array[i];
		}

		delete[] array;
		array = temp;
	}

	int search(int key)
	{
		for (int i = 0; i < size; i++) {
			if (array[i] == key) {
				return i;
			}
		}
		return -1;
	}

	void insertAt(int index, int value)
	{
		if (size == capacity) {
			growArray();
		}

		for (int i = size - 1; i >= index; i--) {
			array[i + 1] = array[i];
		}

		array[index] = value;
		size++;
	}

	void deleteAt(int index)
	{
		for (int i = index; i < size; i++) {
			array[i] = array[i + 1];
		}

		array[size - 1] = 0;
		size--;

		if (size == (capacity / 2)) {
			shrinkArray();
		}
	}

	void printArrayDetails()
	{
		cout << " Массив : ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		cout << endl;
		cout << " Кол-во элементов : " << size
			<< ", capacity :" << capacity << endl;
	}

	bool isEmpty()
	{
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int getMinRun()
	{
		int r = 0;
		int n = size;
		while (n >= RUN) {
			r |= (n & 1);
			n >>= 1;
		}
		return n + r;
	}

	void insertionSort(int left, int right)
	{
		for (int i = left + 1; i <= right; i++) {
			int temp = array[i];
			int j = i - 1;
			while (j >= left && array[j] > temp) {
				array[j + 1] = array[j];
				j--;
			}
			array[j + 1] = temp;
		}
	}


	void merge( int l, int m, int r)
	{

		int len1 = m - l + 1, len2 = r - m;
		int* left = new int [len1], *right = new int [len2];
		for (int i = 0; i < len1; i++)
			left[i] = array[l + i];
		for (int i = 0; i < len2; i++)
			right[i] = array[m + 1 + i];

		int i = 0;
		int j = 0;
		int k = l;

	
		while (i < len1 && j < len2) {
			if (left[i] <= right[j]) {
				array[k] = left[i];
				i++;
			}
			else {
				array[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < len1) {
			array[k] = left[i];
			k++;
			i++;
		}

		
		while (j < len2) {
			array[k] = right[j];
			k++;
			j++;
		}
	}

	void timSort()
	{
		int minRun = getMinRun();
		for (int i = 0; i < size; i += minRun)
			insertionSort(i, min((i + minRun - 1), (size - 1)));
		int len = minRun;
		while (len < size) {
			for (int start = 0; start < size; start += 2 * len) {
				int mid = start + len - 1;
				int end = min((start + 2 * len - 1), (size - 1));
				merge(start, mid, end);
			}
			len *= 2;
		}

	}

	void printArray(int arr[], int n)
	{
		for (int i = 0; i < n; i++)
			printf("%d  ", arr[i]);
		printf("\n");
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	
	DynamicArray da;
	int size, i;
	cout << " Введите количество элементов массива: " << endl;
	cin >> size;
	for (i = 0; i < size; i++) {
		da.push_back(rand() % 199-99);
	}

	da.printArrayDetails();
	int e;
	do {
		cout << " Выберите действие: " << endl;
		cout << "1) Вставка" << endl;
		cout << "2) Получение индекса элемента " << endl;
		cout << "3) Удаление элемента по индексу " << endl;
		cout << "4) Удаление последнего элемента  " << endl;
		cout << "5) Сортировка списка алгоритмом TimSort  " << endl;
		cout << "6) Выход " << endl;

		cin >> e;

		switch (e)
		{
		case 1:
		{
			int index, value;
			cout << "Введите индекс , куда необходимо вставить элемент " << endl;
			cin >> index;
			cout << "Введите элемент " << endl;
			cin >> value;
			da.insertAt(index, value);
			da.printArrayDetails();
		}
		break;
		case 2:
		{
			int value;
			cout << "Введите элемент который хотите получить " << endl;
			cin >> value;
			int index = da.search(value);
			if (index != -1) {
				cout << "Element found at index : " << index << endl;
			}
			else {
				cout << "Element not found " << endl;
			}
		}
		break;
		case 3:
		{
			int index;

			cout << "Введите индекс элемента, который хотите удалить " << endl;
			cin >> index;
			da.deleteAt(index);
			da.printArrayDetails();
		}
		break;
		case 4:
		{
			cout << "Удаление последнего элемента  " << endl;
			da.pop_back();
			da.printArrayDetails();
		}
		break;
		case 5:
		{
			da.timSort();
			da.printArrayDetails();
			break;
		}
		case 6:
		{
			break;
		}
		break;

		}
	} while (e != 6);
}
