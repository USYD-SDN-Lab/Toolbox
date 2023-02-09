clear;
clc;

disp("Error 1");
err1 = Error('code', 20);
err1.Summary();
disp("Error 2");
err2 = Error("filename", "Test_Error.cpp", 'methodname', "main");
err2.Summary();
err21 = Error('methodname',"main");
err21.Summary();
err22 = Error("filename", "Test_Error.cpp");
err22.Summary();
err23 = Error();
err23.Summary();
disp("Error 3");
err3 = Error("filename", "Test_Error.cpp", 'classname', "Main", 'methodname', "main");
err3.Summary();
disp("Error 4");
err4 = Error('pathprefix', "/src", "filename", "Test_Error.cpp", 'classname', "Main", 'methodname', "main");
err4.Summary();

disp("Error 6");
err6 = Error('pathprefix', "/src/", "filename", "Test_Error.cpp", 'classname', "Main", 'methodname', "main(");
err6.SetType2MemoryShortage();
err6.Summary();

disp("Error 7");
err7 = Error('pathprefix', "/src/", "filename", "Test_Error.cpp", 'classname', "Main",  'methodname', "main(", 'msg', "message");
err7.SetType2MemoryShortage();
err7.Summary();