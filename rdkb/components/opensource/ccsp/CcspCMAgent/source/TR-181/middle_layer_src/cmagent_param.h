#ifndef __CMAGENT_PARAM_H__
#define __CMAGENT_PARAM_H__
#include <stdint.h>
#include <stdlib.h>
#include <msgpack.h>

#define LLD_SUBDOC "lldqoscontrol"

typedef struct
{
    bool enable;
} cmagentparam_t;
typedef struct {
    cmagentparam_t  *param;       
    char *       subdoc_name;
    uint32_t     version;
    uint16_t     transaction_id;
} cmagentdoc_t;

/**
 *  Convert the msgpack map into the doc_t structure.
 *
 *  @param e    the entry pointer
 *  @param map  the msgpack map pointer
 *
 *  @return 0 on success, error otherwise
 */
int processcmagentparams( cmagentparam_t *e, msgpack_object_map *map );

/**************************************************************************
 *  This function returns a general reason why the conversion failed.
 *
 *  @param errnum the errno value to inspect
 *
 *  @return the constant string (do not alter or free) describing the error
  **************************************************************************/
const char* cmagentdocStrerror( int errnum );
/**************************************************************************
 *  This function converts a msgpack buffer into an cmagentdoc_t structure
 *  if possible.
 *
 *  @param buf the buffer to convert
 *  @param len the length of the buffer in bytes
 *
 *  @return NULL on error, success otherwise
 **************************************************************************/
cmagentdoc_t* cmagentdocConvert( const void *buf, size_t len );
/**************************************************************************
 *  This function destroys an cmagentdoc_t object.
 *
 *  @param d the gwmgrdoc to destroy
 **************************************************************************/
void cmagentdocDestroy( cmagentdoc_t *gd );

#endif
