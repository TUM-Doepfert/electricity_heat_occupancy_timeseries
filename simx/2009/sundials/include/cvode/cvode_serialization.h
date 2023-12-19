/*
 * -----------------------------------------------------------------
 * This is the header file for the CVODE serialization functions.
 *------------------------------------------------------------------
 */

#ifndef _CVODE_SERIALIZATION_H
#define _CVODE_SERIALIZATION_H

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

#include <stdio.h>

#include <sundials/sundials_config.h>

/* Error codes returned from deserialization function */
#define CVODE_SERIALIZATION_INVALID_MAGIC_HEADER -1
#define CVODE_SERIALIZATION_INVALID_VERSION -2

#define CVODE_SERIALIZE_A(op, type, storageDataPtr, value, mem_size)\
	switch (op) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		SERIALIZE(type, storageDataPtr, value)\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		DESERIALIZE(type, storageDataPtr, value)\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		mem_size += sizeof(type);\
		break;\
	}

#define CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, valuePtr, mem_size)\
	switch (op) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		SerializeNVector(storageDataPtr, valuePtr);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		DeSerializeNVector(storageDataPtr, valuePtr);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		mem_size += sizeof(long int) + ((N_VectorContent_Serial)(valuePtr)->content)->length * sizeof(realtype);\
		break;\
	}

/*
 * -----------------------------------------------------------------
 * Function : CVodeSerializationSize
 * -----------------------------------------------------------------
 * CVodeSerializationSize returns the size of the memory block in
 * bytes that is required to store the complete internal state of
 * the CVODE integrator (all data structures that are allocated by
 * CVODE/SUNDIALS functions themselves).
 * Returns size of memory in bytes required.
 * -----------------------------------------------------------------
 */
long int CVodeSerializationSize(void *cvode_mem);

/*
 * -----------------------------------------------------------------
 * Function : CVodeSerialize
 * -----------------------------------------------------------------
 * CVodeSerialize copies the memory that defines the entire state of
 * CVODE integrator to a continuous memory array. The memory array
 * must have the size that is returned by CVodeSerializationSize().
 * The CVODE memory is not modified. The pointer to the storage location
 * is moved forward and points to the byte just after the last byte
 * of the serialized memory.
 * Returns size of copies memory in bytes.
 * -----------------------------------------------------------------
 */
long int CVodeSerialize(void *cvode_mem, void ** storageDataPtr);

/*
 * -----------------------------------------------------------------
 * Function : CVodeDeserialize
 * -----------------------------------------------------------------
 * CVodeDeserialize copies the memory that defines the entire state of
 * CVODE integrator from a continuous memory array into the CVODE data
 * structure(s). The memory array must have the size that is returned
 * by CVodeSerializationSize() and the CVODE must be properly
 * initialized so that all NVectors etc. have the correct size.
 * The pointer to the storage location is moved forward and points to
 * the byte just after the last byte of the serialized memory.
 * Returns size of copies memory in bytes or error code.
 * -----------------------------------------------------------------
 */
long int CVodeDeserialize(void *cvode_mem, void ** storageDataPtr);

/*
 * The following functions are currently not used but reserved.
 */

long int UserSerializationSize(void *cvode_mem);
long int UserSerialize(void *cvode_mem, void ** storageDataPtr);
long int UserDeserialize(void *cvode_mem, void ** storageDataPtr);

#ifdef __cplusplus
}
#endif

#endif
