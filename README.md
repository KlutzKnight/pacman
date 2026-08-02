# Pacman

A Pac-Man clone written in C++ using SDL3.

## About
I Started this project to learn about game architecture and SDL3, and about making a complete game from scratch in C++. I achieved what I set out to do decided it was time to move on.

Rather than continuing to add more and more features, I decided to leave the project as it is and move on to other projects. I'm happy with where it ended up, and I think it serves as a solid snapshot of what I learned along the way.

---

## What's Included

* Tile-based map system
* Player movement
* Ghost movement and AI
* Pellet collection
* Collision detection
* Sprite rendering and animation
* Game state management

---

## What I didn't Add
I never set out to create a fully featured recreation of the original Pac-Man. After implementing the core gameplay and architecture, I considered the project basically complete.
I thought about adding just one more feature and then just this last one and I could've just kept going but I decided to draw the line here and move onto other projects.

Features I intentionally did **not** implement include:

* Multiple levels
* Complete arcade-accurate ghost behaviors
* Bonus fruit and scoring mechanics
* Menus and settings
* High score saving
* Polish such as visual effects, transitions, and extensive sound design

Many of these would have been fun additions, but they would have shifted the project from a learning exercise into an endless polishing effort. At that point, I preferred to invest my time into building something new instead.

---

## Dependencies
```bash
sd3
sdl3_image
sdl3_ttf
```

## Building

```bash
cmake --preset release
cmake --build build
```

Run the generated executable after the build completes.
```
build/release/src/pacman
```

---

Feel free to browse the code, borrow ideas, or use it as a reference for your own SDL/C++ projects.
