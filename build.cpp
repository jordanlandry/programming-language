#include <iostream>
#include <string>
#include <vector>
using namespace std;void print() {cout << endl;}template<typename First, typename ... Strings>void print(First arg, const Strings&... rest) { cout << arg;print(rest...); }int rand(int min, int max);void test ( string message )  {
  	 print ( message )  ;  
  	 print ( message )  ;  
  	 print ( message )  ;  
  	 print ( message )  ;  
 } int run() {class Time {public:void start(){cout << "TEST";}};
  
 test ( "Hello!" )  ;  ;  
  
 print ( "Hello!!!!!!!" ,  " Testing two inputs!" ,  10 ,  false )  ;  
 return 0;}int rand(int min, int max) {return rand() % (max + min);}