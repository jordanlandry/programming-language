#include <iostream>
#include <string>
#include <vector>
using namespace std;void print() {cout << endl;}template<typename First, typename ... Strings>void print(First arg, const Strings&... rest) { cout << arg;print(rest...); }int rand(int min, int max);void printString ( string s )  {
  	 print ( s )  ;  
 } void printInt ( int number )  {
  	 print ( number )  ;  
 } int run() {class Time {public:void start(){cout << "TEST";}};
  
 
  
 for (int i=0;i<10;i++) {
  	 print ( i )  ;  
 } 
  
 for (int i=0;i<10;i++) {
  	 print ( "Hello!" )  ;  
 } 
  
 for (int i=0;i<10;i++) {
  	 int num = rand ( 0 ,  10 )  ;  ;  
  	 print ( "Random number: " ,  num )  ;  
 } 
  
  
 int i = 10 ;  
 print ( i )  ;  
  
  
 int j = [1 ,  2 ,  3] ;  
 print ( i )  ;  
 return 0;}int rand(int min, int max) {return rand() % (max + min);}