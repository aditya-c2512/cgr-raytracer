# CGR 2025 Raytracer

## Building & Running
### Supported Environments
- This project was developed and tested primarily on **MacOS (Sequoia 15.6.x and Tahoe 26.0.x)**.
- However, all libraries and frameworks employed are compatible with all **Linux** and **Windows** systems.
- The project is developed using **C++20**, utilising **CMake** as the build tool.

> **NOTE:** The `Logger` class uses ANSI escape codes for coloured console output. 
> 
> While these codes are compatible with all recent versions of Linux and MacOS,
> there is a slight chance these escape codes might not work on a Windows system.
> 
> According to [this post](https://superuser.com/questions/1729472/unable-to-use-ansi-escape-sequences-in-windows-10),
> all machines running **Windows 10 v1511 (build 10586)** and later should be able to 
> accurately display the coloured text in the terminal.
> 
> Nonetheless, the `Logger` is not the main aim of this project, and the escape codes
> will not break the intended functionality.

### Build the project
```shell
cd Code/
cmake . # Skip if you don't want to rebuild Makefile.
make
```
### Run the project
```shell
./cgr-raytrace --scene="../ASCII/Scene.json" --bvh="../ASCII/Scene_BVH.json" --render-output="../Output/Scene.ppm"
```

## Features Implemented
### Module 1
- Blender Scene to JSON Exporter Python script. Supports exporting camera, lights, and simple shapes like spheres, cubes, and planes.
- Image I/O Class for .ppm files. Enables main rendering loop to render scenes to frames.
- Virtual pinhole camera class to capture rays through each pixel for the start of raytracing. Configurable via the Blender exported JSON file.
- Simple Scene importer to initialise all shapes and meshes that will be raytraced.

### Module 2
- Supported JSON imports and ray-shape intersection routines for spheres, planes, cubes, and Axis-Aligned Bounding Boxes (used in BVH).
- Structured the shapes as implementation of Shape interface, and used a Shape Factory to abstract the shape instantiation procedure.
- Bounded Volume Hierarchy and Axis-Aligned Bounded Box for optimising ray-scene intersection tests.
- BVH is made from a BVH JSON file. However, if a path is not provided, the renderer doesn't use acceleration structures while rendering.

## Coding Conventions
### Logs
- `[INFO]` is for informational messages like startup, shutdown, etc.
- `[DEBUG]` is for debugging messages added to check current state of the application.
- `[WARN]` is for non-critical errors.
- `[ERROR]` is for critical errors like `nullptr errors`, etc.

## References
- Ray Tracing in One Weekend
- Scratchapixel
- Graphics Codex