#include "../AnalisadorLexico/LexicalAnalyzer.cpp"
#include "../AnalisadorLexico/Tokens.cpp"
#include "../AnalisadorLexico/Token.cpp"
#include <map>
#include <string>
#include <cstdio>

// analisador descendente LL(1) preditivo recursivo; 

class SyntaticAnalyzer {
private:
    
public:
    
    Token token;
    LexicalAnalyzer lexical;
    void printProduction(std::string left, std::string right);
    void error(std::string);
    void S(bool first = false);
    void Body();
    void BodyScope();
    void FunName();
    void Decl();
    void LI();
    void Type();
    void ArrayOpt();
    void Atr();
    void AtrR();
    void Fc();
    void Eb();
    void Ebr();
    void Tb();
    void Tbr();
    void Fb();
    void Fbr();
    void Ra();
    void Rar();
    void Ea();
    void Ear();
    void Ta();
    void Tar();
    void Fa();
    void Far();
    void Comp();
    void ArrayAccess();
    void Params();
    void Paramsr();
    void Inst();
    void LIr();
    void Inr();
    void FunCall();
    void Lec();
    void Lecr();
    void Command();
    void Ifr();
    void Inc();
    std::map<int, std::string> enumToString;
    void init(std::string programName);
    void print(Token t);
    SyntaticAnalyzer();
    void unexpectedToken(TokenType t);
    void nextToken();
    std::string getTokenName(int id);
    bool isTokenType(TokenType t);
    bool isCompToken(TokenType t);
    bool isCommand(TokenType t);
    void verifyTokenAndPrint(TokenType t);
};

std::string SyntaticAnalyzer::getTokenName(int id){
    if(enumToString.count(id)){
		return enumToString[id];		
	}else return "unknown";
}

