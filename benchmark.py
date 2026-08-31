import sys
import time
import csv
import threading

from sorting import Metrics, merge_sort2, merge_sort3, quick_sort1, quick_sort2

sys.setrecursionlimit(2_000_000)


def read_file(path):
    with open(path) as f:
        f.readline()  # n, no se usa directo
        data = list(map(int, f.readline().split()))
    return data


def run_one(dataset, name, func, original, results):
    arr = original.copy()
    m = Metrics()

    def target():
        func(arr, 0, len(arr) - 1, m)

    start = time.perf_counter()
    t = threading.Thread(target=target)
    t.start()
    t.join()
    elapsed_ms = (time.perf_counter() - start) * 1000

    if any(arr[i] > arr[i + 1] for i in range(len(arr) - 1)):
        print(f"ERROR: {name} en {dataset} no ordeno bien")

    results.append((dataset, name, len(arr), m.comparisons, m.moves, elapsed_ms))


def main():
    threading.stack_size(64 * 1024 * 1024)  # stack grande para recursion profunda (peor caso)

    datasets = ["data_random.txt", "data_sorted.txt", "data_reverse.txt", "data_partial.txt"]
    results = []

    for ds in datasets:
        data = read_file(ds)
        run_one(ds, "MergeSort2", merge_sort2, data, results)
        run_one(ds, "MergeSort3", merge_sort3, data, results)
        run_one(ds, "QuickSort1", quick_sort1, data, results)
        run_one(ds, "QuickSort2", quick_sort2, data, results)

    with open("resultados_python.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["dataset", "algoritmo", "n", "comparaciones", "intercambios", "tiempo_ms"])
        w.writerows(results)

    print(f"{'Dataset':<16} {'Algoritmo':<11} {'N':>8} {'Comparaciones':>14} {'Intercambios':>14} {'Tiempo(ms)':>10}")
    for r in results:
        print(f"{r[0]:<16} {r[1]:<11} {r[2]:>8} {r[3]:>14} {r[4]:>14} {r[5]:>10.3f}")

    print("\nResultados guardados en resultados_python.csv")


if __name__ == "__main__":
    main()