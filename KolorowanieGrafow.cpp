#include <iostream>
#include <vector>

void chooseGraphMatrix(int**& graphMatrix, int& vertexCount) {
    std::cout << "Wybierz graf do pokolorowania: \n";
    std::cout << "1. Graf 3-wierzcholkowy\n";
    std::cout << "2. Graf 5-wierzcholkowy\n";
    std::cout << "3. Graf 10-wierzcholkowy\n";

    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        vertexCount = 3;
        graphMatrix = new int* [vertexCount] {
            new int[vertexCount] {0, 1, 1},
            new int[vertexCount] {1, 0, 1},
            new int[vertexCount] {1, 1, 0}};
        break;
    case 2:
        vertexCount = 5;
        graphMatrix = new int* [vertexCount] {
            new int[vertexCount] {0, 1, 1, 1, 1},
            new int[vertexCount] {1, 0, 1, 1, 1},
            new int[vertexCount] {1, 1, 0, 1, 0},
            new int[vertexCount] {1, 1, 1, 0, 1},
            new int[vertexCount] {1, 1, 0, 1, 0}};
        break;
    case 3:
        vertexCount = 10;
        graphMatrix = new int* [vertexCount] {
            new int[vertexCount] {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            new int[vertexCount] {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
            new int[vertexCount] {1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
            new int[vertexCount] {1, 1, 1, 0, 1, 1, 0, 0, 0, 0},
            new int[vertexCount] {1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
            new int[vertexCount] {0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
            new int[vertexCount] {0, 0, 0, 0, 1, 1, 0, 1, 1, 0},
            new int[vertexCount] {0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
            new int[vertexCount] {0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            new int[vertexCount] {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}};
        break;
    default:
        std::cout << "Niepoprawny wybor\n";
        return;
    }
}

void printGraph(int**& graphMatrix, const int& vertexCount) {
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            std::cout << graphMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isSafe(int** graphMatrix, const int& vertexCount, const std::vector<int>& colors, const int& vertex, const int& color) {
    for (int i = 0; i < vertexCount; i++) {
        if (graphMatrix[vertex][i] == 1 && colors[i] == color) {
            return false;
        }
    }
    return true;
}

bool solveColoring(int** graphMatrix, const int& vertexCount, std::vector<int>& colors, const int& vertex, const int& maxColors) {
    if (vertex == vertexCount) {
        return true;
    }

    for (int color = 1; color <= maxColors; color++) {
        if (isSafe(graphMatrix, vertexCount, colors, vertex, color)) {
            colors[vertex] = color;
            if (solveColoring(graphMatrix, vertexCount, colors, vertex + 1, maxColors)) {
                return true;
            }
            colors[vertex] = 0;
        }
    }
    return false;
}

void exactGraphColoring(int** graphMatrix, const int& vertexCount) {
    std::vector<int> colors(vertexCount, 0);

    for (int maxColors = 1; maxColors <= vertexCount; maxColors++) {
        if (solveColoring(graphMatrix, vertexCount, colors, 0, maxColors)) {
            std::cout << "Minimalna liczba kolorow: " << maxColors << "\n";
            for (int i = 0; i < vertexCount; i++) {
                std::cout << "Wierzcholek " << i << ": Kolor " << colors[i] << "\n";
            }
            return;
        }
    }
}

struct Vertex {
    int index, neighboursCount;
};

std::vector<Vertex> getSortedVertexVector(int** graphMatrix, const int& vertexCount) {
    std::vector<Vertex> vertexVector(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        int neighboursCount = 0;
        for (int j = 0; j < vertexCount; j++) {
            if (graphMatrix[i][j] == 1) {
                neighboursCount++;
            }
        }
        vertexVector[i] = {i, neighboursCount};

    }

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (vertexVector[j].neighboursCount > vertexVector[i].neighboursCount) {
                std::swap(vertexVector[i], vertexVector[j]);
            }
        }
    }

    return vertexVector;
}

void LFgraphColoring(int**& graphMatrix, const int& vertexCount) {
    std::vector<int> colors(vertexCount, 0);
    std::vector<Vertex> vertexVector = getSortedVertexVector(graphMatrix, vertexCount);

    int maxColors = 1;
    for (int i = 0; i < vertexCount; i++) {
        int vertexIndex = vertexVector[i].index;
        bool colored = false;

        for (int j = 1; j <= maxColors; j++) {
            if (isSafe(graphMatrix, vertexCount, colors, vertexIndex, j)) {
                colors[vertexIndex] = j;
                colored = true;
                break;
            }
        }

        if (!colored) {
            colors[vertexIndex] = ++maxColors;
        }
    }

    std::cout << "Minimalna liczba kolorow: " << maxColors << "\n";
    for (int i = 0; i < vertexCount; i++) {
        std::cout << "Wierzcholek " << i << ": Kolor " << colors[i] << "\n";
    }
}

int main()
{
    std::cout << "Problem kolorowania grafow\n";

    int** graphMatrix{ nullptr };
    int vertexCount{ 0 };

    chooseGraphMatrix(graphMatrix, vertexCount);
    printGraph(graphMatrix, vertexCount);

    std::cout << "1. Algorytm dokladny\n";
    std::cout << "2. Algorytm LF\n";
    std::cout << "Wybierz algorytm: \n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        exactGraphColoring(graphMatrix, vertexCount);
    }
    else if (choice == 2) {
        LFgraphColoring(graphMatrix, vertexCount);
    }
    else {
        std::cout << "Niepoprawny wybor\n";
        for (int i = 0; i < vertexCount; i++) {
            delete[] graphMatrix[i];
        }
        delete[] graphMatrix;
        return -1;
    }

    for (int i = 0; i < vertexCount; i++) {
        delete[] graphMatrix[i];
    }
    delete[] graphMatrix;

    return 0;
}

//graphMatrix = new int* [vertexCount] {
//    new int[vertexCount] {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
//    new int[vertexCount] {1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
//    new int[vertexCount] {0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
//    new int[vertexCount] {0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
//    new int[vertexCount] {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
//    new int[vertexCount] {1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//    new int[vertexCount] {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//    new int[vertexCount] {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//    new int[vertexCount] {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//    new int[vertexCount] {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};
