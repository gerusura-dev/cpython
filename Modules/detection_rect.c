//
// Created by げるすらいむ on 25/10/23.
//

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "structmember.h"

// 型定義
typedef struct {
    PyObject_HEAD
    double x1, y1, x2, y2;
} RectObject;

// メンバー関数 init
static int
Rect_init(RectObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"x1", "y1", "x2", "y2", NULL};
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "dddd", kwlist, &x1, &y1, &x2, &y2)) {
        return -1;
    }

    self->x1 = x1;
    self->y1 = y1;
    self->x2 = x2;
    self->y2 = y2;

    return 0;
}

// メンバー関数 repr
static PyObject
*Rect_repr(RectObject *self) {
    return PyUnicode_FromFormat(
        "Rect(x1=%R, y1=%R, x2=%R, y2=%R)",
        PyFloat_FromDouble(self->x1),
        PyFloat_FromDouble(self->y1),
        PyFloat_FromDouble(self->x2),
        PyFloat_FromDouble(self->y2)
    );
}

// メンバー定義
static PyMemberDef
Rect_members[] = {
    {"x1", T_DOUBLE, offsetof(RectObject, x1), 0, "left x"},
    {"y1", T_DOUBLE, offsetof(RectObject, y1), 0, "top y"},
    {"x2", T_DOUBLE, offsetof(RectObject, x2), 0, "right x"},
    {"y2", T_DOUBLE, offsetof(RectObject, y2), 0, "bottom y"},
    {NULL}
};

// クラス設定
static PyType_Slot
Rect_slots[] = {
    {Py_tp_init,    (void*)Rect_init},
    {Py_tp_repr,    (void*)Rect_repr},
    {Py_tp_members, (void*)Rect_members},
    {0, 0}
};

static PyType_Spec
Rect_spec = {
    .name      = "detection.Rect",
    .basicsize = sizeof(RectObject),
    .flags     = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .slots     = Rect_slots
};

// factory
PyObject
*Detection_MakeRectType(PyObject *module) {
    PyObject *type = PyType_FromSpec(&Rect_spec);

    if (!type) {
        return NULL;
    }
    if (PyModule_AddObjectRef(module, "Rect", type) < 0) {
        Py_DECREF(type);
        return NULL;
    }

    return type;
}
