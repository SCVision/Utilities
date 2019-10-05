// ImageMatrix.h
//
// Tools for matrix of images
// by Lin, Jingyu, linjy02@hotmail.com, 2016.08
//
#ifndef ImageMatrix_H
#define ImageMatrix_H

#include <windows.h>

#define ImageMatrixExport extern "C" __declspec(dllexport)

/****************************************************************/
/*                     File IO                                  */
/****************************************************************/
// 功能：将二维矩阵保存为文本文件，一行数据用逗号分隔。这样便于在MATLAB中进一步分析。
// 输入：filename - 文本文件名。mat[height][width] - 源矩阵，数据类型取决于mat_type。
//       mat_type - 数据类型，0~9: double (缺省类型), int, unsigned int, char (8 bit), unsigned char(8 bit), 
//                  short (16 bit), unsigned short (16 bit), long (32 bit), unsigned long (32 bit), float。
// 输出：数据写入文本文件。
/* 说明：将一幅图像（h*w*c）按行保存为矩阵文本，用MATLAB读取的例子如下
dat = importdata('test24bit.txt'); % 导入数据（h*cw）
c = 3; % 定义图像的通道数
[h, w] = size(dat); w = w/c; % 定义图像的宽度和高度
dat = reshape(dat,h,c,w); % 转换为三维矩阵
img = permute(dat,[1 3 2])/255; % 转换为h*w*c并归一化强度。
img = img(end:-1:1,:,end:-1:1); % BGR转换为RGB，并上下翻转使得第一行在下
figure(1); image(img)
*/
ImageMatrixExport void __stdcall SaveMatrixToText(char *filename, void *mat, int width, int height, int mat_type);
ImageMatrixExport void __stdcall SaveDoubleMatrixToText(char *filename, double *mat, int width, int height);
ImageMatrixExport void __stdcall SaveIntMatrixToText(char *filename, int *mat, int width, int height);
ImageMatrixExport void __stdcall SaveByteMatrixToText(char *filename, BYTE *mat, int width, int height);

// 功能：从文本文件读取二维矩阵。文本文件的一行为矩阵的行，一行数据用逗号、分号、“|”或空白分隔。
// 输入：filename - 文本文件名。mat[height][width] - 源矩阵缓冲区，数据类型取决于mat_type。
//       mat_type - 数据类型，0~9: double (缺省类型), int, unsigned int, char (8 bit), unsigned char(8 bit), 
//                  short (16 bit), unsigned short (16 bit), long (32 bit), unsigned long (32 bit), float。
// 输出：mat[height][width] - 从文本文件读取的矩阵。
// 返回值：实际读取的行数，不大于height。
/* 说明：用MATLAB读取图像，然后保存为矩阵文本的例子如下
img = double(imread('test24bit.bmp'))/255; % 读取图像并归一化强度
img = permute(img,[1 3 2]); % 转换为h*c*w。
img = img(end:-1:1,end:-1:1,:); % RGB转换为BGR，并上下翻转使得第一行在下
[h, c, w] = size(img);  % 定义图像的高度、宽度和通道数
dat = reshape(img,h,c*w)*255; % 转换为二维矩阵
save('test24bit2.txt','dat','-ascii')
*/
ImageMatrixExport int __stdcall ReadMatrixFromText(char *filename, void *mat, int width, int height, int mat_type);
ImageMatrixExport int __stdcall ReadDoubleMatrixFromText(char *filename, double *mat, int width, int height);
ImageMatrixExport int __stdcall ReadIntMatrixFromText(char *filename, int *mat, int width, int height);
ImageMatrixExport int __stdcall ReadByteMatrixFromText(char *filename, BYTE *mat, int width, int height);

// 功能：读取一个BMP文件。仅支持彩色（16~32bit）和黑白（8bit）图像。
// 输入：filename - BMP文件名。bmi - 图像头缓冲区（40B图像头+4*256B调色板）。Dib[szDib] - 图像点阵缓冲区。
// 输出：bmi - 图像头信息。Dib[szDib] - 图像点阵数据。
// 返回值：实际读取的图像点阵字节数，不大于szDib。-1表示读取失败，0表示只读取图像头。
// 说明：图像的文件头格式为：BITMAPINFOHEADER结构（40B）+调色板（4*256B）。
//       8bit图像的调色板有256色，每种颜色是一个4字节的RGBQUAD结构。16~32bit图像没有调色板。
//       如果Dib为NULL，则只读取图像头bi[szBI]和图像点阵字节数pixelBytes。如果Dib[szDib]空间不足则点阵不完整。
ImageMatrixExport int __stdcall ReadBmpFile(char *filename, BITMAPINFO* bmi, BYTE *Dib, int szDib);

