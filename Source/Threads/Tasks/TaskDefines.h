#pragma once

#include <Core\Core.h>
#include <boost\atomic\atomic.hpp>

#define Task_Data_Max_size 32
#define Max_Tasks 1024

typedef void (*Kernal)(void *_taskData);