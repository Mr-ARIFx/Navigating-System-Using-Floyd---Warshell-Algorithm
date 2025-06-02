#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

#define INF INT_MAX

void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& next, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
}

void printPath(map<int, string>& locations, vector<vector<int>>& next, int u, int v) {
    if (next[u][v] == -1) {
        cout << "No path exists!";
        return;
    }
    
    cout << "Path: " << locations[u];
    while (u != v) {
        u = next[u][v];
        cout << " -> " << locations[u];
    }
}

int main() {
    cout << "Welcome to Campus Navigator!\n\n";
    
    int V;
    cout << "Enter number of locations: ";
    cin >> V;
    
    map<int, string> locations;
    map<string, int> idxMap;
    
    for (int i = 0; i < V; i++) {
        cout << "Enter name for location " << i << ": ";
        string name;
        cin >> name;
        locations[i] = name;
        idxMap[name] = i;
    }
    
    vector<vector<int>> dist(V, vector<int>(V, INF));
    vector<vector<int>> next(V, vector<int>(V, -1));
    
    for (int i = 0; i < V; i++) dist[i][i] = 0;
    
    int E;
    cout << "\nEnter number of paths: ";
    cin >> E;
    
    cout << "Enter paths (from to distance):\n";
    for (int i = 0; i < E; i++) {
        string from, to;
        int d;
        cout << "Path " << i + 1 << ": ";
        cin >> from >> to >> d;
        
        if (idxMap.find(from) == idxMap.end()) {
            cout << "Error: Unknown location '" << from << "'\n";
            i--;
            continue;
        }
        if (idxMap.find(to) == idxMap.end()) {
            cout << "Error: Unknown location '" << to << "'\n";
            i--;
            continue;
        }
        
        int u = idxMap[from];
        int v = idxMap[to];
        
        // Keep shortest distance if multiple edges exist
        if (d < dist[u][v]) {
            dist[u][v] = d;
            next[u][v] = v;
        }
    }
    
    floydWarshall(dist, next, V);
    
    cout << "\nNavigation Ready! Type 'exit' to quit\n";
    
    while (true) {
        string start, end;
        cout << "\nEnter starting point: ";
        cin >> start;
        if (start == "exit") break;
        
        cout << "Enter destination: ";
        cin >> end;
        
        if (!idxMap.count(start) || !idxMap.count(end)) {
            cout << "Invalid locations! Try again\n";
            continue;
        }
        
        int u = idxMap[start];
        int v = idxMap[end];
        
        if (dist[u][v] == INF) {
            cout << "No path exists between " << start << " and " << end << "\n";
            continue;
        }
        
        cout << "\nShortest path from " << start << " to " << end << "\n";
        cout << "Distance: " << dist[u][v] << " units\n";
        printPath(locations, next, u, v);
        cout << "\n";
    }
    
    cout << "\nThank you for using Campus Navigator!\n";
    return 0;
}