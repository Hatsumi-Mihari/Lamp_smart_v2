#define RE_TIME_LAYER_PROTO_H
#ifdef RE_TIME_LAYER_PROTO_H

#include <stdint.h>

typedef struct RE_DB_Time_Layer
{
   char key_name_Layer[64];
   int64_t time_start;
   int64_t time_end;
}RE_DB_Time_Layer;

#endif