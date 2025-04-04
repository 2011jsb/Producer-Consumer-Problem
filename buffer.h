#ifndef BUFFER_H
#define BUFFER_H

#ifdef _WIN32
#include "win_buffer.h"
#elif __linux__
#include "posix_buffer.h"
#endif

#endif
