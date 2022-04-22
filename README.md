## minimal.c

Le fichier *minimal.c* est exactement le même que celui des TPs, à part qu'il faut rajouter

```cpp
#if defined(_WIN32)
#include <windows.h>
#endif
```

avant

```cpp
#include <GL/gl.h>
#include <GL/glu.h>
```

## Compiler

Le build se fait avec *CMake* plutôt que *Makefile*, tout simplement parce que je ne connais pas *Makefile* 😇.
*CMake* est une alternative à *Makefile* moderne et cross-plateform, et c'est ce que vous utiliserez à partir de l'année prochaine.

Pour compiler, tout est expliqué ici : https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/install-a-compiler/.