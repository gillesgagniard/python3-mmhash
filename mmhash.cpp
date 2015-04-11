/*


MurmurHash2 http://murmurhash.googlepages.com/
MurmurHash2, 64-bit versions, by Austin Appleby

Modified by changsheng@douban.com

zsp windows,linux python lib

*/

#include <Python.h>
#include <sys/types.h>

#if defined(_MSC_VER)
typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif 


#define FNV_32_PRIME 0x01000193ULL


uint64_t mmhash_64(const void *key, size_t len) {
	const uint64_t m = 0xc6a4a7935bd1e995ULL;
	const uint64_t r = 47;
	uint64_t h = FNV_32_PRIME ^ (len * m);
	const uint64_t * data = (const uint64_t *)key;
	const uint64_t * end = data + (len/8);

	uint64_t k ;
	while (data != end) {
		k = *data++;
		k *= m;
		k ^= k >> r;
		k *= m;
		h ^= k;
		h *= m;
	};

	const unsigned char * data2 = (const unsigned char*)data;
	switch (len & 7) {
	case 7: h ^= (uint64_t)(data2[6]) << 48;
	case 6: h ^= (uint64_t)(data2[5]) << 40;
	case 5: h ^= (uint64_t)(data2[4]) << 32;
	case 4: h ^= (uint64_t)(data2[3]) << 24;
	case 3: h ^= (uint64_t)(data2[2]) << 16;
	case 2: h ^= (uint64_t)(data2[1]) << 8;
	case 1: h ^= (uint64_t)(data2[0]);
		h *= m;
	}
	h ^= h >> r;
	h *= m;
	h ^= h >> r;
	return h;
}


static PyObject * get_unsigned_hash(PyObject *self,PyObject *args) {
	char * guid;
	unsigned int len;
	if(!PyArg_ParseTuple(args,"z#",&guid,&len)) {
		return NULL;
	}
	uint64_t h =  mmhash_64(guid,len);
	/* return Py_BuildValue("l",h); */
	return PyLong_FromUnsignedLongLong(h);
}

static PyObject * get_hash(PyObject *self,PyObject *args) {
	char * guid;
    unsigned int len;
	if(!PyArg_ParseTuple(args,"z#",&guid,&len)) {
		return NULL;
	}
	int64_t h =  mmhash_64(guid,len);
	/* return Py_BuildValue("l",h); */
#if defined(__x86_64__) || defined(_M_X64)
	return PyInt_FromLong(h);
#else
	return PyLong_FromLongLong(h);
#endif
}


static PyMethodDef methods[] = {
	{"get_hash",(PyCFunction)get_hash,METH_VARARGS,NULL},
	{"get_unsigned_hash",(PyCFunction)get_unsigned_hash,METH_VARARGS,NULL},
	{NULL,NULL,0,NULL}
};

PyMODINIT_FUNC initmmhash() {
	Py_InitModule3("mmhash", methods, "MurmurHash2 hash algorithm extension module.");
}
