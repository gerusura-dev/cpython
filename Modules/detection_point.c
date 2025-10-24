//
// Created by げるすらいむ on 25/10/23.
//

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "structmember.h"

// 型定義
typedef struct {
    PyObject_HEAD
    double x;
    double y;
} PointObject;

// メンバー関数 init
static int
Point_init(PointObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"x", "y", NULL};
    double x = 0.0;
    double y = 0.0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|dd", kwlist, &x, &y)) {
        return -1;
    }

    self->x = x;
    self->y = y;

    return 0;
}

// メンバー関数 repr
static PyObject
*Point_repr(PointObject *self) {
    return PyUnicode_FromFormat(
        "Point(x=%R, y=%R)",
        PyFloat_FromDouble(self->x),
        PyFloat_FromDouble(self->y)
    );
}

// メンバー定義
static PyMemberDef
Point_members[] = {
    {"x", T_DOUBLE, offsetof(PointObject, x), 0, "x coordinate"},
    {"y", T_DOUBLE, offsetof(PointObject, y), 0, "y coordinate"},
    {NULL}
};

// クラス設定
static PyType_Slot
Point_slots[] = {
    {Py_tp_init,    (void*)Point_init},
    {Py_tp_repr,    (void*)Point_repr},
    {Py_tp_members, (void*)Point_members},
    {0, 0}
};

static PyType_Spec
Point_spec = {
    .name      = "detection.Point",
    .basicsize = sizeof(PointObject),
    .flags     = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .slots     = Point_slots
};

// factory
PyObject
*Detection_MakePointType(PyObject *module) {
    PyObject *type = PyType_FromSpec(&Point_spec);

    if (!type) {
        return NULL;
    }
    if (PyModule_AddObjectRef(module, "Point", type) < 0) {
        Py_DECREF(type);
        return NULL;
    }

    return type;
}
