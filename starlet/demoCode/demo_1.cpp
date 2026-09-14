#include "../starlet.cpp"
#include <random>
#include <chrono>

int main() {
    starletScene scene;

    // ============================================================
    //  12 x 6 STAR GRID  —  one space gap between each star
    //  Perfectly readable as a GIF on Reddit
    // ============================================================

    const int GRID_ROWS = 6;
    const int GRID_COLS = 12;
    const int START_ROW = 1;
    const int START_COL = 1;
    const int ROW_STEP  = 2;   // 1 cell + 1 space gap
    const int COL_STEP  = 5;   // 1 cell + 1 space gap

    // ---- Curated aesthetic palette: (glow, bright) ----
    // Every pair is hand-picked so the fade looks like a real star igniting.
    struct Palette { const char* glow; const char* bright; };
    static const Palette PALETTE[] = {
        // Deep blues → icy cores
        {"#0a1a2e", "#74b9ff"},
        {"#0a1a2e", "#48dbfb"},
        {"#0a0a1a", "#dfe6e9"},
        {"#0a0a1a", "#ffffff"},
        {"#0a1a2e", "#54a0ff"},
        // Warm golds → molten cores
        {"#1a1a0a", "#feca57"},
        {"#1a1a0a", "#ffeaa7"},
        {"#2e1a0a", "#ff9f43"},
        {"#2e2e0a", "#fdcb6e"},
        // Pinks & magentas
        {"#1a0a1a", "#ff9ff3"},
        {"#2e0a2e", "#e84393"},
        {"#2e0a2e", "#fd79a8"},
        {"#1a0a1a", "#ff6b9d"},
        // Reds
        {"#1a0a0a", "#ff7675"},
        {"#2e0a0a", "#ee5a6f"},
        // Greens
        {"#0a2e0a", "#55efc4"},
        {"#0a2e0a", "#1dd1a1"},
        {"#0a2e1a", "#00b894"},
        // Purples
        {"#1a0a2e", "#a29bfe"},
        {"#1a0a2e", "#c56cf0"},
    };
    const int PALETTE_SIZE = sizeof(PALETTE) / sizeof(PALETTE[0]);

    // ---- Glyph tier: mostly stars, a few rare giants ----
    // Using a single glyph per star keeps the grid clean and GIF-friendly.
    static const char* GLYPHS[] = {
        "✦", "✧", "✶", "✷",   // mid stars
        "★",                    // bright star (rare)
        "✺",                    // giant (very rare)
    };

    // ---- RNG seeded once so the palette is stable during the GIF ----
    std::mt19937 rng(static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()));

    // ---- Fill the grid ----
    for (int r = 0; r < GRID_ROWS; ++r) {
        for (int c = 0; c < GRID_COLS; ++c) {
            int row = START_ROW + r * ROW_STEP;
            int col = START_COL + c * COL_STEP;

            // Pick a palette entry by weighted random
            // 60% cool (blues/whites), 40% warm/magenta/purple
            int p;
            int roll = static_cast<int>(rng() % 100);
            if (roll < 60) {
                p = static_cast<int>(rng() % 5);          // blues/whites
            } else if (roll < 80) {
                p = 5 + static_cast<int>(rng() % 4);      // golds
            } else if (roll < 92) {
                p = 9 + static_cast<int>(rng() % 4);      // pinks
            } else {
                p = 13 + static_cast<int>(rng() % 7);     // reds/greens/purples
            }

            // Pick a glyph — mostly mid stars, occasional bright/giant
            int gRoll = static_cast<int>(rng() % 100);
            const char* glyph = (gRoll > 97) ? GLYPHS[5]   // giant  ~3%
                             : (gRoll > 88) ? GLYPHS[4]   // bright ~9%
                                            : GLYPHS[rng() % 4];

            // Iteration count: staggered so the grid blooms in a wave,
            // not all at once. Range 30–110 frames.
            int iterations = 30 + static_cast<int>(rng() % 80);

            // Stagger start offsets so some stars are already lit
            // when the animation begins — gives instant visual richness.
            int delay = static_cast<int>(rng() % 40);

            scene.add(starlet(row, col,
                              PALETTE[p].bright,
                              PALETTE[p].glow,
                              glyph,
                              iterations + delay));
        }
    }

    // ---- Slow, cinematic pacing for the GIF ----
    scene.setFrameDelay(70000); // 70 ms per frame

    // ---- Run once (the grid fades in and holds) ----
    scene.run();

    // ---- Hold the fully-lit grid for 2 seconds before exit ----
    usleep(2000000);

    // ---- Optional: clear on exit so the terminal is clean ----
    // scene.clearAll();

    return 0;
}