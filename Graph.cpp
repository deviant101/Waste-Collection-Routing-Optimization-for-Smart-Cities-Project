#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Graph{
    public:
        const int NO_OF_VERTICES;
        int **Vertices_Graph;
        string Locations_Name[13];

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



};