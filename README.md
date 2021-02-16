## Build Instructions

### Command Line

1. Download and Install CMake
2. Open a terminal
3. Run cmake:

```
cd <source_folder>
cmake -S . -B <build_folder>
cmake --build <build_folder> --target install
```

### CMake GUI

You can use the CMake GUI to configure and generate the Visual Studio Project.

1. Download and Install CMake
2. Open the CMake GUI
3. Set the `Where is the source code:` field to the source folder
4. Set the `Where to build the binaries:` field to different location (e.g.: source_folder/build)
5. Click Configure
6. Click Generate

#### Windows

Once that is created you can build the **ALL_BUILD** project followed by building
the **INSTALL** project.

#### Linux

In the terminal:

```
cd <build_folder>
make install
```


## Running

Once built and installed, all the relevant files will be in the **dist** folder
at the top level of the source folder.

### Linux/macOS

In the terminal type:

```
./lab01
```

### Windows

Click on the **lab01.exe** from the File Explorer.

## References

Good place to learn OpenGL
https://www.learnopengl.com

Official OpenGL 4 Reference Documentation
https://www.khronos.org/registry/OpenGL-Refpages/gl4/

Official OpenGL Wiki
https://www.khronos.org/opengl/wiki/

Easy to Navigate OpenGL Function Documentation
http://docs.gl/

GLM Documentation
https://glm.g-truc.net/0.9.9/index.html

GLFW Documentation
https://www.glfw.org/

Good place for advanced graphics theory
https://www.scratchapixel.com/

### Features and Functionality
### Cameras
Model views:
Use keys 1, 2, 3, 4, 5 to toggle between different cameras (one for each model). This also toggles which model is in focus for transformations.

Camera Movement:
Arrow up and arrow down keys shift the camera position in the y direction
Arrow left and arrow right keys shift the camera position in the x direction
Left mouse button and cursor movement in y direction zooms in (cursor up) and out(cursor down)
Right mouse button and cursor movement in x direction pans camera left (cursor left) amd right (cursor right)
Middle mouse button and cursor movement in y direction tilts camera up (cursor up) and doen (cursor down)

Model transformations:
