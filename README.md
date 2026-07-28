*This project has been created as part of the 42 curriculum by catrenet, gechavia.*

# Cub3D

## Description

Cub3D is a raycasting project inspired by the classic game Wolfenstein 3D. It renders a maze-like environment, displaying textured walls from the player's point of view, and allowing movement and camera rotation. It aims to develop the use of maths to create solid raycasting algorithms and real-time rendering using the MiniLibX graphics library.

### Features

- Parsing and validating .cub map files.
- Rendering textured walls with different textures for each cardinal direction.
- Floor and ceiling colors.
- Player movement (forward, backward, left, right).
- Camera rotation using the keyboard.
- Real-time rendering with smooth updates in a window created with MiniLibX.

### Core Concepts

- Raycasting: rendering technique used to create the illusion of a 3D world in 2D. For every vertical column of pixels on the screen, a ray is cast into the map until it intersects a wall. The distance to the wall determines the height of the wall slice that is drawn, creating a perspective effect.

- Digital Differential Analyzer (DDA): algorithm used during raycasting to efficiently determine which wall a ray intersects first by stepping from one grid cell to the next on the nearest horizontal or vertical grid line. This avoids checking every point along the ray, thus both avoiding unnecessary calculations and ensuring no wall is missed.

- Camera Plane: vector perpendicular to the player's viewing direction. It defines the width of the player's field of view (FOV). Rays are cast through different points along this plane, rendering the scene from left to right.

- Rotation Matrix: 2D matrix used to rotate the player's viewing direction and camera plane when the player turns left or right without recalculating angles each time.

- Perspective Projection: after a wall is detected, its distance from the player is used to calculate how tall it should appear on the screen: nearby walls appeartaller, distant ones shorter, for a realistic sense of depth.

- Fish-eye correction: using the perpendicular distance to the camera plane to ensure walls maintain a consistent appearance across the screen instead of the raw distance traveled by each ray which causes walls near the edges to appear distorted. 

- Texture Mapping: applying an image to each wall surface. We calculate the exact point where a ray hits a wall and use that information to determine which column of the texture should be displayed.

## Instructions

- Compile with:
    make

- To clean up:
    make clean
    make fclean

- To rebuild:
    make re

- To run:
    ./cub3D maps/map.cub

- Example:
    ./cub3D maps/valid/big.cub

- To move in the map:
    W/A/S/D keys

- Rotate camera:
    -> / <- keys

- To exit: 
    ESC or upper right corner X in window

## Resources

<ins>General Research</ins>

- https://www.youtube.com/watch?v=G9i78WoBBIU
- https://lodev.org/cgtutor/raycasting.html
- https://harm-smits.github.io/42docs/projects/cub3d
- https://en.wikipedia.org/wiki/Ray_casting
- https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
- https://www.geeksforgeeks.org/maths/vector-addition/
- https://www.geeksforgeeks.org/maths/rotation-matrix/
- https://en.wikipedia.org/wiki/Endianness
- https://www.geeksforgeeks.org/dsa/little-and-big-endian-mystery/
- https://opengameart.org/

<ins> AI Usage </ins>

AI was used to help explain some of the concepts as well as to help testing.