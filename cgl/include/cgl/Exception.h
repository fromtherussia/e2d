#ifndef CGL_EXCEPTION_H
#define CGL_EXCEPTION_H

namespace cgl {
	void lib_assert(const char * _Message, const char *_File, unsigned _Line);
	void lib_check(const char * _Message, const char *_File, unsigned _Line);
}

#ifdef _DEBUG

#define CGL_ASSERT(_Expression) (void)((!!(_Expression)) || (cgl::lib_assert(#_Expression, __FILE__, __LINE__), 0))
#define CGL_FAIL(_Expression) (void)(cgl::lib_assert(_Expression, __FILE__, __LINE__))
#define CGL_FAIL_UNEXPECTED() (void)(cgl::lib_assert("Unexpected failure", __FILE__, __LINE__))

#else

#define CGL_ASSERT(_Expression) ((void)0)
#define CGL_FAIL(_Expression) ((void)0)
#define CGL_FAIL_UNEXPECTED() ((void)0)

#endif 

#define CGL_CHECK(_Expression) (void)((!!(_Expression)) || (cgl::lib_check(#_Expression, __FILE__, __LINE__), 0))

#endif