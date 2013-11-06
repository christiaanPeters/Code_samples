#ifndef  RESOURCE_DETECTOR_H
#define  RESOURCE_DETECTOR_H

#define  main               xmain
#define  malloc(size)       xmalloc ((size), (__FILE__), (__LINE__))
#define  free(addr)         xfree ((addr)), (addr) = NULL
#define  fopen(name,mode)   xfopen ((name),(mode))
#define  fclose(fptr)       xfclose ((fptr)), (fptr) = NULL

extern int      xmain(int argc, char * argv[]);
extern void *   xmalloc(unsigned int size, char * file, unsigned int line);
extern void     xfree(void * addr);
extern FILE *   xfopen(const char * name, const char * mode);
extern int      xfclose(FILE * fptr);
extern void     resource_detection (void);

#endif
