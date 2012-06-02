#include <Python.h>
#include <pthread.h>
#include <unistd.h>

static PyObject *func = NULL;
static pthread_t pid;

int test(int n) {
	return n + 1;
}

PyObject *wrap_test(PyObject *self, PyObject *args) {
	//int n = 0;
	PyObject *dict = NULL;
	if (!PyArg_ParseTuple(args, "O", &dict)) {
		return NULL;
	}

	func = PyDict_GetItemString(dict, "f");
	//Py_INCREF(func);
	//int ret = Py_BuildValue("i", test(n));
	return Py_BuildValue("i", 0);
}

PyObject *invoke(PyObject *self, PyObject *args) {
	PyObject_CallFunctionObjArgs(func, NULL);
}

void thread_run() {
	while (1) {
		printf("thread loop\n");
		sleep(2);
	}
}

PyObject *start_thread() {
	phread_create(&pid, NULL, thread_run, NULL);
}

static PyMethodDef exampleMethods[] = {
	{"test", wrap_test, METH_VARARGS, "just test"},
	{"invoke", invoke, METH_VARARGS, ""},
	{"start_thread", start_thread, METH_VARARGS, ""},
	{NULL}
};

PyMODINIT_FUNC initexample() {
	Py_InitModule("example", exampleMethods);
}
