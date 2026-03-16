#pragma once

#include <stdbool.h>

#include <Allocator.h>
#include <CustomTypes.h>

typedef struct {
    u64 length, capacity;
    char* data;
    Allocator* alloc;
} String;

void String_Init(String* str, Allocator* alloc, const char* initstr);
void String_Deinit(String* str);
void String_Copy(String* dst, const String* src);
void String_CopyRaw(String* dst, const char* src);
void String_Concat(String* dst, const String* src);
void String_ConcatRaw(String* dst, const char* src);
bool String_Eq(const String* dst, const String* src);
bool String_EqRaw(const String* dst, const char* src);
