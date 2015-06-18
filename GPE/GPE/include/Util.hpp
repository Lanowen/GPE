#pragma once

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <Windows.h>

namespace Ogre {
	class Vector3;
}

namespace physx {
	class PxVec3;
}

namespace Util {

	template <class vect_to, class vect_from>
	inline vect_to vect_convert(vect_from inVect) {
		vect_to v;
		v.x = inVect.x;
		v.y = inVect.y;
		v.z = inVect.z;
		return v;
	}

	#pragma deprecated(vect_from_to)
	template <class vect1, class vect2>
	__declspec(deprecated("Use Util::vect_convert for implicit template recognition of second vector parameter"))inline vect2 vec_from_to(vect1 inVect)
	{
		vect2 v;
		v.x = inVect.x;
		v.y = inVect.y;
		v.z = inVect.z;
		return v;
	}

	template <class quat1, class quat2>
	inline quat2 quat_from_to(quat1 inQuat)
	{
		quat2 q;
		q.x = inQuat.x;
		q.y = inQuat.y;
		q.z = inQuat.z;
		q.w = inQuat.w;
		return q;
	}

static void ShowWin32Console() {
	static const WORD MAX_CONSOLE_LINES = 500;
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	// allocate a console for this app
	AllocConsole();
	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
								coninfo.dwSize);
	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);
	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();
}

static void DebugOutput(std::string message){
	OutputDebugStringA(message.c_str());
}

static void DebugOutput(std::wstring message){
	OutputDebugStringW(message.c_str());
}

class DebugLog {

public:

	DebugLog();

	virtual ~DebugLog();

	DebugLog& operator<<(const char*& message);

	DebugLog& operator<<(const WCHAR*& message);

	DebugLog& operator<<(const std::string& message);

	DebugLog& operator<<(const std::wstring& message);

	DebugLog& operator<<(const int& val);

	DebugLog& operator<<(const float& val);

	DebugLog& operator<<(const double& val);

	DebugLog& operator<<(const short& val);

	DebugLog& operator<<(const unsigned int& val);

	DebugLog& operator<<(const unsigned short& val);

	DebugLog& operator<<(const physx::PxVec3& val);

	DebugLog& operator<<(const Ogre::Vector3& val);

	// this is the type of std::cout
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    // this is the function signature of std::endl
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
	DebugLog& operator<<(StandardEndLine manip);

};

static DebugLog dout;

}