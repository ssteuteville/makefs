#include "MakeGenerator.h"

using namespace std;

int main()
{
	string filename = "makefile";
	vector<string> v;
	string CFlags = ".-g.-Wall.-pedantic";
	v.push_back("/makeTest");
	v.push_back("MakeGenerator.cpp");
	v.push_back("metaMakeTest.cpp");
	v.push_back("MetaSystem.cpp");

	MakeGenerator mg(filename);
	mg.makeGen(v,CFlags);
	return 0;
}