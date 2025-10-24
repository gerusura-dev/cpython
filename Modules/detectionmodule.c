//
// Created by げるすらいむ on 25/10/24.
//

#define PY_SSIZE_T_CLEAN
#include "Python.h"

PyObject *Detection_MakePointType(PyObject *module);
PyObject *Detection_MakeRectType(PyObject *module);
PyObject *Detection_MakeSegmentType(PyObject *module);

static int
detection_exec(PyObject *m) {
    if (!Detection_MakePointType(m)) {
        return -1;
    }

    if (!Detection_MakeRectType(m)) {
        return -1;
    }

    if (!Detection_MakeSegmentType(m)) {
        return -1;
    }

    return 0;
}

static PyModuleDef_Slot
detection_slots[] = {
    {Py_mod_exec, detection_exec},
    {0, NULL}
};

static struct PyModuleDef
detection_def = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "detection",
    .m_doc     = "Geometry helper",
    .m_size    = 0,
    .m_methods = NULL,
    .m_slots   = detection_slots
};

PyMODINIT_FUNC
PyInit_detection(void) {
    return PyModuleDef_Init(&detection_def);
}
