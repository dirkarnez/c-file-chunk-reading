#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1024

int main() {
    FILE *file = fopen("../data.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char chunk[CHUNK_SIZE];

    size_t bytesRead;
    char value[CHUNK_SIZE + 1];
    size_t value_idx = 0;

    
    while ((bytesRead = fread(chunk, sizeof(char), CHUNK_SIZE, file)) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            char c = chunk[i];
            
            if (c == 0x0A && (i > 0 && chunk[i - 1] == 0x0D)) {
                // Print the value
                value[value_idx++] = '\0';
                printf("%s\n", value);
                value_idx = 0;
            } else {
                if (c != 0x0D) {
                    value[value_idx++] = c;
                }
            }
        }
    }

    value[value_idx] = '\0';
    printf("%s\n", value);

    fclose(file);
    return 0;
}
