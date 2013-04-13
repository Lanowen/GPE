#ifndef ERRORSTREAM_H
#define ERRORSTREAM_H

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
#endif

class ErrorStream : public NxUserOutputStream
	{
	public:
	void reportError(NxErrorCode e, const char* message, const char* file, int line)
		{
		std::cout << file << "(" << line << ")";
		switch (e)
			{
			case NXE_INVALID_PARAMETER:
				std::cout <<"invalid parameter";
				break;
			case NXE_INVALID_OPERATION:
				std::cout << "invalid operation";
				break;
			case NXE_OUT_OF_MEMORY:
				std::cout << "out of memory";
				break;
			case NXE_DB_INFO:
				std::cout << "info";
				break;
			case NXE_DB_WARNING:
				std::cout << "warning";
				break;
			default:
				std::cout <<"unknown error";
			}

		std::cout << " : " << message << std::endl;
		}

	NxAssertResponse reportAssertViolation(const char* message, const char* file, int line)
		{
		std::cout << "access violation : " << message << "(" << file << " " << line << ")" << std::endl;
#ifdef WIN32
		switch (MessageBox(0, message, "AssertViolation, see console for details.", MB_ABORTRETRYIGNORE))
			{
			case IDRETRY:
				return NX_AR_CONTINUE;
			case IDIGNORE:
				return NX_AR_IGNORE;
			case IDABORT:
			default:
				return NX_AR_BREAKPOINT;
			}
#elif __linux__
		assert(0);
#elif _XBOX
		return NX_AR_BREAKPOINT;
#elif __CELLOS_LV2__
		return NX_AR_BREAKPOINT;
#elif __PPCGEKKO__
		return NX_AR_BREAKPOINT;		
#endif
		}

	void print(const char* message)
		{
		std::cout << message;
		}
	};



#endif
