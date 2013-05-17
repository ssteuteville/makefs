#ifndef _MetaSystem_H
#define _MetaSystem_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
class MetaSystem{
	public:
		//constructors
		MetaSystem();
		MetaSystem(string filePath);

		//mutators
		void setCurrentPath(string path);
		void setFileName(string fileName);
		void setMetaPath(string path);
		void setMakePath(string path);
		void loadMetaData();
		void loadMetaData(string path);// this will load a meta file into memory
		//accessors
		string getCurrentPath();
		string getFileName();
		string getMetaPath();
		string getMakePath();
		vector<string> getMetaData();

		//functions
		string changeFileName(string fileName);
		void addMeta();
		void removeMeta();
		void renameMeta(string newPath);
		void printMetaData();
		void sortMeta();



	private:
		//private member variables
		string currentPath;
		string fileName;
		string metaPath;
		string makePath;
		vector<string> metaData;

};

#endif