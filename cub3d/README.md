*This project has been created as part of the 42 curriculum by mamuzamm.*

# cub3D

## Description

cub3D is a small first-person 3D game inspired by Wolfenstein 3D, the first
FPS in history. It renders the inside of a maze in real time using the
ray-casting technique: for every column of the window, a ray is cast through
the map grid (DDA algorithm) and a textured wall slice is drawn with a height
proportional to the perpendicular distance of the hit.

The scene is described by a `.cub` configuration file that sets the four wall
textures (one per compass facing: NO, SO, WE, EA), the floor and ceiling
colors, and the map itself. This version is themed as the 42 Abu Dhabi
campus: the wall textures are photos taken on campus and `maps/campus.cub`
reproduces the real ground-floor layout of the school.

## Instructions

### Compile

```
make
```

This builds `libft`, the bundled MinilibX, and the `cub3D` executable
(cc, `-Wall -Wextra -Werror`). Requires a Linux machine with X11
development libraries (`libX11`, `libXext`).

### Run

```
./cub3D maps/campus.cub
```

Other maps: `maps/maze.cub`, `maps/open.cub`.

### Controls

| Key | Action |
| --- | --- |
| `W` `A` `S` `D` | move forward / strafe left / back / strafe right |
| `←` `→` | rotate the view |
| Mouse | rotate the view (bonus) |
| `ESC` or window close | quit |

### Map format

A `.cub` file contains, in any order before the map: `NO`, `SO`, `WE`, `EA`
followed by a texture path, and `F`, `C` followed by an `R,G,B` color. The
map comes last, uses only `0` (floor), `1` (wall), spaces (void) and a single
`N`, `S`, `E` or `W` spawn, and must be fully closed by walls. Any
misconfiguration makes the program print `Error` followed by an explicit
message and exit.

## Resources

- [Lode Vandevenne — Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html)
  (the classic reference for grid ray-casting and the camera-plane model)
- [42 Docs — MinilibX](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D — Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D)
- man pages: `math.h` (3), `open` (2), `read` (2), `gettimeofday` (2)

### AI usage

AI assistance (Anthropic's Claude) was used as a tool during this project,
in line with the curriculum's AI guidelines:

- converting the campus photos into 42-compliant XPM textures and making
  them tile seamlessly (offline image-conversion script, not part of the
  submitted code);
- tracing the campus floor plan into the `maps/campus.cub` grid;
- reviewing the code for leaks, norm issues and edge cases, and helping
  debug rendering artifacts (texture mirroring, close-up filtering).

All C code in this repository was reviewed, understood and is defended by
the author.
