// Test_Error.cpp : Defines the entry point for the application.
//
#include <iostream>
#include "../../Error.h"

using namespace std;
using namespace Toolbox;

int main()
{
	cout << "Error 1" << endl;
	Error err1(TOOLBOX_ERR_INTERNAL);
	err1.Summary();
	cout << "\nError 2" << endl;
	Error err2(NULL, "Test_Error.cpp", "main");
	err2.Summary();
	Error err21(NULL, NULL, "main");
	err21.Summary();
	Error err22(NULL, "Test_Error.cpp", NULL);
	err22.Summary();
	Error err23(NULL, NULL, NULL);
	err23.Summary();
	cout << "\nError 3" << endl;
	Error err3(NULL, "Test_Error.cpp", "Main", "main");
	err3.Summary();
	cout << "\nError 4" << endl;
	Error err4("/src", "Test_Error.cpp", "Main", "main");
	err4.Summary();

	cout << "\nError 6" << endl;
	Error err6("/src/", "Test_Error.cpp", "Main", "main(");
	err6.SetType2MemoryShortage();
	err6.Summary();

	cout << "\nError 7" << endl;
	Error err7("/src/", "Test_Error.cpp", "Main", "main(", "message");
	err7.SetType2MemoryShortage();
	err7.Summary();
	return 0;
}
