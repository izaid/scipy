#include <vector>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <numpy/arrayobject.h>
#include <numpy/npy_3kcompat.h>
#include <numpy/ufuncobject.h>

// Just initializes everything needed, can also go in a common header
bool SpecFun_Initialize() {
    Py_Initialize();

    import_array();
    if (PyErr_Occurred()) {
        // import array failed
        return false;
    }

    import_umath();
    if (PyErr_Occurred()) {
        // import umath failed
        return false;
    }

    return true;
}

#if (PY_VERSION_HEX < 0x030a00f0)
// this is in Python >=3.10
int PyModule_AddObjectRef(PyObject *module, const char *name, PyObject *value) {
    Py_INCREF(value);
    return PyModule_AddObject(module, name, value);
}
#endif

template <typename T>
struct npy_type;

template <>
struct npy_type<double> {
    static constexpr int value = NPY_FLOAT64;
};

template <>
struct npy_type<std::complex<double>> {
    static constexpr int value = NPY_COMPLEX128;
};

template <auto F>
struct ufunc_traits;

template <typename Res, typename Arg0, Res (*F)(Arg0)>
struct ufunc_traits<F> {
    static constexpr int nin = 1;
    static constexpr int nout = 1;

    static constexpr char type[2] = {npy_type<Arg0>::value, npy_type<Res>::value};

    static void func(char **args, const npy_intp *dimensions, const npy_intp *steps, void *data) {
        for (npy_intp i = 0; i < dimensions[0]; ++i) {
            *reinterpret_cast<Res *>(args[1]) = F(*reinterpret_cast<Arg0 *>(args[0]));

            args[0] += steps[0];
            args[1] += steps[1];
        }
    }
};

template <size_t NTypes, size_t NIn, size_t NOut>
struct SpecFun_UFuncFuncAndData {
    static constexpr int ntypes = NTypes;
    static constexpr int nin = NIn;
    static constexpr int nout = NOut;

    PyUFuncGenericFunction func[ntypes];
    char types[ntypes * (nin + nout)];
    void *data[ntypes];

    SpecFun_UFuncFuncAndData(std::initializer_list<PyUFuncGenericFunction> func,
                             std::initializer_list<const char *> types) {
        std::copy(func.begin(), func.end(), this->func);

        for (auto it = types.begin(); it != types.end(); ++it) {
            std::copy(*it, *it + nin + nout, this->types + (it - types.begin()) * (nin + nout));
        }

        std::fill_n(data, ntypes, nullptr);
    }
};

// This function now generates a ufunc
template <auto F0, auto... F>
PyObject *SpecFun_UFunc(const char *name, const char *doc) {
    static_assert(((ufunc_traits<F0>::nin == ufunc_traits<F>::nin) && ... && true),
                  "number of inputs must be the same for all functions");
    static_assert(((ufunc_traits<F0>::nout == ufunc_traits<F>::nout) && ... && true),
                  "number of outputs must be the same for all functions");

    using func_and_data_type =
        SpecFun_UFuncFuncAndData<sizeof...(F) + 1, ufunc_traits<F0>::nin, ufunc_traits<F0>::nout>;

    static std::vector<func_and_data_type> entries;
    entries.push_back(
        {{ufunc_traits<F0>::func, ufunc_traits<F>::func...}, {ufunc_traits<F0>::type, ufunc_traits<F>::type...}});

    func_and_data_type &func_and_data = entries.back();
    return PyUFunc_FromFuncAndData(func_and_data.func, func_and_data.data, func_and_data.types,
                                   func_and_data_type::ntypes, func_and_data_type::nin, func_and_data_type::nout,
                                   PyUFunc_None, name, doc, 0);
}