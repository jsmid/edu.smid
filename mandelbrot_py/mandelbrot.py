
def generate_plot(k, xn, yn, xmin, xmax, ymin, ymax, maxiter, horizon):
    log_horizon = np.log(np.log(horizon)) / np.log(2)
    Z, N = mandelbrot_set(xmin, xmax, ymin, ymax, xn, yn, maxiter, horizon)
    # Most pictures of the exterior of the Mandelbrot set use the "escape count" of the
    # iteration. The "escape count" is the number of times that the iteration is performed
    # until the iterated value exceeds some radius. Normally, this count is an integer, and
    # thus, when it is used to select a color, "bands" (areas of constant color) appear.
    #
    # Banding can be eliminated by using a fractional escape count. There are many ways that
    # a fractional escape count can be computed. One possible way of obtaining a fraction is
    # to measure how far the iterated point landed outside of the escape cutoff. One of the
    # smoothest, most mathematically correct formulas is the "renormalized" iteration count.
    #
    # General formula of Mandelbrot equation z(n+1) = z(n) ^ k + c, the renormalized count is
    # mu = N + 1 - log (log  |Z(N)|) / log k
    # Ignoring the +C in the usual formula, the orbit point grows by Z := Z^2.
    # So we have the progression Z, Z^2, Z^4, Z^8, Z^16, etc. Iteration counting
    # amounts to assigning an integer to these values. Ignoring a multiplier,
    # the log of this sequence is: 1, 2, 4, 8, 16. The log-log is 0, 1, 2, 3, 4
    # which matches the integer value from the iteration counting. So the appropriate
    # generalization of the discrete iteration counting to a continuous function would be
    # the double log.
    # https://www.ibm.com/developerworks/community/blogs/jfp/entry/My_Christmas_Gift
    # This line will generate warnings for null values but it is faster to
    # process them afterwards using the nan_to_num
    with np.errstate(invalid='ignore'):
        M = np.nan_to_num(
            N + 1 - np.log(np.log(abs(Z))) / np.log(k) + log_horizon)
    dpi = 72
    width = 10
    height = 10 * yn / xn
    fig = plt.figure(figsize=(width, height), dpi=dpi)
    ax = fig.add_axes([0.0, 0.0, 1.0, 1.0], frameon=False, aspect=1)
    # Shaded rendering
    # norm=colors.PowerNorm(0.3), vert_exag=1.5
    light = colors.LightSource(azdeg=315, altdeg=10)
    M = light.shade(M, cmap=plt.cm.hot, norm=colors.PowerNorm(0.3), vert_exag=1.5, 
        blend_mode='hsv')
    plt.imshow(M, extent=[xmin, xmax, ymin, ymax], interpolation="gaussian")
    ax.set_xticks([])
    ax.set_yticks([])
    
    return plt

"""
===================================
Shaded & power normalized rendering
===================================

The Mandelbrot set rendering can be improved by using a normalized recount
associated with a power normalized colormap (gamma=0.3). Rendering can be
further enhanced thanks to shading.

The `maxiter` gives the precision of the computation. `maxiter=200` should
take a few seconds on most modern laptops.
"""
import numpy as np
import time

k = 2.0

def mandelbrot_set(xmin, xmax, ymin, ymax, xn, yn, maxiter, horizon=2.0):
    X = np.linspace(xmin, xmax, xn, dtype=np.float64)
    Y = np.linspace(ymin, ymax, yn, dtype=np.float64)
    C = X + Y[:, None]*1j
    N = np.zeros(C.shape, dtype=int)
    Z = np.zeros(C.shape, np.complex128)
    prev_done   = 0.
    start_s = int(round(time.time()))
    for n in range(maxiter):
        tmp = n / float(maxiter)
        if (tmp - prev_done) > .05 :
            prev_done = tmp
            time_s = int(round(time.time()))
            used_time = time_s - start_s
            print ("%s %% completed, estimated time to finish %s seconds"
                  % ( int(prev_done*100), int((used_time/prev_done)-used_time)))
        I = np.less(abs(Z), horizon)
        N[I] = n
        Z[I] = Z[I]**k + C[I]
    N[N == maxiter-1] = 0
    return Z, N

