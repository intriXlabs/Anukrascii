#include "../starlet.cpp"
#include <csignal>
#include <ctime>
#include <string>
#include <utility>
#include <algorithm>

int main() {
    /* ── 0 · geometry: trust the real terminal, 210x56 as fallback ─────────── */
    int rows = 56, cols = 210;
    {
        winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 &&
            ws.ws_row > 0 && ws.ws_col > 0) {
            rows = (int)ws.ws_row;
            cols = (int)ws.ws_col;
        }
    }

    /* ── 1 · dice ───────────────────────────────────────────────────────────── */
    srand((unsigned)(time(nullptr) ^ getpid()));

    auto rnd  = [](int lo, int hi) {
        if (hi < lo) return lo;
        return lo + rand() % (hi - lo + 1);
    };
    auto rndf = []() { return (double)rand() / ((double)RAND_MAX + 1.0); };

    /* framework speaks colour codes -> feed it "#rrggbb" */
    auto hex  = [](int v) {
        static const char* d = "0123456789abcdef";
        std::string s;
        s += d[(v >> 4) & 15];
        s += d[v & 15];
        return s;
    };
    auto code = [&](int r, int g, int b) {
        if (r > 255) r = 255; if (g > 255) g = 255; if (b > 255) b = 255;
        return "#" + hex(r) + hex(g) + hex(b);
    };

    /* ── 2 · real-sky flavour tables ────────────────────────────────────────── */
    struct spectral { int r, g, b, w; };
    const spectral classes[] = {
        { 248, 247, 255, 24 },  // F — white
        { 255, 244, 234, 28 },  // G — yellow-white, sun-class
        { 202, 216, 255, 14 },  // A — silvery
        { 255, 236, 210, 14 },  // K — warm gold
        { 255, 214, 165,  8 },  // late K — amber
        { 170, 191, 255,  7 },  // B — blue-white, Rigel mood
        { 255, 181, 108,  4 },  // M — orange
        { 255, 132,  97,  1 },  // red giant, Betelgeuse mood
    };

    struct magnitude { const char* glyph; int w; double bLo, bHi; };
    const magnitude mags[] = {
        { ".", 34, 0.34, 0.60 },  // mag 5-6, the anonymous many
        { "·", 22, 0.50, 0.74 },
        { "◦",  6, 0.60, 0.80 },
        { "+",  8, 0.66, 0.86 },
        { "*", 16, 0.78, 1.00 },
        { "✧",  5, 0.88, 1.00 },
        { "✦",  5, 0.96, 1.00 },  // mag 1, your Orions and Sirii
    };

    auto pickIndex = [](const auto* arr, int n) {
        int tot = 0;
        for (int i = 0; i < n; ++i) tot += arr[i].w;
        int x = rand() % tot;
        for (int i = 0; i < n; ++i) { x -= arr[i].w; if (x < 0) return i; }
        return n - 1;
    };

    /* ── 3 · the moon, drawn once and left in peace ─────────────────────────── */
    const bool haveMoon = (cols >= 30 && rows >= 12);
    const int  moonRow  = haveMoon ? (rows / 9 + 1) : 0;
    const int  moonCol  = haveMoon ? (cols - 14)    : 0;

    auto nearMoon = [haveMoon, moonRow, moonCol](int r, int c) {
        return haveMoon &&
               r >= moonRow - 1 && r <= moonRow + 1 &&
               c >= moonCol - 1 && c <= moonCol + 1;
    };
    auto drawMoon = [&]() {
        if (!haveMoon) return;
        starlet moon(moonRow, moonCol, "#f6f3e9", "#f6f3e9", "☾", 2);
        moon.nextStateAndRender();          // text == glow -> steady moonlight
    };

    /* ── 4 · placement: uniform dome + one biased Milky Way band ────────────── */
    auto placeStar = [&]() -> std::pair<int, int> {
        for (int attempt = 0; attempt < 24; ++attempt) {
            int r, c;
            if (rndf() < 0.52) {            // the galactic band
                double t      = rndf();
                double centre = rows * (0.80 - 0.58 * t);
                double g      = (rndf() + rndf() + rndf()) / 3.0 - 0.5; // ~gaussian
                r = (int)(centre + g * rows * 0.34);
                c = 1 + (int)(t * (cols - 2));
            } else {                        // rest of the dome
                r = rnd(1, rows);
                c = rnd(1, cols - 1);       // last col is wrap-around territory
            }
            if (r < 1) r = 1;           if (r > rows)     r = rows;
            if (c < 1) c = 1;           if (c > cols - 1) c = cols - 1;
            if (!nearMoon(r, c)) return std::make_pair(r, c);
        }
        return std::make_pair(rows / 2 + 1, cols / 2 + 1);
    };

    /* ── 5 · lifecycle: hidden -> ignite -> fade to rest -> rest -> die ─────── */
    struct node {
        starlet star;
        int  delay;      // frames hidden before ignition
        int  linger;     // frames resting dim before death
        bool flared;     // fade completed?
        node(starlet s, int d, int l)
            : star(std::move(s)), delay(d), linger(l), flared(false) {}
    };
    std::vector<node> sky;

    auto makeStar = [&](int row, int col, bool firstLight) -> node {
        const spectral&  k = classes[pickIndex(classes, 8)];
        const magnitude& m = mags[pickIndex(mags, 7)];

        double peak = m.bLo + rndf() * (m.bHi - m.bLo);   // apparent brightness
        int gr = (int)(k.r * peak);
        int gg = (int)(k.g * peak);
        int gb = (int)(k.b * peak);

        double rest = 0.25 + rndf() * 0.30;               // how dim it settles
        int dr = std::max(10, (int)(gr * rest));
        int dg = std::max(10, (int)(gg * rest));
        int db = std::max(10, (int)(gb * rest));

        int iters = 5 + (int)(peak * 16.0) + rnd(0, 4);   // bright fades slow

        return node(
            starlet(row, col, code(dr, dg, db), code(gr, gg, gb), m.glyph, iters),
            firstLight ? rnd(0, 420) : rnd(0, 120),       // birth stagger
            rnd(140, 420));                               // rest before next life
    };

    /* ── 6 · meteors: a running head, a tail of starlets burning out fast ───── */
    bool   meteorLive = false, meteorBig = false;
    int    meteorCol = 0, meteorDir = 1, meteorSteps = 0, meteorSeq = 0;
    double meteorRowF = 0.0, meteorSlope = 0.0;
    int    nextMeteorIn = rnd(200, 500);

    auto spawnMeteorSegment = [&](int row, int col, int seq) {
        double b = seq < 2 ? 1.0 : std::max(0.42, 1.0 - seq * 0.013);
        if (meteorBig) b = std::min(1.0, b * 1.3);
        const char* glyph =
            seq == 0 ? (meteorBig ? "✦" : "*") : (seq < 3 ? "*" : "·");
        sky.push_back(node(
            starlet(row, col,
                    code(8, 10, 18),                        // burns to near-black
                    code((int)(242 * b), (int)(248 * b), (int)(255 * b)),
                    glyph,
                    meteorBig ? rnd(9, 13) : rnd(6, 9)),
            0, 0));                                         // ignite now, no rest
    };

    /* ── 7 · first light ────────────────────────────────────────────────────── */
    const int population = std::max(160, std::min(560, (rows * cols) / 38));
    for (int i = 0; i < population; ++i) {
        std::pair<int, int> p = placeStar();
        sky.push_back(makeStar(p.first, p.second, true));
    }

    /* ── 8 · stage: alt screen, no cursor, graceful way out ─────────────────── */
    std::cout << "\033[?1049h\033[?25l\033[2J\033[H";
    std::cout.flush();

    auto bail = [](int) {
        const char seq[] = "\033[?25h\033[?1049l";   // cursor + screen restored
        write(STDOUT_FILENO, seq, sizeof(seq) - 1);
        _exit(0);
    };
    signal(SIGINT,  bail);
    signal(SIGTERM, bail);

    drawMoon();
    int moonTouchUp = 500;

    /* ── 9 · the eternal frame ──────────────────────────────────────────────── */
    for (;;) {
        for (size_t i = 0; i < sky.size(); ) {
            node& n = sky[i];

            if (n.delay > 0) { --n.delay; ++i; continue; }          // unborn

            if (!n.flared) {
                if (n.star.nextStateAndRender()) { ++i; continue; } // fading
                n.flared = true;                                    // reached rest
            }

            if (n.linger > 0) { --n.linger; ++i; continue; }        // resting dim

            n.star.reset();                                         // vanish
            if (i + 1 < sky.size()) sky[i] = sky.back();
            sky.pop_back();                                         // reborn below
        }

        while ((int)sky.size() < population) {                      // keep it full
            std::pair<int, int> p = placeStar();
            sky.push_back(makeStar(p.first, p.second, false));
        }

        if (meteorLive) {
            for (int k = 0; k < 2 && meteorSteps > 0; ++k) {
                int r = (int)meteorRowF;
                if (r < 1) r = 1;
                if (r > rows) r = rows;
                if (meteorCol >= 1 && meteorCol <= cols - 1 && !nearMoon(r, meteorCol))
                    spawnMeteorSegment(r, meteorCol, meteorSeq++);
                meteorCol  += meteorDir;
                meteorRowF += meteorSlope;
                --meteorSteps;
            }
            if (meteorSteps <= 0 || meteorCol < 1 || meteorCol > cols - 1 ||
                meteorRowF < 0.5 || meteorRowF > rows + 0.5) {
                meteorLive   = false;
                nextMeteorIn = (rndf() < 0.22) ? rnd(25, 90)       // showers happen
                                               : rnd(350, 1500);   // usually not
            }
        } else if (--nextMeteorIn <= 0) {
            meteorLive  = true;
            meteorBig   = rndf() < 0.15;                            // fireball
            meteorDir   = (rndf() < 0.5) ? 1 : -1;
            meteorCol   = meteorDir > 0 ? rnd(1, cols / 3)
                                        : rnd((2 * cols) / 3, cols - 2);
            meteorRowF  = rnd(1, (rows * 2) / 3);
            meteorSlope = rnd(-30, 30) / 100.0;
            meteorSteps = rnd(25, 70);
            meteorSeq   = 0;
        }

        if (--moonTouchUp <= 0) {                                   // self-healing moon
            drawMoon();
            moonTouchUp = rnd(400, 900);
        }

        std::cout.flush();
        usleep(40000);                                              // ~25 fps
    }
}