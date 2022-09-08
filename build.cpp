#include <iostream>
#include <string>
#include <vector>
using namespace std;
void print(string s);
void print(char s);
void print(int s);
void print(bool s);
void print(float s);
void print(double s);
void print(long s);
void print(vector<double> s);
int run() {
	for (int  i= 0; i< 10; i++) {
	
    print(i) ; 
} return 0;
}void print(int s) {
	cout << s << endl;
}
