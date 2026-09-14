
<div align="center">

# Anukrascii

### Terminal-native simulation and visual composition

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Linux-informational.svg)](https://www.linux.org/)
[![Rendering](https://img.shields.io/badge/Rendering-ASCII%20%7C%20Unicode%20%7C%20ANSI-black.svg)](#)
[![Status](https://img.shields.io/badge/Status-Experimental-orange.svg)](#project-status)
[![Made by IntrixLabs](https://img.shields.io/badge/Made%20by-IntrixLabs-purple.svg)](#)

**Give your terminal a living world.**

</div>

---

## About

**Anukrascii** is an experimental C++ framework for creating simulated visual entities, animated scenes and procedural environments inside the terminal.

Instead of treating the terminal as a place where text is simply printed, Anukrascii explores it as a **visual medium**—a space where objects can move, evolve, appear, disappear and interact through time.

A star is not just a character at a coordinate. It can have:

- Its own position and appearance
- A unique lifetime
- Brightness and color transitions
- Spawn and disappearance behavior
- Independent animation state
- Reset and respawn logic

Multiple entities can then form larger environments such as:

- Living star fields
- Meteor showers
- Particle systems
- Atmospheric effects
- Procedural landscapes
- Animated terminal backgrounds
- Interactive visual scenes

## Vision

Anukrascii aims to provide a lightweight and extensible **simulation layer for terminal interfaces**.

The core idea is simple:

```text
Visual Entity
      ↓
Simulation
      ↓
Animation
      ↓
Scene Composition
      ↓
Terminal Frame
````

The framework should handle the complexity of evolving visual objects while keeping the developer-facing API simple.

Developers should be able to create entities, configure their behavior, add them to a scene and let the simulation run.

## TUI Compatibility

Anukrascii is intended to work **with** existing TUI systems rather than replace them.

The long-term direction is to keep the simulation and visual-composition layer independent from terminal ownership, allowing it to integrate with:

* `ncurses`
* `notcurses`
* `FTXUI`
* `termbox`
* Custom TUI frameworks
* Custom terminal renderers

The host interface should control input, layout and presentation, while Anukrascii provides the evolving visual content.

```text
Host TUI
   ↓
Anukrascii Simulation Layer
   ↓
Visual Frame / Overlay
   ↓
Host Renderer
   ↓
Terminal
```

## Current Direction

The current experiments focus on terminal-native entities and procedural scenes, including:

* Animated stars
* Independent entity lifecycles
* Color and brightness transitions
* Procedural star distribution
* Moon and sky composition
* Moving meteors
* Fading meteor trails
* Scene-level entity management
* ANSI and Unicode-based rendering

The project is still evolving, and its architecture may change as the simulation and rendering systems become more capable.

## Project Status

Anukrascii is currently an **experimental project by IntrixLabs**.

Its purpose is to explore how far terminal interfaces can be pushed when animation, simulation and visual composition become first-class concepts.

> **Not just printing characters.
> Simulating worlds inside the terminal.**

## Roadmap

* [ ] Generic visual-entity system
* [ ] Reusable animation behaviours
* [ ] Scene and lifecycle management
* [ ] Framebuffer-based composition
* [ ] Layering and overlap support
* [ ] Diff-based terminal rendering
* [ ] Terminal resize handling
* [ ] TUI adapters
* [ ] Particle and environmental systems
* [ ] Documentation and examples
* [ ] Benchmarks and testing

## Credits

Developed by **IntrixLabs**.