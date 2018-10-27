#include <iostream>
#include "SyntaticAnalyzer.cpp"


int main(int argc, char *argv[]) {
    SyntaticAnalyzer *syntatic = new SyntaticAnalyzer();
	syntatic->lexical.init(std::string(argv[1]));
	syntatic->S(true);
	return 0;
}