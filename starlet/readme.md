<div align="center">

# ⭐ Starlet

**A tiny, header-free, terminal-animation framework for cosmic text effects.**

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Header](https://img.shields.io/badge/header-only-no-orange.svg)
![Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen.svg)
![Terminal](https://img.shields.io/badge/terminal-24--bit%20truecolor-ff69b4.svg)

> **Starlet** is a single-file, dependency-free C++ framework for animating colored glyphs in the terminal. It smoothly interpolates each glyph from a dim *glow* color to a bright *core* color, frame by frame — perfect for starfields, loading effects, ambient terminal art, and procedural night skies.
>
> **`starletScene`** is the companion orchestrator: it owns a collection of `starlet` objects, hides the cursor, drives the frame loop, and renders them all in lockstep.

</div>
---

## ✨ Features

- 🎨 **True-color RGB interpolation** — each glyph fades from glow → bright over N frames
- 🧩 **Single-file design** — drop `starlet.cpp` into your project and go
- 🪶 **Zero dependencies** — only the C++ standard library + POSIX (`unistd.h`, `sys/ioctl.h`)
- 🖥️ **24-bit ANSI truecolor** — `\033[38;2;R;G;Bm` under the hood
- 🎭 **Multi-color input** — accepts `#RRGGBB` hex or `rgb(r,g,b)` strings
- ✍️ **Custom glyphs** — any UTF-8 string works (`*`, `✦`, `★`, `✺`, `→`, `·` …)
- 🎬 **Scene orchestration** — `starletScene` runs the whole animation loop for you
- 🔁 **Reset & replay** — `reset()` and `resetAll()` restore stars to their glow state
- 🧠 **Frame-accurate easing** — linear interpolation with a hard clamp at `progress = 1.0`

---

## 📦 Installation

Starlet is **not header-only by convention** — it's distributed as a single `.cpp` file that you `#include` directly, matching your preferred workflow.

1. Copy `starlet.cpp` into your project.
2. `#include "starlet.cpp"` in your `main.cpp`.
3. Compile with any C++17 compiler.

```bash
g++ -std=c++17 -O2 main.cpp -o starlet_demo
./starlet_demo
```

> **Note:** On some toolchains you may need `-pthread` if you extend the framework with threading. The base framework does not require it.

---

## 🚀 Quick Start

```cpp
#include "starlet.cpp"

int main() {
    starletScene scene;

    scene.add(starlet(10, 10, "#424242", "#FFFFFF", "*", 15));
    scene.add(starlet(12, 15, "rgb(255,0,0)", "rgb(0,255,0)", "+", 30));
    scene.add(starlet(14, 20, "#0000FF", "#FFFF00", "o", 25));

    scene.setFrameDelay(100000); // 100 ms per frame
    scene.run();

    return 0;
}
```

Each `starlet` is placed at `(row, col)` and animates from its glow color to its text color over the specified iteration count.

---

## 🧪 API Reference

### `class starlet`

Represents a single animated glyph.

#### Constructor

```cpp
starlet(int row, int col,
        std::string textColor,
        std::string glowColor,
        std::string glyph,
        int iterations);
```

| Parameter | Type | Description |
|---|---|---|
| `row` | `int` | Terminal row (1-indexed) |
| `col` | `int` | Terminal column (1-indexed) |
| `textColor` | `std::string` | Final bright color (`#RRGGBB` or `rgb(r,g,b)`) |
| `glowColor` | `std::string` | Starting dim color |
| `glyph` | `std::string` | The character(s) to render |
| `iterations` | `int` | Number of frames for the glow → bright transition |

#### Public Methods

| Method | Description |
|---|---|
| `int setTextColor(int r, int g, int b)` | Set target color via RGB |
| `int setTextColor(std::string code)` | Set target color via hex/rgb string |
| `int setGlowColor(int r, int g, int b)` | Set starting color via RGB |
| `int setGlowColor(std::string code)` | Set starting color via hex/rgb string |
| `int setGlyph(std::string glyph)` | Change the rendered glyph |
| `int setTotalIterations(int n)` | Change transition length |
| `bool nextStateAndRender()` | Advance one frame; returns `false` when finished |
| `void reset()` | Clear the glyph and restore glow state |

#### Color Formats

```cpp
"#FFFFFF"           // hex
"#1a1a2e"           // lowercase hex is fine
"rgb(255, 0, 128)"  // functional notation
```

> Hex parsing uses `std::stoi(..., 16)` and assumes exactly 6 hex digits after `#`.

---

### `class starletScene`

Manages a collection of `starlet` objects and runs the render loop.

#### Public Methods

| Method | Description |
|---|---|
| `void add(const starlet& object)` | Add a star to the scene |
| `void setFrameDelay(int microseconds)` | Set delay between frames |
| `void run()` | Run the animation until all stars finish |
| `void resetAll()` | Reset every star to its glow state |
| `void clearAll()` | `resetAll()` then empty the scene |

`run()` automatically hides the cursor before the loop and restores it afterward — you don't need to call `hideCursor()` / `showCursor()` yourself.

---

## 🎨 Crafting a Starfield

Because each star can have its own glyph, palette, and iteration count, you can build layered depth with just a loop:

```cpp
starletScene scene;

// Cosmic palette: dim glow → vivid core
const char* palette[][2] = {
    {"#0a0a1a", "#ffffff"},   // cold white
    {"#0a1a2e", "#48dbfb"},   // ice blue
    {"#1a0a1a", "#ff9ff3"},   // pink
    {"#0a2e0a", "#1dd1a1"},   // mint
    {"#1a1a0a", "#feca57"},   // gold
    {"#1a0a2e", "#c56cf0"},   // violet
};

// Slow-drifting stars across a 210x56 canvas
for (int i = 0; i < 300; ++i) {
    int row = 2 + (i * 7)  % 52;
    int col = 4 + (i * 13) % 200;
    int iters = 60 + (i * 11) % 200;
    const char* glyph = (i % 11 == 0) ? "★"
                      : (i % 5  == 0) ? "✦"
                      : (i % 3  == 0) ? "·"
                                      : "*";
    scene.add(starlet(row, col,
                      palette[i % 6][1],
                      palette[i % 6][0],
                      glyph, iters));
}

scene.setFrameDelay(70000);
scene.run();
```

**Depth trick:** give dust glyphs low iteration counts and bright stars high iteration counts. The bright stars ignite *last*, giving a natural "rising into view" feel.

---

## 🧬 Architecture

```
┌─────────────────────────────────────────────┐
│              starletScene                   │
│  ┌───────────────────────────────────────┐  │
│  │  std::vector<starlet> objects         │  │
│  └───────────────────────────────────────┘  │
│                                             │
│  run() ──► loop:                            │
│    for each starlet:                        │
│      nextStateAndRender()                   │
│    flush()                                  │
│    usleep(frameDelayMicroseconds)           │
└─────────────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────┐
│                 starlet                     │
│  originRow, originCol   ◄─ cursor position  │
│  glyph                  ◄─ what to draw     │
│  textColor, glowColor   ◄─ interpolation    │
│  currentColorState      ◄─ live frame color │
│  currentIteration       ◄─ frame counter    │
│  transitionFinished     ◄─ end-state flag   │
└─────────────────────────────────────────────┘
```

Each frame, `starlet` computes:

```
progress = currentIteration / totalIterations           // clamped to [0, 1]
currentColor = glow + (text - glow) * progress
```

Then renders with:

```
\033[<row>;<col>H                        // move cursor
\033[38;2;<r>;<g>;<b>m<glyph>\033[0m     // colored glyph
```

---

## 🛠️ Extending Starlet

### Adding a true reverse fade

The base `starlet` fades glow → bright only. To fade bright → glow, swap the roles in the interpolation:

```cpp
currentColorState.r =
    static_cast<int>(
        textColor.r + (glowColor.r - textColor.r) * progress
    );
```

Or add a `bool reverse` flag and branch on it inside `nextState()`.

### Removing the glyph when finished

Add a `bool eraseOnFinish` flag and in `render()`, print `" "` instead of the glyph when `transitionFinished` is true.

### Threaded scenes

Since each `starlet` holds its own cursor position, you can spawn multiple `starletScene` instances from different threads — each one targets its own `(row, col)` region. Wrap the `render()` call in a mutex to avoid interleaved ANSI sequences.

---

## ⚠️ Limitations

- **One-way transition** — `starlet` cannot fade back to glow without a code change.
- **No resize handling** — terminal dimensions are not queried; out-of-bounds positions wrap or clip.
- **No `SIGINT` cleanup** — `Ctrl+C` mid-`run()` may leave the cursor hidden. Wrap `run()` in a `try`/`finally`-style guard or install a signal handler that prints `\033[?25h`.
- **Copy semantics** — `starlet` is copy-assignable, which is fine for `std::vector` but means two copies share no state. That's intentional.

---

## 🧹 Graceful Shutdown Pattern

```cpp
#include <csignal>
#include <cstdlib>

static void restoreCursor(int) {
    std::cout << "\033[?25h" << std::flush;
    std::exit(0);
}

int main() {
    std::signal(SIGINT, restoreCursor);
    starletScene scene;
    // ... add stars ...
    scene.run();
    return 0;
}
```

---

## 📄 License

MIT — do whatever you want, attribution appreciated.

```
Copyright (c) 2024 Starlet contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```

---

## 🤝 Contributing

1. Fork it
2. Create your feature branch (`git checkout -b feature/reverse-fade`)
3. Commit your changes (`git commit -am 'Add reverse fade'`)
4. Push to the branch (`git push origin feature/reverse-fade`)
5. Open a Pull Request

---

<p align="center">
  <sub>Built with ✦ by people who think the terminal should be beautiful.</sub>
</p>