#include "ufunc.h"

#include "special.h"

using namespace std;

using cfloat = complex<float>;
using cdouble = complex<double>;

using float_1dspan = mdspan<float, dextents<ptrdiff_t, 1>, layout_stride>;
using float_2dspan = mdspan<float, dextents<ptrdiff_t, 2>, layout_stride>;
using double_1dspan = mdspan<double, dextents<ptrdiff_t, 1>, layout_stride>;
using double_2dspan = mdspan<double, dextents<ptrdiff_t, 2>, layout_stride>;
using cfloat_1dspan = mdspan<cfloat, dextents<ptrdiff_t, 1>, layout_stride>;
using cfloat_2dspan = mdspan<cfloat, dextents<ptrdiff_t, 2>, layout_stride>;
using cdouble_1dspan = mdspan<cdouble, dextents<ptrdiff_t, 1>, layout_stride>;
using cdouble_2dspan = mdspan<cdouble, dextents<ptrdiff_t, 2>, layout_stride>;

// 1 input, 1 output
using func_f_f1_t = void (*)(float, float_1dspan);
using func_f_f2_t = void (*)(float, float_2dspan);
using func_d_d1_t = void (*)(double, double_1dspan);
using func_d_d2_t = void (*)(double, double_2dspan);
using func_F_F1_t = void (*)(cfloat, cfloat_1dspan);
using func_D_D1_t = void (*)(cdouble, cdouble_1dspan);

// 1 input, 2 outputs
using func_f_f1f1_t = void (*)(float, float_1dspan, float_1dspan);
using func_f_f2f2_t = void (*)(float, float_2dspan, float_2dspan);
using func_d_d1d1_t = void (*)(double, double_1dspan, double_1dspan);
using func_d_d2d2_t = void (*)(double, double_2dspan, double_2dspan);
using func_F_F1F1_t = void (*)(cfloat, cfloat_1dspan, cfloat_1dspan);
using func_F_F2F2_t = void (*)(cfloat, cfloat_2dspan, cfloat_2dspan);
using func_D_D1D1_t = void (*)(cdouble, cdouble_1dspan, cdouble_1dspan);
using func_D_D2D2_t = void (*)(cdouble, cdouble_2dspan, cdouble_2dspan);

// 1 input, 3 outputs
using func_f_f1f1f1_t = void (*)(float, float_1dspan, float_1dspan, float_1dspan);
using func_f_f2f2f2_t = void (*)(float, float_2dspan, float_2dspan, float_2dspan);
using func_d_d1d1d1_t = void (*)(double, double_1dspan, double_1dspan, double_1dspan);
using func_d_d2d2d2_t = void (*)(double, double_2dspan, double_2dspan, double_2dspan);
using func_F_F1F1F1_t = void (*)(cfloat, cfloat_1dspan, cfloat_1dspan, cfloat_1dspan);
using func_D_D1D1D1_t = void (*)(cdouble, cdouble_1dspan, cdouble_1dspan, cdouble_1dspan);

// 2 inputs, 1 output
using func_ff_F2_t = void (*)(float, float, cfloat_2dspan);
using func_dd_D2_t = void (*)(double, double, cdouble_2dspan);
using func_qF_F2_t = void (*)(long long int, cfloat, cfloat_2dspan);
using func_qD_D2_t = void (*)(long long int, cdouble, cdouble_2dspan);

// 2 inputs, 2 outputs
using func_qF_F2F2_t = void (*)(long long int, cfloat, cfloat_2dspan, cfloat_2dspan);
using func_qD_D2D2_t = void (*)(long long int, cdouble, cdouble_2dspan, cdouble_2dspan);

// 2 inputs, 3 outputs
using func_qF_F2F2F2_t = void (*)(long long int, cfloat, cfloat_2dspan, cfloat_2dspan, cfloat_2dspan);
using func_qD_D2D2D2_t = void (*)(long long int, cdouble, cdouble_2dspan, cdouble_2dspan, cdouble_2dspan);

extern const char *lpn_all_doc;
extern const char *lpmn_doc;
extern const char *clpmn_doc;
extern const char *lqn_doc;
extern const char *lqmn_doc;
extern const char *rctj_doc;
extern const char *rcty_doc;
extern const char *sph_harm_all_doc;

// This is needed by sf_error, it is defined in the Cython "_ufuncs_extra_code_common.pxi" for "_generate_pyx.py".
// It exists to "call PyUFunc_getfperr in a context where PyUFunc_API array is initialized", but here we are
// already in such a context.
extern "C" int wrap_PyUFunc_getfperr() { return PyUFunc_getfperr(); }

