#include <iostream>
#include <string>
#include <vector>
using namespace std;
int rand(int min, int max);int run() {
	 
 for (int i=0;i<10;i++) {
   cout <<i<< endl ;  
 } 
 return 0;
}int rand(int min, int max) {
	return rand() % (max + min);
}