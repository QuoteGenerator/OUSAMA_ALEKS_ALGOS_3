#include <iostream>
#include <fstream>
#include <vector>

// Edge between stations
struct Edge
{
    std::string to;
    int weight;
    std::string line;
};


// Station in the graph
struct Station
{
    std::string name;
    std::vector<Edge> neighbors;
};


// Graph (list of stations)
std::vector<Station> graph;


// Find station index in graph
int findStation(std::string name)
{
    for(size_t i = 0; i < graph.size(); i++)
    {
        if(graph[i].name == name)
        {
            return i;
        }
    }

    return -1;
}


// Add connection between two stations
void addEdge(std::string from, std::string to, int weight, std::string line)
{
    int index = findStation(from);

    // if station does not exist yet, create it
    if(index == -1)
    {
        Station s;
        s.name = from;

        graph.push_back(s);
        index = graph.size() - 1;
    }

    Edge e;
    e.to = to;
    e.weight = weight;
    e.line = line;

    graph[index].neighbors.push_back(e);
}


// Read graph from file
void readFromFile(const char* filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }

    std::string line;

    while(getline(file, line))
    {
        int pos = line.find(":");

        std::string lineName = line.substr(0, pos);

        std::vector<std::string> stations;
        std::vector<int> weights;

        size_t i = pos + 1;

        while(i < line.length())
        {
            // read station name
            if(line[i] == '"')
            {
                i++;
                std::string station = "";

                while(line[i] != '"')
                {
                    station += line[i];
                    i++;
                }

                stations.push_back(station);
            }

            // read number (weight)
            if(isdigit(line[i]))
            {
                std::string number = "";

                while(isdigit(line[i]))
                {
                    number += line[i];
                    i++;
                }

                weights.push_back(stoi(number));
            }

            i++;
        }

        // create edges
        for(size_t j = 0; j < weights.size(); j++)
        {
            addEdge(stations[j], stations[j + 1], weights[j], lineName);
            addEdge(stations[j + 1], stations[j], weights[j], lineName);
        }
    }

    file.close();
}


int main()
{
    readFromFile("wien.txt");

    // Ausgabe testen
    for(size_t i = 0; i < graph.size(); i++)
    {
        std::cout << graph[i].name << std::endl;

        for(size_t j = 0; j < graph[i].neighbors.size(); j++)
        {
            std::cout << " -> "
                 << graph[i].neighbors[j].to
                 << " "
                 << graph[i].neighbors[j].weight
                 << " "
                 << graph[i].neighbors[j].line
                 << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
