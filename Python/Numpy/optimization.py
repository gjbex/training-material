#!/usr/bin/env python


# this function has:
#  * a minimum at [x == -1.012273212379936, y == 0.0]
#    (f_xx*f_yy - f_xy**2 > 0 and f_xx > 0)
#  * a saddle point at [x == 0.9872574572835215, y == 0.0]
#    (f_xx*f__y - f_xy**2 < 0)
#  * a maximum at [x == 0.02501565538380409, y == 0.0]
#    (f_xx*f_yy - f_xy**2 > 0 and f_xx < 0)
def func(X, y=None):
    if y is None:
        x, y = X
    else:
        x = X
    return (x**2 + y**2)**2 - 2*x**2 - 2*y**2 + 0.1*x


def func_grad(X):
    x, y = X
    func_x = 4*(x**2 + y**2)*x - 4*x + 0.1
    func_y = 4*(x**2 + y**2)*y - 4*y
    return np.array([func_x, func_y])


def func_hess(X):
    x, y = X
    func_x_x = 12*x**2 + 4*y**2 - 4
    func_x_y = 8*x*y
    func_y_x = 8*x*y
    func_y_y = 4*x**2 + 12*y**2 - 4
    return np.array([[func_x_x, func_x_y], [func_y_x, func_y_y]])


def check_solution(x):
    from scipy.linalg import det
    hessian = func_hess(x)
    det_hessian = det(hessian)
    type_str = '  ||H|| = {0:.4f}'.format(det_hessian)
    if det_hessian > 0.0:
        type_str += ', f_xx = {0:.4f}'.format(hessian[0, 0])
        if hessian[0, 0] > 0.0:
            type_str += ': relative minimum'
        else:
            type_str += ': relative maximum'
    elif det_hessian < 0.0:
        type_str += ': saddle point'
    else:
        type_str += ': inconclusive'
    print(type_str)

if __name__ == '__main__':
    from argparse import ArgumentParser
    import time
    import numpy as np
    import scipy.optimize as opt

# handle command line arguments
    arg_parser = ArgumentParser(description='optimize a 2D-function')
    arg_parser.add_argument('--x0', type=float, default=1.0,
                            help='initial x-value')
    arg_parser.add_argument('--y0', type=float, default=0.0,
                            help='initial y-value')
    arg_parser.add_argument('--xtol', type=float, default=1.0e-4,
                            help='line-search error tolerance (Powell)')
    arg_parser.add_argument('--ftol', type=float, default=1.0e-4,
                            help='relative error in function value '
                                 'acceptable for convergence (Powell)')
    arg_parser.add_argument('--gtol', type=float, default=1.0e-5,
                            help='stop when the norm of the gradient is '
                                 'less than gtol (CG & BFGS)')
    arg_parser.add_argument('--avextol', type=float, default=1.0e-5,
                            help='stop when the average relative error is '
                                 'less than gtol (N-CG)')
    arg_parser.add_argument('--check', action='store_true',
                            help='check critical point')
    options = arg_parser.parse_args()

# Powell's method
    x0 = np.array([options.x0, options.y0])
    start = time.time()
    xopt, fopt, _, iter, funcalls, warnflag = opt.fmin_powell(
                                                  func, x0,
                                                  xtol=options.xtol,
                                                  ftol=options.ftol,
                                                  full_output=True,
                                                  disp=False
                                              )
    durationn = time.time() - start
    output_str = '  minimum {fopt:.15} at ({x:.15}, {y:.15})'
    info_str = '  needed {iter} iterations, {calls} function calls'
    time_str = '  in {sec:.6f} seocnds'
    warn_str = '  result flag = {flag}'
    print("Powell's method:")
    print(output_str.format(fopt=fopt, x=xopt[0], y=xopt[1]))
    print(info_str.format(iter=iter, calls=funcalls))
    print(time_str.format(sec=durationn))
    print(warn_str.format(flag=warnflag))
    if options.check:
        check_solution(xopt)

# conjugate gradient method
    x0 = np.array([options.x0, options.y0])
    start = time.time()
    xopt, fopt, funcalls, gradcalls, warnflag = opt.fmin_cg(
                                                    func, x0,
                                                    fprime=func_grad,
                                                    gtol=options.gtol,
                                                    full_output=True,
                                                    disp=False
                                                )
    durationn = time.time() - start
    output_str = '  minimum {fopt:.15} at ({x:.15}, {y:.15})'
    info_str = '  needed {calls} function calls, {gradcalls} gradient calls'
    time_str = '  in {sec:.6f} seocnds'
    warn_str = '  result flag = {flag}'
    print('\nconjugate gradient method')
    print(output_str.format(fopt=fopt, x=xopt[0], y=xopt[1]))
    print(info_str.format(calls=funcalls, gradcalls=gradcalls))
    print(time_str.format(sec=durationn))
    print(warn_str.format(flag=warnflag))
    if options.check:
        check_solution(xopt)

# Broyden-Fletcher-Goldfarb-Shanno algorithm
    x0 = np.array([options.x0, options.y0])
    start = time.time()
    xopt, fopt, _, _, funcalls, gradcalls, warnflag = opt.fmin_bfgs(
                                                          func, x0,
                                                          fprime=func_grad,
                                                          gtol=options.gtol,
                                                          full_output=True,
                                                          disp=False
                                                      )
    durationn = time.time() - start
    output_str = '  minimum {fopt:.15} at ({x:.15}, {y:.15})'
    info_str = '  needed {calls} function calls, {gradcalls} gradient calls'
    time_str = '  in {sec:.6f} seocnds'
    warn_str = '  result flag = {flag}'
    print('\nBFGS method')
    print(output_str.format(fopt=fopt, x=xopt[0], y=xopt[1]))
    print(info_str.format(calls=funcalls, gradcalls=gradcalls))
    print(time_str.format(sec=durationn))
    print(warn_str.format(flag=warnflag))
    if options.check:
        check_solution(xopt)

# Newton conjugate gradient method
    x0 = np.array([options.x0, options.y0])
    start = time.time()
    xopt, fopt, funcalls, gradcalls, hesscalls, warnflag = opt.fmin_ncg(
                                                    func, x0,
                                                    fprime=func_grad,
                                                    fhess=func_hess,
                                                    avextol=options.avextol,
                                                    full_output=True,
                                                    disp=False
                                                )
    durationn = time.time() - start
    output_str = '  minimum {fopt:.15} at ({x:.15}, {y:.15})'
    info_str = ('  needed {calls} function calls'
                ', {gradcalls} gradient calls'
                ', {hesscalls} Hessian calls')
    time_str = '  in {sec:.6f} seocnds'
    warn_str = '  result flag = {flag}'
    print('\nNewton conjugate gradient method')
    print(output_str.format(fopt=fopt, x=xopt[0], y=xopt[1]))
    print(info_str.format(calls=funcalls, gradcalls=gradcalls,
                          hesscalls=hesscalls))
    print(time_str.format(sec=durationn))
    print(warn_str.format(flag=warnflag))
    if options.check:
        check_solution(xopt)
