#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "build.cpp";
//using namespace std;

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
	build << "#include <vector>\n";
	build << "using namespace std;\n";

	// Create print overloads
	build << "void print(string s);";
	build << "void print(char s);";
	build << "void print(int s);";
	build << "void print(bool s);";
	build << "void print(float s);";
	build << "void print(double s);";
	build << "void print(long s);";

	build << "void print(vector<double> s);\n";

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

	string body = "";
	string run = "";
	
	char c;
	string currentWord = "";
	string prevWord;
	
	vector<string> words;
	fstream i("build.janninscript", fstream::in);
	while (i >> noskipws >> c) {
		if (c == '\n' || c == ' ' || c == ';') {
			//cout << currentWord << endl;
			words.push_back(currentWord);
			currentWord = "";
		}
		currentWord += c;
	}


	/*for (int i = 0; i < words.size(); i++) {
		cout << words[i] << i;
	}*/
	// Go through each word
	for (int i = 0; i < words.size(); i++) {
		// Check prevwords
		if (i > 0) {
			// For loops
			if (replaceAll(words[i - 1], " ", "") == "for") {
				run += "(int " + words[i] + "=" + words[i + 1] + ";" + words[i] + "<";
				if (words[i + 2] == "to" || words[i + 2] == " to" || words[i + 2] == "to " || words[i + 1] == " to ") {
					run += words[i + 3];
				}
				run += ";" + words[i] + "++) {";
				i += 5;		// Skip to the curly bracket
			}
		}
		run += words[i] + ' ';
	}
	appendToBuild(run);
	appendToBuild("return 0;\n}");
	appendToBuild("void print(int s) {cout << s << endl;}");

	return 0;

	// Add to the build file letter by letter
	char ch;
	string build = "";
	fstream fin("build.janninscript", fstream::in);
	while (fin >> noskipws >> ch) {
		//if (ch == '\n') continue;
		build += ch;
	}

	// Replace script keywords with c++ keywords
	build = replaceAll(build, "number", "double");
	build = replaceAll(build, "str", "string");
	build = replaceAll(build, "boolean", "bool");

	// Turn arrays into vectors
	build = replaceAll(build, "number[]", "vector<number>");
	build = replaceAll(build, "string=[]", "vector<string>");
	build = replaceAll(build, "str[]", "vector<string>");
	build = replaceAll(build, "char[]", "vector<char>");
	build = replaceAll(build, "int[]", "vector<int>");
	build = replaceAll(build, "long[]", "vector<long>");
	build = replaceAll(build, "float[]", "vector<float>");
	build = replaceAll(build, "double[]", "vector<double>");
	build = replaceAll(build, "bool[]", "vector<bool>");
	build = replaceAll(build, "boolean[]", "vector<bool>");
	build = replaceAll(build, ".push(", ".push_back(");

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

		// Vector overloads
		appendToBuild("void print(vector<double> s) {\n\tcout << \"[\";\n\tfor (int i = 0; i < s.size(); i++) {\n\t\t cout << s[i];\n\t\tif (i < s.size() -1) cout << \", \";\n\t}\n\tcout << \"]\";\n}\n");
	}

	return 0;
}