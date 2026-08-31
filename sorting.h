#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <algorithm>

struct Metrics {
    long long comparisons = 0;
    long long moves = 0;
};

//MERGE SORT (2 particiones) - O(n log n) 

inline void merge2(std::vector<int>& arr, int lo, int mid, int hi, Metrics& m) {
    std::vector<int> left(arr.begin() + lo, arr.begin() + mid + 1);
    std::vector<int> right(arr.begin() + mid + 1, arr.begin() + hi + 1);
    size_t i = 0, j = 0;
    int k = lo;
    while (i < left.size() && j < right.size()) {
        m.comparisons++;
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
        m.moves++;
    }
    while (i < left.size()) { arr[k++] = left[i++]; m.moves++; }
    while (j < right.size()) { arr[k++] = right[j++]; m.moves++; }
}

inline void mergeSort2(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    mergeSort2(arr, lo, mid, m);
    mergeSort2(arr, mid + 1, hi, m);
    merge2(arr, lo, mid, hi, m);
}

//MERGE SORT MODIFICADO (3 particiones) 
//Divide en 3 tercios, ordena cada uno, y une con 2 llamadas a merge2.

inline void mergeSort3(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    int len = hi - lo + 1;
    if (len < 3) { mergeSort2(arr, lo, hi, m); return; } // caso base: cae a merge clasico
    int third = len / 3;
    int mid1 = lo + third - 1;
    int mid2 = lo + 2 * third - 1;
    mergeSort3(arr, lo, mid1, m);
    mergeSort3(arr, mid1 + 1, mid2, m);
    mergeSort3(arr, mid2 + 1, hi, m);
    merge2(arr, lo, mid1, mid2, m);   //une primeros 2 tercios
    merge2(arr, lo, mid2, hi, m);     //une resultado con el ultimo tercio
}

//QUICK SORT CLASICO (1 pivote) - O(n log n) prom, O(n^2) peor

inline int partition1(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        m.comparisons++;
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            m.moves++;
        }
    }
    std::swap(arr[i + 1], arr[hi]);
    m.moves++;
    return i + 1;
}

inline void quickSort1(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    if (lo < hi) {
        int p = partition1(arr, lo, hi, m);
        quickSort1(arr, lo, p - 1, m);
        quickSort1(arr, p + 1, hi, m);
    }
}

//QUICK SORT MODIFICADO (2 pivotes: primero y ultimo, 3 particiones) 

inline void quickSort2(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    if (lo >= hi) return;

    if (arr[lo] > arr[hi]) { std::swap(arr[lo], arr[hi]); m.moves++; }
    int p1 = arr[lo], p2 = arr[hi];

    int lt = lo + 1, gt = hi - 1, i = lo + 1;
    while (i <= gt) {
        m.comparisons++;
        if (arr[i] < p1) {
            std::swap(arr[i], arr[lt]);
            m.moves++;
            lt++; i++;
        } else {
            m.comparisons++;
            if (arr[i] > p2) {
                while (i < gt) {
                    m.comparisons++;
                    if (arr[gt] <= p2) break;
                    gt--;
                }
                std::swap(arr[i], arr[gt]);
                m.moves++;
                gt--;
                m.comparisons++;
                if (arr[i] < p1) {
                    std::swap(arr[i], arr[lt]);
                    m.moves++;
                    lt++;
                }
            }
            i++;
        }
    }
    lt--; gt++;
    std::swap(arr[lo], arr[lt]); m.moves++;
    std::swap(arr[hi], arr[gt]); m.moves++;

    quickSort2(arr, lo, lt - 1, m);
    quickSort2(arr, lt + 1, gt - 1, m);
    quickSort2(arr, gt + 1, hi, m);
}

#endif
