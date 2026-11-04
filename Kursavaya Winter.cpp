#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Сортировка пузырьком (Bubble Sort)
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Сортировка расческой (Comb Sort)
void combSort(vector<int>& arr)
{
    int n = arr.size();
    int gap = n;
    double division = 1.3;
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        gap = int(gap / division);
        if (gap < 1) gap = 1;

        swapped = false;
        for (int i = 0; i < n - gap; ++i)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> operations = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
    int runs = 1000; // Количество генераций для усреднения

    random_device rd;
    mt19937 gen(rd());

    cout << "Size\tBubble\tCombot\n";
    

    for (int size : operations) {
        long long totalBubble = 0;
        long long totalComb = 0;

        for (int r = 0; r < runs; ++r) 
        {
            // Генерируем случайный массив
            vector<int> arr(size);
            for (int i = 0; i < size; ++i)
            {
                arr[i] = gen();
            }

            // Замер для сортировки пузырьком
            vector<int> arrBubble = arr;
            auto startB = chrono::high_resolution_clock::now();
            bubbleSort(arrBubble);
            auto endB = chrono::high_resolution_clock::now();
            totalBubble += chrono::duration_cast<chrono::nanoseconds>(endB - startB).count();

            // Замер для сортировки расческой
            vector<int> arrComb = arr;
            auto startC = chrono::high_resolution_clock::now();
            combSort(arrComb);
            auto endC = chrono::high_resolution_clock::now();
            totalComb += chrono::duration_cast<chrono::nanoseconds>(endC - startC).count();
        }

        // Вывод среднего времени
        cout << size << "\t" << totalBubble / runs << "\t\t" << totalComb / runs << "\n";
    }
    return 0;
}