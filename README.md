stucktubes
==========

# C++/OpenCV/Qt Object Abandonment Detection Tool

At the moment, this is only tested/supported in a Linux environment with OpenCV
already installed and configured.  As I work through the project, I will be
sure to document all of the dependencies as best as I can and hopefully provide
information (or links to information) on how to build and install dependencies.

One of the goals of this project is to make it compatible with Windows as the
end-users will be on Windows boxes.  However, if time does not allow that, it
should at least run in a virtual Linux box.

## Recommended Build Instructions:

```bash
$ cd stucktubes
$ mkdir build
$ cd build
$ cmake ..
$ make
```

You can then run the project from the build directory with

```bash
$ ./bin/StuckTubes.out
```
