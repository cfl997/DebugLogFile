#include "DebugLogFile.h"

#define USE_WCOUT

#ifdef USE_WCOUT
#define USE_COUT
#else
#define USE_COUT
#endif // USE_WCOUT

namespace DebugLogFile
{
	std::wfilebuf* g_pDebugFileBuf_w = nullptr; // std::wcout
	std::filebuf* g_pDebugFileBuf = nullptr; // std::cout

	std::wstreambuf* originalWcoutBuffer = nullptr; // 原始宽字符输出缓冲区
	std::streambuf* originalCoutBuffer = nullptr; // 原始窄字符输出缓冲区

	void OpenDebugFile(const std::wstring & szFilePath)
	{
		std::wstring strFileName;
		if (szFilePath.empty()) {
			return;
		}

		std::time_t now = std::time(nullptr);
		std::tm timeInfo;
#ifdef _WIN32
		localtime_s(&timeInfo, &now);
#else
		localtime_r(&now, &timeInfo);
#endif

		std::wstringstream ss;
		ss << szFilePath;
		ss << L"/CGTIMERender2D";
		ss << std::put_time(&timeInfo, L"%Y%m%d");
		ss << L".log";
		strFileName = ss.str();

#ifdef USE_WCOUT
		g_pDebugFileBuf_w = new std::wfilebuf;
		if (!g_pDebugFileBuf_w->open(strFileName.c_str(), std::ios::out | std::ios::app)) {
			delete g_pDebugFileBuf_w;
			g_pDebugFileBuf_w = nullptr;
			return;
		}
		// 保存原始的宽字符输出缓冲区并重定向
		originalWcoutBuffer = std::wcout.rdbuf();
		std::wcout.rdbuf(g_pDebugFileBuf_w);
#endif //USE_WCOUT

#ifdef USE_COUT
		g_pDebugFileBuf = new std::filebuf;
		if (!g_pDebugFileBuf->open(strFileName.c_str(), std::ios::out | std::ios::app)) {
			delete g_pDebugFileBuf;
			g_pDebugFileBuf = nullptr;
			return;
		}
		// 保存原始的窄字符输出缓冲区并重定向
		originalCoutBuffer = std::cout.rdbuf();
		std::cout.rdbuf(g_pDebugFileBuf);

		std::cout << timeInfo.tm_hour << ":" << timeInfo.tm_min << ":" << timeInfo.tm_sec << std::endl;
#endif //USE_COUT
	}

	void CloseDebugFile()
	{
#ifdef USE_WCOUT
		// 还原宽字符输出
		if (originalWcoutBuffer) {
			std::wcout.rdbuf(originalWcoutBuffer);
			originalWcoutBuffer = nullptr;
		}

		if (g_pDebugFileBuf_w) {
			g_pDebugFileBuf_w->close();
			delete g_pDebugFileBuf_w;
			g_pDebugFileBuf_w = nullptr;
		}
#endif //USE_WCOUT

#ifdef USE_COUT
		// 还原窄字符输出
		if (originalCoutBuffer) {
			std::cout.rdbuf(originalCoutBuffer);
			originalCoutBuffer = nullptr;
		}

		if (g_pDebugFileBuf) {
			g_pDebugFileBuf->close();
			delete g_pDebugFileBuf;
			g_pDebugFileBuf = nullptr;
		}
#endif //USE_COUT
	}
}
