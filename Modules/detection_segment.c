//
// Created by げるすらいむ on 25/10/23.
//

#define PY_SSIZE_T_CLEAN
#include "Python.h"

// 型定義
typedef struct {
    PyObject_HEAD
    PyObject *points;
} SegmentObject;

// メンバー関数 init
static int
Segment_init(SegmentObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"points", NULL};
    PyObject *seq;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &seq)) {
        return -1;
    }
    if (!PySequence_Check(seq)) {
        PyErr_SetString(PyExc_TypeError, "points must be a sequence");
        return -1;
    }

    Py_INCREF(seq);
    Py_XSETREF(self->points, seq);

    return 0;
}

// メンバー関数 del
static void
Segment_dealloc(SegmentObject *self) {
    Py_XDECREF(self->points);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

// メンバー関数 repr
static PyObject
*Segment_repr(SegmentObject *self) {
    return PyUnicode_FromFormat(
        "Segment(points=%R)",
        self->points
    );
}

// メンバー関数 len
static PyObject
*Segment_len(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    SegmentObject *seg = (SegmentObject *)self;
    Py_ssize_t n = PySequence_Size(seg->points);

    if (n < 0) {
        return NULL;
    }

    return PyLong_FromSsize_t(n);
}

// メンバー定義
static PyMethodDef
Segment_methods[] = {
    {"__len__", (PyCFunction)Segment_len, METH_NOARGS, "number of points"},
    {NULL, NULL}
};

static PyType_Slot
Segment_slots[] = {
    {Py_tp_init,    (void*)Segment_init},
    {Py_tp_dealloc, (void*)Segment_dealloc},
    {Py_tp_repr,    (void*)Segment_repr},
    {Py_tp_methods, (void*)Segment_methods},
    {0, 0}
};

static PyType_Spec
Segment_spec = {
    .name      = "detection.Segment",
    .basicsize = sizeof(SegmentObject),
    .flags     = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .slots     = Segment_slots
};

// factory
PyObject
*Detection_MakeSegmentType(PyObject *module) {
    PyObject *type = PyType_FromSpec(&Segment_spec);

    if (!type) {
        return NULL;
    }
    if (PyModule_AddObjectRef(module, "Segment", type) < 0) {
        Py_DECREF(type);
        return NULL;
    }

    return type;
}
