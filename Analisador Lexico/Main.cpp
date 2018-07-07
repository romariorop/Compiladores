#include <iostream>
#include "Tokens.cpp"
#include "Token.cpp"
#include "LexicalAnalyzer.cpp"


int main(int argc, char *argv[]) {
	LexicalAnalyzer l;
	std::map<int, std::string>mp;
	l.init(std::string(argv[1]));
	while(l.hasToken()){
		Token t = l.nextToken();
		t.print(mp);
	}
	return 0;
}

