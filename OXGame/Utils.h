#ifndef _UTIL_H_
#define _UTIL_H_

#include "Game Design\Game.h"

#define	SAFE_DELETE(x)	{ if(x) { delete x; x = NULL; } }
#define	SAFE_ARRAY_DELETE(x) if(x) { delete[] x; x = NULL; }
#define DEF_CREATE_OBJECT(vector, class_type) { \
		class_type* pObject = new class_type; \
		vector.push_back(pObject); }

#pragma region ErrorTypes
#define NOT_ERROR 0

/* #define ERROR_TYPE 0x2ff[error_num]*/
#define ERROR_CONSOLE_GET_SCREEN_INFO 0x2ff0
#pragma endregion

template<class T>
inline void ClearVector(std::vector<T> &vec) 
{
	vec.clear();
	std::vector<T>().swap(vec);
}

inline void ConsoleSize(HANDLE hWndConsole, int* width, int* heigth)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
	{
		*width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
		*heigth = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
		SetLastError(NOT_ERROR);
	}
	else
	{
		*width = 0;
		*heigth = 0;
		SetLastError(ERROR_CONSOLE_GET_SCREEN_INFO);
	}
}

inline void WindowToConsoleCoords(int windowX, int windowY, int* consoleX, int* consoleY)
{
	RECT rect;
	GameManager* pManager = GameManager::getSingleton();
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	int windowWidth = rect.right - rect.left;
	int windowHeigth = rect.bottom - rect.top;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);

	float persentW = (float)windowX / windowWidth;
	float persentH = (float)windowY / windowHeigth;

	*consoleX = (int)(persentW * (info.srWindow.Right - info.srWindow.Left));
	*consoleY = (int)(persentH * (info.srWindow.Bottom - info.srWindow.Top));
}

inline void ConsoleToWindowCoords(int consoleX, int consoleY, int* windowX, int* windowY)
{
	RECT rect;
	GameManager* pManager = GameManager::getSingleton();
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);

	int bufferWidth = info.srWindow.Right - info.srWindow.Left;
	int bufferHeigth = info.srWindow.Bottom - info.srWindow.Top;
	int windowWidth = rect.right - rect.left;
	int windowHeigth = rect.bottom - rect.top;

	float persentW = (float)consoleX / bufferWidth;
	float persentH = (float)consoleY / bufferHeigth;

	*windowX = (int)(persentW * windowWidth);
	*windowY = (int)(persentH * windowHeigth);
}

inline int WindowToConsoleX(int windowX)
{
	RECT rect;
	GameManager* pManager = GameManager::getSingleton();
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	int windowWidth = rect.right - rect.left;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);

	float persentW = (float)windowX / windowWidth;

	return (int)(persentW * (info.srWindow.Right - info.srWindow.Left));
}

inline int ConsoleToWindowX(int consoleX)
{
	RECT rect;
	GameManager* pManager = GameManager::getSingleton();
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);

	int bufferWidth = info.srWindow.Right - info.srWindow.Left;
	int windowWidth = rect.right - rect.left;

	float persentW = (float)consoleX / bufferWidth;
	return (int)(persentW * windowWidth);
}

inline int WindowToConsoleY(int windowY)
{
	RECT rect;
	GameManager* pManager = GameManager::getSingleton();
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	int windowHeigth = rect.bottom - rect.top;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);

	float persentH = (float)windowY / windowHeigth;
	int result = (int)(persentH * (info.srWindow.Bottom - info.srWindow.Top));
	return result == 0 ? 1 : result;
}

inline int ConsoleToWindowY(int consoleY)
{
	RECT rect;
	GameManager* pManager = GameManager::getSingleton();
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);

	int bufferHeigth = info.srWindow.Bottom - info.srWindow.Top;
	int windowHeigth = rect.bottom - rect.top;

	float persentH = (float)consoleY / bufferHeigth;
	int result = (int)(persentH * windowHeigth);
	return result == 0 ? 1 : result;
}

inline int GetCenterBufferLine()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GameManager* pManager = GameManager::getSingleton();
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);
	return ConsoleToWindowX(info.srWindow.Right - info.srWindow.Left) / 2;
}

inline int GetCenterBufferColoumn()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GameManager* pManager = GameManager::getSingleton();
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);
	return ConsoleToWindowY(info.srWindow.Bottom - info.srWindow.Top) / 2;
}

inline int GetÑonsoleBottomBuffer()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GameManager* pManager = GameManager::getSingleton();
	GetConsoleScreenBufferInfo(pManager->getConsoleHandle(), &info);
	return info.srWindow.Bottom - info.srWindow.Top;
}

inline char* DublicateSymbol(char* s, int count)
{
	char* temp = new char[(strlen(s) * count) + 1];
	for (char i = 0; i < count; i++)
		memcpy(temp + i * strlen(s), s, strlen(s));

	temp[strlen(s) * count] = 0x00;
	return temp;
}
#endif //!_UTIL_H_