#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

#include "build.cpp";


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

	// Keywords
	std::string noNewLine = "noNewLine";
	std::string importFile = "import";

	// Methods
	std::string appendToArray = ".push";
	std::string sizeOfArray = ".length";

	// File properties
	std::string fileExtension = "j";
	std::string buildName = "build";


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
	outfile.open("build.cpp", std::ios_base::app);
	outfile << text;
}

void appendToBuild(char text) {
	std::ofstream outfile;
	outfile.open("build.cpp", std::ios_base::app);
	outfile << text;
}

std::string createBaseFile() {
	std::ofstream build("build.cpp");
	std::string extraClasses = "";

	build << "#include <iostream>\n";
	build << "#include <string>\n";
	build << "#include <vector>\n";

	// Include Types
	build << "#include \"Int.h\";\n";
	build << "#include \"String.h\";\n";
	build << "#include \"Float.h\";\n";

	// Including other header files
	build << "#include \"Math.h\";\n";
	build << "#include \"Time.h\";\n";

	// Print Function
	build << "void print() {\n\tstd::cout << std::endl;\n}\ntemplate<typename First, typename ... Strings>\n";
	build << "void print(First arg, const Strings&... rest) {\n\tstd::cout << arg;\n\tprint(rest...);\n }\n";

	// Random Function
	build << "int rand(int min, int max);\n";

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
			run += varType + " ";
			run += words[i + 1];
			run += ";";

			// Get the value of the new variable;
			std::cout << (words[i + 1] == ";") << std::endl;

			/*while (words[i + 1] != ";") {

			}*/
			run += words[i + 1] + ".value = " + words[i + 3];
			i += 4;
		}

		// Arrays / Vectors

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