static PyModuleDef _gufuncs_def = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_gufuncs",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit__gufuncs() {
    if (!SpecFun_Initialize()) {
        return nullptr;
    }

    PyObject *_gufuncs = PyModule_Create(&_gufuncs_def);
    if (_gufuncs == nullptr) {
        return nullptr;
    }

    PyObject *lpn_all = Py_BuildValue(
        "(N,N,N)",
        SpecFun_NewGUFunc(
            {static_cast<func_d_d1_t>(::lpn_all), static_cast<func_f_f1_t>(::lpn_all),
             static_cast<func_D_D1_t>(::lpn_all), static_cast<func_F_F1_t>(::lpn_all)},
            1, "lpn_all", lpn_all_doc, "()->(np1)"
        ),
        SpecFun_NewGUFunc(
            {static_cast<func_d_d1d1_t>(::lpn_all), static_cast<func_f_f1f1_t>(::lpn_all),
             static_cast<func_D_D1D1_t>(::lpn_all), static_cast<func_F_F1F1_t>(::lpn_all)},
            2, "lpn_all", lpn_all_doc, "()->(np1),(np1)"
        ),
        SpecFun_NewGUFunc(
            {static_cast<func_d_d1d1d1_t>(::lpn_all), static_cast<func_f_f1f1f1_t>(::lpn_all),
             static_cast<func_D_D1D1D1_t>(::lpn_all), static_cast<func_F_F1F1F1_t>(::lpn_all)},
            3, "lpn_all", lpn_all_doc, "()->(np1),(np1),(np1)"
        )
    );
    PyModule_AddObjectRef(_gufuncs, "lpn_all", lpn_all);

    PyObject *lpmn_all = Py_BuildValue(
        "{O:N}", Py_False,
        Py_BuildValue(
            "(N,N,N)",
            SpecFun_NewGUFunc(
                {static_cast<func_d_d2_t>(::lpmn_all), static_cast<func_f_f2_t>(::lpmn_all)}, 1, "lpmn_all", lpmn_doc,
                "()->(mpmp1,np1)"
            ),
            SpecFun_NewGUFunc(
                {static_cast<func_d_d2d2_t>(::lpmn_all), static_cast<func_f_f2f2_t>(::lpmn_all)}, 2, "lpmn_all",
                lpmn_doc, "()->(mpmp1,np1),(mpmp1,np1)"
            ),
            SpecFun_NewGUFunc(
                {static_cast<func_d_d2d2d2_t>(::lpmn_all), static_cast<func_f_f2f2f2_t>(::lpmn_all)}, 3, "lpmn_all",
                lpmn_doc, "()->(mpmp1,np1),(mpmp1,np1),(mpmp1,np1)"
            )
        )
    );
    PyModule_AddObjectRef(_gufuncs, "lpmn_all", lpmn_all);

    PyObject *clpmn_all = Py_BuildValue(
        "{O:N}", Py_False,
        Py_BuildValue(
            "(N,N,N)",
            SpecFun_NewGUFunc(
                {static_cast<func_qD_D2_t>(::clpmn_all), static_cast<func_qF_F2_t>(::clpmn_all)}, 1, "clpmn_all",
                clpmn_doc, "(),()->(mpmp1,np1)"
            ),
            SpecFun_NewGUFunc(
                {static_cast<func_qD_D2D2_t>(::clpmn_all), static_cast<func_qF_F2F2_t>(::clpmn_all)}, 2, "clpmn_all",
                clpmn_doc, "(),()->(mpmp1,np1),(mpmp1,np1)"
            ),
            SpecFun_NewGUFunc(
                {static_cast<func_qD_D2D2D2_t>(::clpmn_all), static_cast<func_qF_F2F2F2_t>(::clpmn_all)}, 3,
                "clpmn_all", clpmn_doc, "(),()->(mpmp1,np1),(mpmp1,np1),(mpmp1,np1)"
            )
        )
    );
    PyModule_AddObjectRef(_gufuncs, "clpmn_all", clpmn_all);

    PyObject *_lqn = SpecFun_NewGUFunc(
        {static_cast<func_d_d1d1_t>(special::lqn), static_cast<func_f_f1f1_t>(special::lqn),
         static_cast<func_D_D1D1_t>(special::lqn), static_cast<func_F_F1F1_t>(special::lqn)},
        2, "_lqn", lqn_doc, "()->(np1),(np1)"
    );
    PyModule_AddObjectRef(_gufuncs, "_lqn", _lqn);

    PyObject *_lqmn = SpecFun_NewGUFunc(
        {static_cast<func_d_d2d2_t>(special::lqmn), static_cast<func_f_f2f2_t>(special::lqmn),
         static_cast<func_D_D2D2_t>(special::lqmn), static_cast<func_F_F2F2_t>(special::lqmn)},
        2, "_lqmn", lqmn_doc, "()->(mp1,np1),(mp1,np1)"
    );
    PyModule_AddObjectRef(_gufuncs, "_lqmn", _lqmn);

    PyObject *_sph_harm_all = SpecFun_NewGUFunc(
        {static_cast<func_dd_D2_t>(special::sph_harm_all), static_cast<func_ff_F2_t>(special::sph_harm_all)}, 1,
        "_sph_harm_all", sph_harm_all_doc, "(),()->(mp1,np1)"
    );
    PyModule_AddObjectRef(_gufuncs, "_sph_harm_all", _sph_harm_all);

    PyObject *_rctj = SpecFun_NewGUFunc(
        {static_cast<func_d_d1d1_t>(special::rctj), static_cast<func_f_f1f1_t>(special::rctj)}, 2, "_rctj", rctj_doc,
        "()->(np1),(np1)"
    );
    PyModule_AddObjectRef(_gufuncs, "_rctj", _rctj);

    PyObject *_rcty = SpecFun_NewGUFunc(
        {static_cast<func_d_d1d1_t>(special::rcty), static_cast<func_f_f1f1_t>(special::rcty)}, 2, "_rcty", rcty_doc,
        "()->(np1),(np1)"
    );
    PyModule_AddObjectRef(_gufuncs, "_rcty", _rcty);

    return _gufuncs;
}
