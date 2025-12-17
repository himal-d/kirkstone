#ifndef __CMAGENT_HELPERS_H__
#define __CMAGENT_HELPERS_H__
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
/*----------------------------------------------------------------------------*/
/*                               helper    Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */
#define match(p, s) strncmp((p)->key.via.str.ptr, s, (p)->key.via.str.size)
#define member_size(type, member) sizeof(((type *)0)->member)
/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
enum {
    HELPERS_OK = 0,
    HELPERS_OUT_OF_MEMORY,
    HELPERS_INVALID_FIRST_ELEMENT,
    HELPERS_MISSING_WRAPPER,
    HELPERS_PARTIAL_APPLY
};

typedef int (*process_fn_t)(void *, int, ...);
typedef void (*destroy_fn_t)(void *);
/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 *  Simple helper function that decodes the msgpack, then checks for a few
 *  sanity items (including an optional wrapper map) before calling the process
 *  argument passed in.  This also allocates the structure for the caller.
 *
 *  @param buf          the buffer to decode
 *  @param len          the length of the buffer in bytes
 *  @param struct_size  the size of the structure to allocate and pass to process
 *  @param wrapper      the optional wrapper to look for & enforce
 *  @param expect_type  the type of object expected
 *  @param optional     if the inner wrapper layer is optional
 *  @param process      the process function to call if successful
 *  @param destroy      the destroy function to call if there was an error
 *
 *  @returns the object after process has done it's magic to it on success, or
 *           NULL on error
 *******************************************************************************/
void* comp_helper_convert( const void *buf, size_t len,
                      size_t struct_size, const char *wrapper,
                      msgpack_object_type expect_type, bool optional,
                      process_fn_t process,
                      destroy_fn_t destroy );


#endif
        