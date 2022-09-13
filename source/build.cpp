#include <iostream>
#include <string>
#include <vector>
#include "Int.h";
#include "String.h";
#include "Float.h";
#include "Math.h";
#include "Time.h";
void print() {
	std::cout << std::endl;
}
template<typename First, typename ... Strings>
void print(First arg, const Strings&... rest) {
	std::cout << arg;
	print(rest...);
 }
int rand(int min, int max);
int run() {
Int test;test.value = 10;  ;  
 print ( test.value )  ;  ;  
 return 0;}int rand(int min, int max) {return rand() % (max + min);}