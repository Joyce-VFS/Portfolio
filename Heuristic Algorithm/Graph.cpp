#include "Graph.hpp"

namespace VertexCover
{

    Graph readFromFile(const std::string &filename)
    {
        Graph graph;
        std::ifstream file(filename);

        if (file.fail())
        {
            throw std::runtime_error("Couldnt open file: " + filename);
        }
        std::string line;
        while (std::getline(file, line))
        {
            // To get the dest and depart airports
            // departure first
            size_t departureCode_start = line.find("- ") + 2;
            size_t departureCode_end = line.find(" |", departureCode_start);
            Vertex departure = line.substr(departureCode_start, departureCode_end - departureCode_start);
            // destination second
            size_t destinationCode_start = line.rfind("- ") + 2;
            Vertex destination = line.substr(destinationCode_start);

            // gonna insert indirectly to graph
            graph[departure].insert(destination);
            graph[destination].insert(departure);
        }
        return graph;
    }

    std::unordered_set<Vertex> cover_graph(Graph g)
    {
        std::unordered_set<Vertex> cover;

        while (true)
        {
            Vertex vertexMax;
            size_t degreeMax = 0;
            bool hasEdges = false; // gonna flag the edges
            for (const auto &pair : g)
            {
                const Vertex &vertex = pair.first;
                const Neighbors &neighbors = pair.second;

                if (!neighbors.empty())
                    hasEdges = true;
                if (neighbors.size() > degreeMax)
                {
                    degreeMax = neighbors.size();
                    vertexMax = vertex;
                }

            } // if no more edges left
            if (!hasEdges)
                break;
            // adding vertex to cover
            cover.insert(vertexMax);
            // removing all edges connected to this vertex added
            for (const auto &neighbor : g[vertexMax])
            {
                g[neighbor].erase(vertexMax);
            }
            g.erase(vertexMax); // and then the vertex itself
        }
        return cover;
    }
}
