#include <iostream>
#include "LexicalAnalyzer.cpp"

void print(Token t, std::map<int , std::string>enumToString){
	printf("        [%04d, %04d] (%04d, %10s) {%s}\n", t.line + 1, t.column + 1, t.type , t.getString(t.type, enumToString).c_str() , t.value.c_str());
}
int main(int argc, char *argv[]) {
	LexicalAnalyzer l;
	std::map<int, std::string>mp;
	l.init(std::string(argv[1]));
	while(l.hasToken()){
		Token t = l.nextToken();
		print(t, mp);
	}
	return 0;
}