if __name__ == '__main__':
    from matplotlib import colors
    import matplotlib.pyplot as plt

    orig_coords_x = (-2.25, +0.75, int(3000/2))
    orig_coords_y = (-1.25, +1.25, int(2500/2))
    orig_max_iter = 200

    xmin, xmax, xn = orig_coords_x
    ymin, ymax, yn = orig_coords_y
    maxiter = 1000
    horizon = 2. ** 40
    plt = generate_plot(k, xn, yn, xmin, xmax, ymin, ymax, maxiter, horizon)
    
    plt.show()

# registered color maps :
# -----------------------------
# Accent
# Accent_r
# Blues
# Blues_r
# BrBG
# BrBG_r
# BuGn
# BuGn_r
# BuPu
# BuPu_r
# CMRmap
# CMRmap_r
# Dark2
# Dark2_r
# GnBu
# GnBu_r
# Greens
# Greens_r
# Greys
# Greys_r
# LUTSIZE
# OrRd
# OrRd_r
# Oranges
# Oranges_r
# PRGn
# PRGn_r
# Paired
# Paired_r
# Pastel1
# Pastel1_r
# Pastel2
# Pastel2_r
# PiYG
# PiYG_r
# PuBu
# PuBuGn
# PuBuGn_r
# PuBu_r
# PuOr
# PuOr_r
# PuRd
# PuRd_r
# Purples
# Purples_r
# RdBu
# RdBu_r
# RdGy
# RdGy_r
# RdPu
# RdPu_r
# RdYlBu
# RdYlBu_r
# RdYlGn
# RdYlGn_r
# Reds
# Reds_r
# ScalarMappable
# Set1
# Set1_r
# Set2
# Set2_r
# Set3
# Set3_r
# Spectral
# Spectral_r
# Vega10
# Vega10_r
# Vega20
# Vega20_r
# Vega20b
# Vega20b_r
# Vega20c
# Vega20c_r
# Wistia
# Wistia_r
# YlGn
# YlGnBu
# YlGnBu_r
# YlGn_r
# YlOrBr
# YlOrBr_r
# YlOrRd
# YlOrRd_r
# afmhot <--
# afmhot_r
# autumn
# autumn_r
# binary
# binary_r
# bone
# bone_r
# brg
# brg_r
# bwr
# bwr_r
# cbook
# cmap_d
# cmapname
# cmaps_listed
# colors
# cool
# cool_r
# coolwarm
# coolwarm_r
# copper
# copper_r
# cubehelix
# cubehelix_r
# datad
# division
# flag
# flag_r
# gist_earth
# gist_earth_r
# gist_gray
# gist_gray_r
# gist_heat
# gist_heat_r
# gist_ncar
# gist_ncar_r
# gist_rainbow
# gist_rainbow_r
# gist_stern
# gist_stern_r
# gist_yarg
# gist_yarg_r
# gnuplot
# gnuplot2
# gnuplot2_r
# gnuplot_r
# gray
# gray_r
# hot
# hot_r
# hsv
# hsv_r
# inferno
# inferno_r
# jet
# jet_r
# ma
# magma
# magma_r
# mpl
# nipy_spectral
# nipy_spectral_r
# np
# ocean
# ocean_r
# os
# pink
# pink_r
# plasma
# plasma_r
# print_function
# prism
# prism_r
# rainbow
# rainbow_r
# seismic
# seismic_r
# six
# spec
# spec_reversed
# spectral
# spectral_r
# spring
# spring_r
# summer
# summer_r
# tab10
# tab10_r
# tab20
# tab20_r
# tab20b
# tab20b_r
# tab20c
# tab20c_r
# terrain
# terrain_r
# unicode_literals
# viridis
# viridis_r
# winter
# winter_r