/****************************************************************/
/*                     Bitmap Display                           */
/****************************************************************/
// ShowBmp和ShowBmp2显示整个图像，保持图像宽高比。前者占用整个窗口，后者可以改变显示位置。
// ShowBmpEx可实现多种显示方式。

// 功能：在指定窗口的整个可视区域显示整个图像（保持图像宽高比）。
// 输入：hwnd - 用于显示图像的窗口。bmi - 图像头结构。pixels - 图像点阵。
ImageMatrixExport void __stdcall ShowBmp(HWND hwnd, const BITMAPINFO* bmi, const BYTE* pixels);

// 功能：在指定窗口的指定矩形显示整个图像（保持图像宽高比）。
// 输入：hwnd - 用于显示图像的窗口。rectDest - 窗口中用于显示的区域。bmi - 图像头结构。pixels - 图像点阵。
ImageMatrixExport void __stdcall ShowBmp2(HWND hwnd, const RECT& rectDest, const BITMAPINFO* bmi, const BYTE* pixels);

// 功能：在指定窗口的指定矩形显示图像的指定范围。
// 输入：hwnd - 用于显示图像的窗口。rectDest - 窗口中用于显示的区域。
//       bmi - 图像头结构。pixels - 图像点阵。rectSrc - 图像中用于显示的区域。
//       mirror - 镜像显示：0显示原图像，1左右镜像，2上下镜像，3上下左右镜像。
//       dwRop - 光栅操作码，取值参阅BitBlt，常用值如下：
//BLACKNESS: Fills the destination rectangle using the color associated with index 0 in the physical palette. (This color is black for the default physical palette.)
//CAPTUREBLT: Includes any windows that are layered on top of your window in the resulting image.By default, the image only contains your window.Note that this generally cannot be used for printing device contexts.
//DSTINVERT: Inverts the destination rectangle.
//MERGECOPY: Merges the colors of the source rectangle with the brush currently selected in hdcDest, by using the Boolean AND operator.
//MERGEPAINT: Merges the colors of the inverted source rectangle with the colors of the destination rectangle by using the Boolean OR operator.
//NOMIRRORBITMAP: Prevents the bitmap from being mirrored.
//NOTSRCCOPY: Copies the inverted source rectangle to the destination.
//NOTSRCERASE: Combines the colors of the source and destination rectangles by using the Boolean OR operator and then inverts the resultant color.
//PATCOPY: Copies the brush currently selected in hdcDest, into the destination bitmap.
//PATINVERT: Combines the colors of the brush currently selected in hdcDest, with the colors of the destination rectangle by using the Boolean XOR operator.
//PATPAINT: Combines the colors of the brush currently selected in hdcDest, with the colors of the inverted source rectangle by using the Boolean OR operator. The result of this operation is combined with the colors of the destination rectangle by using the Boolean OR operator.
//SRCAND: Combines the colors of the source and destination rectangles by using the Boolean AND operator.
//SRCCOPY: Copies the source rectangle directly to the destination rectangle.
//SRCERASE: Combines the inverted colors of the destination rectangle with the colors of the source rectangle by using the Boolean AND operator.
//SRCINVERT: Combines the colors of the source and destination rectangles by using the Boolean XOR operator.
//SRCPAINT: Combines the colors of the source and destination rectangles by using the Boolean OR operator.
//WHITENESS: Fills the destination rectangle using the color associated with index 1 in the physical palette. (This color is white for the default physical palette.)
ImageMatrixExport void __stdcall ShowBmpEx(HWND hwnd, const RECT& rectDest,
	const BITMAPINFO* bmi, const BYTE* pixels, const RECT& rectSrc, int mirror, DWORD dwRop = SRCCOPY);

/****************************************************************/
/*                     Matrix Display                           */
/****************************************************************/
// ShowMatrix和ShowMatrix2显示整个图像，保持图像宽高比。前者占用整个窗口，后者可以改变显示位置。
// ShowMatrixEx可实现多种显示方式。

