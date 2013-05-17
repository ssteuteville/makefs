#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class MakeGenerator
{
	public:
		MakeGenerator();
		MakeGenerator(string name, string meta, string make);//the paths to these files.

		void setMetaFile(string path);
		void setMakeFile(string path);
		void setFileName(string fileName);
		string getMetaFile(string path);
		string getMakeFile(string path);
		string getFileName(string path);

		void makeGen(string metaFile, makeFile);

	private:	
		string makeCFlags();
		string makeObjects();
		string makeCompiler();
		string metaFile;
		string makeFile;
		string fileName;


}