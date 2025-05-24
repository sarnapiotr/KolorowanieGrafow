#include <iostream>

class Graph {
private:
    int vertexCount;
    int edgeCount;
    int** graphMatrix;

public:
    Graph(int vertexCount, int edgeCount) : vertexCount(vertexCount), edgeCount(edgeCount) {
        graphMatrix = new int*[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            graphMatrix[i] = new int[vertexCount]();
        }

        int currentEdgeCount = 0;
    }

    void printGraph() {
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                std::cout << graphMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    ~Graph() {
        for (int i = 0; i < vertexCount; i++) {
            delete[] graphMatrix[i];
        }
        delete[] graphMatrix;
    }
};

int main()
{
    std::cout << "Problem kolorowania grafow\n";
    std::cout << "1. Algorytm dokladny\n";
    std::cout << "2. Algorytm LF\n";
    std::cout << "Wybierz algorytm: \n";

    int choice;
    std::cin >> choice;

    int vertexCount;
    int edgeCount;

    if (choice == 1) {
        std::cout << "Podaj ilosc wierzcholkow: \n";
        std::cin >> vertexCount;
        std::cout << "Podaj ilosc krawedzi: \n";
        std::cin >> edgeCount;

        int edgeMax{(vertexCount * (vertexCount - 1)) / 2};
        if (vertexCount < 1 || edgeCount < 1 || edgeCount > edgeMax) {
            std::cout << "Niepoprawne dane wejsciowe\n";
            return -1;
        }

        Graph graph = Graph(vertexCount, edgeCount);
        graph.printGraph();

    }
    else if (choice == 2) {

    }
    else {
        std::cout << "Niepoprawny wybor\n";
        return -1;
    }

    return 0;
}