// 功能：生成图像头结构bmi。
// 输入：bmi - 长度为1064字节的图像头结构缓冲区。chnpp、width、height - 图像通道数（1、3、4）、宽、高。
//       TopDown - 矩阵图像是否自上而下。1表示图像点阵第一行对应图像顶部，0表示图像点阵第一行对应图像底部。
// 输出：bmi - 图像头结构信息。
// 说明：bmi的结构为一个BITMAPINFOHEADER（40字节）和256个RGBQUAD结构（1024字节）。
ImageMatrixExport void __stdcall FillDibHead(BITMAPINFO* bmi, int chnpp, int width, int height, int TopDown);

// 功能：在指定窗口的整个可视区域显示整个二维矩阵（矩阵图像保持图像宽高比）。
// 输入：hwnd - 用于显示矩阵的窗口。mat[height][chnpp*width] - 二维矩阵数据。chnpp - 图像通道数（1、3、4）。
//       minVal, maxVal - 矩阵元素的下界和上界，超过下界的数值转化为0，超过上界的数值转化为255。
//       TopDown - 矩阵图像是否自上而下。1表示矩阵第一行对应图像顶部，0表示矩阵第一行对应图像底部。
// 说明：频繁显示应使用BYTE类型矩阵。
ImageMatrixExport void __stdcall ShowMatrix(HWND hwnd, const double* mat, int chnpp, int width, int height,
	double minVal, double maxVal, int TopDown);
ImageMatrixExport void __stdcall ShowByteMatrix(HWND hwnd, const BYTE* mat, int chnpp, int width, int height, 
	int TopDown);

// 功能：在指定窗口的指定矩形显示整个二维矩阵（矩阵图像保持图像宽高比）。
// 输入：hwnd - 用于显示矩阵的窗口。rectDest - 窗口中用于显示的区域。mat[height][chnpp*width] - 二维矩阵数据。
//       chnpp - 图像通道数（1、3、4）。minVal, maxVal - 矩阵元素的下界和上界，超过下界的数值转化为0，超过上界的数值转化为255。
//       TopDown - 矩阵图像是否自上而下。1表示矩阵第一行对应图像顶部，0表示矩阵第一行对应图像底部。
// 说明：频繁显示应使用BYTE类型矩阵。
ImageMatrixExport void __stdcall ShowMatrix2(HWND hwnd, const RECT& rectDest, const double* mat, int chnpp, int width, int height,
	double minVal, double maxVal, int TopDown);
ImageMatrixExport void __stdcall ShowByteMatrix2(HWND hwnd, const RECT& rectDest, const BYTE* mat, int chnpp, int width, int height, 
	int TopDown);

// 功能：在指定窗口的指定矩形显示二维矩阵的指定范围。仅支持1~4通道矩阵。矩阵图像自上而下，即矩阵第一行对应图像顶部。
// 输入：hwnd - 用于显示矩阵的窗口。rectDest - 窗口中用于显示的区域。mat[height][chnpp*width] - 二维矩阵数据。
//       chnpp - 图像通道数（1、3、4）。minVal, maxVal - 矩阵元素的下界和上界，超过下界的数值转化为0，超过上界的数值转化为255。
//       rectSrc - 矩阵中用于显示的区域。mirror - 镜像显示：0显示原图像，1左右镜像，2上下镜像，3上下左右镜像。
//       dwRop - 光栅操作码，取值说明参阅ShowBmpEx。
// 说明：rectMat是矩阵坐标而不是图像坐标。图像坐标原点是左下角，向上为正；矩阵坐标原点是左上角，向下为正。
// 说明：频繁显示应使用BYTE类型矩阵。
ImageMatrixExport void __stdcall ShowMatrixEx(HWND hwnd, const RECT& rectDest, const double* mat, int chnpp, int width, int height,
	double minVal, double maxVal, const RECT& rectSrc, int mirror, DWORD dwRop);
ImageMatrixExport void __stdcall ShowByteMatrixEx(HWND hwnd, const RECT& rectDest, const BYTE* mat, int chnpp, int width, int height,
	const RECT& rectSrc, int mirror, DWORD dwRop);

#endif // #ifndef ImageMatrix_H
