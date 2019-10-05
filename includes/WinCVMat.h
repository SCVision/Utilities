// WinCVMat.h
//
// Windows interface for Mat object of openCV
// by Lin, Jingyu, linjy02@hotmail.com, 2016.08
//
#ifndef WinCVMat_H
#define WinCVMat_H

//#include "opencv/cv.h"
//#include "opencv/highgui.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define WinCVMatExport extern "C" __declspec(dllexport)

/****************************************************************/
/*                     File IO                                  */
/****************************************************************/
// 功能：将二维多通道数组按照行保存为文本文件。这样便于在MATLAB中进一步分析。
// 输入：filename - 文本文件名。mat - 源数组。
// 输出：数据写入文本文件。
// 返回值：文本行数。
// 说明：文本文件的一行为数组的一行，一行数据用逗号分隔，格式如下：
//       第一列通道1，第一列通道2，...，第一列通道K，第二列通道1，...，第N列通道K。
WinCVMatExport int __stdcall SaveMatToText(const char* filename, const cv::Mat& mat);

// 功能：从文本文件读取二维多通道数组数据。文件可来源于MATLAB命令：save '文件名' 变量名 -ascii -double。
// 输入：filename - 文本文件名。mat - 获取数据的数组，其行数、列数、通道数规定了文本文件的格式。
// 输出：mat - 获取从文本文件读取的数据。数据不足则填0。
// 返回值：文本行数。
// 说明：文本文件的一行为数组的一行，一行数据用逗号、分号、“|”或空白分隔，格式如下：
//       第一列通道1，第一列通道2，...，第一列通道K，第二列通道1，...，第N列通道K。
WinCVMatExport int __stdcall LoadMatFromText(const char* filename, cv::Mat& mat);

/****************************************************************/
/*                     Bitmap Display                           */
/****************************************************************/
// ShowCVMat和ShowCVMat2显示整个图像，保持图像宽高比。前者占用整个窗口，后者可以改变显示位置。
// ShowCVMatEx可实现多种显示方式。

// 功能：在指定窗口的整个可视区域显示整个二维矩阵（矩阵图像保持图像宽高比）。仅支持1~4通道数组。
// 输入：hwnd - 用于显示矩阵的窗口。mat - 二维矩阵数据。
//       minVal, maxVal - 矩阵元素的下界和上界，超过下界的数值转化为最小强度值，超过上界的数值转化为最大强度值。
//       TopDown - 矩阵图像是否自上而下。1表示矩阵第一行对应图像顶部，0表示矩阵第一行对应图像底部。
// 说明：频繁显示应使用数据类型为8bit（即CV_8U或CV_8S）的矩阵（不需要数据转换，不需要minVal和maxVal）。
WinCVMatExport void _stdcall ShowCVMat(HWND hwnd, const cv::Mat& img, double minVal, double maxVal, int TopDown);

// 功能：在指定窗口的指定矩形显示整个二维矩阵（矩阵图像保持图像宽高比）。仅支持1~4通道数组。
// 输入：hwnd - 用于显示矩阵的窗口。rectWin - 窗口中用于显示的区域。mat - 二维矩阵数据。
//       minVal, maxVal - 矩阵元素的下界和上界，超过下界的数值转化为最小强度值，超过上界的数值转化为最大强度值。
//       TopDown - 矩阵图像是否自上而下。1表示矩阵第一行对应图像顶部，0表示矩阵第一行对应图像底部。
// 说明：频繁显示应使用数据类型为8bit（即CV_8U或CV_8S）的矩阵（不需要数据转换，不需要minVal和maxVal）。
WinCVMatExport void _stdcall ShowCVMat2(HWND hwnd, const RECT& rectDest, const cv::Mat& img, double minVal, double maxVal, int TopDown);

// 功能：在指定窗口的指定矩形显示二维矩阵的指定范围。仅支持1~4通道矩阵。矩阵图像自上而下，即矩阵第一行对应图像顶部。
// 输入：hwnd - 用于显示矩阵的窗口。rectWin - 窗口中用于显示的区域。
//       mat - 二维矩阵数据。rectMat - 矩阵中用于显示的区域（不是图像区域）。
//       minVal, maxVal - 矩阵元素的下界和上界，超过下界的数值转化为最小强度值，超过上界的数值转化为最大强度值。
//       mirror - 镜像显示：0显示原图像，1左右镜像，2上下镜像，3上下左右镜像。
//       dwRop - 光栅操作码，取值参阅BitBlt，常用值如下：
//#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
//#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
//#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
//#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
//#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
//#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
//#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
//#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
//#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
//#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
//#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
//#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
//#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
//#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
//#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */
// 说明：频繁显示应使用数据类型为8bit（即CV_8U或CV_8S）的矩阵（不需要数据转换，不需要minVal和maxVal）。
WinCVMatExport void _stdcall ShowCVMatEx(HWND hwnd, const RECT& rectWin, const cv::Mat& img, const RECT& rectMat,
	double minVal, double maxVal, int mirror, DWORD dwRop = SRCCOPY);

#endif // #ifndef WinOpenCV_H
