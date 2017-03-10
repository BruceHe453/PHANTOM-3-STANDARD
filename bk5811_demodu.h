/*
 *
 *
 *
 *
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include "packet_common.h"

#define SPACE_NULL
#define IN  SPACE_NULL
#define OUT SPACE_NULL

#define DLT                 10.0

#define BK_SUCCESS          1
#define BK_FAILED           0
#define BK_OVERFLOW         4294967295
// Enhanced ShockBurst
#define BK_PREAMBLE_BITS    (1*8)
#define BK_ADDRESS_BITS     (5*8)
#define BK_PCF_BITS         9
#define BK_PAYLOAD_BITS     (32*8)
#define BK_CRC_BITS         (2*8)
//

#define SIGNAL_MAX_BITS    (BK_PREAMBLE_BITS + BK_ADDRESS_BITS + BK_PCF_BITS + BK_PAYLOAD_BITS + BK_CRC_BITS) 

#define PACKET_COUNT 1000

extern long g_inter[PACKET_COUNT];

// get file size
long get_file_size(char* filename);

// read signal from file
// g_buffer : malloc in this function, and should be freed by release() function
int get_signal_data(IN char *filename, IN char *buffer,IN long read_offset, IN OUT long *read_length);

// free the buffer
void release(IN char *buffer);

// calculate the threshold
float mean(IN char *buffer, IN long start, IN long length);

// find the signal
int find_inter(IN char *buffer, IN long start, IN long length);

// work function
// if find signal return 1, others 0.
int work(IN char *buffer, IN packet_param *lpp, OUT long *start_position, OUT uint8_t *channel);

/* pravite functions */

// dedmodulate the signal
int8_t demod_bits(IN char *buffer, IN long ss, IN int demod_length, IN int sample_per_symbol);

// search the preamble
long search_preamble(IN char *buffer, IN long ss, IN long sig_len, IN int match_length, IN int preamble_bytes, IN uint64_t dest_preamble, IN int sample_per_symbol);

// value to bytes array
void packet_pack(IN int64_t address, IN uint16_t pcf, IN uint8_t *payload, IN int payload_len, OUT uint8_t *packet);

// check the crc, if the crc not match, disable the signal
uint32_t calc_crc( IN const uint8_t *data, IN size_t data_len);

/*
 * debug function
 * 
*/
// debug the could not demodule signal.
void set_inter(long end);
