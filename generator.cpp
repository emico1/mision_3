#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

void writeFile(const std::string& path, const std::vector<int>& data) {
    std::ofstream f(path);
    f << data.size() << "\n";
    for (int v : data) f << v << " ";
    f.close();
}

int main(int argc, char** argv) {
    //N distinto para casos O(n log n) vs peor caso O(n^2) 
    int nEasy = (argc > 1) ? std::stoi(argv[1]) : 100000;
    int nHard = (argc > 2) ? std::stoi(argv[2]) : 8000;
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 1000000);

    //1. aleatorio
    std::vector<int> random(nEasy);
    for (int& v : random) v = dist(rng);
    writeFile("data_random.txt", random);

    //2. ya ordenado ascendente
    std::vector<int> sorted(nHard);
    for (int& v : sorted) v = dist(rng);
    std::sort(sorted.begin(), sorted.end());
    writeFile("data_sorted.txt", sorted);

    //3. ordenado en forma inversa
    std::vector<int> reverse = sorted;
    std::reverse(reverse.begin(), reverse.end());
    writeFile("data_reverse.txt", reverse);

    //4. parcialmente ordenado: bloques grandes ya ordenados
    std::vector<int> partial(nHard);
    for (int& v : partial) v = dist(rng);
    int blockSize = std::max(1, nHard / 10);
    for (int i = 0; i < nHard; i += blockSize) {
        int end = std::min(nHard, i + blockSize);
        std::sort(partial.begin() + i, partial.begin() + end);
    }
    writeFile("data_partial.txt", partial);

    std::cout << "Generado: random/partial n=" << nEasy << ", sorted/reverse n=" << nHard << "\n";
    return 0;
}