#ifndef LOAD_DYNAMIC_LIBRARY_LIBRARY_H
#define LOAD_DYNAMIC_LIBRARY_LIBRARY_H

extern "C" __declspec(dllexport) int library_getint();

extern "C" __declspec(dllexport) void library_setint(int*);

#endif
