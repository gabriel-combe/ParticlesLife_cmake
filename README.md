# ParticlesLife_cmake
Particle interaction system in my custom engine (OpenGL + Imgui).

https://github.com/gabriel-combe/ParticlesLife_cmake/assets/26323828/a065b5a6-4e9b-40b8-b241-228632a06b3a


## Installation

This project uses cmake and the dependencies listed below.
I will try to add a guide in the future for the compilation of the dependencies.

## Usage example

Prepare the build directory with 
```bash
cmake -S . -B build
```
And build with
```bash
cmake --build build
```

To change the parameters of the particles, directly change the attraction coefficients in the code.

> Need to add Imgui interaction to manage the particles

> Note: It may not work as I am a beginner in cmake

## Dependencies
- [GLFW](https://github.com/glfw/glfw)
- [Glad](https://github.com/Dav1dde/glad)
- [glm](https://github.com/g-truc/glm)
- [ImGUI](https://github.com/ocornut/imgui/tree/docking)

## Thoughts

I am not pleased by this version as it does not compile the dependencies itself, and the particle system needs some improvments.

## Meta

[Gabriel Combe-Ounkham](https://github.com/gabriel-combe)

Distributed under the GNU GENERAL PUBLIC license. See ``LICENSE`` for more information.


