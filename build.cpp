#include <iostream>
#include <string>
#include <vector>
using namespace std;
int rand(int min, int max);int run() {
	class Time {
public:
void start(){
cout << "TEST";
}
}; Time time; 
 for (int i=0;i<100;i++) {
  	 int test = rand ( 0 ,  10 )  ;  
  	 cout <<test<< endl ;  
 } 
  
 time.start (  )  ;  ;  
 return 0;
}int rand(int min, int max) {
	return rand() % (max + min);
}