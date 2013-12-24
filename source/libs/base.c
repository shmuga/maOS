#include "system.h"
void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const unsigned char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

int strcmp(const char *s1, const char *s2)
{
        for (;;) {
                int cmp = *s1 - *s2;
                if (cmp != 0 || *s1 == '\0' || *s2 == '\0') {
                        return cmp;
                }
                ++s1;
                ++s2;
        }
}

int strncmp(const char *s1, const char *s2, size_t limit)
{
        size_t i = 0;
        while (i < limit) {
                int cmp = *s1 - *s2;
                if (cmp != 0 || *s1 == '\0' || *s2 == '\0') {
                        return cmp;
                }
                ++s1;
                ++s2;
                ++i;
        }
        return 0;
}

char *strncpy(char *dest, const char *src, size_t limit)
{
        char *ret = dest;

        while (*src != '\0' && limit > 0) {
                *dest++ = *src++;
                --limit;
        }
        if (limit > 0) {
                *dest = '\0';
        }

        return ret;
}

