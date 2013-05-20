#include "MakeGenerator.h"

using namespace std;

MakeGenerator::MakeGenerator()
{
	makeFile = "";
}

MakeGenerator::MakeGenerator(string make)
{
	makeFile = make;
}

void MakeGenerator::setMakeFile(string path)
{
	makeFile = path;
}

string MakeGenerator::getMakeFile()
{
	return makeFile;
}


void MakeGenerator::makeGen(vector<string> files, string CFlags) //CFlags format: .flag1.flag2.flag3
{

	//Declare all variables
	ofstream fout;
	stringstream output;
	string runnable = "";
	string compiler = "";
	string objects = "";
	string flags = "";
	//Name the runnable
	runnable = files[0];
	runnable.erase(runnable.begin());
	files.erase(files.begin());
	//Determing the compiler
	compiler = makeCompiler(files);
	//Build the objects strings
	objects = makeObjects(files, compiler);
	cout << objects << endl;
	flags = makeCFlags(CFlags);
	fout.open(makeFile.c_str());
	fout << ".PHONY: clean" << endl;
	fout << "CC = " << compiler << endl;
	if(flags == "")
	{
		fout << flags << endl;
	}
	fout << "CFLAGS = " << flags << endl;
	fout << "OBJ = " << objects << endl << endl;
	fout << "%%.o: %%.c" << endl;
	fout << "\t$(CC) -c -o $@ $< $(CFLAGS)" << endl << endl;
	fout << runnable << ": $(OBJ)" << endl;
	fout << "\t$(CC) -o $@ $^ $(CFLAGS)" << endl << endl;
	fout << "clean:" << endl;
	fout << "\trm -f " << runnable << " *.o" << endl;
	fout.close();

}

string MakeGenerator::makeCFlags(string CFlags)
{
	cout << "entered makeCFlags" << endl;
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
	if(compiler == "gcc ")
	{
		cout << "Compiler was gcc" << endl;
		for(vector<string>::size_type i = 0; i < files.size(); i++)
		{
			files[i][files[i].size() - 1] = 'o';
			objects << files[i] << " ";
		}
	}
	else if (compiler == "g++ ")
	{
		for(vector<string>::size_type i = 0; i < files.size(); i++)
		{
			files[i].erase(files[i].end() - 2 , files[i].end());
			cout << files[i] << endl;
			files[i][files[i].size() -1] = 'o';
			objects << files[i] << " ";
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
		if (files[i][files[i].size() -1] == 'p')
		{
			compiler = "g++ ";
			flag = true;
		}
		else
		{
			compiler = "gcc ";
			flag = true;		
		}
	i++;
	}
	return compiler;
}
