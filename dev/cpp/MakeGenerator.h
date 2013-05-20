#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class MakeGenerator
{
	public:
		MakeGenerator();
		MakeGenerator(string make);//the paths to these files.
		void setMakeFile(string path);
		string getMakeFile();
		void makeGen(vector<string> files, string CFlags);

	private:	
		string makeCFlags(string CFlags);
		string makeObjects(vector<string> files, string compiler);
		string makeCompiler(vector<string> files);
		string metaFile;
		string makeFile;
		string fileName;


};