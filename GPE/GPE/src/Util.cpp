#include "Util.hpp"
#include <PxPhysics.h>
#include <OgreVector3.h>

namespace Util {


	DebugLog::DebugLog() {

	}

	DebugLog::~DebugLog() {

	}

	DebugLog& DebugLog::operator<<(const char*& message) {
		OutputDebugStringA(message);
		return *this;
	}

	DebugLog& DebugLog::operator<<(const WCHAR*& message) {
		OutputDebugStringW(message);
		return *this;
	}

	DebugLog& DebugLog::operator<<(const std::string& message) {
		OutputDebugStringA(message.c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const std::wstring& message) {
		OutputDebugStringW(message.c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const int& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const float& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const double& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const short& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const unsigned int& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const unsigned short& val) {
		std::stringstream ss;
		ss << val;
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const physx::PxVec3& val) {
		std::stringstream ss;
		ss << "PxVec3(" << val.x << ", " << val.y << ", " << val.z << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	DebugLog& DebugLog::operator<<(const Ogre::Vector3& val) {
		std::stringstream ss;
		ss << "Vector3(" << val.x << ", " << val.y << ", " << val.z << ")";
		OutputDebugStringA(ss.str().c_str());
		return *this;
	}

	// define an operator<< to take in std::endl
	DebugLog& DebugLog::operator<<(StandardEndLine manip) {
		OutputDebugStringA("\n");

		return *this;
	}


}