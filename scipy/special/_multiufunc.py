import inspect
import numpy as np

class MultiUFunc:
    __slots__ = ["ufuncs", "resolve_out_shapes", "resolve_ufunc",
                 "__forces_complex_output"]
    def __init__(self, ufuncs, *, resolve_ufunc=None, resolve_out_shapes=None,
                 force_complex_output=False):
        self.ufuncs = ufuncs
        self.resolve_out_shapes = resolve_out_shapes
        self.resolve_ufunc = resolve_ufunc
        self.__forces_complex_output = force_complex_output

    @property
    def forces_complex_output(self):
        return self.__forces_complex_output

    def as_resolve_ufunc(self, func):
        sig = inspect.signature(func)
        params = list(inspect.signature(func).parameters.values())[1:]
        new_sig = sig.replace(parameters=params)

        def wrapper(**kwargs):
            return func(self.ufuncs, **kwargs)

        wrapper.__signature__ = new_sig
        wrapper.__doc__ = \
            """Resolve to a ufunc based on keyword arguments."""
        self.resolve_ufunc = wrapper

    def as_resolve_out_shapes(self, func):
        self.resolve_out_shapes = func

    def __call__(self, *args, **kwargs):
        ufunc = self.resolve_ufunc(**kwargs)
        if ((ufunc.nout == 0) or (self.resolve_out_shapes is None)):
            return ufunc(*args)

        ufunc_args = args[-ufunc.nin:] # array arguments to be passed to the ufunc

        ufunc_arg_shapes = tuple(np.shape(ufunc_arg) for ufunc_arg in ufunc_args)
        ufunc_out_shapes = self.resolve_out_shapes(*args[:-ufunc.nin],
            *ufunc_arg_shapes, ufunc.nout)

        ufunc_arg_dtypes = tuple((ufunc_arg.dtype if hasattr(ufunc_arg, 'dtype')
            else np.dtype(type(ufunc_arg))) for ufunc_arg in ufunc_args)
        if hasattr(ufunc, 'resolve_dtypes'):
            ufunc_dtypes = ufunc_arg_dtypes + ufunc.nout * (None,)
            ufunc_dtypes = ufunc.resolve_dtypes(ufunc_dtypes) 
            ufunc_out_dtypes = ufunc_dtypes[-ufunc.nout:]
        else:
            ufunc_out_dtype = np.result_type(*ufunc_arg_dtypes)
            if (not np.issubdtype(ufunc_out_dtype, np.inexact)):
                ufunc_out_dtype = np.float64

            ufunc_out_dtypes = ufunc.nout * (ufunc_out_dtype,)

        if self.forces_complex_output:
            ufunc_out_dtypes = tuple(np.result_type(1j, ufunc_out_dtype)
                for ufunc_out_dtype in ufunc_out_dtypes)

        b = np.broadcast(*ufunc_args)
        ufunc_out_new_dims = tuple(len(ufunc_out_shape) - b.ndim
            for ufunc_out_shape in ufunc_out_shapes)

        out = tuple(np.empty(ufunc_out_shape, dtype = ufunc_out_dtype)
            for ufunc_out_shape, ufunc_out_dtype
            in zip(ufunc_out_shapes, ufunc_out_dtypes))

        ufunc_out = tuple(np.moveaxis(out[i],
            tuple(range(axis)), tuple(range(-axis, 0)))
            for i, axis in enumerate(ufunc_out_new_dims))
        ufunc(*ufunc_args, out = ufunc_out)

        if (len(out) == 1):
            out, = out

        return out
