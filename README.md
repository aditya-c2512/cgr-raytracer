# CGR 2025 Raytracer

## Building & Running
### Supported Environments
- This project was developed and tested primarily on **MacOS (Sequoia 15.6.x)**.
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

### Run the project

## Features Implemented

## Coding Conventions
### Logs
- `[INFO]` is for informational messages like startup, shutdown, etc.
- `[DEBUG]` is for debugging messages added to check current state of the application.
- `[WARN]` is for non-critical errors.
- `[ERROR]` is for critical errors like `nullptr errors`, etc.