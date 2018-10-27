#pragma once
#include <map>
class Token{
private:
	
public:
	Token(TokenType type, int line, int column, std::string value);
	Token();
	TokenType type;
	int line;
	int column;
	std::string value;
	std::string getString(TokenType t, std::map<int , std::string>enumToString);
	
};

Token::Token(TokenType type, int line, int column, std::string value){
	this->type = type;
	this->line = line;
	this->column = column;
	this->value = value;
}

Token::Token(){
	this->type = TokenType::unknown;
}

std::string Token::getString(TokenType t, std::map<int , std::string>enumToString){
	if(enumToString.empty()){
		enumToString[comma] = "comma";
		enumToString[funDec] = "funDec";
		enumToString[semiColon] = "semiColon";
		enumToString[headerCons] = "headerCons";
		enumToString[headerName] = "headerName";
		enumToString[reMain] = "reMain";
		enumToString[intType] = "intType";
		enumToString[intConst] = "intConst";
		enumToString[floatType] = "floatType";
		enumToString[floatConst] = "floatConst";
		enumToString[boolType] = "boolType";
		enumToString[boolConst] = "boolConst";
		enumToString[stringType] = "stringType";
		enumToString[addOp] = "addOp";
		enumToString[subOp] = "subOp";
		enumToString[multOp] = "multOp";
		enumToString[divOp] = "divOp";
		enumToString[andOpLog] = "andOpLog";
		enumToString[andOpBin] = "andOpBin";
		enumToString[orOpLog] = "orOpLog";
		enumToString[orOpBin] = "orOpBin";
		enumToString[xorOpBin] = "xorOpBin";
		enumToString[negOp] = "negOp";
		enumToString[negUn] = "negUn";
		enumToString[eqRel] = "eqRel";
		enumToString[greEqRel] = "greEqRel";
		enumToString[lowEqRel] = "lowEqRel";
		enumToString[lowRel] = "lowRel";
		enumToString[notEqRel] = "notEqRel";
		enumToString[concaten] = "concaten";
		enumToString[increOp] = "increOp";
		enumToString[decreOp] = "decreOp";
		enumToString[openBrack] = "openBrack";
		enumToString[closeBrack] = "closeBrack";
		enumToString[openPar] = "openPar";
		enumToString[closePar] = "closePar";
		enumToString[openBrace] = "openBrace";
		enumToString[closeBrace] = "closeBrace";
		enumToString[endLine] = "endLine";
		enumToString[reIf] = "reIf";
		enumToString[reElse] = "reElse";
		enumToString[reFor] = "reFor";
		enumToString[reWhile] = "reWhile";
		enumToString[ternOp1] = "ternOp1";
		enumToString[ternOp2] = "ternOp2";
		enumToString[reElseIf] = "reElseIf";
		enumToString[id] = "id";
		enumToString[greRel] = "greRel";
		enumToString[reVoid] = "reVoid";
		enumToString[atrib] = "atrib";
		enumToString[stringCons] = "stringCons";
		enumToString[reReturn] = "reReturn";
	}
	
}
