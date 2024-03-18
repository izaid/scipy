const char *bei_doc = R"(
    bei(x, out=None)

    Kelvin function bei.

    Defined as

    .. math::

        \mathrm{bei}(x) = \Im[J_0(x e^{3 \pi i / 4})]

    where :math:`J_0` is the Bessel function of the first kind of
    order zero (see `jv`). See [dlmf]_ for more details.

    Parameters
    ----------
    x : array_like
        Real argument.
    out : ndarray, optional
        Optional output array for the function results.

    Returns
    -------
    scalar or ndarray
        Values of the Kelvin function.

    See Also
    --------
    ber : the corresponding real part
    beip : the derivative of bei
    jv : Bessel function of the first kind

    References
    ----------
    .. [dlmf] NIST, Digital Library of Mathematical Functions,
        https://dlmf.nist.gov/10.61

    Examples
    --------
    It can be expressed using Bessel functions.

    >>> import numpy as np
    >>> import scipy.special as sc
    >>> x = np.array([1.0, 2.0, 3.0, 4.0])
    >>> sc.jv(0, x * np.exp(3 * np.pi * 1j / 4)).imag
    array([0.24956604, 0.97229163, 1.93758679, 2.29269032])
    >>> sc.bei(x)
    array([0.24956604, 0.97229163, 1.93758679, 2.29269032])

    )";

const char *beip_doc = R"(
    beip(x, out=None)

    Derivative of the Kelvin function bei.

    Parameters
    ----------
    x : array_like
        Real argument.
    out : ndarray, optional
        Optional output array for the function results.

    Returns
    -------
    scalar or ndarray
        The values of the derivative of bei.

    See Also
    --------
    bei

    References
    ----------
    .. [dlmf] NIST, Digital Library of Mathematical Functions,
        https://dlmf.nist.gov/10#PT5

    )";

const char *ber_doc = R"(
    ber(x, out=None)

    Kelvin function ber.

    Defined as

    .. math::

        \mathrm{ber}(x) = \Re[J_0(x e^{3 \pi i / 4})]

    where :math:`J_0` is the Bessel function of the first kind of
    order zero (see `jv`). See [dlmf]_ for more details.

    Parameters
    ----------
    x : array_like
        Real argument.
    out : ndarray, optional
        Optional output array for the function results.

    Returns
    -------
    scalar or ndarray
        Values of the Kelvin function.

    See Also
    --------
    bei : the corresponding real part
    berp : the derivative of bei
    jv : Bessel function of the first kind

    References
    ----------
    .. [dlmf] NIST, Digital Library of Mathematical Functions,
        https://dlmf.nist.gov/10.61

    Examples
    --------
    It can be expressed using Bessel functions.

    >>> import numpy as np
    >>> import scipy.special as sc
    >>> x = np.array([1.0, 2.0, 3.0, 4.0])
    >>> sc.jv(0, x * np.exp(3 * np.pi * 1j / 4)).real
    array([ 0.98438178,  0.75173418, -0.22138025, -2.56341656])
    >>> sc.ber(x)
    array([ 0.98438178,  0.75173418, -0.22138025, -2.56341656])

    )";

const char *berp_doc = R"(
    berp(x, out=None)

    Derivative of the Kelvin function ber.

    Parameters
    ----------
    x : array_like
        Real argument.
    out : ndarray, optional
        Optional output array for the function results.

    Returns
    -------
    scalar or ndarray
        The values of the derivative of ber.

    See Also
    --------
    ber

    References
    ----------
    .. [dlmf] NIST, Digital Library of Mathematical Functions,
        https://dlmf.nist.gov/10#PT5

    )";

