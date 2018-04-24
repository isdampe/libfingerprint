#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "fingerprint.h"

fprt_obj fingerprint_init(char *input_text, char *fingerprint)
{
	fprt_obj fprt;
	fprt.input_text = calloc(strlen(input_text) +1, sizeof(char));
	fprt.fingerprint = calloc(strlen(fingerprint) +1, sizeof(char));
	strcpy(fprt.input_text, input_text);
	strcpy(fprt.fingerprint, fingerprint);
	fprt.mode = FPRT_MODE_START_END;
	return fprt;
}

bool fingerprint_encode(fprt_obj *fprt)
{
	//Not implemented yet.
	if (fprt->mode != FPRT_MODE_START_END)
		return false;

	size_t input_length = strlen(fprt->input_text);
	size_t fingerprint_length = strlen(fprt->fingerprint);

	//Get the encoded fingerprint.
	char *fingerprint_encoded = fingerprint_to_encoded(fprt->fingerprint, fingerprint_length);

	//The output size is the input length + 2 times the fingerprint length * 8 (to bits) + 1 for null-terminating char + 1 for magic bit..
	fprt->output_text = calloc(input_length + (2 * fingerprint_length * 8) + 1 + 1, sizeof(char));

	strcat(fprt->output_text, fingerprint_encoded);
	strcat(fprt->output_text, fprt->input_text);
	strcat(fprt->output_text, fingerprint_encoded);

	free(fingerprint_encoded);
	return true;
}

char *fingerprint_to_encoded(char *fingerprint, size_t fingerprint_length)
{
	char *output_text = calloc((fingerprint_length * 8) + 1 + 1, sizeof(char));
	for (int i=0; i<fingerprint_length; ++i)
	{
		char current_char = fingerprint[i];
		for (int b=0; b<8; ++b)
		{
			//Each bit.
			uint8_t current_bit = (current_char >> (7 -b)) & 1;
			output_text[i * 8 + b] = (current_bit == 0 ? FPRT_BIT_ZERO : FPRT_BIT_ONE);
		}
	}

	//Set the magic bit.
	output_text[fingerprint_length * 8] = FPRT_BIT_MAGIC;
	return output_text;
}

void fingerprint_free(fprt_obj *fprt)
{
	free(fprt->output_text);
}
