#ifndef C_HIGHWAYHASH_H_
#define C_HIGHWAYHASH_H_

#include <stdint.h>
#include <string.h>
#include "zmalloc.h"

typedef struct {
    uint64_t v0[4];
    uint64_t v1[4];
    uint64_t mul0[4];
    uint64_t mul1[4];
} HighwayHashState;

static HighwayHashState highway_hash_init_state, target_state;
/* Initializes state with given key */
void HighwayHashReset(const uint64_t key[4]);

/* Takes a packet of 32 bytes */
void HighwayHashUpdatePacket(const uint8_t *packet, HighwayHashState *state);

/* Adds the final 1..31 bytes, do not use if 0 remain */
void HighwayHashUpdateRemainder(const uint8_t *bytes, const size_t size_mod32,
                                HighwayHashState *state);
/* Compute final hash value. Makes state invalid. */
//static uint64_t HighwayHashFinalize64(HighwayHashState* state);


/*////////////////////////////////////////////////////////////////////////////*/
/* Non-cat API: single call on full data                                      */
/*////////////////////////////////////////////////////////////////////////////*/

uint64_t HighwayHash64(const uint8_t *data, size_t size);

/*
Usage examples:
#include <inttypes.h>
#include <stdio.h>
void Example64() {
  uint64_t key[4] = {1, 2, 3, 4};
  const char* text = "Hello world!";
  size_t size = strlen(text);
  uint64_t hash = HighwayHash64((const uint8_t*)text, size, key);
  printf("%016"PRIx64"\n", hash);
}
void Example64Cat() {
  uint64_t key[4] = {1, 2, 3, 4};
  HighwayHashCat state;
  uint64_t hash;
  HighwayHashCatStart(key, &state);
  HighwayHashCatAppend((const uint8_t*)"Hello", 5, &state);
  HighwayHashCatAppend((const uint8_t*)" world!", 7, &state);
  hash = HighwayHashCatFinish64(&state);
  printf("%016"PRIx64"\n", hash);
}
*/

#endif  // C_HIGHWAYHASH_H_
