#include <iostream>
#include <vector>
#include <array> 
#include <ctime>
#include <time.h> 
#include <random>
#include <chrono>
using namespace std;
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // Левый дочерний элемент
    int right = 2 * i + 2; // Правый дочерний элемент

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если самый большой элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Рекурсивно применяем heapify к измененному поддереву
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();

    // Построение max heap (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // Вызываем heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    vector<int> L(n1), R(n2);

    // Копируем данные во временные массивы L[] и R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Объединяем временные массивы обратно в основной массив arr[left..right]
    int i = 0; // Индекс первого подмассива (L)
    int j = 0; // Индекс второго подмассива (R)
    int k = left; // Индекс сливаемого подмассива (arr)

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы L[], если такие есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы R[], если такие есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находим среднюю точку
        int mid = left + (right - left) / 2;

        // Рекурсивно сортируем обе половины
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Объединяем отсортированные половины
        merge(arr, left, mid, right);
    }
}

void quick_sort(vector<int>& arr, int start, int end)
{
    int i = start;
    int j = end - 1;

    // Выбираем центральный элемент как медиану из трех
    int mid = arr[(start + end) / 2];

    // Делим массив
    while (i <= j)
    {
        // Пропускаем элементы, которые меньше центрального
        while (arr[i] < mid) {
            i++;
        }

        // Пропускаем элементы, которые больше центрального
        while (arr[j] > mid) {
            j--;
        }

        // Меняем элементы местами
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    // Рекурсивные вызовы, если осталось, что сортировать
    if (j > start) {
        // "Левый кусок"
        quick_sort(arr, start, j + 1);
    }
    if (i < end) {
        // "Правый кусок"
        quick_sort(arr, i, end);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int i = 0;
    double a_time = 0;
    double count = 5;
    while (i < 5) {
        clock_t start, end;
        int size = 500000;
        vector<int> arr(size);
        start = clock();
        for (int i = 1; i <= size; ++i) {
            arr[i - 1] = i;
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(arr.begin(), arr.end(), g);
        cout << endl;
        heap_sort(arr); (arr, 0, arr.size() - 1);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

        cout << time_taken;
        a_time += time_taken;
        i++;


    }
    cout << "\n" << a_time / count;
}
