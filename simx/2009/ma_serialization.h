
#include "ma_sparse.h"
#define z6eb08ccc90(type, storageDataPtr, value)\
{\
	*(type *)(storageDataPtr) = (value);\
	(storageDataPtr) = (char *)(storageDataPtr) + sizeof(type);\
}
#define zdceda3f4bf(type, storageDataPtr, value)\
{\
	(value) = *(type *)(storageDataPtr);\
	(storageDataPtr) = (char *)(storageDataPtr) + sizeof(type);\
}
void z34d6de563c(void**storageDataPtr,struct z5baae04982*z177bce671b);void 
zbaac5bbd3a(void**storageDataPtr,struct z307b03c7b0*z480f2ba3f9,struct 
z5baae04982*z177bce671b);void zd08ab6e0d1(void**storageDataPtr,struct 
z5baae04982*z177bce671b);void z69391c23cc(void**storageDataPtr,struct 
z307b03c7b0*z480f2ba3f9,struct z5baae04982*z177bce671b);
