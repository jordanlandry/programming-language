#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string readfile(string path);
int convertfile(string text);
void addSemicolons(string text);

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: janninscript file" << endl;
		return 1;
	}

	cout << "Reading file " << argv[1] << "..." << endl;

	string text = readfile(argv[1]);
	if (text == "") {
		cout << "Something went wrong reading file: " << argv[1] << " please try again" << endl;
		return 1;
	}

	convertfile(text);
	return 0;
}

string readfile(string path) {
	string result = "";
	string line;
	ifstream file(path);
	if (!file.is_open()) return "";

	while (getline(file, line)) {
		result.append(line);
		result.append("\n");
	}
	file.close();
	return result;
}

void addSemicolons(string text) {
	ofstream build("build.janninscript");
	char prevC = '\n';
	if (build.is_open()) {
		for (char& c : text) {
			if (c == '\n' && prevC != '\n') {
				build << ";";
			}
			else if (c != '\n') {
				build << c;
			}
			prevC = c;
		}
	}
	build.close();
}


void appendToBuild(string text) {
	ofstream outfile;
	outfile.open("build.cpp", ios_base::app);
	outfile << text;
}

void appendToBuild(char text) {
	ofstream outfile;
	outfile.open("build.cpp", ios_base::app);
	outfile << text;
}

void createBaseFile() {
	ofstream build("build.cpp");
	build << "#include <iostream>\nint main(int argc, char* argv[]) {";
}

int convertfile(string text) {
	createBaseFile();

	char ch;
	fstream fin("test.janninscript", fstream::in);

	string currentWord = "";
	string prevWord = "";

	while (fin >> noskipws >> ch) {
		if (ch == ' ' || ch == '\n' || ch == '(' || ch == ';' || ch == ')' || ch == '{' || ch == '}') {
			appendToBuild(ch);
			if (ch == '\n') {
				if (prevWord != "{" && prevWord != ";" && prevWord != "\n") {
					appendToBuild(';');
				}
			}
			if (currentWord == "number") {
				appendToBuild("double");
			}
			else {
				appendToBuild(currentWord);
			}

			prevWord = currentWord;
			currentWord = "";
		}
		else {
			currentWord += ch;
		}
	}

	appendToBuild('}');
	return 1;
}
