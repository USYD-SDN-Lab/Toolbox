#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include "../../../FileManager.h"

using namespace std;
using namespace Toolbox;

int main(int argc, char* argv[]) {
	int ret = -1000;
	FileManager fm = FileManager();

	// test create path
	cout << "Test - create path" << endl;
	string strPath = "./_build\\str";
	const char * chrPath = "./_build/chr/";
	ret = fm.CreatePath(strPath);
	if (ret == 200) {
		cout << "     - string path pass!" << endl;
	}
	ret = fm.CreatePath(chrPath);
	if (ret == 200) {
		cout << "     - char path pass!" << endl;
	}

	// test file
	cout << "Test - file operations" << endl;
	ret = fm.Open("./_build\\str2/fuck.csv");
	if (ret == 404) {
		cout << "     - open illegal path pass!" << endl;
	}
	ret = fm.Open("./_build\\str/fuck.csv");
	if (ret == 200) {
		cout << "     - open legal path pass!" << endl;
	}
	fm.AddCSVItem("fuck");
	fm.AddCSVItem(27, true);
	fm.close();
	cout << "     - write data & close pass!" << endl;
	

	// pause to let users see outcomes
	//system("pause");
}