#include "Logger.h"
#include <stdarg.h>
#include <fstream>

const int LOG_STR_LENGTH = 2048;
static std::ofstream::ios_base::openmode g_openMode = std::ofstream::ios_base::out;

void Assert(bool assert, const char* file, int line) //, const char* format, ...)
{
	if (assert == false)
	{
		std::ofstream outFile("projectKT.log.txt", g_openMode);
		if (g_openMode == std::ofstream::ios_base::out)
			g_openMode |= std::ofstream::ios_base::app;

		char temp[LOG_STR_LENGTH];
		sprintf_s(temp, "assert fail: file[%s], line[%d]", file, line);
		outFile << temp << std::endl;

		/*va_list arg;
		va_start(arg, format);
		sprintf_s(temp, format, arg);
		va_end(arg);

		outFile << temp << std::endl;*/
		outFile.close();
	}
}

void Log(const char* format, ...) 
{
	std::ofstream outFile("projectKT.log.txt", g_openMode);
	if (g_openMode == std::ofstream::ios_base::out)
		g_openMode |= std::ofstream::ios_base::app;

	char temp[LOG_STR_LENGTH];
	va_list arg;
	va_start(arg, format);
	sprintf_s(temp, format, arg);
	va_end(arg);

	outFile << temp << std::endl;
	outFile.close();
}