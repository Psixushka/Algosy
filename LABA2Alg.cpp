#include <iostream>
using namespace std;
const int RUN = 32;

class dynamic_array
{
private:
    int size;
    int* array;

public:
    dynamic_array()
    {
        size = 0;
        array = NULL;
        cout << "Введите количество элементов" << endl;
        cin >> size;
        array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = rand() % 199 - 99;
        }
    }
    ~dynamic_array() {
        delete[] array;
        array = nullptr;
    }

    void show()
    {
        for (int i = 0; i < size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    void insertArray()
    {
        show();
        cout << endl;
        int Index, Data;
        int* array2 = new int[size++];

        cout << "Введите индекс для вставки" << endl;
        cin >> Index;
        cout << "Введите значение для вставки" << endl;
        cin >> Data;
        for (int i = 0; i < size; i++)
        {
            if (i < Index)
            {
                array2[i] = array[i];
            }

            if (i >= Index)
            {
                array2[i + 1] = array[i];

            }
            if (i == Index) {

                array2[i] = Data;
            }

        }

        for (int i = 0; i < size; i++)
        {
            array[i] = array2[i];
        }
        for (int i = 0; i < size; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    void deleteArray()
    {
        show();
        cout << "Введите индекс элемента" << endl;
        int index;
        cin >> index;
        for (int i = index; i < size - 1; i++)
        {
            array[i] = array[i + 1];
        }
        size--;

        for (int i = 0; i < size; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    int GetElemIndex(int Index, int Data)
    {

        for (int i = 0; i < size; i++)
        {
            if (i == Index)
            {
                Data = array[i];
            }
        }

        return Data;
    }
    int GetElemData(int Index, int Data)
    {

        for (int i = 0; i < size; i++)
        {
            if (array[i] == Data)
            {
                Index = i;
            }

        }

        return Index;
    }


    void InsertionSort(int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int temp = array[i];
            int j = i - 1;
            while (array[j] > temp && j >= left) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = temp;
        }
    }


    void merge(int l, int m, int r)
    {

        int len1 = m - l + 1, len2 = r - m;
        int* left = new int [len1], *right = new int [len2];
        for (int i = 0; i < len1; i++)
            left[i] = array[l + i];
        for (int i = 0; i < len2; i++)
            right[i] = array[m + 1 + i];

        int i = 0, j = 0, k = l;

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
        delete[] left;
        delete[] right;
    }


    void timSort()
    {

        for (int i = 0; i < size; i += RUN)
            InsertionSort( i, min((i + RUN - 1), (size - 1)));


        for (int sized = RUN; sized < size; sized = 2 * size) {


            for (int left = 0; left < size; left += 2 * size) {
                int mid = left + size - 1;
                int right = min((left + 2 * size - 1), (size - 1));

                if (mid < right)
                    merge(left, mid, right);
            }
        }
    }
};

int main()
{
    setlocale(0, "RUS");
    cout << "Поехали" << endl;
    dynamic_array my_array;
    int e;
    do {
        cout << "Выберите действие: " << endl;
        cout << "1) Вставка" << endl;
        cout << "2) Получение значения по индексу " << endl;
        cout << "3) Получение значения по значению элемента " << endl;
        cout << "4) Удаление элемента " << endl;
        cout << "5) Cортировка методом TimSort " << endl << endl;
        my_array.show();
        cin >> e;
        switch (e)
        {
        case 1:
        {
            my_array.insertArray();

        }
        break;
        case 2:
        {
            int Index, Data = 0;
            my_array.show();
            cout << "Введите индекс элемента котрый хотите получить " << endl;
            cin >> Index;

            Data = my_array.GetElemIndex(Index, Data);
            cout << endl << "Ваш элемент = " << Data << endl;

        }
        break;
        case 3:
        {
            int Index = -5, Data = 0;
            my_array.show();
            cout << "Введите элемент котрый хотите получить " << endl;
            cin >> Data;
            Index = my_array.GetElemData(Index, Data);
            if (Index != -5) {
                cout << endl << "Ваш элемент находится под номером " << Index  << endl;
            }
            else
            {
                cout << "Элемент не найден!" << endl;
            }
        }
        break;
        case 4:
        {
            my_array.deleteArray();
        }
        break;
        case 5:
        {
            my_array.timSort();
            break;
        }
        break;
        default:cout << "Ошибка! Повторите попытку" << endl;
            break;
        }

    } while (e != 6);

}