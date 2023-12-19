/*
 * -------------------------------------------------------------------------
 * This is the implementation file for the SUNDIALS serialization functions.
 * -------------------------------------------------------------------------
 */

#include <sundials/sundials_serialization.h>
#include <sundials/sundials_dense.h>
#include <nvector/nvector_serial.h>
#include <assert.h>

void SerializeNVector(void **storageDataPtr, N_Vector vec)
{
	long int i;
	N_VectorContent_Serial nvecSerial = (N_VectorContent_Serial)vec->content;
	SERIALIZE(long, *storageDataPtr, nvecSerial->length);
	for (i = 0; i < nvecSerial->length; ++i)
		SERIALIZE(realtype, *storageDataPtr, nvecSerial->data[i]);
}

void SerializeDenseMat(void **storageDataPtr, DenseMat mat)
{
	long int i;
	SERIALIZE(long, *storageDataPtr, mat->M);
	SERIALIZE(long, *storageDataPtr, mat->N);
	for (i = 0; i < mat->M * mat->N; ++i)
		SERIALIZE(realtype, *storageDataPtr, mat->data[0][i]);
}

void DeSerializeNVector(void **storageDataPtr, N_Vector vec)
{
	long int i, N;
	N_VectorContent_Serial nvecSerial = (N_VectorContent_Serial)vec->content;
	DESERIALIZE(long, *storageDataPtr, N);
	assert(N == nvecSerial->length);
	for (i = 0; i < N; ++i)
		DESERIALIZE(realtype, *storageDataPtr, nvecSerial->data[i]);
}

void DeSerializeDenseMat(void **storageDataPtr, DenseMat mat)
{
	long int i, M, N;
	DESERIALIZE(long, *storageDataPtr, M);
	DESERIALIZE(long, *storageDataPtr, N);
	assert(M == mat->M);
	assert(N == mat->N);
	for (i = 0; i < M * N; ++i)
		DESERIALIZE(realtype, *storageDataPtr, mat->data[0][i]);
}
