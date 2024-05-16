#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <limits>
#include <algorithm>

using namespace std;
using namespace std::chrono;

double calculateTotalDistance(const vector<int> &route, const vector<vector<double>> &distMatrix)
{
    double totalDistance = 0;
    for (size_t i = 0; i < route.size() - 1; ++i)
    {
        totalDistance += distMatrix[route[i]][route[i + 1]];
    }
    return totalDistance;
}

vector<int> nearestNeighborAlgorithm(const vector<vector<double>> &distMatrix, int startNode = 0)
{
    int n = distMatrix.size();
    vector<bool> visited(n, false);
    vector<int> route;
    route.push_back(startNode);
    visited[startNode] = true;

    int currentNode = startNode;
    while (route.size() < n)
    {
        double minDistance = numeric_limits<double>::max();
        int nextNode = -1;
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i] && distMatrix[currentNode][i] < minDistance)
            {
                minDistance = distMatrix[currentNode][i];
                nextNode = i;
            }
        }
        visited[nextNode] = true;
        route.push_back(nextNode);
        currentNode = nextNode;
    }
    route.push_back(startNode); // Completing the cycle
    return route;
}

vector<int> twoOpt(const vector<int> &initialRoute, const vector<vector<double>> &distMatrix)
{
    vector<int> bestRoute = initialRoute;
    double bestCost = calculateTotalDistance(bestRoute, distMatrix);
    bool improved = true;

    while (improved)
    {
        improved = false;
        for (size_t i = 1; i < bestRoute.size() - 2; ++i)
        {
            for (size_t j = i + 1; j < bestRoute.size(); ++j)
            {
                if (bestRoute[j] == bestRoute[0])
                    continue;
                vector<int> newRoute = bestRoute;
                reverse(newRoute.begin() + i, newRoute.begin() + j);
                double newCost = calculateTotalDistance(newRoute, distMatrix);
                if (newCost < bestCost)
                {
                    bestRoute = newRoute;
                    bestCost = newCost;
                    improved = true;
                    break;
                }
            }
            if (improved)
                break;
        }
    }
    return bestRoute;
}

vector<vector<double>> readDistanceMatrix(const string &filename)
{
    ifstream file(filename);
    vector<vector<double>> distanceMatrix;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<double> row;
        double value;
        while (ss >> value)
        {
            row.push_back(value);
            if (ss.peek() == ',')
                ss.ignore();
        }
        distanceMatrix.push_back(row);
    }
    return distanceMatrix;
}

int main()
{
    string filename = "dist.txt";
    vector<vector<double>> distanceMatrix = readDistanceMatrix(filename);

    auto startTime = high_resolution_clock::now();

    vector<int> initialRoute = nearestNeighborAlgorithm(distanceMatrix);
    vector<int> optimizedRoute = twoOpt(initialRoute, distanceMatrix);
    double optimizedCost = calculateTotalDistance(optimizedRoute, distanceMatrix);

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    cout << "Optimized route: ";
    for (int city : optimizedRoute)
    {
        cout << city << " ";
    }
    cout << endl;
    cout << "Optimized cost: " << optimizedCost << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}