#include "Bathroom.hpp"
 
// To start programm
// g++ -I ./ WantTo.cpp Bathroom.cpp -std=c++11 
// ./a.out 


void Bathroom::__init__(){
    current = Empty; 
    time_to_stay = 0; 
    num_of_people = 0; 
}
long int Bathroom::getPeople(){
    return num_of_people; 
}
BathroomState Bathroom::iSPresent(){
    return current;
}
void Bathroom::allotBathroom(Gender g,long int _time_to_stay){
    if(g == Man) current = ManPresent;
    else if(g == Woman) current = WomanPresent;
    time_to_stay = _time_to_stay; 
    num_of_people = num_of_people + 1; 
}
void Bathroom::CheckandEmptyBathroom(){
   
    if(time_to_stay <= 0 && num_of_people <= 1){
        current = Empty;
        time_to_stay = 0;
        num_of_people = 0;
    }
    else if(time_to_stay <= 0){
        num_of_people = num_of_people - 1;
        time_to_stay = 0;
    }
}
void Bathroom::decreaseTime(long int dec){
    time_to_stay -= dec;
}