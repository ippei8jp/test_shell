#ifndef __UTIL_H__
#define __UTIL_H__

extern int str_split(char* string, const char* separator, char** result, size_t result_size);
extern char* rtrim(char* string);
extern int str_to_uint32(char* s, uint32_t* pData, int base);

#endif  /* !__UTIL_H__ */
