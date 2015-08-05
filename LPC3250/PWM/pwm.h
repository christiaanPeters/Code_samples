/*
 *  chardev.h - the header file with the ioctl definitions.
 *
 *  The declarations here have to be in a header file, because
 *  they need to be known both to the kernel module
 *  (in chardev.c) and the process calling ioctl (ioctl.c)
 */

#ifndef pwm_H
#define pwm_H

/* 
 * The major device number. We can't rely on dynamic 
 * registration any more, because ioctls need to know 
 * it. 
 */
#define MAJOR_NUM 100
#define SUCCESS 0
#define DEVICE_NAME "pwm"
#define BUF_LEN 80
#define MAX_NUMBER_OF_FILES 5 // 0 also counts as 1

#endif
