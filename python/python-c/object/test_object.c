#include <Python.h>
PyObject *module = NULL;

typedef struct {
	PyObject_HEAD
} TestObject;

static PyTypeObject TestObjectType = {
	PyObject_HEAD_INIT(NULL)
	0,
	"TestObject",
	sizeof(TestObject),
	0,                         /*tp_itemsize*/
	0,                         /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,
	"My TestObject"
}; 

static PyMethodDef testObjectMethods[] = {
	{NULL}
};

void inittest_object() {
	TestObjectType.tp_new = PyType_GenericNew;

	if (PyType_Ready(&TestObjectType) < 0) {
		return;
	}

	module = Py_InitModule("test_object", testObjectMethods);	

	if (module == NULL) {
		return;
	}

	Py_INCREF(&TestObjectType);
	PyModule_AddObject(module, "TestObject", (PyObject *)&TestObjectType);
}
