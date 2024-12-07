#include <stdlib.h>

typedef struct {
    size_t requested_amount;
    void* allocation;
} alc;

enum Result {
    SUCCESS,
    FAILURE,
};

enum Result _multialloc(alc* request, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        void* allocation = malloc(request[i].requested_amount);
        if (allocation == NULL) {
            while (i != 0) {
                --i;
                free(request[i].allocation);
            }
            return FAILURE;
        }
        request[i].allocation = allocation;
    }
    return SUCCESS;
}

void _multifree(alc* request, size_t size) {
    while (size != 0) {
        --size;
        free(request[size].allocation);
    }
}

#define multialloc(request) _multialloc(request, sizeof(request)/sizeof(request[0]))
#define multifree(request) _multifree(request, sizeof(request)/sizeof(request[0]))
