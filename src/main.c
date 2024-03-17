#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1024

void processChunk(char *chunk, size_t chunkSize, char *partialValue, size_t *partialSize) {
    size_t i = 0;
    char value[CHUNK_SIZE + 1];

    if (partialValue != NULL) {
        // Copy the partial value to the value buffer
        size_t partialLength = *partialSize;
        for (size_t j = 0; j < partialLength; j++) {
            value[i++] = partialValue[j];
        }
        *partialSize = 0;
    }

    for (; i < chunkSize; i++) {
        char c = chunk[i];
        if (c == ',') {
            // Print the value
            value[i] = '\0';
            printf("%s\n", value);
            i++;
            break;
        }
        value[i] = c;
    }

    // Copy the partial value from the current chunk
    for (; i < chunkSize; i++) {
        char c = chunk[i];
        if (c == ',' || c == '\n') {
            *partialSize = 0;
            break;
        }
        partialValue[*partialSize] = c;
        (*partialSize)++;
    }
}

int main() {
    FILE *file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char chunk[CHUNK_SIZE];
    char partialValue[CHUNK_SIZE];
    size_t partialSize = 0;
    size_t bytesRead;

    while ((bytesRead = fread(chunk, sizeof(char), CHUNK_SIZE, file)) > 0) {
        processChunk(chunk, bytesRead, partialValue, &partialSize);
    }

    fclose(file);
    return 0;
}
