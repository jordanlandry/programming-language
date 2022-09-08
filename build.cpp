#include <iostream>
#include <string>
using namespace std;
void print(string s);
void print(char s);
void print(int s);
void print(bool s);
void print(float s);
void print(double s);
void print(long s);
int run() {
	string a = "Hello World in JanninScript";print(a);bool b = true;;print(b);char c = 'a';print(c);return 0;}
void print(string s) {
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
