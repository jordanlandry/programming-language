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
	string myMessage = "JanninScript is dope!";print(myMessage);;vector<double> test;;test.push_back(10);test.push_back(11);test.push_back(12);test.push_back(13);print(test);return 0;}
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
void print(vector<double> s) {
	cout << "[";
	for (int i = 0; i < s.size(); i++) {
		 cout << s[i];
		if (i < s.size() -1) cout << ", ";
	}
	cout << "]";
}
