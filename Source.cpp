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

class Keywords {
public:
	string print = "print";
	string forLoop = "for";
	string ifStatement = "if";
	string elseStatement = "else";
	string switchStatement = "switch";
	string classStatement = "class";
	string whileLoop = "while";
	string noNewLine = "noNewLine";
	string functionDecloration = "func";
};
const Keywords keywords;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: J file" << endl;
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
	ofstream build("build.j");
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

string createBaseFile() {
	ofstream build("build.cpp");
	string extraClasses = "";

	build << "#include <iostream>\n";
	build << "#include <string>\n";
	build << "#include <vector>\n";
	build << "using namespace std;";

	// Print Function
	build << "void print() {cout << endl;}template<typename First, typename ... Strings>";
	build << "void print(First arg, const Strings&... rest) { cout << arg;print(rest...); }";

	// Random Function
	build << "int rand(int min, int max);";


	// Time class
	extraClasses += "class Time {public:void start(){cout << \"TEST\";}};";
	

	// Base function 
	return "int run() {" + extraClasses;

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
	addSemicolons(text);

	string body = "";
	string run = createBaseFile();

	char c;
	string currentWord = "";
	string prevWord;

	vector<string> words;
	fstream i("build.j", fstream::in);

	// Split each word by certain characters
	while (i >> noskipws >> c) {
		if (c == '\n' || c == ' ' || c == ';' || c == '(' || c == ')' || c == ',' || c == '\t') {
			words.push_back(currentWord);
			currentWord = "";

			if (c != ' ') {
				currentWord += c;
				words.push_back(currentWord);
				currentWord = "";
			}
		}
		else currentWord += c;
	}

	int currentBracketCount = 0;


	// Go through each word
	for (int i = 0; i < words.size(); i++) {
		if (currentBracketCount > 1) {

		}

		// For loops
		if (replaceAll(words[i], " ", "") == keywords.forLoop) {
			run += "for (int " + words[i + 1] + "=" + words[i + 2] + ";" + words[i + 1] + "<";
			if (replaceAll(words[i + 3], " ", "") == "to") {
				run += words[i + 4];
			}

			run += ";" + words[i + 1] + "++) {";
			i += 6;		// Skip to the curly bracket
		}

		// If statements
		if (replaceAll(words[i], " ", "") == keywords.ifStatement) {
			run += "if (";
			int j = 1;
			while (replaceAll(words[i + j], " ", "") != "{") {
				run += words[i + j];
				j++;
			}
			run += ")";
			i += j;
		}


		// Functions
		if (replaceAll(words[i], " ", "") == keywords.functionDecloration) {
			int bracketCount = 1;

			body += "void ";
			int j = 1;
			while (words[i + j] != "{") {
				body += words[i + j] + ' ';
				j++;
			}
			body += "{";
			j += 1;
			while (bracketCount > 0 && (i + j) < words.size()) {
				if (words[i + j] == "}") bracketCount--;
				else if (words[i + j] == "{") bracketCount++;
				body += words[i + j] + ' ';
				j++;
			}

			i += j;
		}

		// While Loops
		if (replaceAll(words[i], " ", "") == keywords.whileLoop) {
			run += "(";
			int j = 1;
			while (replaceAll(words[i + j], " ", "") != "{") {
				run += words[i + j];
				j++;
			}
			run += ") {";
			i += j;
		}

		run += words[i] + ' ';
	}
	appendToBuild(body);
	appendToBuild(run);
	appendToBuild("return 0;}");

	// Import random function
	if (run.find("rand(") || body.find("rand(")) {
		appendToBuild("int rand(int min, int max) {return rand() % (max + min);}");
	}

	return 0;
}