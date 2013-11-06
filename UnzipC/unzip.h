#ifndef _UNZIP_H_
#define _UNZIP_H_

#include "stdtypes.h"

extern void history_test (void);

extern bool unzip_dump_hex             (const char * filename_in, const char * filename_out);
extern bool unzip_dump_header_and_text (const char * filename_in, const char * filename_out);
extern bool unzip_lz77                 (const char * filename_in, const char * filename_out);

#endif /* _UNZIP_H_ */

