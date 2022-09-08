#include <iostream>
#include <string>
#include <vector>
using namespace std;
void print(char* s);void print(char s);void print(int s);void print(bool s);void print(float s);void print(double s);void print(long s);void print(vector<double> s);
int run() {
	for (int  i= 0; i< 5; i++) {
   if ( i == 2) { 
        print("Yay") ; 
    } 
} return 0;
}
void print(char* s) {
	cout << s << endl;
}
void print(bool s) {
	if (s) cout << "true" << endl;
	else cout << "false" << endl;
}
void print(int s) {
	cout << s << endl;
}
void print(float s) {
	cout << s << endl;
}
void print(double s) {
	cout << s << endl;
}
void print(long s) {
	cout << s << endl;
}
void print(char s) {
	cout << s << endl;
}
