#include "special/specfun.h"
#include "ufunc.h"

extern const char *bei_doc;
extern const char *beip_doc;
extern const char *ber_doc;
extern const char *berp_doc;
extern const char *exp1_doc;
extern const char *expi_doc;
extern const char *it2i0k0_doc;
extern const char *it2j0y0_doc;
extern const char *it2struve0_doc;
extern const char *itairy_doc;
extern const char *iti0k0_doc;
extern const char *itj0y0_doc;
extern const char *itmodstruve0_doc;
extern const char *itstruve0_doc;
extern const char *kei_doc;
extern const char *keip_doc;
extern const char *kelvin_doc;
extern const char *ker_doc;
extern const char *kerp_doc;
extern const char *mathieu_a_doc;
extern const char *mathieu_b_doc;

static PyModuleDef _specfun2_def = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_specfun2",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit__specfun2() {
    SpecFun_Initialize();

    PyObject *specfun2 = PyModule_Create(&_specfun2_def);
    if (specfun2 == nullptr) {
        return nullptr;
    }

    PyObject *bei = SpecFun_UFunc<special::bei>("bei", bei_doc);
    PyModule_AddObjectRef(specfun2, "bei", bei);

    PyObject *beip = SpecFun_UFunc<special::beip>("beip", beip_doc);
    PyModule_AddObjectRef(specfun2, "beip", beip);

    PyObject *ber = SpecFun_UFunc<special::ber>("ber", ber_doc);
    PyModule_AddObjectRef(specfun2, "ber", ber);

    PyObject *berp = SpecFun_UFunc<special::berp>("berp", berp_doc);
    PyModule_AddObjectRef(specfun2, "berp", berp);

    PyObject *exp1 = SpecFun_UFunc<special::exp1, special::cexp1>("exp1", exp1_doc);
    PyModule_AddObjectRef(specfun2, "exp1", exp1);

    PyObject *expi = SpecFun_UFunc<special::expi, special::cexpi>("expi", expi_doc);
    PyModule_AddObjectRef(specfun2, "expi", expi);

    PyObject *it2i0k0 = SpecFun_UFunc<special::it2i0k0>("it2i0k0", it2i0k0_doc, 2);
    PyModule_AddObjectRef(specfun2, "it2i0k0", it2i0k0);

    PyObject *it2j0y0 = SpecFun_UFunc<special::it2j0y0>("it2j0y0", it2j0y0_doc, 2);
    PyModule_AddObjectRef(specfun2, "it2j0y0", it2j0y0);

    PyObject *it2struve0 = SpecFun_UFunc<special::it2struve0>("it2struve0", it2struve0_doc);
    PyModule_AddObjectRef(specfun2, "it2struve0", it2struve0);

    PyObject *itairy = SpecFun_UFunc<special::itairy>("itairy", itairy_doc, 4);
    PyModule_AddObjectRef(specfun2, "itairy", itairy);

    PyObject *iti0k0 = SpecFun_UFunc<special::it1i0k0>("iti0k0", iti0k0_doc, 2);
    PyModule_AddObjectRef(specfun2, "iti0k0", iti0k0);

    PyObject *itj0y0 = SpecFun_UFunc<special::it1j0y0>("itj0y0", itj0y0_doc, 2);
    PyModule_AddObjectRef(specfun2, "itj0y0", itj0y0);

    PyObject *itmodstruve0 = SpecFun_UFunc<special::itmodstruve0>("itmodstruve0", itmodstruve0_doc);
    PyModule_AddObjectRef(specfun2, "itmodstruve0", itmodstruve0);

    PyObject *itstruve0 = SpecFun_UFunc<special::itstruve0>("itstruve0", itstruve0_doc);
    PyModule_AddObjectRef(specfun2, "itstruve0", itstruve0);

    PyObject *kei = SpecFun_UFunc<special::kei>("kei", kei_doc);
    PyModule_AddObjectRef(specfun2, "kei", kei);

    PyObject *keip = SpecFun_UFunc<special::keip>("keip", keip_doc);
    PyModule_AddObjectRef(specfun2, "keip", keip);

    PyObject *kelvin = SpecFun_UFunc<special::kelvin>("kelvin", kelvin_doc, 4);
    PyModule_AddObjectRef(specfun2, "kelvin", kelvin);

    PyObject *ker = SpecFun_UFunc<special::ker>("ker", ker_doc);
    PyModule_AddObjectRef(specfun2, "ker", ker);

    PyObject *kerp = SpecFun_UFunc<special::kerp>("kerp", kerp_doc);
    PyModule_AddObjectRef(specfun2, "kerp", kerp);

    PyObject *mathieu_a = SpecFun_UFunc<special::cem_cva>("mathieu_a", mathieu_a_doc);
    PyModule_AddObjectRef(specfun2, "mathieu_a", mathieu_a);

    PyObject *mathieu_b = SpecFun_UFunc<special::sem_cva>("mathieu_b", mathieu_b_doc);
    PyModule_AddObjectRef(specfun2, "mathieu_b", mathieu_b);

    return specfun2;
}
