#include "logger.h"
#include "../Worldmodel/worldmodel.h"

extern WorldModel wm;

Logger::Logger(string const & fn)
{
	///cout<<" initmyfilestream"<<endl;
///	fileName=fn;
	fatherDir = "./log/nowlog/";
	isEnabled = true;
}

void Logger::SetEnable(bool set)
{
	isEnabled = set;
}

bool Logger::IsLogFileOpened()
{
	return isEnabled;
}

void Logger::OpenFileStream(string const & fn)
{
	///cout<<" openmyfilestream"<<endl;
	fileName = fn;
	if (isEnabled == true)
	{
		outStream.open((fatherDir + fn).c_str());
		outStream << ">>>>>>>>>>>>>>>>>>>>>log file start<<<<<<<<<<<<<<<<<<<<<<"
				<< endl;
	}
}

void Logger::OpenFileStream()
{
	if (isEnabled == true)
	{
		outStream.open((fatherDir + fileName).c_str());
		outStream << ">>>>>>>>>>>>>>>>>>>>>log file start<<<<<<<<<<<<<<<<<<<<<<"
				<< endl;
	}
}

void Logger::CloseFileStream()
{
	if (IsLogFileOpened() == true)
	{
		outStream
				<< ">>>>>>>>>>>>>>>>>>>>>end of log file<<<<<<<<<<<<<<<<<<<<<<"
				<< endl;
		outStream.clear();
		outStream.close();
	}
}

void Logger::DoLogByString(string const& sourceFileName, string const& info)
{
	if (IsLogFileOpened() == true)
	{
		///outStream<<"current game time:"<<wm.GetCurrentGameTime()<<" --> "<<sourceFileName<<": "<<info<<endl<<endl;
//		if(wm.GetMyNumber()==2)
		outStream << sourceFileName << info << endl;
	}
}

void Logger::DoLogByFormatting(string const& sourceFileName, char const* format, ...)
{
	if(IsLogFileOpened() == true)
	{
		///	static char formattedString[1024];
		static char formattedString[2048];
		va_list arguPtr;
		va_start(arguPtr, format);
		vsnprintf(&formattedString[0], sizeof(formattedString), format, arguPtr);
		va_end(arguPtr);
		DoLogByString(sourceFileName,&formattedString[0]);
	}
}

void Logger::ClearLog()
{
	outStream.clear();
}

void Logger::Flush()
{
	outStream.flush();
}
