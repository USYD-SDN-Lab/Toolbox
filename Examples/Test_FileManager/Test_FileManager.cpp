#include <stdio.h>
#include <iostream>
#include <string>
#include "../../FileManager.h"

using namespace std;
using namespace Toolbox;

int main(int argc, char* argv[]) {
	int ret = -1000;
	FileManager fm = FileManager();

	// test create path
	cout << "Test - create path" << endl;
	string strPath = "./_build/str";
	const char * chrPath = "./_build/chr/";
	ret = FileManager::CreatePath(strPath);
	if (ret == 200) {
		cout << "     - string path pass!" << endl;
	}
	ret = FileManager::CreatePath(chrPath);
	if (ret == 200) {
		cout << "     - char path pass!" << endl;
	}

	// test file
	cout << "Test - file operations" << endl;
	ret = fm.Open("./_build/str2/fuck.csv");
	if (ret == 404) {
		cout << "     - open illegal path pass!" << endl;
	}
	ret = fm.Open("./_build/str/fuck.csv");
	if (ret == 200) {
		cout << "     - open legal path pass!" << endl;
	}
	fm.AddCSVItem("fuck");
	fm.AddCSVItem(27, true);
	fm.Close();
	cout << "     - write data & close pass!" << endl;
	
	// test folder
	cout << "Test - check file or folders" << endl;
	ret = FileManager::IsFolderOrFileExist("./_build");
	if (ret) {
		cout << "     - folder check pass!" << endl;
	}
	ret = fm.Open("./_build/test.txt");
	if (ret == 200) {
		cout << "     - file created!" << endl;
	}
	fm.AddTextLine("test");
	fm.Close();


	// pause to let users see outcomes
	//system("pause");
}