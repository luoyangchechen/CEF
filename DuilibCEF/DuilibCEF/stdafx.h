// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <atlstr.h>
#include <Shellapi.h>
#include <Shlobj.h>



// TODO: 在此处引用程序需要的其他头文件
#include "..\Duilib\UIlib.h"

using namespace DuiLib;



#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_ud.lib")
#       pragma comment(lib, "..\\Lib\\Debug\\libcef.lib")
//#       pragma comment(lib, "..\\Lib\\Debug\\cef_sandbox.lib")
#       pragma comment(lib, "..\\Lib\\Debug\\libcef_dll_wrapper.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_u.lib")
#       pragma comment(lib, "..\\Lib\\Release\\libcef.lib")
#       pragma comment(lib, "..\\Lib\\Release\\libcef_dll_wrapper.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib.lib")
#   endif
#endif