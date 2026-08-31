#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "sorting.h"

std::vector<int> readFile(const std::string& path) {
    std::ifstream f(path);
    int n; f >> n;
    std::vector<int> data(n);
    for (int& v : data) f >> v;
    return data;
}

struct Result {
    std::string dataset;
    std::string algorithm;
    int n;
    long long comparisons;
    long long moves;
    double ms;
};

void runOne(const std::string& dataset, const std::string& algName,
            void (*fn)(std::vector<int>&, int, int, Metrics&),
            const std::vector<int>& original, std::vector<Result>& results) {
    std::vector<int> arr = original;
    Metrics m;
    auto start = std::chrono::high_resolution_clock::now();
    fn(arr, 0, (int)arr.size() - 1, m);
    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    if (!std::is_sorted(arr.begin(), arr.end())) {
        std::cerr << "ERROR: " << algName << " en " << dataset << " no ordeno bien\n";
    }
    results.push_back({dataset, algName, (int)arr.size(), m.comparisons, m.moves, ms});
}

int main() {
    std::vector<std::string> datasets = {"data_random.txt", "data_sorted.txt",
                                          "data_reverse.txt", "data_partial.txt"};
    std::vector<Result> results;

    for (const auto& ds : datasets) {
        std::vector<int> data = readFile(ds);
        runOne(ds, "MergeSort2", mergeSort2, data, results);
        runOne(ds, "MergeSort3", mergeSort3, data, results);
        runOne(ds, "QuickSort1", quickSort1, data, results);
        runOne(ds, "QuickSort2", quickSort2, data, results);
    }

    std::ofstream csv("resultados.csv");
    csv << "dataset,algoritmo,n,comparaciones,intercambios,tiempo_ms\n";
    for (const auto& r : results) {
        csv << r.dataset << "," << r.algorithm << "," << r.n << ","
            << r.comparisons << "," << r.moves << "," << r.ms << "\n";
    }
    csv.close();

    printf("%-16s %-11s %8s %14s %14s %10s\n",
           "Dataset", "Algoritmo", "N", "Comparaciones", "Intercambios", "Tiempo(ms)");
    for (const auto& r : results) {
        printf("%-16s %-11s %8d %14lld %14lld %10.3f\n",
               r.dataset.c_str(), r.algorithm.c_str(), r.n, r.comparisons, r.moves, r.ms);
    }

    std::cout << "\nResultados guardados en resultados.csv\n";
    return 0;
}