#ifndef __UTIL_H__
#define __UTIL_H__

#if defined(__CC_ARM) || defined(__ICCARM__)

int fputc(int ch, FILE *f);

#elif defined(__GNUC__)

int _write(int fd, char *ptr, int len);

#endif

#endif