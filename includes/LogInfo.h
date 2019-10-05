// LogInfo.H
//
// log information to a txt file.
// by Lin, Jingyu, linjy02@hotmail.com, 2016.8
//
// C++ Demos:
// #include <strsafe.h>
// ...
// char buf[8192];
// char logFile = "demo.txt";
//
// // demo 1: log a simple string
// StringCbPrintfA(buf, sizeof(buf), "%d, %d, %d", s1, s2, s3);
// LogString(logFile, buf);
//
// // demo 2: log an array data[]
// StringCbPrintfA(buf, sizeof(buf), "%d", timeStamp);
// for (int i = 0; i < nData; ++i)
// {
//    size_t p = strlen(buf);
//    StringCbPrintfA(buf + p, sizeof(buf)-p, " %f", data[i]);
// }
// LogString(logFile, buf);
//

#ifndef LogInfo_H
#define LogInfo_H

#define LogInfoExport extern "C" __declspec(dllexport)

// 功能：在指定文本文件中记录信息及记录时间
LogInfoExport void __stdcall LogString(const char *filename, const char *infoString);

// 功能：在指定文本文件中记录最新错误信息及记录时间
LogInfoExport void __stdcall LogLastError(const char *filename);

#endif // #ifndef LogInfo_H
