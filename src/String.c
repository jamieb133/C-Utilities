#include <Allocator.h>
#include <Logger.h>
#include <String.h>

static void Resize(String* str, u64 size, bool keep)
{
    char* newdata = Acquire(str->alloc, char, size);

    if (keep)
    {
        Memcpy(char, newdata, str->data, str->length); 
    }

    Release(str->alloc, str->data);
    str->data = newdata;
    str->capacity = size;
}

u64 Strlen(const char* str)
{
    Assert(str, "str null");
    const char* ptr;
    for (ptr = str; *ptr != '\0'; ptr++);
    return ptr - str;
}

void Strcpy(char* str, const char* str2)
{
    Assert(str, "str null");
    Assert(str2, "str2 null");
    Memcpy(char, str, str2, Strlen(str2) + 1);
    str[Strlen(str2)] = '\0';
}

bool Strcmp(const char* str, const char* str2)
{
    Assert(str, "str null");
    Assert(str2, "str2 null");
    u64 strlen1 = Strlen(str);
    if (strlen1 != Strlen(str2))
    {
        return false;
    }
    return Memcmp(char, str, str2, strlen1);
}

void String_Init(String* str, Allocator* alloc, const char* src)
{
    Assert(str, "str null");
    Assert(alloc, "str null");
    Assert(src, "src null");

    // Allocate twice the length
    str->length = Strlen(src) + 1;
    str->capacity = str->length * 2;
    str->data = Acquire(alloc, char, str->capacity);
    str->alloc = alloc;

    String_CopyRaw(str, src);
}

void String_Deinit(String* str)
{
    Assert(str, "str null");

    Release(str->alloc, str->data);

    str->length = 0;
    str->capacity = 0;
    str->data = NULL;
    str->alloc = NULL;
}

void String_Copy(String* dst, const String* src)
{
    Assert(dst, "str null");
    Assert(src, "src null");

    if ((dst->capacity <= src->length) || (dst->capacity >= (src->length * 2)))
    {
        Resize(dst, src->length * 2, false);
    }

    Memcpy(char, dst->data, src->data, src->length + 1);
    dst->length = src->length;
}

void String_CopyRaw(String* dst, const char* src)
{
    Assert(dst, "str null");
    Assert(src, "src null");

    u64 srclen = Strlen(src);

    if ((dst->capacity <= srclen) || (dst->capacity >= (srclen * 2)))
    {
        Resize(dst, srclen * 2, false);
    }

    Memcpy(char, dst->data, src, srclen + 1);
    dst->length = srclen;
}

void String_Concat(String* dst, const String* src)
{
    Assert(dst, "str null");
    Assert(src, "src null");

    u64 requiredSize = dst->length + src->length + 1;

    if ((dst->capacity <= requiredSize) || (dst->capacity >= (requiredSize * 2)))
    {
        Resize(dst, requiredSize * 2, true);
    }

    Memcpy(char, dst->data + dst->length, src->data, src->length + 1);
    dst->length += src->length;
}

void String_ConcatRaw(String* dst, const char* src)
{
    Assert(dst, "str null");
    Assert(src, "src null");

    u64 srclen = Strlen(src);
    u64 requiredSize = dst->length + srclen + 1;

    if ((dst->capacity <= requiredSize) || (dst->capacity >= (requiredSize * 2)))
    {
        Resize(dst, requiredSize * 2, true);
    }

    Memcpy(char, dst->data + dst->length, src, srclen + 1);
    dst->length += srclen;
}

bool String_Eq(const String* dst, const String* src)
{
    Assert(dst, "str null");
    Assert(src, "src null");

    if (dst->length != src->length)
    {
        return false;
    }

    return Memcmp(char, dst->data, src->data, dst->length);
}

bool String_EqRaw(const String* dst, const char* src)
{
    Assert(dst, "str null");
    Assert(src, "src null");

    if (dst->length != Strlen(src))
    {
        return false;
    }

    return Memcmp(char, dst->data, src, dst->length);
}

