// mandelbrot.cpp – C++/SFML rewrite of mandelbrot.py
//
// Interactive controls:
//   Mouse wheel   – zoom (centred on cursor)
//   Left drag     – pan
//   R             – reset to original view
//   + / =         – double iteration count (max 8192)
//   -             – halve  iteration count (min 50)
//   Tab           – cycle fractal sequence (Mandelbrot → Burning Ship → Julia → Tricorn)

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <string>
#include <thread>
#include <vector>

// ─────────────────────────────────────────────────────────────────────────────
//  Parameters
// ─────────────────────────────────────────────────────────────────────────────
constexpr unsigned WIN_W = 900;
constexpr unsigned WIN_H = 750;   // 900 × (2.5/3.0) preserves the aspect ratio

// ─────────────────────────────────────────────────────────────────────────────
//  Fractal sequence abstraction
//  Subclasses encapsulate the recurrence formula, its exponent, and the
//  derived smooth (renormalised) iteration count.  Swapping in a different
//  subclass (e.g. Burning Ship, Julia, Tricorn) is sufficient to render a
//  completely different fractal without touching the renderer.
// ─────────────────────────────────────────────────────────────────────────────
struct IterResult { int n; long double absZ; };

class FractalSequence {
public:
    virtual ~FractalSequence() = default;

    /** Short display name shown in the window title. */
    virtual std::string name() const = 0;

    /** Iterate the sequence for a given point (cx, cy).
     *  Returns {n, |Z_n|} where n is the first iteration at which |Z| ≥ sqrt(horizon2),
     *  or {0, 0} when the point never escapes (interior of the set).
     */
    virtual IterResult iterate(long double cx, long double cy,
                               int maxiter, long double horizon2) const = 0;

    /** Smooth (renormalised) iteration count.
     *  Returns 0 for interior points (n == 0).
     *  log_horizon = log(log(horizon)) / log(k), precomputed by the caller.
     */
    virtual long double smooth_mu(int n, long double absZ,
                                  long double log_horizon) const = 0;

    /** log(log(horizon)) / log(k)  – precomputed constant passed to smooth_mu. */
    virtual long double log_horizon_factor(long double horizon) const = 0;
};

// ─────────────────────────────────────────────────────────────────────────────
//  Shared smooth coloring for all quadratic (k=2) sequences
// ─────────────────────────────────────────────────────────────────────────────
class QuadraticSequence : public FractalSequence {
protected:
    static constexpr long double K    = 2.0L;
    static const     long double LOGK;   // = std::log(K), defined below
public:
    long double smooth_mu(int n, long double absZ,
                          long double log_horizon) const override
    {
        if (n == 0 || absZ <= 1.0L)
            return 0.0L;
        return static_cast<long double>(n) + log_horizon
               - std::log(std::log(absZ)) / LOGK;
    }

    long double log_horizon_factor(long double horizon) const override
    {
        return std::log(std::log(horizon)) / LOGK;
    }
};
const long double QuadraticSequence::LOGK = std::log(QuadraticSequence::K);

// ─────────────────────────────────────────────────────────────────────────────
//  Mandelbrot:      Z(0) = 0,           Z(n+1) = Z(n)^2 + c
// ─────────────────────────────────────────────────────────────────────────────
class MandelbrotSequence : public QuadraticSequence {
public:
    std::string name() const override { return "Mandelbrot"; }

