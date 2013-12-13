#ifndef __SYSEX_H
#define __SYSEX_H

#ifdef WIN32
#include "../Libraries/win-util/stdint.h"
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

   uint8_t data_to_sysex(uint8_t *data, uint8_t *sysex, uint8_t len);
   uint8_t sysex_to_data(uint8_t *sysex, uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __SYSEX_H */
