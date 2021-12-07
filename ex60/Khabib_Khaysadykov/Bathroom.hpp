#include <iostream> 
#include <thread>   
#include <chrono>   
 
// To start programm
// g++ -I ./ WantTo.cpp Bathroom.cpp -std=c++11 
// ./a.out 



//enum is used to differentiate easily
enum Gender {Man,Woman}; 
enum BathroomState {Empty,WomanPresent,ManPresent}; 
//Bathroom at any time can have one of the 3 states
 
class Bathroom
{
private:
    BathroomState current; 
    long int time_to_stay; 
    long int num_of_people; 
   
public:
    void __init__(); 
    long int getPeople(); 
    
    BathroomState iSPresent(); 
    void allotBathroom(Gender g,long int _time_to_stay);
   
    void CheckandEmptyBathroom();
    void decreaseTime(long int dec); 
};