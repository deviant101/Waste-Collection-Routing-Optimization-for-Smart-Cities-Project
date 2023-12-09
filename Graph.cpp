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
        int **graphVertices;
        string Locations_Name[13];
        int binLevels[12];
        vector<int> collectibleBins;        //to store collectible bins

        Graph():NO_OF_VERTICES(13){
            graphVertices = new int*[NO_OF_VERTICES];
            for(int i=0; i<NO_OF_VERTICES; ++i){
                graphVertices[i] = new int[NO_OF_VERTICES];
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
                            graphVertices[vertex][x_axis++]=stoi(sub_part);
                            // cout<<graphVertices[vertex][x_axis-1]<<endl;
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

            int binsHourlyData[73];
            fstream binFile;
            binFile.open("Bin-Data.csv",ios::in);

            for(int i=1; i<=72; i++){
                
                string percent;
                getline(binFile,percent);
                binsHourlyData[i]=stoi(percent);
            }
            binFile.close();

            vector<int> bin;
            srand(time(NULL));
            for(int i=2; i<=11; ++i){

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

        }

        void findShortestPath(int src, int dest, Driver &driver){
            dijkstra(graphVertices, src, dest, NO_OF_VERTICES, driver);
        }

        void Display_Graph(){
            for(int i=1; i<NO_OF_VERTICES; ++i){
                cout<<Locations_Name[i]<<" = ";
                for(int j=1; j< NO_OF_VERTICES; ++j){
                    cout<<graphVertices[i][j]<<" ";
                }
                cout<<endl;
            }
        }

    private:

        void dijkstra(int **graph, int src, int dest, int vertices, Driver &driver){
            int distance[13];
            int vertices_in_path[13];
            bool visited[13];

            for (int i = 1; i < vertices; i++){
                distance[i] = INT_MAX;
                vertices_in_path[i] = -1;  // Initialize vertices_in_paths to -1
                visited[i] = false;
            }
            distance[src] = 0;

            // Find shortest path for all vertices
            for(int count = 1; count < vertices; count++){
                // Find the minimum distance vertex from the set of vertices not yet processed
                int minDistance = INT_MAX, minIndex;

                for(int v = 1; v < vertices; v++){
                    if (!visited[v] && distance[v] <= minDistance){
                        minDistance = distance[v];
                        minIndex = v;
                    }
                }
                visited[minIndex] = true;

                // Update distance value of the adjacent vertices of the picked vertex
                for(int v = 1; v < vertices; v++){
                    if (!visited[v] && graph[minIndex][v] && distance[minIndex] != INT_MAX && distance[minIndex] + graph[minIndex][v] < distance[v]) {
                        distance[v] = distance[minIndex] + graph[minIndex][v];
                        vertices_in_path[v] = minIndex;
                    }
                }
            }

            // Print the shortest distance from src to dest
            cout << "Shortest distance from " << src << " to " << dest << " is: " << distance[dest] << endl;

            // Print the path
            // cout << "Path: ";
            // vector<int> path;
            int currentVertex = dest;

            driver.routeIndexes.push_back(dest);
            driver.routeTime.push_back(distance[dest]);
            driver.routeLocations.push_back(Locations_Name[dest]);
            
            //to store parent vertices in path from src to dest
            // while(currentVertex != -1){
            //     path.push_back(currentVertex);
            //     currentVertex = vertices_in_path[currentVertex];
            // }
            // for (int i = path.size() - 1; i >= 0; i--) {
            //     cout << path[i] << " ";
            // }
            // cout << endl;
        }



};