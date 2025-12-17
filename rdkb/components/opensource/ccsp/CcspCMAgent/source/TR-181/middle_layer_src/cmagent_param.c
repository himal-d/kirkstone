#include <errno.h>
#include <string.h>
#include <msgpack.h>
#include <stdarg.h>
#include "cmagent_helpers.h"
#include "cmagent_param.h"
#include "ansc_platform.h"
/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
enum {
    OK                       = HELPERS_OK,
    OUT_OF_MEMORY            = HELPERS_OUT_OF_MEMORY,
    INVALID_FIRST_ELEMENT    = HELPERS_INVALID_FIRST_ELEMENT,
    INVALID_OBJECT,
    INVALID_VERSION,
};
/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
int processcmagentparams( cmagentparam_t *e, msgpack_object_map *map );
int processcmagentdoc( cmagentdoc_t *gd, int num, ...); 

cmagentdoc_t* cmagentdocConvert( const void *buf, size_t len )
{
	return comp_helper_convert( buf, len, sizeof(cmagentdoc_t), LLD_SUBDOC, 
                            MSGPACK_OBJECT_MAP, true,
                           (process_fn_t) processcmagentdoc,
                           (destroy_fn_t) cmagentdocDestroy );
}
void cmagentdocDestroy( cmagentdoc_t *gd )
{

    if( gd != NULL )
    {
        if( NULL != gd->param )
		{
			free( gd->param );
		}
        if( NULL != gd->subdoc_name )
	    {
	        free( gd->subdoc_name );
        }
	    free( gd );
    }
}

/* See webcfgdoc.h for details. */
const char* cmagentdocStrerror( int errnum )
{
    struct error_map {
        int v;
        const char *txt;
    } map[] = {
        { .v = OK,                               .txt = "No errors." },
        { .v = OUT_OF_MEMORY,                    .txt = "Out of memory." },
        { .v = INVALID_FIRST_ELEMENT,            .txt = "Invalid first element." },
        { .v = INVALID_VERSION,                 .txt = "Invalid 'version' value." },
        { .v = INVALID_OBJECT,                .txt = "Invalid 'value' array." },
        { .v = 0, .txt = NULL }
    };
    int i = 0;
    while( (map[i].v != errnum) && (NULL != map[i].txt) ) { i++; }
    if( NULL == map[i].txt )
    {
	CcspTraceWarning(("----gwmgrdocStrerror----\n"));
        return "Unknown error.";
    }
    return map[i].txt;
}

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
/**
 *  Convert the msgpack map into the doc_t structure.
 *
 *  @param e    the entry pointer
 *  @param map  the msgpack map pointer
 *
 *  @return 0 on success, error otherwise
 */
int processcmagentparams( cmagentparam_t *e, msgpack_object_map *map )
{
    int left = map->size;
    uint8_t objects_left = 0x01;
    msgpack_object_kv *p;
    p = map->ptr;
    while( (0 < objects_left) && (0 < left--) )
    {
        if( MSGPACK_OBJECT_STR == p->key.type )
        {
              if( MSGPACK_OBJECT_BOOLEAN == p->val.type )
              {
                if( 0 == match(p, "Device.QOS.X_RDK_LldMarkingRules.Enable") )
                {
                    e->enable = p->val.via.boolean;
                    printf("e->enable - %d-%s-%d\n",e->enable,__FUNCTION__,__LINE__);
                    objects_left &= ~(1 << 0);
                }
            }
        }
           p++;
    }     
    
    if( 1 & objects_left ) {
    } else {
        errno = OK;
    }
   
    return (0 == objects_left) ? 0 : -1;
}

int processcmagentdoc( cmagentdoc_t *gd,int num, ... )
{
    //To access the variable arguments use va_list 
	va_list valist;
	va_start(valist, num);//start of variable argument loop

	msgpack_object *obj = va_arg(valist, msgpack_object *);//each usage of va_arg fn argument iterates by one time
	msgpack_object_map *mapobj = &obj->via.map;

	msgpack_object *obj1 = va_arg(valist, msgpack_object *);
	gd->subdoc_name = strndup( obj1->via.str.ptr, obj1->via.str.size );

	msgpack_object *obj2 = va_arg(valist, msgpack_object *);
	gd->version = (uint32_t) obj2->via.u64;

	msgpack_object *obj3 = va_arg(valist, msgpack_object *);
	gd->transaction_id = (uint16_t) obj3->via.u64;
	va_end(valist);//End of variable argument loop


	gd->param = (cmagentparam_t *) malloc( sizeof(cmagentparam_t) );
    if( NULL == gd->param )
    {
	    CcspTraceWarning(("entries count malloc failed\n"));
        return -1;
    }
    memset( gd->param, 0, sizeof(cmagentparam_t));

	if( 0 != processcmagentparams(gd->param, mapobj) )
	{
		CcspTraceWarning(("process_portdocparams failed\n"));
		return -1;
	}

    return 0;
}
