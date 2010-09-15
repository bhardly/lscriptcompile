
#include "linden_common.h"
#include "lscript_rt_interface.h"

const char* URL_REQUEST_GRANTED = "URL_REQUEST_GRANTED";
const char* URL_REQUEST_DENIED = "URL_REQUEST_DENIED";

#define EXTERN_C extern "C"

#ifdef WIN32 
#define DLL_EXPORT __declspec(dllexport) 
#else 
#define DLL_EXPORT 
#endif

EXTERN_C DLL_EXPORT bool compile(const char* src_filename, const char* dst_filename, const char* err_filename,
                                 bool compile_to_mono, const char* class_name, bool is_god_like)
{
	return lscript_compile(src_filename, dst_filename, err_filename, compile_to_mono, class_name, is_god_like);
}
