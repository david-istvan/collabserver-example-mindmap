# collabserver-example-mindmap

## Overview

---

Mindmap is a tool that uses the [CollabServer Framework](https://github.com/collabserver/) to work with several collaborators in realtime.

## Build (CMake)

---

- Requirements
  - [CMake](https://cmake.org/)
  - C++11
  - `pragma once` support
  - Tested with gcc 4.8.4
  - Tested with clang 5.0.0
  - Tested only on Linux. No support certified for Mac and Windows

```bash
# Build the tests

mkdir build
cd build
cmake ..
make

# Or use the build script
./build.sh
```

| CMake option | Description |
| --- | --- |
| CMAKE_BUILD_TYPE | Debug, Release, RelWithDebInfo, MinSizeRel |

## Mindmap description

---

![EA mindmap model](model/domainmodel.png)
