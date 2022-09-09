#include <iostream>
#include <string>
#include <vector>
using namespace std;
int rand(int min, int max);int run() {
	 
 for (int i=0;i<10;i++) {
   cout <<i<<"<<"<<"poop"<< endl ;  
 } 
  
 if (1==10){ 
  	 cout <<"hello!"<< endl ;  
 } else cout <<"goodbye!"<< endl ;  ;  
 return 0;
}int rand(int min, int max) {
	return rand() % (max + min);
}