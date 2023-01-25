#pragma once
#ifndef __FILEMANAGER_H
    #define __FILEMANAGER_H
    // headers
    #if defined WIN32 || defined _WIN32 || defined _WIN64
        #include <io.h>
        #include <direct.h> 
    #else
        #include <unistd.h>
        #include <sys/stat.h>
    #endif
    #include <stdio.h>
    #include <stdint.h>
    #include <string>
    // macros
    #define MAX_PATH_LEN 2048
    #if defined WIN32 || defined _WIN32 || defined _WIN64
        #define ACCESS(fileName,accessMode) _access(fileName,accessMode)
        #define MKDIR(path) _mkdir(path)
    #else
        #define ACCESS(fileName,accessMode) access(fileName,accessMode)
        #define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
    #endif

    class FileManager {
    protected:
        char * path = NULL;
    public:
        /**
         * create all folders along the path (the last part will be taken as a folder)
         * <INPUT>
         * @strOriginPath:  a path in string of <string>
         * <RETURN>
         * @-2:             the path length is too long
         * @-1:             one folder along this path cannot be created
         * @1:              all folders are created
         */
        int static createPath(const std::string& strOriginPath) {
            // init variables
            int ret = 1;                            // set the return value (the default is success)
            char * ptrPathTmp = NULL;               // set the temporary path pointer to null                      

            // duplicate the path into a temporary parameter
            std::string path = strOriginPath;
            // check whether the path has too many characters
            uint32_t pathLen = path.length();
            if (pathLen > MAX_PATH_LEN) {
                ret = -2;
            }
            else {
                // create all folders
                ptrPathTmp = new char[pathLen + 1];
                memset(ptrPathTmp, pathLen + 1, 0);
                for (uint32_t i = 0; i < pathLen; ++i) {
                    ptrPathTmp[i] = path[i];
                    if (ptrPathTmp[i] == '\\' || ptrPathTmp[i] == '/') {
                        // create when it does not exist
                        if (ACCESS(ptrPathTmp, 0) != 0) {
                            int32_t retMKDIR = MKDIR(ptrPathTmp);
                            // turn off creating if one folder cannot be created
                            if (retMKDIR != 0){
                                ret = -1;
                                break;
                            }
                        }
                    }
                }
            }
            // reset memory
            if (ptrPathTmp) {
                delete[] ptrPathTmp;
            }
            // return
            return ret;
        }

        /**
         * write a 
         */
        int static write2CSV(){

        }
    };
#endif