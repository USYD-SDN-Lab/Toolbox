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
    #include <fstream>
#include <iostream>
    // macros
    #if defined WIN32 || defined _WIN32 || defined _WIN64
        #define ACCESS(fileName,accessMode) _access(fileName,accessMode)
        #define MKDIR(path) _mkdir(path)
    #else
        #define ACCESS(fileName,accessMode) access(fileName,accessMode)
        #define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
    #endif
    
    namespace Toolbox {
        class FileManager {
        private:
            void addCSVDataSeparator(bool isLast) {
                if (isLast) {
                    this->file << '\n';
                }
                else {
                    this->file << ',';
                }
            };

        protected:
            const static size_t PATH_LEN_MAX;               // max path length
            std::fstream file;                             // the file object
        public:
            /**
             * create all folders along the path (the last part will be taken as a folder)
             * <INPUT>
             * @strOriginPath:  a path in string of <string>
             * <RETURN>
             * @401:             the path pointer is NULL
             * @402:             the path length is 0
             * @403:             the path length is too long
             * @404:             one folder along this path cannot be created
             * @200:             all folders are created
             */
            int static createPath(const char* chrOriginPath) {
                if (!chrOriginPath) {
                    return 401;
                }
                else {
                    std::string strOriginPath = chrOriginPath;
                    return FileManager::createPath(strOriginPath);
                }
            };
            int static createPath(const std::string& strOriginPath) {
                // init variables
                int ret = 200;                          // set the return value (the default is success)
                char* ptrPathTmp = NULL;               // set the temporary path pointer to null                      

                // duplicate the path into a temporary parameter
                std::string path = strOriginPath;
                // check whether the path is illegal
                size_t pathLen = path.length();
                if (pathLen == 0) {
                    ret = 402;
                }
                else if (pathLen > FileManager::PATH_LEN_MAX) {
                    ret = 403;
                }
                else {
                    // if the last character is not the separator, add it
                    if (path.back() != '\\' && path.back() != '/') {
                        path.append("/");
                        pathLen = path.length();    // recalculate the path length
                    }
                    // create all folders
                    ptrPathTmp = new char[pathLen + 1];
                    memset(ptrPathTmp, '\0', (pathLen + 1));
                    for (uint32_t i = 0; i < pathLen; ++i) {
                        ptrPathTmp[i] = path[i];
                        if (ptrPathTmp[i] == '\\' || ptrPathTmp[i] == '/') {
                            // create when it does not exist
                            if (ACCESS(ptrPathTmp, 0) != 0) {
                                int32_t retMKDIR = MKDIR(ptrPathTmp);
                                // turn off creating if one folder cannot be created
                                if (retMKDIR != 0) {
                                    ret = 404;
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
            };


            /**
             * <INPUT>
             * @path:               the file path
             * @isOverWritten:      whether overwrite this file (default: false)
             * <RETURN>
             * @401:                the path is NULL
             * @402:                the path length is 0
             * @403:                the path length is too long
             * @404:                the file of the path cannot be open
             * @200:                the file is open
             */
            int open(const char* path, bool isOverWritten = false) {
                if (!path) {
                    return 401;
                }
                else {
                    std::string strPath = path;
                    return this->open(strPath, isOverWritten);
                }
            };
            int open(const std::string& path, bool isOverWritten = false) {
                // init variables
                int ret = 200;

                // check whether the path is illegal
                if (path.length() == 0) {
                    ret = 402;
                }
                else if (path.length() > FileManager::PATH_LEN_MAX) {
                    ret = 403;
                }
                else {
                    try {
                        if (isOverWritten) {
                            this->file.open(path, std::fstream::in | std::fstream::out);
                        }
                        else {
                            this->file.open(path, std::fstream::in | std::fstream::app);
                        }
                        if (!this->file.is_open()) {
                            ret = 404;
                        }
                    }
                    catch (std::ios_base::failure e) {
                        ret = 404;
                    }
                }
                // return
                return ret;
            };

            /**
             * add a CSV item
             * @ptrData:    the pointer of data
             * @isLast:     whether this data is the last of this line
             */
            void addCSVItem(char data, bool isLast = false) {
                this->file << data;
                this->addCSVDataSeparator(isLast);
            }
            void addCSVItem(char * data, bool isLast = false) {
                this->file << data;
                this->addCSVDataSeparator(isLast);
            }
            void addCSVItem(std::string data, bool isLast = false) {
                this->file << data;
                this->addCSVDataSeparator(isLast);
            }
            void addCSVItem(int data, bool isLast = false) {
                this->file << data;
                this->addCSVDataSeparator(isLast);
            }
            void addCSVItem(float data, bool isLast = false) {
                this->file << data;
                this->addCSVDataSeparator(isLast);
            }
            void addCSVItem(double data, bool isLast = false) {
                this->file << data;
                this->addCSVDataSeparator(isLast);
            }
            /**
             * close
             */
            void close() {
                this->file.close();
            };

        };
        // initialise static members
        // static members cannot be initialised inside a class but only outside
        const size_t FileManager::PATH_LEN_MAX = 2048;
    }
#endif