    IterResult iterate(long double cx, long double cy,
                       int maxiter, long double horizon2) const override
    {
        long double zr = 0.0L, zi = 0.0L;
        for (int n = 0; n < maxiter; ++n) {
            long double zr2 = zr * zr, zi2 = zi * zi;
            if (zr2 + zi2 >= horizon2)
                return { n, std::sqrt(zr2 + zi2) };
            long double tmp = zr2 - zi2 + cx;
            zi = 2.0L * zr * zi + cy;
            zr = tmp;
        }
        return { 0, 0.0L };
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  Julia:           Z(0) = c,           Z(n+1) = Z(n)^2 + julia_c
//  Classic parameter: julia_c = -0.7 + 0.27015i  (Douady rabbit neighbourhood)
// ─────────────────────────────────────────────────────────────────────────────
class JuliaSequence : public QuadraticSequence {
    long double jr, ji;   // fixed Julia parameter
public:
    explicit JuliaSequence(long double real = -0.7L, long double imag = 0.27015L)
        : jr(real), ji(imag) {}

    std::string name() const override { return "Julia"; }

    IterResult iterate(long double cx, long double cy,
                       int maxiter, long double horizon2) const override
    {
        long double zr = cx, zi = cy;   // seed is the pixel coordinate
        for (int n = 0; n < maxiter; ++n) {
            long double zr2 = zr * zr, zi2 = zi * zi;
            if (zr2 + zi2 >= horizon2)
                return { n, std::sqrt(zr2 + zi2) };
            long double tmp = zr2 - zi2 + jr;
            zi = 2.0L * zr * zi + ji;
            zr = tmp;
        }
        return { 0, 0.0L };
    }
};



// ─────────────────────────────────────────────────────────────────────────────
//  Colour map utilities
// ─────────────────────────────────────────────────────────────────────────────
struct RGB { float r, g, b; };
struct HSV { float h, s, v; };

class ColourMap {
public:
    virtual ~ColourMap() = default;

    virtual std::string name() const = 0;
    virtual RGB operator()(float t) const = 0;

    /** Convert an RGB colour to HSV.
     *  RGB components are in [0,1].
     *  Returns HSV with H in [0,1], S in [0,1], V in [0,1].
     */
    static HSV rgb_to_hsv(RGB c)
    {
        float mx = std::max({ c.r, c.g, c.b });
        float mn = std::min({ c.r, c.g, c.b });
        float d  = mx - mn;
        if (mx < 1e-7f) return { 0.f, 0.f, 0.f };
        float h = 0.f;
        if (d > 1e-7f) {
            if      (c.r >= mx) h = (c.g - c.b) / d;
            else if (c.g >= mx) h = 2.f + (c.b - c.r) / d;
            else                h = 4.f + (c.r - c.g) / d;
            h /= 6.f;
            if (h < 0.f) h += 1.f;
        }
        return { h, d / mx, mx };
    }

    /** Convert an HSV colour to RGB.
     *  HSV components are in [0,1].
     *  Returns RGB with R, G, B in [0,1].
     */
    static RGB hsv_to_rgb(HSV c)
    {
        if (c.s < 1e-7f) return { c.v, c.v, c.v };
        float h6 = c.h * 6.f;
        int   i  = static_cast<int>(h6) % 6;
        float f  = h6 - std::floor(h6);
        float p  = c.v * (1.f - c.s);
        float q  = c.v * (1.f - c.s * f);
        float t  = c.v * (1.f - c.s * (1.f - f));
        switch (i) {
            case 0:  return { c.v,   t,   p };
            case 1:  return {   q, c.v,   p };
            case 2:  return {   p, c.v,   t };
            case 3:  return {   p,   q, c.v };
            case 4:  return {   t,   p, c.v };
            default: return { c.v,   p,   q };
        }
    }
};

// matplotlib 'hot' colormap  (dark grey → red → yellow → white)
// Breakpoints from the matplotlib source: 0, 0.3657, 0.7461, 1.0
class Hot : public ColourMap {
public:
    std::string name() const override { return "Hot"; }

    RGB operator()(float t) const override
    {
        t = std::clamp(t, 0.f, 1.f);
        constexpr float P1 = 0.3657f, P2 = 0.7461f;
        if (t < P1) return { 0.2f + 0.8f * t / P1,                     0.f,              0.f };
        if (t < P2) return {      1.f, (t - P1) / (P2 - P1),              0.f };
                    return {      1.f,                    1.f, (t-P2)/(1.f-P2) };
    }
};

// matplotlib-style 'ice' colormap
// A cool blue-white ramp intended to read as frozen water/ice.
class Ice : public ColourMap {
public:
    std::string name() const override { return "Ice"; }

    RGB operator()(float t) const override
    {
        t = std::clamp(t, 0.f, 1.f);

        auto lerp = [](float a, float b, float u) {
            return a + (b - a) * u;
        };

        if (t < 0.40f) {
            const float u = t / 0.40f;
            return {
                lerp(0.02f, 0.00f, u),
                lerp(0.08f, 0.55f, u),
                lerp(0.32f, 0.95f, u)
            };
        }
        if (t < 0.78f) {
            const float u = (t - 0.40f) / 0.38f;
            return {
                lerp(0.00f, 0.68f, u),
                lerp(0.55f, 0.92f, u),
                lerp(0.95f, 1.00f, u)
            };
        }

        const float u = (t - 0.78f) / 0.22f;
        return {
            lerp(0.68f, 1.00f, u),
            lerp(0.92f, 1.00f, u),
            lerp(1.00f, 1.00f, u)
        };
    }
};

// matplotlib-style 'amber' colormap
// A warm amber-to-gold ramp intended to read as glowing resin/metal.
class Amber : public ColourMap {
public:
    std::string name() const override { return "Amber"; }

    RGB operator()(float t) const override
    {
        t = std::clamp(t, 0.f, 1.f);

        auto lerp = [](float a, float b, float u) {
            return a + (b - a) * u;
        };

        if (t < 0.34f) {
            const float u = t / 0.34f;
            return {
                lerp(0.12f, 0.72f, u),
                lerp(0.05f, 0.32f, u),
                lerp(0.00f, 0.02f, u)
            };
        }
        if (t < 0.72f) {
            const float u = (t - 0.34f) / 0.38f;
            return {
                lerp(0.72f, 0.98f, u),
                lerp(0.32f, 0.64f, u),
                lerp(0.02f, 0.08f, u)
            };
        }

        const float u = (t - 0.72f) / 0.28f;
        return {
            lerp(0.98f, 1.00f, u),
            lerp(0.64f, 0.94f, u),
            lerp(0.08f, 0.76f, u)
        };
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  View bounds in the complex plane
//  The initial values are chosen to show the whole set with a bit of padding.
//  The aspect ratio of the viewport should match the window's aspect ratio to avoid distortion.
//  The initial viewport is approximately [-2.25, 0.75] × [-1.25, 1.25], 
//  which has an aspect ratio of 3:2, matching the window's aspect ratio of 900:750 = 3:2.
//  The viewport is updated interactively by zooming and panning, 
//  but the aspect ratio is preserved during these operations to avoid distortion of the fractal image.
//  The viewport is defined by its minimum and maximum real and imaginary values (xmin, xmax, ymin, ymax).
//  
// ─────────────────────────────────────────────────────────────────────────────
struct Viewport {
    long double xmin = -2.25L, xmax = 0.75L;
    long double ymin = -1.25L, ymax = 1.25L;
};

/** Compute effective iteration count from zoom level.
 *  The user-controlled value is treated as a base, and we add extra iterations
 *  as the viewport width shrinks.
 * 
 * The formula is designed to add a certain number of iterations (OCTAVE_BONUS) for every doubling of zoom level,
 * where the zoom level is defined as the ratio of the initial viewport width (INITIAL_WIDTH) to the current viewport width.
 * The log2(zoom) term calculates how many doublings of zoom have occurred, 
 * and multiplying this by OCTAVE_BONUS gives the total bonus iterations to add to the base iteration count.
 * The resulting effective iteration count is then clamped to a reasonable range (50 to 65536) 
 * to prevent it from becoming too low or too high.
 */
int adaptive_maxiter(int baseIter, const Viewport& vp)
{
    constexpr long double INITIAL_WIDTH = 3.0L;   // default xmax - xmin
    constexpr long double OCTAVE_BONUS  = 48.0L;  // added iterations per 2x zoom

    const long double width = std::max(vp.xmax - vp.xmin,
                                       std::numeric_limits<long double>::min());
    const long double zoom  = INITIAL_WIDTH / width;

    long double bonus = 0.0L;
    if (zoom > 1.0L)
        bonus = OCTAVE_BONUS * std::log2(zoom);

    const int effective = baseIter + static_cast<int>(std::llround(bonus));
    return std::clamp(effective, 50, 65536);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Render one frame into img
//
//  The img is assumed to be the same size as the viewport.
//  The rendering is done in three stages:
//    1. Compute smooth iteration counts (multi-threaded)
//    2. Normalise exterior values to [0,1] then apply γ = 0.3
//    3. Hill-shade + HSV blend
//  
// ─────────────────────────────────────────────────────────────────────────────
void render(sf::Image& img, const Viewport& vp, int maxiter, long double horizon,
            const FractalSequence& seq, const ColourMap& colour_map)
{
    const unsigned W = img.getSize().x;
    const unsigned H = img.getSize().y;

    const long double horizon2    = horizon * horizon;
    const long double log_horizon = seq.log_horizon_factor(horizon);

    // ── 1. Compute smooth iteration counts (multi-threaded) ──────────────────
    // M[y * W + x] = smooth_mu(n, |Z|) for each pixel (x,y)
    // (interior points have M=0)
    // Note that the Python version uses np.nan for interior points, but we use 0.0 here.
    // This is because we want to ignore interior points when normalising the exterior values to [0,1].
    // The Python version also uses np.nanmin and np.nanmax to find the min/max of the exterior values, 
    // but we can just ignore the interior points (M=0) when finding the min/max.
    std::vector<long double> M(W * H, 0.0L);

    const unsigned nT = std::min(H, std::max(1u, std::thread::hardware_concurrency()));
    {
        std::vector<std::thread> threads;
        const unsigned step = H / nT;

        auto work = [&](unsigned y0, unsigned y1) {
            for (unsigned y = y0; y < y1; ++y) {
                // y = 0 is the top of the window → ymax; y = H-1 → ymin
                long double cy = vp.ymax - (vp.ymax - vp.ymin) * y / (H - 1.0L);
                for (unsigned x = 0; x < W; ++x) {
                    long double cx = vp.xmin + (vp.xmax - vp.xmin) * x / (W - 1.0L);
                    auto [n, absZ] = seq.iterate(cx, cy, maxiter, horizon2);
                    M[y * W + x]   = std::max(0.0L, seq.smooth_mu(n, absZ, log_horizon));
                }
            }
        };

        for (unsigned t = 0; t < nT; ++t) {
            unsigned y0 = t * step;
            unsigned y1 = (t + 1 == nT) ? H : y0 + step;
            threads.emplace_back(work, y0, y1);
        }
        for (auto& th : threads) th.join();
    }

    // ── 2. Normalise exterior values to [0,1] then apply γ = 0.3 ────────────
    // Find min/max of M (ignoring interior points)
    // If all points are interior, set mMin=0, mMax=1 to avoid division by zero.
    // This mirrors the Python version, which uses np.nanmin and np.nanmax.
    // (The Python version also uses np.clip to clamp the normalised values to [0,1].)
    // Note that the Python version uses np.power(..., 0.3) to apply the γ=0.3 power.
    // The C++ version uses std::pow(..., 0.3f) to do the same.
    // The Python version also uses np.nan_to_num to replace NaN with 0.0, 
    // but this is not needed in C++ because we already ignore interior points.
    long double mMin = std::numeric_limits<long double>::max();
    long double mMax = std::numeric_limits<long double>::lowest();
    for (long double v : M)
        if (v > 0.0L) { mMin = std::min(mMin, v); mMax = std::max(mMax, v); }
    if (mMax <= mMin) { mMin = 0.0L; mMax = 1.0L; }

    // Power-normalised array (mirrors PowerNorm(0.3) in the Python version)
    std::vector<float> Mn(W * H, 0.f);
    for (std::size_t i = 0; i < M.size(); ++i)
        if (M[i] > 0.0L)
            Mn[i] = std::pow(float((M[i] - mMin) / (mMax - mMin)), 0.3f);

    // ── 3. Hill-shade + HSV blend ────────────────────────────────────────────
    //  LightSource(azdeg=315, altdeg=10)
    //  matplotlib direction vector:
    //    ( sin(az)*cos(alt),  −cos(az)*cos(alt),  sin(alt) )
    constexpr float DEG = 3.14159265f / 180.f;
    const float lx =  std::sin(315.f * DEG) * std::cos(10.f * DEG);  // ≈ −0.6963
    const float ly = -std::cos(315.f * DEG) * std::cos(10.f * DEG);  // ≈  0.6963
    const float lz =  std::sin( 10.f * DEG);                          // ≈  0.1736
    const float VERT_EXAG = 1.5f;

    // Clamped raw-M accessor for central-difference gradient
    auto Mxy = [&](int x, int y) -> long double {
        return M[std::clamp(y, 0, (int)H - 1) * W
                + std::clamp(x, 0, (int)W - 1)];
    };

    for (unsigned y = 0; y < H; ++y) {
        for (unsigned x = 0; x < W; ++x) {
            float t = Mn[y * W + x];

            // Gradient of raw M (×vert_exag) via central differences
            float gx = VERT_EXAG * float(Mxy(x + 1, y) - Mxy(x - 1, y)) * 0.5f;
            float gy = VERT_EXAG * float(Mxy(x, y + 1) - Mxy(x, y - 1)) * 0.5f;

            // The surface normal vector is derived from the gradient of the Mandelbrot iteration counts,
            // which gives a sense of the "height" of the fractal surface at each point
            // The gradient (gx, gy) represents the rate of change of the iteration counts in the x and y directions,
            // and by taking the negative of these values, we can create a normal vector 
            // that points upwards from the surface of the fractal. 
            // The z component of the normal vector is set to 1 to give it a vertical orientation.
            // The normal vector is then normalised to have a length of 1, which is necessary 
            // for the lighting calculations that follow.
            float nx = -gx, ny = -gy, nz = 1.f;
            float nl = std::sqrt(nx * nx + ny * ny + nz * nz);
            nx /= nl; ny /= nl; nz /= nl;

            // The Lambertian diffuse intensity is used to create a shading effect that gives the fractal image 
            // a more three-dimensional appearance.
            // The intensity is calculated as the dot product of the light direction vector (lx, ly, lz) 
            // and the surface normal vector (nx, ny, nz).
            // The resulting intensity value is then clamped to the range [0, 1] to ensure that it represents 
            // a valid diffuse lighting intensity.
            // The light direction vector is determined by the specified azimuth and altitude angles,
            // while the surface normal vector is derived from the gradient of the Mandelbrot iteration counts,
            // which gives a sense of the "height" of the fractal surface at each point.
            float intensity = std::clamp(nx * lx + ny * ly + nz * lz, 0.f, 1.f);

            // The HSV blend mode is used to combine the colour from the colormap with the shading intensity.
            // The colour from the colormap is first converted from RGB to HSV colour space,
            // and then the Value (V) component of the HSV colour is replaced with the calculated shading intensity.
            // This allows the colour to retain its Hue and Saturation from the colormap, 
            // while the brightness is modulated by the shading intensity.
            // The resulting HSV colour is then converted back to RGB colour space for display.
            RGB col = colour_map(t);
            HSV hsv = ColourMap::rgb_to_hsv(col);
            hsv.v   = intensity;
            RGB out = ColourMap::hsv_to_rgb(hsv);

            img.setPixel(sf::Vector2u{ x, y }, sf::Color{
                static_cast<std::uint8_t>(std::clamp(out.r, 0.f, 1.f) * 255.f),
                static_cast<std::uint8_t>(std::clamp(out.g, 0.f, 1.f) * 255.f),
                static_cast<std::uint8_t>(std::clamp(out.b, 0.f, 1.f) * 255.f),
                255u
            });
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  main
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    // ── Create window ─────────────────────────────────────────────────────────
    sf::RenderWindow window(sf::VideoMode({ WIN_W, WIN_H }), "Fractal Set");
    window.setFramerateLimit(60);

    // ── Fractal sequences (Tab cycles through them) ───────────────────────────
    MandelbrotSequence  seqMandel;
    JuliaSequence       seqJulia;

    // One default viewport per sequence (same order)
    // All viewports must satisfy (xmax-xmin)/(ymax-ymin) == WIN_W/WIN_H == 1.2
    const std::array<Viewport, 2> defaultVps = {{
        { -2.25L, 0.75L, -1.25L,  1.25L },  // Mandelbrot  – w=3.0  h=2.5  AR=1.2 ✓
        { -1.8L,  1.8L,  -1.5L,   1.5L  },  // Julia        – w=3.6  h=3.0  AR=1.2 ✓
    }};
    const std::array<FractalSequence*, 2> sequences = {{
        &seqMandel, &seqJulia
    }};
    int seqIdx = 0;

    // ── Initial viewport and parameters ───────────────────────────────────────
    Viewport vp = defaultVps[seqIdx];
    int    baseIter = 200;
    long double horizon = std::ldexp(1.0L, 40);   // 2^40 (same as the Python script)

    // ── Create image buffer ─────────────────────────────────────────────────
    sf::Image img(sf::Vector2u{ WIN_W, WIN_H });

    // ── Initial render ───────────────────────────────────────────────────────
    window.setTitle(sequences[seqIdx]->name() + " – rendering…");
    Hot colourHot;
    Ice colourIce;
    Amber colourAmber;
    const std::array<const ColourMap*, 3> colourMaps = {{
        &colourHot, &colourIce, &colourAmber
    }};
    int colourIdx = 0;

    render(img, vp, adaptive_maxiter(baseIter, vp), horizon, *sequences[seqIdx], *colourMaps[colourIdx]);

    // ── Create texture and sprite ─────────────────────────────────────────────
    sf::Texture tex;
    if (!tex.loadFromImage(img)) return 1;
    sf::Sprite sprite(tex);

    // ── Window title and update function ─────────────────────────────────────
    const std::string HINT = "  |  scroll=zoom  drag=pan  R=reset  +/-=iter  Tab=toggle";
    auto updateTitle = [&]() {
        const int iterNow = adaptive_maxiter(baseIter, vp);
        window.setTitle(sequences[seqIdx]->name()
            + " [map=" + colourMaps[colourIdx]->name()
            + ", iter=" + std::to_string(iterNow)
            + ", base=" + std::to_string(baseIter) + "]" + HINT);
    };
    updateTitle();

    // ── Interaction state ────────────────────────────────────────────────────
    bool         needRender = false;
    bool         dragging   = false;
    sf::Vector2i dragOrigin;
    Viewport     dragVp;

    // ── Coordinate conversion (pixel → world) ─────────────────────────────────
    // Converts pixel coordinates (with origin at top-left) to complex plane coordinates (with origin at bottom-left).
    // This is used to determine the point in the complex plane that corresponds to the mouse cursor position,
    // which is necessary for implementing zooming centred on the cursor and panning.
    // The conversion is done by linearly interpolating between the viewport bounds (vp.xmin, vp.xmax) and (vp.ymin, vp.ymax)
    // based on the pixel coordinates (p.x, p.y) and the window dimensions (WIN_W, WIN_H).
    // The y-coordinate is inverted (vp.ymax - ...) because pixel coordinates have the y-axis pointing downwards,
    // while the complex plane coordinates have the y-axis pointing upwards.
    // The resulting world coordinates are returned as a pair of long doubles representing 
    // the real and imaginary parts of the complex number.
    auto pixelToWorld = [&](sf::Vector2i p) {
        return std::pair<double, double>{
            vp.xmin + (vp.xmax - vp.xmin) * p.x / static_cast<long double>(WIN_W - 1),
            vp.ymax - (vp.ymax - vp.ymin) * p.y / static_cast<long double>(WIN_H - 1)
        };
    };

    // ── Main loop ────────────────────────────────────────────────────────────
    while (window.isOpen())
    {
        while (const std::optional ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>()) window.close();

            // Scroll → zoom centred on cursor
            if (const auto* sw = ev->getIf<sf::Event::MouseWheelScrolled>()) {
                auto [wx, wy] = pixelToWorld({ sw->position.x, sw->position.y });
                long double f = (sw->delta > 0.f) ? 0.7L : (1.0L / 0.7L);
                vp.xmin = wx + (vp.xmin - wx) * f;
                vp.xmax = wx + (vp.xmax - wx) * f;
                vp.ymin = wy + (vp.ymin - wy) * f;
                vp.ymax = wy + (vp.ymax - wy) * f;
                needRender = true;
            }

            // Left button → start pan
            if (const auto* mb = ev->getIf<sf::Event::MouseButtonPressed>())
                if (mb->button == sf::Mouse::Button::Left) {
                    dragging   = true;
                    dragOrigin = mb->position;
                    dragVp     = vp;
                }

            // Release → commit pan and re-render
            if (const auto* mb = ev->getIf<sf::Event::MouseButtonReleased>())
                if (mb->button == sf::Mouse::Button::Left && dragging) {
                    dragging   = false;
                    needRender = true;
                }

            // Move → update viewport live (renders on release)
            if (const auto* mm = ev->getIf<sf::Event::MouseMoved>()) {
                if (dragging) {
                    long double dx = (dragVp.xmax - dragVp.xmin)
                              * (mm->position.x - dragOrigin.x) / static_cast<long double>(WIN_W);
                    long double dy = (dragVp.ymax - dragVp.ymin)
                              * (mm->position.y - dragOrigin.y) / static_cast<long double>(WIN_H);
                    vp.xmin = dragVp.xmin - dx;  vp.xmax = dragVp.xmax - dx;
                    vp.ymin = dragVp.ymin + dy;  vp.ymax = dragVp.ymax + dy;
                }
            }

            // Keyboard shortcuts
            if (const auto* kp = ev->getIf<sf::Event::KeyPressed>()) {
                if (kp->code == sf::Keyboard::Key::R) {
                    vp         = defaultVps[seqIdx];
                    needRender = true;
                }
                if (kp->code == sf::Keyboard::Key::Equal) {   // + or =
                    baseIter   = std::min(baseIter * 2, 8192);
                    needRender = true;
                }
                if (kp->code == sf::Keyboard::Key::Hyphen) {  // -
                    baseIter   = std::max(baseIter / 2, 50);
                    needRender = true;
                }
                if (kp->code == sf::Keyboard::Key::Tab) {
                    seqIdx     = (seqIdx + 1) % static_cast<int>(sequences.size());
                    vp         = defaultVps[seqIdx];
                    needRender = true;
                }
                if (kp->code == sf::Keyboard::Key::C) {
                    colourIdx  = (colourIdx + 1) % static_cast<int>(colourMaps.size());
                    needRender = true;
                }
            }
        }

        // Trigger re-render after a pan or zoom is committed
        if (needRender && !dragging) {
            needRender = false;
            window.setTitle(sequences[seqIdx]->name() + " – rendering…");
            render(img, vp, adaptive_maxiter(baseIter, vp), horizon, *sequences[seqIdx], *colourMaps[colourIdx]);
            tex.update(img);
            updateTitle();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}
