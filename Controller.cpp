#include <iostream>
#include <string>
#include "Truck-Driver.cpp"
#include "Graph.cpp"
using namespace std;

class Controller{
    public:
        string Name;
        string ID;
        string Password;
        Driver *drivers;
        Graph *Graphs;
        int threshold;
    
    Controller(Driver *driverPtr, Graph *graphs, int Thres=75, string name="Dennis", string id="CRL-1094", string password="cont_41siml")
        :Name(name), ID(id), Password(password),drivers(driverPtr), Graphs(graphs) {}

    void Login(){
        cout<<"--------------[CONTROLLER LOGIN]--------------\n\n";
        while(1){
            string id="";
            cout<<"Enter ID : ";
            // getline(cin,id);
            id="CRL-1094";
            if(id==ID){
                while(1){
                    string pass="";
                    cout<<"Enter Password : ";
                    // getline(cin,pass);
                    pass="cont_41siml";
                    if(pass==Password){
                        cout<<"\nSuccessfully Logged in as Controller\n";
                        Menu();
                        break;
                    }
                    else{
                        cout<<"\nInvalid Password! Try again."<<"\n\n";
                    }
                }
                break;
            }
            else
                cout<<"\nInvalid ID! Try again."<<"\n\n";
        }
    }

    void Menu(){
        while(1){
            cout<<"\n--------------[CONTROLLER MENU]--------------\n\n";
            cout<<"1 - Bin Fill Data"<<endl
                <<"2 - Set Collection Threshold"<<endl
                <<"3 - Set Colletible Bins"<<endl
                <<"4 - Exit"<<endl;
            int choice;
            cout<<"\nChoice: ";
            cin>>choice;
            cin.ignore();

            if(choice==1){
                view_bin_fill_level();
            }
            else if(choice==2){
                setColletionThreshold();
            }
            else if(choice==3){
                setColletibleBins();
            }
            else if(choice==4)
                break;
        }
    }

    void view_bin_fill_level(){
        cout<<"\n--------------[BIN FILL LEVELS]--------------\n\n";
        while(1){
            int areaNo=0;
            cout<<"Enter Area (1-5) : ";
            cin>>areaNo;
            if(areaNo>=1 && areaNo<=5){
                Graphs[areaNo].binsData();
                break;
            }
            else{
                cout<<"Invalid Area! Try again."<<"\n\n";
            }
        }
    }

    void setColletionThreshold(){

        while(1){
            cout<<"\n--------------[Set Threshold]--------------\n\n";
            cout<<"Enter New Threshold for Bins : ";
            cin>>threshold;
            if(threshold<0 || threshold>100)
                cout<<"\nInvalid Threshold! Try again."<<"\n\n";
            else{
                cout<<"\nThreshold for all Areas Bins Changed Successfully"<<endl;
                break;
            }
        }
    }

    void setColletibleBins(){
        int areaNo;
        while(1){
            cout<<"\n--------------[Set Collectible Bins]--------------\n\n";
            cout<<"Enter Area to set Collectible Bins (1-5) : ";
            cin>>areaNo;
            if(areaNo>=1 && areaNo<=5){
                break;
            }
            else{
                cout<<"Invalid Area! Try again."<<"\n\n";
            }
        }
        drivers[areaNo].collection_status = true;
        cout<<"\nBins Collection Notification sent to Area "<<areaNo<<" Truck Driver Successfully\n"<<endl;
        // cout<<"Start: "<<Graphs[areaNo].Locations_Name[1]<<"\tDump: "<<Graphs[areaNo].Locations_Name[12]<<endl;
        for(int i=1; i<=10; ++i){
            // cout<<Graphs[areaNo].binLevels[i]<<" - ";
            if(Graphs[areaNo].binLevels[i]>=threshold)
                cout<<Graphs[areaNo].Locations_Name[i+1]<<endl;
            // cout<<endl;
        }
/*
        Graphs[areaNo].collectibleBins.clear();
        for(int i=2; i<=11; ++i)
            if(Graphs[areaNo].binLevels[i]>=threshold){
                Graphs[areaNo].collectibleBins.push_back(i);
            }
        
        //will use heap after allocating bin and put that vector of bins in driver's collection vector
        //will implement heap on the basis of filled percentage or one's that are near trunk departure point
        for(int i=1; i<Graphs[areaNo].collectibleBins.size(); ++i)
            cout<<Graphs[areaNo].Locations_Name[i]<<endl;
*/
    }

    void Profile(){
        cout<<"\n--------------[Controller Profile]--------------\n";
        cout<<"NAME: "<<Name<<endl
            <<"ID: "<<ID<<endl
            <<"Password: "<<Password<<endl;
        cout<<"------------------------------------------------\n";
    }

    //----------------------------------------------------------------//
    void driverLogin(){
        cout<<"--------------[CONTROLLER LOGIN]--------------\n\n";
        int driverIndex = -1;
        while(1){

            string id="";
            cout<<"Enter Driver ID : ";
            // getline(cin,id);
            id=="22i-1669";
            for(int i=0;i<5; ++i){
                if(id==drivers[i].ID){
                    driverIndex = i;
                    break;
                }
            }
            if(driverIndex == -1)
                cout<<"\nInvalid ID! Try again."<<"\n\n";
            else
                break;
        }
        while(1){
            string pass="";
            cout<<"Enter Password : ";
            // getline(cin,pass);
            pass="tyk465";
            if(pass!=drivers[driverIndex].Password)
                cout<<"\nInvalid Password! Try again."<<"\n\n";
            else{
                cout<<"\nSuccessfully Logged in as "<<drivers[driverIndex].Name<<endl;
                break;
            }
        }
        driverMenu(driverIndex);
    }

    void driverMenu(int driverIndex){
        while (1){
            cout<<"\n--------------[Driver MENU]--------------\n\n";
            cout<<"1 - Check Duty Status"<<endl
                <<"2 - Check Route"<<endl
                <<"3 - Exit"<<endl;
            int choice;
            cout<<"\nChoice : ";
            cin>>choice;
            if(choice==1){
                drivers[driverIndex].checkCollectionStatus();
            }
            else if(choice==2){
                drivers[driverIndex].viewCollectionRoute();
            }
            else if(choice==3)
                break;
            else
                break;
        }
        
    }

};