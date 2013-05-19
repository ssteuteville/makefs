#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class MakeGenerator
{
	public:
		MakeGenerator();
		MakeGenerator(string name, string meta, string make);//the paths to these files.
		void setMetaFile(string path);
		void setMakeFile(string path);
		void setFileName(string name);
		string getMetaFile(string path);
		string getMakeFile(string path);
		string getFileName(string path);
		void makeGen(vector<string> files, string CFlags);

	private:	
		string makeCFlags();
		string makeObjects(vector<string> files, string compiler);
		string makeCompiler();
		string metaFile;
		string makeFile;
		string fileName;


};