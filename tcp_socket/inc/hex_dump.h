#ifndef _HEX_DUMP_H_
#define _HEX_DUMP_H_

#include <stdint.h>

#define VARIABLE_PTR_STRGFY(var) var, #var

#ifdef __cplusplus
extern "C" {
#endif

void hex_dump(uint8_t *buffer, char *var_name, size_t len);

#ifdef __cplusplus
}
#endif

#endif