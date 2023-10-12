#include <iostream>

using namespace std;

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
            array[i] = rand() % 199-99;
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
        cout << "5) Выход " << endl;

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
                cout << endl << "Ваш элемент находится под номером " << Index + 1 << endl;
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
            break;
        }
        break;
        default:cout << "Ошибка! Повторите попытку" << endl;
            break;
        }

    } while (e != 5);

}
