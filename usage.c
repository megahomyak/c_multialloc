#include "multialloc.c"
#include <stdio.h>

void main(void) {
    alc request[] = {
        /* The NULL pointers here are just for demonstration (to show that the field they're assigned to changed), actually manually setting .allocation to anything is unnecessary */
        (alc){ .requested_amount = 50, .allocation = NULL },
        (alc){ .requested_amount = 102, .allocation = NULL },
        (alc){ .requested_amount = 73 },
        (alc){ .requested_amount = 67 },
    };
    if (multialloc(request) == SUCCESS) {
        printf("SUCCESS!:");
        for (int i = 0; i < sizeof(request)/sizeof(request[0]); ++i) {
            printf(" %p", request[i].allocation);
        }
        multifree(request);
        printf("\n");
    } else {
        printf("FAILURE!\n");
    }
}
