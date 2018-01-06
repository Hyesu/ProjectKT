#pragma once

#define ASSERT(assert, ...) Assert(assert, __FILE__, __LINE__)

void Assert(bool assert, const char* file, int line); //, const char* format, ...);
void Log(const char* format, ...);