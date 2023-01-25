#pragma once
#ifndef __FILEMANAGER_H
    #define __FILEMANAGER_H
    #ifdef WIN32
        #include <io.h>
        #include <direct.h> 
    #else
        #include <unistd.h>
        #include <sys/stat.h>
    #endif

    #include <stdint.h>
    #include <string>
    #define MAX_PATH_LEN 2048

    #ifdef WIN32
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
            // duplicate the path into a temporary parameter
            std::string path = strOriginPath;
            // check whether the path has too many characters
            uint32_t pathLen = path.length();
            if (pathLen > MAX_PATH_LEN) {
                return -2;
            }
            // create all folders
            char pathTmp[pathLen + 1] = { 0 };
            for (uint32_t i = 0; i < pathLen; ++i) {
                pathTmp[i] = path[i];
                if (pathTmp[i] == '\\' || pathTmp[i] == '/') {
                    // create when it does not exist
                    if (ACCESS(pathTmp, 0) != 0) {
                        int32_t ret = MKDIR(pathTmp);
                        if (ret != 0)
                        {
                            return -1;
                        }
                    }
                }
            }
            return 1;
        }

        /**
         * write a 
         */
        int static write2CSV(){

        }
    };
#endif