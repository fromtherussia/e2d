#include <assert.h>

#include "Exception.h"

namespace cgl {
		void lib_assert(const char* _Message, const char* _File, unsigned _Line) {
			assert(_Message);
		}

		void lib_check(const char * _Message, const char *_File, unsigned _Line) {
			lib_assert(_Message, _File, _Line);
		}
}