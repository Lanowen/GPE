#pragma once

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreDataStream.h>
#include <OgreAxisAlignedBox.h>
#include <OgreString.h>
#include <OgreMesh.h>

#include <PxPhysics.h>
#include <foundation\PxVec2.h>
#include <foundation\PxVec3.h>
#include <foundation\PxVec4.h>

//namespace Ogre {
//	class Vector3;
//	class AxisAlignedBox;
//	class DataStreamPtr;
//}

//namespace physx {
//	class PxVec3;
//}

namespace Util {

	struct ObjObject {
	public:
		ObjObject(Ogre::String objectName) : name(objectName) {
		}
		Ogre::String name;

		std::vector<float> vertices;
		//std::vector<float> normals;
		//std::vector<float> texcoords;

		std::vector<unsigned short> faces;
		Ogre::AxisAlignedBox bounds;
	};

	std::vector<ObjObject> ParseSimpleVertexOnlyObj(Ogre::DataStreamPtr& fileHandle);

	void CreateOgreMesh(Ogre::MeshPtr levelMesh, ObjObject& simpleObj);

	void CookTrimeshFromObj(char* dst, ObjObject& obj);

	template <class vect2_to, class vect2_from>
	inline vect2_to vect2_convert(vect2_from inVect) {
		vect2_to v;
		v.x = inVect.x;
		v.y = inVect.y;
		return v;
	}

	template <class vect3_to, class vect3_from>
	inline vect3_to vect3_convert(vect3_from inVect) {
		vect3_to v;
		v.x = inVect.x;
		v.y = inVect.y;
		v.z = inVect.z;
		return v;
	}

	template <class vect4_to, class vect4_from>
	inline vect4_to vect4_convert(vect4_from inVect) {
		vect4_to v;
		v.w = inVect.w;
		v.x = inVect.x;
		v.y = inVect.y;
		v.z = inVect.z;
		return v;
	}

	template <class quat_to, class quat_from>
	inline quat_to quat_convert(quat_from inQuat) {
		quat_to q;
		q.w = inQuat.w;
		q.x = inQuat.x;
		q.y = inQuat.y;
		q.z = inQuat.z;
		return q;
	}

#ifndef WIN8_ARM

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

#endif

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

	DebugLog& operator<<(const physx::PxVec2& val);
	DebugLog& operator<<(const physx::PxVec3& val);
	DebugLog& operator<<(const physx::PxVec4& val);

	DebugLog& operator<<(const Ogre::Vector2& val);
	DebugLog& operator<<(const Ogre::Vector3& val);
	DebugLog& operator<<(const Ogre::Vector4& val);

	// this is the type of std::cout
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    // this is the function signature of std::endl
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
	DebugLog& operator<<(StandardEndLine manip);

};

static DebugLog dout;

}