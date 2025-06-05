#include "Graph.hpp"
#include <iostream>

void printCover(const std::unordered_set<Vertex> &cover)
{
    std::cout << "Vertex Cover (TSA Agents needed at): ";
    for (const auto &airport : cover)
    {
        std::cout << airport << " ";
    }
    std::cout << "\nSize: " << cover.size() << " airports" << std::endl;
}

int main()
{
    try
    {
        // Test with sm_flights.txt
        Graph graph = VertexCover::readFromFile("sm_flights.txt");
        std::unordered_set<Vertex> cover = VertexCover::cover_graph(graph);
        printCover(cover);

        // Optional: Test with an empty graph
        Graph emptyGraph;
        std::unordered_set<Vertex> emptyCover = VertexCover::cover_graph(emptyGraph);
        std::cout << "\nEmpty Graph Test:" << std::endl;
        printCover(emptyCover);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}