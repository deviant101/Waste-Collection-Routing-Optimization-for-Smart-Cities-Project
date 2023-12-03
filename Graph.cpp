#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include <vector>
#include <time.h>
using namespace std;

class Graph{
    public:
        const int NO_OF_VERTICES;
        int **Vertices_Graph;
        string Locations_Name[13];
        int binLevels[11];
        vector<int> collectibleBins;        //to store collectible bins

        Graph():NO_OF_VERTICES(13){
            Vertices_Graph = new int*[NO_OF_VERTICES];
            for(int i=0; i<NO_OF_VERTICES; ++i){
                Vertices_Graph[i] = new int[NO_OF_VERTICES];
            }
        }

        void make_graph(string fileName){

            fstream file;
            file.open(fileName,ios::in);

            string line="";
            getline(file,line);

            for(int vertex=1; vertex<NO_OF_VERTICES; vertex++){
                line="";
                getline(file,line);
                // cout<<line<<endl;
                string sub_part="";
                int comma_count = 0;
                int x_axis = 1;

                for(int i=0; i<line.length(); i++){
                    if(line[i]!=',' && i!=line.length()-1)  //giving extra
                        sub_part+=line[i];
                    else{
                        if(comma_count==0){
                            Locations_Name[vertex]=sub_part;
                            // cout<<vertex<<" "<<Locations_Name[vertex]<<endl;
                        }
                        else if(comma_count>=1){
                            Vertices_Graph[vertex][x_axis++]=stoi(sub_part);
                            // cout<<Vertices_Graph[vertex][x_axis-1]<<endl;
                        }
                        sub_part="";
                        ++comma_count;
                    }
                }
            }
            file.close();
            // binsData();
        }

        void binsData(){

            int binsHourlyData[72];
            fstream binFile;
            binFile.open("Bin-Data.csv",ios::in);

            for(int i=0; i<72; i++){
                
                string percent;
                getline(binFile,percent);
                binsHourlyData[i]=stoi(percent);
            }
            binFile.close();

            vector<int> bin;
            srand(time(NULL));
            for(int i=1; i<11; ++i){

                int index = 1+rand()%72;
                bool exist=false;
                for(int j=0; j<bin.size(); ++j){
                    if(index==bin[j]){
                        exist=true;
                        break;
                    }
                }
                if(!exist){
                    binLevels[i]=binsHourlyData[index];
                    bin.push_back(index);
                }
                else
                    --i;
            }

            cout<<"\n---------------[FILL LEVELS]---------------\n\n";
            for(int i=1,j=2; i<11; ++i,++j)
                cout<<Locations_Name[j]<<"  =  "<<binLevels[i]<<" %"<<endl;

        }

        void findShortestPath(int src, int dest){
            dijkstra(Vertices_Graph, src, dest, NO_OF_VERTICES);
        }

        void Display_Graph(){
            for(int i=1; i<NO_OF_VERTICES; ++i){
                cout<<Locations_Name[i]<<" = ";
                for(int j=1; j< NO_OF_VERTICES; ++j){
                    cout<<Vertices_Graph[i][j]<<" ";
                }
                cout<<endl;
            }
        }

    private:
    /*
        void dijkstra(int **graph, int src, int dest, int maxVertices){
            int distance[13];
            bool visited[13];

            // Initialize distance array and visited array
            for (int i = 1; i < maxVertices; i++) {
                distance[i] = INT_MAX;
                visited[i] = false;
            }

            // Distance from src to itself is always 0
            distance[src] = 0;

            // Find shortest path for all vertices
            for (int count = 1; count < maxVertices; count++) {
                // Find the minimum distance vertex from the set of vertices not yet processed
                int minDistance = INT_MAX, minIndex;

                for (int v = 1; v < maxVertices; v++) {
                    if (!visited[v] && distance[v] <= minDistance) {
                        minDistance = distance[v];
                        minIndex = v;
                    }
                }

                // Mark the picked vertex as visited
                visited[minIndex] = true;

                // Update distance value of the adjacent vertices of the picked vertex
                for (int v = 1; v < maxVertices; v++){
                    if (!visited[v] && graph[minIndex][v] && distance[minIndex] != INT_MAX &&
                        distance[minIndex] + graph[minIndex][v] < distance[v]){
                        distance[v] = distance[minIndex] + graph[minIndex][v];
                    }
                }
            }

            // Print the shortest distance from src to dest
            cout << "Shortest distance from " << src << " to " << dest << " is: " << distance[dest]<<endl;
        }*/

        void dijkstra(int **graph, int src, int dest, int vertices) {
            int distance[13];
            int predecessor[13];  // To store the predecessor of each vertex in the shortest path
            bool visited[13];

            // Initialize distance array, predecessor array, and visited array
            for (int i = 1; i < vertices; i++) {
                distance[i] = INT_MAX;
                predecessor[i] = -1;  // Initialize predecessors to -1
                visited[i] = false;
            }

            // Distance from src to itself is always 0
            distance[src] = 0;

            // Find shortest path for all vertices
            for (int count = 1; count < vertices; count++) {
                // Find the minimum distance vertex from the set of vertices not yet processed
                int minDistance = INT_MAX, minIndex;

                for (int v = 1; v < vertices; v++) {
                    if (!visited[v] && distance[v] <= minDistance) {
                        minDistance = distance[v];
                        minIndex = v;
                    }
                }

                // Mark the picked vertex as visited
                visited[minIndex] = true;

                // Update distance value of the adjacent vertices of the picked vertex
                for (int v = 1; v < vertices; v++) {
                    if (!visited[v] && graph[minIndex][v] && distance[minIndex] != INT_MAX &&
                        distance[minIndex] + graph[minIndex][v] < distance[v]) {
                        distance[v] = distance[minIndex] + graph[minIndex][v];
                        predecessor[v] = minIndex;
                    }
                }
            }

            // Print the shortest distance from src to dest
            cout << "Shortest distance from " << src << " to " << dest << " is: " << distance[dest] << endl;

            // Print the path
            cout << "Path: ";
            vector<int> path;
            int currentVertex = dest;
            while (currentVertex != -1) {
                path.push_back(currentVertex);
                currentVertex = predecessor[currentVertex];
            }
            for (int i = path.size() - 1; i >= 0; i--) {
                cout << path[i] << " ";
            }
            cout << endl;
        }



};