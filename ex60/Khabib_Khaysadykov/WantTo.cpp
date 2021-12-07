#include "Bathroom.hpp"


// To start programm
// g++ -I ./ WantTo.cpp Bathroom.cpp -std=c++11 
// ./a.out 


using namespace std;
#define MaxStrength 5 //Maximum no of people who can enter a bathroom
 
enum WantTo {ManWantToEnter,WomanWantToEnter,NoOneWantToEnter};
//enum to define if a man,woman,or no one wants to enter a bathroom
 
int getTime(){
    return rand()%100;
}
 
WantTo enter(){
    int read = getTime();
    WantTo ret;
    if(read < 50) ret = NoOneWantToEnter;
    else if(read < 75) ret = WomanWantToEnter;
    else ret = ManWantToEnter;
    return ret;
}
 
int main(){
    srand(time(NULL));
    Bathroom b;
    b.__init__();
    while(1){
        WantTo w = enter();
        b.CheckandEmptyBathroom();
        
        b.decreaseTime(getTime());
 
        if(b.getPeople() == MaxStrength){
            cout<<"\nBathroom Full\n\n";
            continue;
        }
        if(w == NoOneWantToEnter){
            cout<<"No One Wants To Enter\t";
            if(b.iSPresent() == ManPresent)
                cout<<"Man Present:"<<b.getPeople()<<"\n";            
            else if(b.iSPresent() == WomanPresent) cout<<"Woman Present:"<<b.getPeople()<<"\n";
            else cout<<"Bathroom's Empty!!\n";
            continue;
        }
        
        else if(w == ManWantToEnter){
            cout<<"Man Wants To Enter\t";
            if(b.iSPresent() == WomanPresent)
                cout<<"A Woman is Present Man Cannot Enter!!\n";
            else{
                b.allotBathroom(Man,getTime());
                cout<<"Man Present:"<<b.getPeople()<<"\n";
            }
        }
        
        else if(w == WomanWantToEnter){
            cout<<"Woman Wants To Enter\t";
            if(b.iSPresent() == ManPresent)
                cout<<"A Man is Present Woman Cannot Enter!!\n";
            else{
                b.allotBathroom(Woman,getTime());
                cout<<"Woman Present:"<<b.getPeople()<<"\n";
            }           
        }
    }
    return 0;
}