#pragma once

#include <sstream>
#include <WinBase.h>

namespace Util {

template <class vect1, class vect2>
	static inline vect2 vec_from_to(vect1 inVect)
	{
		vect2 v;
		v.x = inVect.x;
		v.y = inVect.y;
		v.z = inVect.z;
		return v;
	}

	template <class quat1, class quat2>
	static inline quat2 quat_from_to(quat1 inQuat)
	{
		quat2 q;
		q.x = inQuat.x;
		q.y = inQuat.y;
		q.z = inQuat.z;
		q.w = inQuat.w;
		return q;
	}

static void DebugOutput(std::string message){
	OutputDebugStringA(message.c_str());
}

static void DebugOutput(std::wstring message){
	OutputDebugStringW(message.c_str());
}

class DebugLog {

public:

	DebugLog() {

	}

	virtual ~DebugLog(){

	}

	DebugLog& operator<<(const char*& message){
		OutputDebugStringA(message);
		return *this;
	}

	DebugLog& operator<<(const WCHAR*& message){
		OutputDebugStringW(message);
		return *this;
	}

	DebugLog& operator<<(const std::string& message){
		OutputDebugStringA(message.c_str());
		return *this;
	}

	DebugLog& operator<<(const std::wstring& message){
		OutputDebugStringW(message.c_str());
		return *this;
	}

	DebugLog& operator<<(const int& val){
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& operator<<(const float& val){
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& operator<<(const double& val){
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& operator<<(const short& val){
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& operator<<(const unsigned int& val){
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& operator<<(const unsigned short& val){
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	// this is the type of std::cout
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    // this is the function signature of std::endl
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
    DebugLog& operator<<(StandardEndLine manip)
    {
    	OutputDebugStringA("\n");

    	return *this;
    }

//	static DebugLog* getInstance(){
//		if(instance == 0)
//			instance = new DebugLog();
//
//		return instance;
//	}
//
//public:
//	static DebugLog& operator<<(DebugLog, const char*& message){
//		return *getInstance() << message;
//	}
//
//	static DebugLog& operator<<(DebugLog, const WCHAR*& message){
//		OutputDebugStringW(message);
//		return *getInstance() << message;
//	}
//
//	static DebugLog& operator<<(DebugLog, const std::string& message){
//		OutputDebugStringA(message.c_str());
//		return *getInstance() << message;
//	}
//
//	static DebugLog& operator<<(DebugLog, const std::wstring& message){
//		OutputDebugStringW(message.c_str());
//		return *getInstance() << message;
//	}
//
//private:
//	static DebugLog* instance;
};

//DebugLog* DebugLog::instance = 0;

static DebugLog dout;



}