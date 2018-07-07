#include <map>
#include <vector>
#include <deque>
#include <regex>
#include<fstream>
class LexicalAnalyzer{
private:
	std::map<std::string, TokenType>tokensMap;
	std::string nextLine;
	std::ifstream infile;
	int line;
	int column;
	int index;
	void nextChar();
public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	void init(std::string programName);
	std::vector<Token> analyze();
	Token nextToken();
	bool hasToken();
};


LexicalAnalyzer::LexicalAnalyzer(){
	line = -1;
}

LexicalAnalyzer::~LexicalAnalyzer(){
	
}

void LexicalAnalyzer::init(std::string programName){
	infile.open(programName);
	index = 0;
	tokensMap[","] = TokenType::comma;
	tokensMap[";"] = TokenType::semiColon;
	tokensMap["main"] = TokenType::reMain;
	tokensMap["int"] = TokenType::intType;
	tokensMap["float"] = TokenType::floatType;
	tokensMap["bool"] = TokenType::boolType;
	tokensMap["false"] = TokenType::boolConst;
	tokensMap["true"] = TokenType::boolConst;
	tokensMap["string"] = TokenType::stringType;
	tokensMap["stringCons"] = TokenType::stringCons;
	tokensMap["+"] = TokenType::addOp;
	tokensMap["-"] = TokenType::subOp;
	tokensMap["*"] = TokenType::multOp;
	tokensMap["/"] = TokenType::divOp;
	tokensMap["&&"] = TokenType::andOpLog;
	tokensMap["&"] = TokenType::andOpBin;
	tokensMap["||"] = TokenType::orOpLog;
	tokensMap["|"] = TokenType::orOpBin;
	tokensMap["^"] = TokenType::xorOpBin;
	tokensMap["!"] = TokenType::negOp;
	tokensMap["=="] = TokenType::eqRel;
	tokensMap[">="] = TokenType::greEqRel;
	tokensMap["<="] = TokenType::lowEqRel;
	tokensMap["<"] = TokenType::lowRel;
	tokensMap["!="] = TokenType::notEqRel;
	tokensMap["+="] = TokenType::concaten;
	tokensMap["++"] = TokenType::increOp;
	tokensMap["--"] = TokenType::decreOp;
	tokensMap["["] = TokenType::openBrack;
	tokensMap["]"] = TokenType::closeBrack;
	tokensMap["("] = TokenType::openPar;
	tokensMap[")"] = TokenType::closePar;
	tokensMap["{"] = TokenType::openBrace;
	tokensMap["}"] = TokenType::closeBrace;
	tokensMap["\n"] = TokenType::endLine;
	tokensMap["if"] = TokenType::reIf;
	tokensMap["else"] = TokenType::reElse;
	tokensMap["for"] = TokenType::reFor;
	tokensMap["while"] = TokenType::reWhile;
	tokensMap["?"] = TokenType::ternOp1;
	tokensMap[":"] = TokenType::ternOp2;
	tokensMap["elseif"] = TokenType::reElseIf;
	tokensMap[">"] = TokenType::greRel;
	tokensMap["void"] = TokenType::reVoid;
	tokensMap["="] = TokenType::atrib;
}

bool LexicalAnalyzer::hasToken(){
	if(index == (int)nextLine.size() || nextLine.empty()){
		++line;
		column = 0;
		index = 0;
		if(getline(infile, nextLine)){
			if(!nextLine.size()){
				std::cout << "Line " << line << " :" << nextLine << std::endl; 
				return hasToken();
			}
			return true;
		}else {
			return false;
		}
	}
	return true;
}

Token LexicalAnalyzer::nextToken() {
	char c = nextLine[index];
	int col = column;
	std::string value = "";
	if(c == '\"'){
		nextChar();
		while(index != (int)nextLine.size()){
			c = nextLine[index];
			if(c == '\"'){
				Token retToken(TokenType::stringCons, line, col, value);
				nextChar();
				return retToken;
			}else {
				value += nextLine[index];
				nextChar();
			}
		}
		return Token(TokenType::unknown, line, col,"\"" + value);
	}else if(c >= '0' && c <= '9'){
		value += c;
		nextChar();
		bool point  = false;
		while(index != (int)nextLine.size()){
			c = nextLine[index];
			if(c >= '0' && c <= '9'){
				value+=c;
				nextChar();
			}else if(c == '.' && !point){
				point = true;
				value+=c;
				nextChar();
			}else break;
		}
		if(point){	
			return Token(TokenType::floatConst, line, col, value);
		}else {
			return Token(TokenType::intConst, line, col, value);
		}
	}else if((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z')){
		value += c;
		nextChar();
		while(index != (int)nextLine.size()){
			c = nextLine[index];
			if((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z')|| (c >= '0' && c <= '9') || (c == '_')){
				value+=c;
				nextChar();
			}else break; 
		}
		if(tokensMap.count(value))return Token(tokensMap[value], line, col, value);
		return Token(TokenType::id, line, col, value);
	}else if(c == ' ' || c == '\t'){
		nextChar();
		if(hasToken())return nextToken();
		else return Token(TokenType::unknown, line, col, value);
	}else {
		value+=c;
		nextChar();
		if(tokensMap.count(value)){
			std::string temp = value;
			if(index != (int)nextLine.size()){
				c = nextLine[index];
				temp += c;
				if(tokensMap.count(temp)){
					nextChar();
					return Token(tokensMap[temp], line, col, temp);
				}
			}
			return Token(tokensMap[value], line, col, value);
		}else {
			if(value == " ")return nextToken();
			return Token(TokenType::unknown, line, col, value);
		}
	}
}

void LexicalAnalyzer::nextChar(){
	++index;
	++column;
}