const char *exp1_doc = R"(
    exp1(z, out=None)

    Exponential integral E1.

    For complex :math:`z \ne 0` the exponential integral can be defined as
    [1]_

    .. math::

       E_1(z) = \int_z^\infty \frac{e^{-t}}{t} dt,

    where the path of the integral does not cross the negative real
    axis or pass through the origin.

    Parameters
    ----------
    z: array_like
        Real or complex argument.
    out : ndarray, optional
        Optional output array for the function results

    Returns
    -------
    scalar or ndarray
        Values of the exponential integral E1

    See Also
    --------
    expi : exponential integral :math:`Ei`
    expn : generalization of :math:`E_1`

    Notes
    -----
    For :math:`x > 0` it is related to the exponential integral
    :math:`Ei` (see `expi`) via the relation

    .. math::

       E_1(x) = -Ei(-x).

    References
    ----------
    .. [1] Digital Library of Mathematical Functions, 6.2.1
           https://dlmf.nist.gov/6.2#E1

    Examples
    --------
    >>> import numpy as np
    >>> import scipy.special as sc

    It has a pole at 0.

    >>> sc.exp1(0)
    inf

    It has a branch cut on the negative real axis.

    >>> sc.exp1(-1)
    nan
    >>> sc.exp1(complex(-1, 0))
    (-1.8951178163559368-3.141592653589793j)
    >>> sc.exp1(complex(-1, -0.0))
    (-1.8951178163559368+3.141592653589793j)

    It approaches 0 along the positive real axis.

    >>> sc.exp1([1, 10, 100, 1000])
    array([2.19383934e-01, 4.15696893e-06, 3.68359776e-46, 0.00000000e+00])

    It is related to `expi`.

    >>> x = np.array([1, 2, 3, 4])
    >>> sc.exp1(x)
    array([0.21938393, 0.04890051, 0.01304838, 0.00377935])
    >>> -sc.expi(-x)
    array([0.21938393, 0.04890051, 0.01304838, 0.00377935])

    )";

const char *expi_doc = R"(
    expi(x, out=None)

    Exponential integral Ei.

    For real :math:`x`, the exponential integral is defined as [1]_

    .. math::

        Ei(x) = \int_{-\infty}^x \frac{e^t}{t} dt.

    For :math:`x > 0` the integral is understood as a Cauchy principal
    value.

    It is extended to the complex plane by analytic continuation of
    the function on the interval :math:`(0, \infty)`. The complex
    variant has a branch cut on the negative real axis.

    Parameters
    ----------
    x : array_like
        Real or complex valued argument
    out : ndarray, optional
        Optional output array for the function results

    Returns
    -------
    scalar or ndarray
        Values of the exponential integral

    See Also
    --------
    exp1 : Exponential integral :math:`E_1`
    expn : Generalized exponential integral :math:`E_n`

    Notes
    -----
    The exponential integrals :math:`E_1` and :math:`Ei` satisfy the
    relation

    .. math::

        E_1(x) = -Ei(-x)

    for :math:`x > 0`.

    References
    ----------
    .. [1] Digital Library of Mathematical Functions, 6.2.5
           https://dlmf.nist.gov/6.2#E5

    Examples
    --------
    >>> import numpy as np
    >>> import scipy.special as sc

    It is related to `exp1`.

    >>> x = np.array([1, 2, 3, 4])
    >>> -sc.expi(-x)
    array([0.21938393, 0.04890051, 0.01304838, 0.00377935])
    >>> sc.exp1(x)
    array([0.21938393, 0.04890051, 0.01304838, 0.00377935])

    The complex variant has a branch cut on the negative real axis.

    >>> sc.expi(-1 + 1e-12j)
    (-0.21938393439552062+3.1415926535894254j)
    >>> sc.expi(-1 - 1e-12j)
    (-0.21938393439552062-3.1415926535894254j)

    As the complex variant approaches the branch cut, the real parts
    approach the value of the real variant.

    >>> sc.expi(-1)
    -0.21938393439552062

    The SciPy implementation returns the real variant for complex
    values on the branch cut.

    >>> sc.expi(complex(-1, 0.0))
    (-0.21938393439552062-0j)
    >>> sc.expi(complex(-1, -0.0))
    (-0.21938393439552062-0j)

    )";

