#include <iostream>
#include <string>
#include <vector>
#include "../headers/Int.h";
#include "../headers/String.h";
#include "../headers/Float.h";
#include "../headers/Boolean.h";
#include "../headers/Math.h";
#include "../headers/Time.h";
void print() {
	std::cout << std::endl;
}
template<typename First, typename ... Strings>
void print(First arg, const Strings&... rest) {
	std::cout << arg;
	print(rest...);
 }
int rand(int min, int max);
Math math;
Time timer;
int run() {
Float test;test.value = sqrt( 81 )  ;  
 print ( test . value )  ;  
  
 timer. start (  )  ;  ;  
 return 0;}int rand(int min, int max) {return rand() % (max + min);}