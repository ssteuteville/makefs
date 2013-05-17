#include "MetaSystem.h"

using namespace std;

int main(int argc, char** argv)
{
	MetaSystem ms(argv[1]);//Use this one to check overloaded constructor
	//MetaSystem ms;//use this to check default constructor should print errors
	char next = ' ';
	string renamed_file = "renamed_file.c";
	cout << ".....::::: Testing Accessors ::::: ....." << endl;
	cout << "Current path: "<< ms.getCurrentPath() << endl;
	cout << "Meta path: " << ms.getMetaPath() << endl;
	cout << "Make path: " << ms.getMakePath() << endl;
	cout << "File name: " << ms.getFileName() << endl;
	cout << "Enter a key to continue." << endl;
	cin >> next;
	
	cout << ".....::::: Testing Load/Print Meta Data ::::: ....." << endl;
	ms.printMetaData();
	cout << "Enter a key to continue." << endl;
	cin >> next;
	
	cout << ".....::::: Testing Remove/Add/Rename/Sort :::::....." << endl;
	cout << "Removing " << ms.getFileName() << " from meta file" << endl;
	ms.removeMeta();
	ms.printMetaData();
	cout << "Adding " << ms.getFileName() << " back into meta file" << endl;
	ms.addMeta();
	ms.printMetaData();
	cout << "Renaming " << ms.getFileName() <<" to " << renamed_file << endl;
	ms.renameMeta(renamed_file);
	ms.printMetaData();
	cout << "Sorting meta data" << endl;
	ms.sortMeta();
	ms.printMetaData();
	cout << "Enter a key to continue." << endl;
	cin >> next;


	cout << ".....::::: Testing Mutators ::::: ....." << endl;
	ms.setCurrentPath("dir/dir/dir/filename.c");
	ms.setMetaPath("dir/dir/dir/filename.c");
	ms.setMakePath("dir/dir/dir/filename.c");
	ms.setFileName("dir/dir/dir/filename.c");
	cout << ms.getCurrentPath() << endl;
	cout << ms.getMetaPath() << endl;
	cout << ms.getMakePath() << endl;
	cout << ms.getFileName() << endl;


	return 0;
}