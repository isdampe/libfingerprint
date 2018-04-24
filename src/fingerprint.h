#ifndef FINGERPRINT_H
#define FINGERPRINT_H
#include <string.h>
#include <stdbool.h>

#define FPRT_BIT_ZERO '0'
#define FPRT_BIT_ONE  '1'
#define FPRT_BIT_MAGIC '2'

typedef enum {
	FPRT_MODE_START_END,
	FPRT_MODE_START_END_SPACES,
	FPRT_MODE_STEALTHY
} fprt_mode;

typedef struct {
	char *input_text;
	char *fingerprint;
	char *output_text;
	char sha1[20];
	fprt_mode mode;
} fprt_obj;

fprt_obj fingerprint_init(char *input_text, char *fingerprint);
bool fingerprint_encode(fprt_obj *fprt);
char *fingerprint_to_encoded(char *fingerprint, size_t fingerprint_length);
void fingerprint_free(fprt_obj *fprt);

#endif
