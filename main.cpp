#include "test.h"
#include "MyClass.h"
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

    int
    main(int argc, char *argv[])
    {
        PyObject *pmodule;
        wchar_t *program;

        program = Py_DecodeLocale(argv[0], NULL);
        if (program == NULL)
        {
            fprintf(stderr, "Fatal error: cannot decode argv[0], got %d arguments\n", argc);
            exit(1);
        }

        /* Add a built-in module, before Py_Initialize */
        if (PyImport_AppendInittab("test", PyInit_test) == -1)
        {
            fprintf(stderr, "Error: could not extend in-built modules table\n");
            exit(1);
        }

        /* Pass argv[0] to the Python interpreter */
        Py_SetProgramName(program);

        /* Initialize the Python interpreter.  Required.
           If this step fails, it will be a fatal error. */
        Py_Initialize();

        /* Optionally import the module; alternatively,
           import can be deferred until the embedded script
           imports it. */
        pmodule = PyImport_ImportModule("test");
        if (!pmodule)
        {
            PyErr_Print();
            fprintf(stderr, "Error: could not import module 'test'\n");
            PyMem_RawFree(program);
            Py_Finalize();
            return 1;
        }

        PyObject *p = createMyClass();
        // print p.add(1,2)
        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, PyLong_FromLong(1));
        PyTuple_SetItem(args, 1, PyLong_FromLong(2));
        PyObject *result = PyObject_CallMethod(p, "add", "OO", PyLong_FromLong(1), PyLong_FromLong(2));
        std::cout << PyLong_AsLong(result) << std::endl;

        /* Clean up after using CPython. */
        PyMem_RawFree(program);
        Py_Finalize();

        return 0;
    }

#ifdef __cplusplus
}
#endif