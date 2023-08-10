#ifndef _DEBUGLOGFILE_H_
#define _DEBUGLOGFILE_H_

#include <iostream>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

namespace DebugLogFile
{
    void OpenDebugFile(const std::wstring& szFilePath);
    void CloseDebugFile();
}

#endif // !_DEBUGLOGFILE_H_
