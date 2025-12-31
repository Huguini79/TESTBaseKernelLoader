#ifndef STRING_H
#define STRING_H

static inline int strncmp(const char* str1, const char* str2, int n)
{
    unsigned char u1, u2;

    while(n-- > 0)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}

static inline size_t strlen(const char* str) {
	size_t len = 0;

	while(str[len]) {
		len++;
	}

	return len;

}

static inline void memcpy(void *dest, void *src, int len) {
    char *d = dest;
    char *s = src;

    while(len--) {
        *d++ = *s++;
    }

    return dest;

}

#endif