// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>


#include <stdio.h>
#include <tchar.h>
#include <winsock.h>

#include <string>

#include <process.h>
#include <iostream>
using namespace std;
#pragma  comment(lib, "ws2_32.lib")

#include "Standrad/vSynch.h"

#include "Data/HandleFunction.h"
#include "Data/ErrCode.h"
#include "Data/Macro.h"
#include "Data/MyString.h"
#include "Data/Sturct.h"

#include "Export/InterfaceExport.h"






