
#include "vector.h"

namespace bcu {

Int32
Size_alloc::get_realloc(Int32 new_alloc)
{
	if(new_alloc>f_alloc){
		if(new_alloc>2*f_alloc){
			return new_alloc;
		} else {
			return 2*f_alloc;
		}
	} else {
		if(new_alloc<f_alloc/4){
			return new_alloc;
		} else if(new_alloc<f_alloc/2){
			return f_alloc/2;
		} else {
			// nothing
		}
	}
	return f_alloc;
}


}; // namespace bcu
