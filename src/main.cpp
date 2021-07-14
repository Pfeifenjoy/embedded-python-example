#include <iostream>
#include <vector>
#include <Python.h>

PyObject *to_double_list(const std::vector<double>& data) {
	auto list = PyList_New(0);

	for(const auto& element : data) {
		auto pyelement = PyFloat_FromDouble(element);
		PyList_Append(list, pyelement);
		Py_DECREF(pyelement);
	}

	return list;
}

int main(const int argc, const char** argv) {
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	if (argc < 3) {
		fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
		return 1;
	}

	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import os");
	PyRun_SimpleString("sys.path.append(os.getcwd())");

	pName = PyUnicode_DecodeFSDefault(argv[1]);
	pModule = PyImport_Import(pName);

	Py_DECREF(pName);

	std::vector<double> data;
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);

	if(pModule != nullptr) {
		pFunc = PyObject_GetAttrString(pModule, argv[2]);
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc)) {
			auto pydata = to_double_list(data);

			pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, pydata);
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			Py_DECREF(pydata);

			if (pValue != NULL) {
				printf("Result of call: %ld\n", PyLong_AsLong(pValue));
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr,"Call failed\n");
				return 1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}
	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}
