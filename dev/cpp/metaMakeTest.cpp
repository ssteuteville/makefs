#include "MakeGenerator.h"
#include "MetaSystem.h"

using namespace std;

int main()
{
	string filePath = "metaMakeTest.cpp";
	string cflags = ".-g.-Wall.-pedantic";
	MetaSystem ms(filePath);
	MakeGenerator mg(ms.getMakePath());
	ms.loadMetaData();
	mg.makeGen(ms.getMetaData(), cflags);
	return 0;
}