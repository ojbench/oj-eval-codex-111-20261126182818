#pragma once

#undef strtok

inline char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *next = nullptr;
    if (str != nullptr) next = str;
    if (next == nullptr) return nullptr;

    bool separator[256] = {};
    for (const char *p = delim; *p != '\0'; ++p) {
        separator[static_cast<unsigned char>(*p)] = true;
    }

    // Leading separators do not produce empty tokens or modify the buffer.
    while (*next != '\0' && separator[static_cast<unsigned char>(*next)]) {
        ++next;
    }
    if (*next == '\0') return nullptr;

    char *token = next;
    while (*next != '\0' && !separator[static_cast<unsigned char>(*next)]) {
        ++next;
    }
    if (*next != '\0') {
        *next = '\0';
        ++next;
    }
    return token;
}
