#pragma once
#ifndef __TOOLBOX_FILEMANAGER_H
    #define __TOOLBOX_FILEMANAGER_H
    // headers
    #if defined WIN32 || defined _WIN32 || defined _WIN64
        #include <io.h>
        #include <direct.h> 
    #else
        #include <unistd.h>
        #include <sys/stat.h>
    #endif
    #include <string.h>                 // support memset()
    #include <string>
    #include <fstream>
    // macros
    #if defined WIN32 || defined _WIN32 || defined _WIN64
        #define ACCESS(fileName,accessMode) _access(fileName,accessMode)
        #define MKDIR(path) _mkdir(path)
    #else
        #define ACCESS(fileName,accessMode) access(fileName,accessMode)
        #define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
    #endif
    // constants
    #define __TOOLBOX_FILEMANAGER_PATH_LEN_MAX 2048
    
    namespace Toolbox {
        class FileManager {
        private:
            void _AddCSVDataSeparator(bool isLast) {
                if (isLast) {
                    this->file << '\n';
                }
                else {
                    this->file << ',';
                }
            };

        protected:
            std::fstream file;                             // the file object
        public:
            /**
             * check whether a file exist or not
             * <INPUT> (v1)
             * @pathPrefix:     the path of the prefix
             * @fileName:       the file name
             * <INPUT> (v2)
             * @filePath:       the file paht
             */
            static bool IsFolderOrFileExist(const char * pathPrefix, const char * fileName) {
                if (!pathPrefix || !fileName) {
                    return false;
                }
                else {
                    std::string strPathPrefix = pathPrefix;
                    std::string strFileName = fileName;
                    return IsFolderOrFileExist(strPathPrefix, strFileName);
                }
            }
            static bool IsFolderOrFileExist(std::string & pathPrefix, std::string & fileName) {
                if (pathPrefix.back() != '\\' && pathPrefix.back() != '/') {
                    pathPrefix.append("/");
                }
                std::string filePath = pathPrefix + fileName;
                return IsFolderOrFileExist(filePath);
            }
            static bool IsFolderOrFileExist(std::string & filepath) {
                return IsFolderOrFileExist(filepath.c_str());
            }
            static bool IsFolderOrFileExist(const char * filepath) {
                if (!filepath) {
                    return false;
                }
                else {
                    return ACCESS(filepath, 0) == 0;
                }
            }

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
            static int CreatePath(const char* chrOriginPath) {
                if (!chrOriginPath) {
                    return 401;
                }
                else {
                    std::string strOriginPath = chrOriginPath;
                    return FileManager::CreatePath(strOriginPath);
                }
            };
            static int CreatePath(const std::string& strOriginPath) {
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
                else if (pathLen > __TOOLBOX_FILEMANAGER_PATH_LEN_MAX) {
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
            int Open(const char* path, bool isOverWritten = false) {
                if (!path) {
                    return 401;
                }
                else {
                    std::string strPath = path;
                    return this->Open(strPath, isOverWritten);
                }
            };
            int Open(const std::string& path, bool isOverWritten = false) {
                // init variables
                int ret = 200;

                // check whether the path is illegal
                if (path.length() == 0) {
                    ret = 402;
                }
                else if (path.length() > __TOOLBOX_FILEMANAGER_PATH_LEN_MAX) {
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
             * close
             */
            void Close() {
                this->file.close();
            };

            /**
             * add a CSV item
             * @ptrData:    the pointer of data
             * @isLast:     whether this data is the last of this line
             */
            void AddCSVItem(char data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(char * data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(const char * data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(std::string data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(int data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(unsigned int data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(float data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }
            void AddCSVItem(double data, bool isLast = false) {
                this->file << data;
                this->_AddCSVDataSeparator(isLast);
            }

            /**
             * add a line of text
             */
            void AddTextLine(const char * text) {
                this->file << text << '\n';
            }
            void AddTextLine(std::string & text) {
                this->file << text << '\n';
            }
            void AddTextLine() {
                this->file << '\n';
            }
        };
    }
#endif