const char *it2i0k0_doc = R"(
    it2i0k0(x, out=None)

    Integrals related to modified Bessel functions of order 0.

    Computes the integrals

    .. math::

        \int_0^x \frac{I_0(t) - 1}{t} dt \\
        \int_x^\infty \frac{K_0(t)}{t} dt.

    Parameters
    ----------
    x : array_like
        Values at which to evaluate the integrals.
    out : tuple of ndarrays, optional
        Optional output arrays for the function results.

    Returns
    -------
    ii0 : scalar or ndarray
        The integral for `i0`
    ik0 : scalar or ndarray
        The integral for `k0`

    References
    ----------
    .. [1] S. Zhang and J.M. Jin, "Computation of Special Functions",
           Wiley 1996

    Examples
    --------
    Evaluate the functions at one point.

    >>> from scipy.special import it2i0k0
    >>> int_i, int_k = it2i0k0(1.)
    >>> int_i, int_k
    (0.12897944249456852, 0.2085182909001295)

    Evaluate the functions at several points.

    >>> import numpy as np
    >>> points = np.array([0.5, 1.5, 3.])
    >>> int_i, int_k = it2i0k0(points)
    >>> int_i, int_k
    (array([0.03149527, 0.30187149, 1.50012461]),
     array([0.66575102, 0.0823715 , 0.00823631]))

    Plot the functions from 0 to 5.

    >>> import matplotlib.pyplot as plt
    >>> fig, ax = plt.subplots()
    >>> x = np.linspace(0., 5., 1000)
    >>> int_i, int_k = it2i0k0(x)
    >>> ax.plot(x, int_i, label=r"$\int_0^x \frac{I_0(t)-1}{t}\,dt$")
    >>> ax.plot(x, int_k, label=r"$\int_x^{\infty} \frac{K_0(t)}{t}\,dt$")
    >>> ax.legend()
    >>> ax.set_ylim(0, 10)
    >>> plt.show()
    )";

const char *it2j0y0_doc = R"(
    it2j0y0(x, out=None)

    Integrals related to Bessel functions of the first kind of order 0.

    Computes the integrals

    .. math::

        \int_0^x \frac{1 - J_0(t)}{t} dt \\
        \int_x^\infty \frac{Y_0(t)}{t} dt.

    For more on :math:`J_0` and :math:`Y_0` see `j0` and `y0`.

    Parameters
    ----------
    x : array_like
        Values at which to evaluate the integrals.
    out : tuple of ndarrays, optional
        Optional output arrays for the function results.

    Returns
    -------
    ij0 : scalar or ndarray
        The integral for `j0`
    iy0 : scalar or ndarray
        The integral for `y0`

    References
    ----------
    .. [1] S. Zhang and J.M. Jin, "Computation of Special Functions",
           Wiley 1996

    Examples
    --------
    Evaluate the functions at one point.

    >>> from scipy.special import it2j0y0
    >>> int_j, int_y = it2j0y0(1.)
    >>> int_j, int_y
    (0.12116524699506871, 0.39527290169929336)

    Evaluate the functions at several points.

    >>> import numpy as np
    >>> points = np.array([0.5, 1.5, 3.])
    >>> int_j, int_y = it2j0y0(points)
    >>> int_j, int_y
    (array([0.03100699, 0.26227724, 0.85614669]),
     array([ 0.26968854,  0.29769696, -0.02987272]))

    Plot the functions from 0 to 10.

    >>> import matplotlib.pyplot as plt
    >>> fig, ax = plt.subplots()
    >>> x = np.linspace(0., 10., 1000)
    >>> int_j, int_y = it2j0y0(x)
    >>> ax.plot(x, int_j, label=r"$\int_0^x \frac{1-J_0(t)}{t}\,dt$")
    >>> ax.plot(x, int_y, label=r"$\int_x^{\infty} \frac{Y_0(t)}{t}\,dt$")
    >>> ax.legend()
    >>> ax.set_ylim(-2.5, 2.5)
    >>> plt.show()
    )";

