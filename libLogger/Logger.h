#pragma once

#define ASSERT(assert) Assert(assert, __FILE__, __LINE__)
#define ASSERT_EXTRA(assert, format, ...) Assert(assert, __FILE__, __LINE__, format, __VA_ARG__)

void Assert(bool assert, const char* file, int line);
void AssertExtraInfo(bool assert, const char* file, int line, const char* format, ...);
void Log(const char* format, ...);