SyntaticAnalyzer::SyntaticAnalyzer(){
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

void SyntaticAnalyzer::nextToken(){
    if(!lexical.hasToken()){
        printProduction("S", "epsilon");
        exit(0);
    }
    token = lexical.nextToken();
}

void SyntaticAnalyzer::print(Token t){
	printf("              [%04d, %04d] (%04d, %10s) {%s}\n", t.line + 1, t.column + 1, t.type , getTokenName(t.type).c_str() , t.value.c_str());
    nextToken();
}

void SyntaticAnalyzer::init(std::string programName) {
    lexical.init(programName);
}

void SyntaticAnalyzer::S(bool first) {
    if(!lexical.hasToken()){
        printProduction("S", "epsilon");
    } else {
        if(first)nextToken();
        if(token.type == TokenType::funDec) {
            printProduction("S", "funDec Type FunName '[' Params ']' Body S");
            print(token);
            Type();
            FunName();
            verifyTokenAndPrint(TokenType::openBrack);
            Params();
            verifyTokenAndPrint(TokenType::closeBrack);
            Body();
            S();
        } else if (isTokenType(token.type)) {
            printProduction("S", "Decl S");
            Decl();
            S();
        } else {
            unexpectedToken(token.type);
        }
    }
}

void SyntaticAnalyzer::Body() {
    printProduction("Body", "'{' BodyScope '}' ");
    verifyTokenAndPrint(openBrace);
    BodyScope();
    verifyTokenAndPrint(closeBrace);
}

void SyntaticAnalyzer::BodyScope() {
    if(isTokenType(token.type)){
        printProduction("BodyScope", "Decl BodyScope");
        Decl();
        BodyScope();
    } else if (token.type == TokenType::id){
        printProduction("BodyScope", "Atr BodyScope");
        Atr();
        BodyScope();
    } else if (token.type == TokenType::reReturn){
        printProduction("BodyScope", "Return ';'");
        print(token);
    } else if(isCommand(token.type)){
        printProduction("BodyScope", "Command BodyScope");
        Command();
        BodyScope();
    } else {
         printProduction("BodyScope", "epsilon");
    }
}

void SyntaticAnalyzer::Command(){
    if(token.type == TokenType::reFor){
        printProduction("Command", "'reFor' '[' Atr ';' 'Eb' ';' Inc ']' Body");
        print(token);
        verifyTokenAndPrint(TokenType::openBrack);
        Atr();
        Eb();
        verifyTokenAndPrint(TokenType::semiColon);
        Inc();
        verifyTokenAndPrint(TokenType::closeBrack);
        Body();
    } else if(token.type == TokenType::reWhile){
        printProduction("Command", "'reWhile' '[' Eb ']' Body");
        print(token);
        verifyTokenAndPrint(TokenType::openBrack);
        Eb();
        verifyTokenAndPrint(TokenType::closeBrack);
        Body();
    } else if(token.type == TokenType::reIf){
        printProduction("Command", "'reIf' '[' Eb ']' Body Ifr");
        print(token);
        verifyTokenAndPrint(TokenType::openBrack);
        Eb();
        verifyTokenAndPrint(TokenType::closeBrack);
        Body();
        Ifr();
    }
}

void SyntaticAnalyzer::Inc(){
    if(token.type == TokenType::id) {
        printProduction("Inc", "'id'");
        print(token);
    } else if(token.type == TokenType::intConst){
        printProduction("Inc", "'intConst'");
        print(token);
    } else {
        unexpectedToken(token.type);
    }
}

void SyntaticAnalyzer::Ifr(){
    if(token.type == TokenType::reElseIf) {
        printProduction("Ifr", "'reElseIf' '[' Eb ']' Body Ifr");
        print(token);
        verifyTokenAndPrint(TokenType::openBrack);
        Eb();
        verifyTokenAndPrint(TokenType::closeBrack);
        Body();
        Ifr();
    } else if(token.type == TokenType::reElse) {
        printProduction("Ifr", "'reElse' Body");
        print(token);
        Body();
    } else {
        printProduction("Ifr", "epsilon");
    }
}



void SyntaticAnalyzer::Atr() {
    printProduction("Atr", "'id' AtrR");
    print(token);
    AtrR();
}

void SyntaticAnalyzer::AtrR() {
    if(token.type == TokenType::openPar || token.type == TokenType::atrib){
        printProduction("Atr", "ArrayOpt 'atrib' Fc ';'");
        ArrayOpt();
        verifyTokenAndPrint(TokenType::atrib);
        Fc();
        verifyTokenAndPrint(TokenType::semiColon);
    } else if(token.type == TokenType::openBrack) {
        printProduction("Atr", "FunCall");
        FunCall();
    } else if(token.type == TokenType::increOp) {
        printProduction("Atr", "'increOp' ';' ");
        print(token);
        verifyTokenAndPrint(TokenType::semiColon);
    } else if(token.type == TokenType::decreOp) {
        printProduction("Atr", "'decreOp' ';' ");
        print(token);
        verifyTokenAndPrint(TokenType::semiColon);
    } else {
        unexpectedToken(token.type);
    }
}

void SyntaticAnalyzer::FunCall() {
    printProduction("FunCall", "'[' Lec ']' ;");
    print(token);
    Lec();
    verifyTokenAndPrint(TokenType::closeBrack);
    verifyTokenAndPrint(TokenType::semiColon);
}

void SyntaticAnalyzer::Lec() {
    printProduction("Lec", "Fc Lecr");
    Fc();
    Lecr();
}

void SyntaticAnalyzer::Lecr() {
    if(token.type == TokenType::comma){
        printProduction("Lecr", "',' Fc Lecr");
        print(token);
        Fc();
        Lecr();
    } else {
        printProduction("Lecr", "epsilon");
    } 
}

void SyntaticAnalyzer::Fc() {
    if(token.type == TokenType::stringCons){
        printProduction("Fc", "StringConst");
        print(token);
    } else {
        printProduction("Fc", "Eb");
        Eb();
    }
}

void SyntaticAnalyzer::Eb(){
    printProduction("Eb", "Tb Ebr");
    Tb();
    Ebr();
}

void SyntaticAnalyzer::Ebr() {
    if(token.type == TokenType::orOpLog){
        printProduction("Ebr", "'orOpLog' Tb Ebr");
        print(token);
        Tb();
        Ebr();
    } else {
        printProduction("Ebr", "epsilon");
    }
}

void SyntaticAnalyzer::Tb() {
    printProduction("Tb", "Fb Tbr");
    Fb();
    Tbr();
}

void SyntaticAnalyzer::Tbr(){
    if(token.type == TokenType::andOpLog){
        printProduction("Tbr", "'andOpLog' Fb Tbr");
        print(token);
        Fb();
        Tbr();
    } else {
        printProduction("Tbr", "epsilon");
    }
}

void SyntaticAnalyzer::Fb(){
    if(token.type == TokenType::negOp){
        printProduction("Fb", "'negOp' Fb");
        print(token);
        Fb();
    } else if(token.type == TokenType::boolConst){
        printProduction("Fb", "'boolConst'");
        print(token);
    } else {
        printProduction("Fb", "Ra Fbr");
        Ra();
        Fbr();
    }
}

void SyntaticAnalyzer::Fbr() {
    if(isCompToken(token.type)){
        printProduction("Fbr", "Comp Ra Fbr");
        Comp();
        Ra();
        Fbr();
    } else {
        printProduction("Fbr", "epsilon");
    }
}

void SyntaticAnalyzer::Ra() {
    printProduction("Ra", "Ea Rar");
    Ea();
    Rar();
}

void SyntaticAnalyzer::Rar(){
    if(token.type == TokenType::eqRel) {
        printProduction("Rar", "'eqRl' Ea Rar");
        print(token);
        Ea();
        Rar();
    } else if(token.type == TokenType::notEqRel){
        printProduction("Rar", "'notEqRl' Ea Rar");
        print(token);
        Ea();
        Rar();
    } else {
        printProduction("Rar", "Epsilon");
    }
}

void SyntaticAnalyzer::Ea() {
    printProduction("Ea", "Ta Ear");
    Ta();
    Ear();
}

void SyntaticAnalyzer::Ear(){
    if(token.type == TokenType::subOp){
        printProduction("Ear", "'subOp' Ta Ear");
        print(token);
        Ta();
        Ear();
    } else if(token.type == TokenType::addOp){
        printProduction("Ear", "'addOp' Ta Ear");
        print(token);
        Ta();
        Ear();
    } else {
        printProduction("Ear", "epsilon");
    }
}

void SyntaticAnalyzer::Ta() {
    printProduction("Ta", "Fa Tar");
    Fa();
    Tar();
}

void SyntaticAnalyzer::Tar(){
    if(token.type == TokenType::divOp){
        printProduction("Tar", "'divOp' Fa Tar");
        print(token);
        Fa();
        Tar();
    } else if(token.type == TokenType::multOp){
        printProduction("Tar", "'multOp' Fa Tar");
        print(token);
        Fa();
        Tar();
    } else {
        printProduction("Tar", "epsilon");
    }
}

void SyntaticAnalyzer::Fa(){
    if(token.type == TokenType::openPar){
        printProduction("Fa", "'(' Eb ')' ");
        print(token);
        Eb();
        verifyTokenAndPrint(TokenType::closePar);
    } else if(TokenType::subOp == token.type){
        printProduction("Fa", "'subOp' Far");
        print(token);
        Far();
    } else if(token.type == TokenType::id){
        printProduction("Fa", "'id' arrayOpt");
        print(token);
        ArrayOpt();
    } else {
         printProduction("Fa", "Far");
         Far();
    }
}

void SyntaticAnalyzer::Far() {
    if(token.type == TokenType::id) {
        printProduction("Far", "'id'");
        print(token);
    } else if(token.type == TokenType::intConst){
        printProduction("Far", "'intConst'");
        print(token);
    } else if(token.type == TokenType::floatConst){
        printProduction("Far", "'floatConst'");
        print(token);
    } else {
        printProduction("Far" , "epsilon");
    }
}



void SyntaticAnalyzer::Comp(){
    print(token);
}

void SyntaticAnalyzer::FunName() {
    if(token.type == TokenType::id){
        printProduction("FunName", "'id'");
        print(token);
    } else if(token.type == TokenType::reMain){
        printProduction("FunName", "ReMain");
        print(token);
    } else {
        unexpectedToken(token.type);
    }
}

void SyntaticAnalyzer::Params() {
    if (isTokenType(token.type)) {
        printProduction("Params", "Type 'id' ArrayOpt Paramsr");
        Type();
        verifyTokenAndPrint(TokenType::id);
        print(token);
        ArrayOpt();
        Paramsr();
    } else {
        printProduction("Params", "epsilon");
    }
}

void SyntaticAnalyzer::Paramsr() {
    if(token.type == TokenType::comma) {
        printProduction("Paramsr", "',' Type 'id' ArrayOpt Paramsr");
        Type();
        verifyTokenAndPrint(TokenType::id);
        ArrayOpt();
        Paramsr();
    } else {
        printProduction("Paramsr", "epsilon");
    }
}

void SyntaticAnalyzer::Decl(){
    printProduction("Decl", "Type LI");
    Type();
    LI();
}

void SyntaticAnalyzer::Type() {
    if (isTokenType(token.type)){    
        printProduction("Type", enumToString[token.type]);
        print(token);
    } else {
        unexpectedToken(token.type);
    }
}

void SyntaticAnalyzer::LI() {
    if(token.type == TokenType::id){
        printProduction("LI","'id' ArrayOpt Inst LIr");
        print(token);
        ArrayOpt();
        Inst();
        LIr();
    } else {
        unexpectedToken(token.type);
    }
}

void SyntaticAnalyzer::LIr() {
    if(token.type == TokenType::comma) {
        printProduction("LIr", "',' 'id' ArrayOpt Inst LIr");
        print(token);
        if(token.type == TokenType::id){
            print(token);
            ArrayOpt();
            Inst();
            LIr();
        } else {
            unexpectedToken(token.type);
        }
    } else if(token.type == TokenType::semiColon) {
        printProduction("LIr", "';'");
        print(token);
    } else {
        unexpectedToken(token.type);
    }
}

void SyntaticAnalyzer::ArrayOpt(){
    if(token.type == TokenType::openPar) {
        printProduction("ArrayOpt", "'(' ArrayAccess");
        print(token);
        ArrayAccess();
    } else {
        printProduction("ArrayOpt", "epsilon");
    }
}

void SyntaticAnalyzer::ArrayAccess(){
    if(token.type == TokenType::intConst) {
        printProduction("ArrayAccess", "'intConst' ')' ");
        print(token);
        verifyTokenAndPrint(TokenType::closePar);

    } else if(token.type == TokenType::id){
        printProduction("ArrayAccess", "'id' ')' ");
        print(token);
        verifyTokenAndPrint(TokenType::closePar);
    }
    else if(token.type == TokenType::closePar) {
        printProduction("ArrayAccess", "')'");
        print(token);
    }
}

void SyntaticAnalyzer::Inst() {
    if(token.type == TokenType::atrib) {
        printProduction("Inst", "'atrib' Inr");
        print(token);
        Inr();
    } else {
        printProduction("Inst", "epsilon");
    }
}

void SyntaticAnalyzer::Inr() {
    if(token.type == TokenType::openPar){
        printProduction("Inr", "ArrayOpt");
        ArrayOpt();
    } else {
        printProduction("Inr", "Fc");
        Fc();
    }
}

void SyntaticAnalyzer::printProduction(std::string left, std::string right){
    printf("%10s%s = %s\n", "", left.c_str(), right.c_str());
}

void SyntaticAnalyzer::error(std::string message) {
    printf("Error: %s", message.c_str());
    exit(0);
}

void SyntaticAnalyzer::unexpectedToken(TokenType t) {
    error("unexpected Token -> " + enumToString[t]);
}

bool SyntaticAnalyzer::isTokenType(TokenType t){
    return (t == TokenType::stringType
        || t == TokenType::intType
        || t == TokenType::floatType
        || t == TokenType::boolType
        || t == TokenType::reVoid);
}

bool SyntaticAnalyzer::isCompToken(TokenType t){
    return (t == TokenType::greEqRel
    || t == TokenType::greRel
    || t == TokenType::lowEqRel
    || t == TokenType::lowRel);
}

bool SyntaticAnalyzer::isCommand(TokenType t) {
    return(t == TokenType::reFor
    || t == TokenType::reWhile
    || t == TokenType::reIf);
}

void SyntaticAnalyzer::verifyTokenAndPrint(TokenType t){
    if(token.type != t){
        unexpectedToken(token.type);
    } 
    print(token);
}