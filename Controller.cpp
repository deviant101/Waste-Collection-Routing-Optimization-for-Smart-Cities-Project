#include <iostream>
#include <string>
#include <ctime>
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
        :Name(name), ID(id), Password(password),drivers(driverPtr), Graphs(graphs), threshold(Thres){
            for(int i=1; i<=5; ++i){
                drivers[i].BinLevels=Graphs[i].binLevels;
            }
        }

    void Login(){
        cout<<"--------------[CONTROLLER LOGIN]--------------\n\n";
        while(1){
            string id="";
            cout<<"Enter ID : ";
            getline(cin,id);
            // id="CRL-1094";
            if(id==ID){
                while(1){
                    string pass="";
                    cout<<"Enter Password : ";
                    getline(cin,pass);
                    // pass="cont_41siml";
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
        for(int i=1; i<=5; ++i)
            Graphs[i].binsData();
        while(1){
            cout<<"\n--------------[CONTROLLER MENU]--------------\n\n";
            cout<<"1 - Bin Fill Data"<<endl
                <<"2 - Set Collection Threshold"<<endl
                <<"3 - Set Colletible Bins"<<endl
                <<"4 - Allot Route to Truck Driver"<<endl
                <<"5 - Check bin fill Notifications"<<endl
                <<"6 - Live Tracking of Trucks"<<endl
                <<"7 - Exit"<<endl;
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
            else if(choice==4){
                makeRouteForDriver();
            }
            else if(choice==5){
                checkNotifications();
            }
            else if(choice==6){
                LiveTracking();
            }
            else if(choice==7)
                break;
        }
    }

    void view_bin_fill_level(){
        cout<<"\n--------------[BIN FILL LEVELS]--------------\n\n";
        int areaNo;
        while(1){
            areaNo=0;
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
        cout<<"\n---------------[FILL LEVELS]---------------\n\n";
            for(int i=2; i<=11; ++i)
                cout<<Graphs[areaNo].Locations_Name[i]<<"  =  "<<Graphs[areaNo].binLevels[i]<<" %"<<endl;
    }

    void LiveTracking(){
        cout<<"\n--------------[Live Tracking]--------------\n\n";
        int areaNo;
        while(1){
            areaNo=0;
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
        if(drivers[areaNo].collectedBins.empty()){
            cout<<"\nDriver did not started collecting bins\n"<<endl;
            return;
        }
        drivers[areaNo].ViewLive();
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

        Graphs[areaNo].collectibleBins.clear();
        drivers[areaNo].collectedBins.clear();
        drivers[areaNo].collectionTimes.clear();
        for(int i=2; i<=11; ++i){
            if(Graphs[areaNo].binLevels[i]>=threshold){
                Graphs[areaNo].collectibleBins.push_back(i);
                for (int i = Graphs[areaNo].collectibleBins.size() / 2 - 1; i >= 0; i--)
                    heapify(Graphs[areaNo].collectibleBins, Graphs[areaNo].binLevels, Graphs[areaNo].collectibleBins.size(), 0);
                // cout<<Graphs[areaNo].Locations_Name[i]<<" = "<<Graphs[areaNo].binLevels[i]<<endl;
            }
        }
        if(Graphs[areaNo].collectibleBins.size()>0){
            drivers[areaNo].collection_status = true;
            cout<<"\nBins Collection Notification sent to Area "<<areaNo<<" Truck Driver Successfully\n"<<endl;
        }
        
        for(int i=0; i<Graphs[areaNo].collectibleBins.size(); ++i)
            cout<<Graphs[areaNo].Locations_Name[Graphs[areaNo].collectibleBins[i]]<<" = "<<Graphs[areaNo].binLevels[Graphs[areaNo].collectibleBins[i]]<<endl;

    }

    void heapify(vector<int>& binsArr, int *binLevels, int size, int i){
        int largest = i;
        int l = 2*i+1, r = 2*i+2;

        if (l < size && binLevels[binsArr[l]] > binLevels[binsArr[largest]])
            largest = l;
        if (r < size && binLevels[binsArr[r]] > binLevels[binsArr[largest]])
            largest = r;

        if (largest != i){
            swap(binsArr[i], binsArr[largest]);
            heapify(binsArr, binLevels, size, largest);
        }
    }

    void makeRouteForDriver(){
        int areaNo;
        while(1){
            cout<<"\n--------------[Alloting Route]--------------\n\n";
            cout<<"Enter Area to set Collectible Bins (1-5) : ";
            cin>>areaNo;
            if(areaNo>=1 && areaNo<=5){
                break;
            }
            else{
                cout<<"Invalid Area! Try again."<<"\n\n";
            }
        }
        if(Graphs[areaNo].collectibleBins.size()>0){
            for(int i=0; i<Graphs[areaNo].collectibleBins.size(); ++i){
                cout<<Graphs[areaNo].collectibleBins[i]<<" ";
            }
            cout<<endl;


            Graphs[areaNo].findShortestPath(1,Graphs[areaNo].collectibleBins[0], drivers[areaNo]);
            for(int i=0; i<Graphs[areaNo].collectibleBins.size()-1; ++i){
                int src, dest;
                    src = Graphs[areaNo].collectibleBins[i];
                    dest = Graphs[areaNo].collectibleBins[i+1];
                    Graphs[areaNo].findShortestPath(src, dest, drivers[areaNo]);
            }
            Graphs[areaNo].findShortestPath(Graphs[areaNo].collectibleBins[Graphs[areaNo].collectibleBins.size()-1], 12, drivers[areaNo]);
        }
        else{
            cout<<"\nThere are no Collectible bins available\n"<<endl;
        }
    }

    void checkNotifications(){
        cout<<"\n--------------[Bin Fill Notifications]--------------\n";
        for(int i=1; i<=5; ++i){
            cout<<"Area - "<<i<<endl;
            for(int j=2; j<=11; ++j){
                if(Graphs[i].binLevels[j] > threshold)
                    cout<<Graphs[i].Locations_Name[j]<<endl;
            }
            cout<<"\n";
        }
        cout<<"\n------------------------------------------------------\n";
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
            getline(cin,id);
            // id=="22i-1669";
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
            getline(cin,pass);
            // pass="tyk465";
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
                <<"3 - Start Collecting"<<endl
                <<"4 - Live Tracking"<<endl
                <<"5 - Exit"<<endl;
            int choice;
            cout<<"\nChoice : ";
            cin>>choice;
            if(drivers[driverIndex].routeLocations.empty()){
                drivers[driverIndex].collection_status=false;
            }
            if(choice==1){
                drivers[driverIndex].checkCollectionStatus();
            }
            else if(choice==2){
                drivers[driverIndex].viewCollectionRoute();
            }
            else if(choice==3){
                drivers[driverIndex].startCollecting();
            }
            else if(choice==4){
                drivers[driverIndex].ViewLive();
            }
            else if(choice==5)
                break;
            else
                break;
        }
        
    }

};