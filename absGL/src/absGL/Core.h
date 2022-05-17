#pragma once

#ifdef ABSGL_BUILD_DLL
#define ABSGL_API __declspec(dllexport)
#else
#define ABSGL_API __declspec(dllimport)
#endif