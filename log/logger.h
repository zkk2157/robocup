#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <cstdarg>

using namespace std;

/**
 \file logger.h
 @author Leisland <leisland@163.com>
 */

/**
 \class logger is one of utils for our code,it can record the informatons of agent when the main loop is running.
 */

class Logger
{
public:
	/**construct function of class Log*/
	Logger(string const & fn);

	/**set the value of enable label
	 *\param set enable label of isEnabled
	 */
	void SetEnable(bool set);

	/**get the file stream state*/
	bool IsLogFileOpened();

	/**open the file stream
	 *\param fn the name of log file
	 */
	void OpenFileStream(string const & fn);

	/**open the file stream*/
	void OpenFileStream();

	/**close the file stream*/
	void CloseFileStream();

	/**write string information into the log file
	 *\param sourceFileName the name of source file which called this function
	 *\param info the logged information
	 */
	void DoLogByString(string const& sourceFileName, string const& info);

	/**formatted log function
	 *
	 * This function works just like fprint and may be used
	 * to place formatted strings in the logs.
	 * \param format The format string (first part of printf)
	 * \param ... The arguments (second part of printf)
	 */
	void DoLogByFormatting(string const& sourceFileName, char const* format, ...);

	/**clear eofbit and failbit set due to end-of-file*/
	void ClearLog();

	/**flush the log stream*/
	void Flush();

private:
	/**output file stream*/
	ofstream outStream;

	/**the name of log file*/
	string fileName;

	/**the father directory of log file*/
	string fatherDir;

	/**enable label of logger,only the value of isEnabled is true,the logger will record the informations*/
	bool isEnabled;
}; //end of class Log
#endif//end of LOGGER_H