const char *it2struve0_doc = R"(
    it2struve0(x, out=None)

    Integral related to the Struve function of order 0.

    Returns the integral,

    .. math::
        \int_x^\infty \frac{H_0(t)}{t}\,dt

    where :math:`H_0` is the Struve function of order 0.

    Parameters
    ----------
    x : array_like
        Lower limit of integration.
    out : ndarray, optional
        Optional output array for the function values

    Returns
    -------
    I : scalar or ndarray
        The value of the integral.

    See Also
    --------
    struve

    Notes
    -----
    Wrapper for a Fortran routine created by Shanjie Zhang and Jianming
    Jin [1]_.

    References
    ----------
    .. [1] Zhang, Shanjie and Jin, Jianming. "Computation of Special
           Functions", John Wiley and Sons, 1996.
           https://people.sc.fsu.edu/~jburkardt/f_src/special_functions/special_functions.html

    Examples
    --------
    Evaluate the function at one point.

    >>> import numpy as np
    >>> from scipy.special import it2struve0
    >>> it2struve0(1.)
    0.9571973506383524

    Evaluate the function at several points by supplying
    an array for `x`.

    >>> points = np.array([1., 2., 3.5])
    >>> it2struve0(points)
    array([0.95719735, 0.46909296, 0.10366042])

    Plot the function from -10 to 10.

    >>> import matplotlib.pyplot as plt
    >>> x = np.linspace(-10., 10., 1000)
    >>> it2struve0_values = it2struve0(x)
    >>> fig, ax = plt.subplots()
    >>> ax.plot(x, it2struve0_values)
    >>> ax.set_xlabel(r'$x$')
    >>> ax.set_ylabel(r'$\int_x^{\infty}\frac{H_0(t)}{t}\,dt$')
    >>> plt.show()
    )";

const char *itairy_doc = R"(
    itairy(x, out=None)

    Integrals of Airy functions

    Calculates the integrals of Airy functions from 0 to `x`.

    Parameters
    ----------

    x : array_like
        Upper limit of integration (float).
    out : tuple of ndarray, optional
        Optional output arrays for the function values

    Returns
    -------
    Apt : scalar or ndarray
        Integral of Ai(t) from 0 to x.
    Bpt : scalar or ndarray
        Integral of Bi(t) from 0 to x.
    Ant : scalar or ndarray
        Integral of Ai(-t) from 0 to x.
    Bnt : scalar or ndarray
        Integral of Bi(-t) from 0 to x.

    Notes
    -----

    Wrapper for a Fortran routine created by Shanjie Zhang and Jianming
    Jin [1]_.

    References
    ----------

    .. [1] Zhang, Shanjie and Jin, Jianming. "Computation of Special
           Functions", John Wiley and Sons, 1996.
           https://people.sc.fsu.edu/~jburkardt/f_src/special_functions/special_functions.html

    Examples
    --------
    Compute the functions at ``x=1.``.

    >>> import numpy as np
    >>> from scipy.special import itairy
    >>> import matplotlib.pyplot as plt
    >>> apt, bpt, ant, bnt = itairy(1.)
    >>> apt, bpt, ant, bnt
    (0.23631734191710949,
     0.8727691167380077,
     0.46567398346706845,
     0.3730050096342943)

    Compute the functions at several points by providing a NumPy array for `x`.

    >>> x = np.array([1., 1.5, 2.5, 5])
    >>> apt, bpt, ant, bnt = itairy(x)
    >>> apt, bpt, ant, bnt
    (array([0.23631734, 0.28678675, 0.324638  , 0.33328759]),
     array([  0.87276912,   1.62470809,   5.20906691, 321.47831857]),
     array([0.46567398, 0.72232876, 0.93187776, 0.7178822 ]),
     array([ 0.37300501,  0.35038814, -0.02812939,  0.15873094]))

    Plot the functions from -10 to 10.

    >>> x = np.linspace(-10, 10, 500)
    >>> apt, bpt, ant, bnt = itairy(x)
    >>> fig, ax = plt.subplots(figsize=(6, 5))
    >>> ax.plot(x, apt, label=r"$\int_0^x\, Ai(t)\, dt$")
    >>> ax.plot(x, bpt, ls="dashed", label=r"$\int_0^x\, Bi(t)\, dt$")
    >>> ax.plot(x, ant, ls="dashdot", label=r"$\int_0^x\, Ai(-t)\, dt$")
    >>> ax.plot(x, bnt, ls="dotted", label=r"$\int_0^x\, Bi(-t)\, dt$")
    >>> ax.set_ylim(-2, 1.5)
    >>> ax.legend(loc="lower right")
    >>> plt.show()
    )";