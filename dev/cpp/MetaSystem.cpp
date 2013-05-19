#include "MetaSystem.h"

using namespace std;

MetaSystem::MetaSystem()
{
	currentPath = "";
	fileName = "";
	makePath = "";
	metaPath = "";
	flags = "";

}

MetaSystem::MetaSystem(string filePath, string cflags)
{	
	currentPath = filePath;
	//get location to /filename in dir/dir/filename
	unsigned it = filePath.find_last_of("/\\");
	fileName = filePath.substr(it+1);
	makePath = changeFileName("Makefile");
	metaPath = changeFileName(".meta.txt");
	flags = cflags;
}

void MetaSystem::setCurrentPath(string path)
{
	currentPath = path;
}

void MetaSystem::setFileName(string path)
{
	unsigned it = path.find_last_of("/\\");
	fileName = path.substr(it+1);
}

void MetaSystem::setMakePath(string path)
{
	makePath = changeFileName("Makefile");
}

void MetaSystem::setMetaPath(string path)
{
	metaPath = changeFileName(".meta.txt");
}

void MetaSystem::loadMetaData()
{
	if(metaPath == "")
		cout << "Meta path wasn't set, use the other version of load." << endl;
	else
	{
		ifstream fin(metaPath.c_str());
		string input = "";
		if(!metaData.empty())
			metaData.clear();
		while(getline(fin,input))
		{
			metaData.push_back(input);
		}
		fin.close();
	}
}

void MetaSystem::loadMetaData(string path)
{
	setMetaPath(path);
	setMakePath(path);
	setFileName(path);
	setCurrentPath(path);
	ifstream fin(metaPath.c_str());
	string input = "";
	if(!metaData.empty())
		metaData.clear();
	while(getline(fin,input))
	{
		metaData.push_back(input);
	}
	fin.close();
}

string MetaSystem::getCurrentPath()
{
	return currentPath;
}

string MetaSystem::getFileName()
{
	return fileName;
}
string MetaSystem::getMakePath()
{
	return makePath;
}

string MetaSystem::getMetaPath()
{
	return metaPath;
}

vector<string> MetaSystem::getMetaData()
{
	return metaData;
}

void MetaSystem::printMetaData()
{
	if(metaPath == "")
		cout << "Meta path wasn't set." << endl;
	else
	{
		loadMetaData();//to make sure all updates are applied.
		for(vector<string>::size_type i = 0; i < metaData.size(); i++)
		cout << "Index " << i << " of meta data is " << metaData.at(i) << endl;	
	}
}
string MetaSystem::changeFileName(string fileName)
{
	string ret = "";
	unsigned it = currentPath.find_last_of("/\\");
	ret = currentPath.substr(0, it+1);
	ret += fileName;
	return ret;
}

void MetaSystem::addMeta()
{
	if(metaPath == "")
		cout << "Meta path wasn't set." << endl;
	else
	{
		ofstream fout;
		fout.open(metaPath.c_str(), fstream::app);
		fout << fileName << endl;
		fout.close();
	}

}

void MetaSystem::removeMeta()
{
	if(metaPath == "")
		cout << "Meta path wasn't set." << endl;
	else
	{
		loadMetaData();
		ofstream fout(metaPath.c_str());
		
		vector<string>::iterator it = find(metaData.begin(), metaData.end(), getFileName());
		if(it!=metaData.end())
			metaData.erase(it);
		for(vector<string>::size_type i = 0; i < metaData.size(); i++)
		{
				fout << metaData[i] << endl;
		}
		fout.close();
	}
}

void MetaSystem::renameMeta(string newPath)
{
	if(metaPath == "")
		cout << "Meta path wasn't set." << endl;
	else
	{
		ofstream fout(metaPath.c_str());
		for(vector<string>::size_type i = 0; i < metaData.size(); i++)
		{
			if(metaData[i] == fileName)
			{
				setFileName(newPath);
				metaData[i] = fileName;
				fout << metaData[i] << endl;
			}
			else
				fout << metaData[i] << endl;
		}
		fout.close();
	}

}

void MetaSystem::sortMeta()
{
	if(metaPath == "")
		cout << "Meta path wasn't set." << endl;
	else
	{
		loadMetaData();
		sort(metaData.begin(), metaData.end());
		ofstream fout(metaPath.c_str());
		for(vector<string>::size_type i = 0; i <metaData.size(); i++)
			fout << metaData[i] << endl;
		fout.close();
	}
}