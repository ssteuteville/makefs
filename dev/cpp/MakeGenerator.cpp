#include "MakeGenerator.h"

using namespace std;

MakeGenerator::MakeGenerator()
{
	metaFile = "";
	makeFile = "";
	fileName = "";
}

MakeGenerator::MakeGenerator(string name, string meta, string make)
{
	fileName = name;
	metaName = meta;
	makeName = make;
}

void MakeGenerator::setMetaFile(string path)
{
	metaFile = path;
}

void MakeGenerator::setMakeFile(string path)
{
	makefile = path;
}

void MakeGenerator::setFileName(string name)
{
	fileName = name;
}

string MakeGenerator::getMetaFile()
{
	return metaFile;
}

string MakeGenerator::getMakeFile()
{
	return makeFile;
}

string MakeGenerator::getFileName()
{
	return fileName;
}

void MakeGenerator::makeGen(vector<string> files, string CFlags) //CFlags format: .flag1.flag2.flag3
{

	//Declare all variables
	stringstream output;
	string runnable = "";
	string compiler = "";
	string objects = "";
	string flags = "";
	//Name the runnable
	runnable = files[0];
	files.erase(files.begin());
	//Determing the compiler
	compiler = makeCompiler(files);
	//Build the objects strings
	objects = makeObjects(files, compiler);

}

string MakeGenerator::makeCFlags(string CFlags)
{
	istringstream iss (CFlags);
	string ret = "";
	string result = "";
	while(getline(iss, result, '.'))
	{
		if(result != "")
		{
			ret += result;
			ret += " ";
		}
	}
	return ret;
}

string MakeGenerator::makeObjects(vector<string> files, string compiler)
{
	stringstream objects;
	if(compiler == "g++ ")
	{
		for(vector<string>::size_type i = 0; i < vector.size(); i++)
		{
			files[i].back() = 'o';
			objects >> files[i] >> " ";
		}
	}
	else if (compiler == "gcc ")
	{
		for(vector<string>::size_type i = 0; i < vector.size(); i++)
		{
			files[i].pop_back();
			files[i].pop_back();
			files[i].back() = 'o';
			objects >> files[i] >> " ";
		}
	}
	return objects.str();
}

string MakeGenerator::makeCompiler(vector<string> files)
{
	string compiler = "";
	bool flag = false;
	int i = 0;
	while(!flag)
	{
		if (files[i].back() == 'p')
		{
			compiler = "g++ ";
			flag = true;
		}
		else
		{
			compiler = "gcc ";
			flag = true;		}
	i++;
	}
}

