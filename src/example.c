#include <stdio.h>
#include "fingerprint.h"

int main()
{
	printf("Creating fprt_obj for text Hello world, with fingerprint 'My fingerprint.'\n");

	fprt_obj fingerprint = fingerprint_init("Hello world", "My fingerprint.");
	if (!fingerprint_encode(&fingerprint))
	{
		printf("Error encoding fprt_obj.\n");
		return 1;
	}

	printf("Encoded: %s\n", fingerprint.output_text);
	fingerprint_free(&fingerprint);
	
	return 0;
}
