#include "special/specfun.h"
#include "ufunc.h"

static PyModuleDef specfun2_def = {
    PyModuleDef_HEAD_INIT,
    .m_name = "specfun2",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_specfun2() {
    SpecFun_Initialize();

    PyObject *specfun2 = PyModule_Create(&specfun2_def);
    if (specfun2 == nullptr) {
        return nullptr;
    }

    PyObject *expi = SpecFun_UFunc<special::expi, special::cexpi>("expi", "docstring goes here");
    PyModule_AddObjectRef(specfun2, "expi", expi);

    // More ufuncs would follow ...

    return specfun2;
}