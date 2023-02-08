#pragma once
#ifndef __TOOLBOX_ERROR_H
	#include <string.h>
	#define __TOOLBOX_ERROR_H
	#define __TOOLBOX_ERR_STR_MAX_LEN					1024		// the maximal length for a string
	#define __TOOLBOX_ERR_ILLEGAL_PARAMETERS			400			// error - illegal parameters
	#define __TOOLBOX_ERR_MEMORY_SHORTAGE				406			// error - not enough memory
	#define __TOOLBOX_ERR_INTERNAL						500			// error - cannot create this exception
	namespace Toolbox {
		class Error {
		private:
			unsigned int code = 0;									// error code
			char* loc = NULL;										// the location: `[prefix]/[filename] [classname]::[methodname]`
			unsigned int locLen = 0;
			char* msg = NULL;										// user defined message
			unsigned int msgLen = 0;
			// clean the assigend memory
			void Clear() {
				if (this->loc) {
					delete[] this->loc;
				}
				if (this->msg) {
					delete[] this->msg;
				}
				this->locLen = 0;
				this->msgLen = 0;
			}
			// set the location `[prefix]/[filename] [classname]::[methodname]`
			void SetLoc(const char* filePathPrefix, const char* filename, const char * classname, const char * methodname) {
				// get string length
				unsigned int filePathPrefixLen	= filePathPrefix ? strnlen(filePathPrefix, __TOOLBOX_ERR_STR_MAX_LEN): 0;
				unsigned int filenameLen		= filename ? strnlen(filename, __TOOLBOX_ERR_STR_MAX_LEN): 0;
				unsigned int classnameLen		= classname ? strnlen(classname, __TOOLBOX_ERR_STR_MAX_LEN): 0;
				unsigned int methodnameLen		= methodname ? strnlen(methodname, __TOOLBOX_ERR_STR_MAX_LEN) : 0;
				// check whether we need to add an extra separator
				bool needPathSeparator = !(filePathPrefixLen > 0 && (filePathPrefix[filePathPrefixLen - 1] == '/' || filePathPrefix[filePathPrefixLen - 1] == '\\'));
				bool needSpace = classnameLen > 0 || methodnameLen > 0;
				bool needClassMethodSeparator = classnameLen > 0 && methodnameLen > 0;
				bool needMethodParentheses = methodnameLen > 1 && methodname[methodnameLen - 2] != '(' && methodname[methodnameLen - 2] != ')' && methodname[methodnameLen - 1] != '(' && methodname[methodnameLen - 1] != ')';
				// calculate the memory cost
				this->locLen = filePathPrefixLen + filenameLen + classnameLen + methodnameLen + 1;	// 1 extra for '\0'
				if (needPathSeparator) { ++(this->locLen); }
				if (needSpace) { ++(this->locLen); }
				if (needClassMethodSeparator){ this->locLen = this->locLen + 2; }
				if (needMethodParentheses) { this->locLen = this->locLen + 2; }
				// memory allocate & copy
				try {
					this->loc = new char[this->locLen];
					memset(this->loc, 0, this->locLen);				// init all with '\0'
					// copy
					if (filePathPrefixLen) { strncat_s(this->loc, this->locLen, filePathPrefix, __TOOLBOX_ERR_STR_MAX_LEN); }		// copy - filePathPrefix
					if (needPathSeparator) { strncat_s(this->loc, this->locLen, "/", 2); }											// copy - '/'
					if (filenameLen) { strncat_s(this->loc, this->locLen, filename, __TOOLBOX_ERR_STR_MAX_LEN); }					// copy - filename
					if (needSpace) { strncat_s(this->loc, this->locLen, " ", __TOOLBOX_ERR_STR_MAX_LEN); }							// copy - ' '
					if (classnameLen) { strncat_s(this->loc, this->locLen, classname, __TOOLBOX_ERR_STR_MAX_LEN); }					// copy - classname
					if (needClassMethodSeparator) { strncat_s(this->loc, this->locLen, "::", 3); }									// copy - "::"
					if (methodnameLen) { strncat_s(this->loc, this->locLen, methodname, __TOOLBOX_ERR_STR_MAX_LEN); }				// copy - methodname
					if (needMethodParentheses) { strncat_s(this->loc, this->locLen, "()", 3); }										// copy - "()"
				}
				catch (const std::bad_alloc& e) {
					this->Clear();
					throw Error(__TOOLBOX_ERR_INTERNAL);
				}
			}
			// set the message
			void SetMsg(const char* msg) {
				if (msg) {
					this->msgLen = strnlen(msg, __TOOLBOX_ERR_STR_MAX_LEN);
					if (this->msgLen > 0) {
						++(this->msgLen);
						try {
							this->msg = new char[this->msgLen];
							memset(this->msg, 0, this->msgLen);
							strcpy_s(this->msg, this->msgLen-1, msg);		// copy - the last one is set to '\0'
						}
						catch (std::bad_alloc) {
							this->Clear();
							throw Error(__TOOLBOX_ERR_INTERNAL);
						}
					}
				}
			}
		public:
			/**
			 * Constructor
			 * @filePathPrefix: the file path prefix (NULL for root files)
			 * @filename:		the name of the file
			 * @classname:		the classname
			 * @methodname:		the method/function name
			 * @msg:			the message
			 */
			Error(const char* filePathPrefix, const char* filename, const char* classname, const char* methodname, const char* msg) {
				this->SetLoc(filePathPrefix, filename, classname, methodname);
				this->SetMsg(msg);
			};
			Error(const char* filePathPrefix, const char* filename, const char* classname, const char* methodname) {
				this->SetLoc(filePathPrefix, filename, classname, methodname);
			};
			Error(const char* filePathPrefix, const char* filename, const char* functionname) {
				this->SetLoc(filePathPrefix, filename, NULL, functionname);
			};
			/**
			 * Constructor
			 * @code:			the error code 
			 */
			Error(unsigned int code) {
				this->code = code;
			}
			~Error() {
				this->Clear();
			}
			/*** Set Types ***/
			void SetType2IllegalParameters() {
				this->code = __TOOLBOX_ERR_ILLEGAL_PARAMETERS;
			}
			void SetType2MemoryShortage() {
				this->code = __TOOLBOX_ERR_MEMORY_SHORTAGE;
			}

			/**
			 * Summary
			 */
			void Summary() {
				printf("%u - ", this->code);
				if (this->loc) {
					printf("%s ", this->loc);
				}
				if (this->msg) {
					printf("%s ", this->msg);
				}
				printf("\n");
			}
		};
	}
#endif