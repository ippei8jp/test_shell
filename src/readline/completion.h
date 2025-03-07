#ifndef __COMPLETION_H__
#define __COMPLETION_H__

extern char *command_generator(const char *text, int state);
extern char **my_completion(const char *text, int start, int end);

#endif  /* !__COMPLETION_H__ */
