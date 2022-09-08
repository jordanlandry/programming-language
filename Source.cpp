#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "build.cpp";

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

	int status = convertfile(text);
	if (status != 0) return status;

	run();
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
			if (c == '\n' && prevC != '\n' && prevC != '{' && prevC != '}') {
				build << ";";
			}
			build << c;
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
	build << "#include <iostream>\n";
	build << "#include <string>\n";
	build << "using namespace std;\n";

	// Create print overloads
	build << "void print(string s);\n";
	build << "void print(char s);\n";
	build << "void print(int s);\n";
	build << "void print(bool s);\n";
	build << "void print(float s);\n";
	build << "void print(double s);\n";
	build << "void print(long s);\n";

	build << "int run() {\n\t";
}


string replaceAll(string str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

int convertfile(string text) {
	createBaseFile();
	addSemicolons(text);

	char ch;
	fstream fin("build.janninscript", fstream::in);

	string currentWord = "";
	string prevWord = "";

	string build = "";
	string finalBuild = "";
	while (fin >> noskipws >> ch) {
		if (ch == '\n') continue;
		build += ch;
	}

	// Replace script keywords with c++ keywords
	build = replaceAll(build, "number", "double");
	build = replaceAll(build, "str", "string");
	build = replaceAll(build, "boolean", "bool");
	appendToBuild(build);
	appendToBuild("return 0;");

	// End main function
	appendToBuild('}');

	// Check if you should add the print function
	if (build.find("print(") != string::npos) {
		// Add print overload functions
		appendToBuild("\nvoid print(string s) {\n\tcout << s << endl;\n}\n");
		appendToBuild("void print(bool s) {\n\tif (s) cout << \"true\" << endl;\n\telse cout << \"false\" << endl;\n}\n");
		appendToBuild("void print(int s) {\n\tcout << s << endl;\n}\n");
		appendToBuild("void print(float s) {\n\tcout << s << endl;\n}\n");
		appendToBuild("void print(double s) {\n\tcout << s << endl;\n}\n");
		appendToBuild("void print(long s) {\n\tcout << s << endl;\n}\n");
		appendToBuild("void print(char s) {\n\tcout << s << endl;\n}\n");
	}

	return 0;
}