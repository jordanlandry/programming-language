#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "source/build.cpp";

std::string readfile(std::string path);
int convertfile(std::string text);
void addSemicolons(std::string text);

class variableNames {
public:
	std::string currentVariableName = "a";
	std::string next(std::string curr) {
		return "a";
	}
};

class Keywords {
public:
	// Built in functions
	std::string print = "print";
	std::string random = "rand";

	// Types
	std::string stringType = "string";
	std::string intType = "int";
	std::string floatType = "float";
	std::string doubleType = "double";
	std::string boolType = "boolean";
	
	// Statements
	std::string forLoop = "for";
	std::string ifStatement = "if";
	std::string elseStatement = "else";
	std::string switchStatement = "switch";
	std::string classStatement = "class";
	std::string functionDecloration = "func";
	std::string whileLoop = "while";

	// Key Operators
	std::string startArray = "[";
	std::string endArray = "]";

	// Classes
	std::string timeClass = "time";
	std::string mathClass = "math";

	// Keywords
	std::string noNewLine = "noNewLine";
	std::string importFile = "import";

	// Methods
	std::string appendToArray = "push";
	std::string sizeOfArray = "length";

	// File properties
	std::string fileExtension = "j";
	std::string buildName = "build";
	std::string cppBuildName = "source/build.cpp";
};
const Keywords keywords;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: J file" << std::endl;
		return 1;
	}

	std::cout << "Reading file " << argv[1] << "..." << std::endl;

	std::string text = readfile(argv[1]);
	if (text == "") {
		std::cout << "Something went wrong reading file: " << argv[1] << " please try again" << std::endl;
		return 1;
	}

	int status = convertfile(text);
	if (status != 0) return status;

	run();
	return 0;
}

std::string readfile(std::string path) {
	std::string result = "";
	std::string line;
	std::ifstream file(path);
	if (!file.is_open()) return "";

	while (getline(file, line)) {
		result.append(line);
		result.append("\n");
	}
	file.close();
	return result;
}

void addSemicolons(std::string text) {
	std::ofstream build(keywords.buildName + "." + keywords.fileExtension);
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

void appendToBuild(std::string text) {
	std::ofstream outfile;
	outfile.open(keywords.cppBuildName, std::ios_base::app);
	outfile << text;
}

void appendToBuild(char text) {
	std::ofstream outfile;
	outfile.open(keywords.cppBuildName, std::ios_base::app);
	outfile << text;
}

std::string createBaseFile() {
	std::ofstream build(keywords.cppBuildName);
	std::string extraClasses = "";

	build << "#include <iostream>\n";
	build << "#include <string>\n";
	build << "#include <vector>\n";

	// Include Types
	build << "#include \"../headers/Int.h\";\n";
	build << "#include \"../headers/String.h\";\n";
	build << "#include \"../headers/Float.h\";\n";
	build << "#include \"../headers/Boolean.h\";\n";

	// Including other header files
	build << "#include \"../headers/Math.h\";\n";
	build << "#include \"../headers/Time.h\";\n";

	// Print Function
	build << "void print() {\n\tstd::cout << std::endl;\n}\ntemplate<typename First, typename ... Strings>\n";
	build << "void print(First arg, const Strings&... rest) {\n\tstd::cout << arg;\n\tprint(rest...);\n }\n";

	// Random Function
	build << "int rand(int min, int max);\n";

	// Using classes
	build << "Math math;\n";
	build << "Time timer;\n";

	// Base function 
	return "int run() {\n" + extraClasses;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

std::string getVariableType(std::string type) {
	if (type == keywords.stringType) return "String";
	if (type == keywords.intType) return "Int";
	if (type == keywords.boolType) return "Bool";
	if (type == keywords.floatType) return "Float";
	if (type == keywords.doubleType) return "Double";
	return "";
}

int convertfile(std::string text) {
	addSemicolons(text);

	std::string body = "";
	std::string run = createBaseFile();

	char c;
	std::string currentWord = "";
	std::string prevWord;

	std::vector<std::string> words;
	std::fstream i(keywords.buildName + "." + keywords.fileExtension, std::fstream::in);

	bool inQuotes = false;

	// Split each word by certain characters
	while (i >> std::noskipws >> c) {
		if (c == '\n' || c == ' ' || c == ';' || c == '(' || c == ')' || c == ',' || c == '\t' || c == '.' || c == '[' || c == ']') {
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
		// Check to see if you are putting keywords in a string
		/*if (words[i][0] == '"') {
			inQuotes = !inQuotes;
		}
		std::cout << inQuotes << std::endl;*/

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

		// Types
		// Integers
		std::string varType = getVariableType(replaceAll(words[i], " ", ""));
		if (varType != "") {
			// Look through the line to see if there is a start of an array
			int j = 0;
			bool doRun = true;
			while (true) {
				if (i + j == words.size() - 1 || words[i + j] == "]") {
					doRun = false;	// Don't run if you are making an array
					i += 3;			// Remove "int x ="
					break;
				}
				j++;
			}

			if (doRun) {
				run += varType + " ";
				run += words[i + 1];
				run += ";";
				// Get the value of the new variable;

				/*while (words[i + 1] != ";") {

				}*/
				run += words[i + 1] + ".value = " + words[i + 3];
				i += 4;
			}
		}

		/*std::vector<int> p = { 1, 2, 3, 4, 5 };
		int p = [1, 2, 3, 4, 5]*/

		// Arrays / Vectors
		if (i > 2) {
			// Continue moving through spaces
			if (replaceAll(words[i], " ", "") == keywords.startArray) {
				if (words[i - 1] == "=" || words[i - 2] == "=") {
					run += "std::vector<";
					run += words[i - 4];	// Type
					run += "> ";
					run += words[i - 3];	// Variable name
					run += " = {";

					int j = 1;
					while (words[i + j] != keywords.endArray) {
						run += words[i + j];
						j++;
					}

					i += j + 1;
					run += "};";
				}
			}
		}

		// Array functions
		// Append
		if (replaceAll(words[i], " ", "") == keywords.appendToArray) {
			if (words[i - 1] == ".") {
				run += "push_back";
				i += 1;
			}
		}

		// Size
		if (replaceAll(words[i], " ", "") == keywords.sizeOfArray) {
			if (words[i - 1] == ".") {
				run += "size()";
				i += 1;
			}
		}


		// Time class
		if (replaceAll(words[i], " ", "") == keywords.timeClass) {
			run += "timer";	// Temp
			i++;
		}

		// Math class
		if (replaceAll(words[i], " ", "") == keywords.mathClass) {
			run += "math";
			i++;
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