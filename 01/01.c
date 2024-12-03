#include <stdio.h>
#include <stdlib.h>


int commpare(const void* num1, const void* num2){
    int f = *((int*) num1);
    int s = *((int*) num2);
    if (f>s) return 1;
    if (f<s) return -1;
    return 0;
}

int main() {
    FILE* file;
    int* array1 = NULL;
    int* array2 = NULL;
    char filename[] = "input.txt";  // Replace with your file name

    unsigned int capacity = 1000;
    unsigned int index = 0;

    array1 = (int*)malloc(capacity * sizeof(int));
    array2 = (int*)malloc(capacity * sizeof(int));

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read numbers line by line
    while (fscanf(file, "%d %d", array1 + index, array2 + index) == 2) {
        index += 1;
        if (index >= 1000) {  // Safety check to avoid exceeding array bounds
            capacity += 100;
            array1 = (int*)realloc(array1, capacity * sizeof(int));
            array2 = (int*)realloc(array2, capacity * sizeof(int));
            if (array1 == NULL || array2 == NULL){
                perror("MEM ALLOC FAILED");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("Total lines read: %d\n", index);

    qsort(array1, index, sizeof(int), commpare);
    qsort(array2, index, sizeof(int), commpare);

    int total_distance = 0;

    for (unsigned int i = 0; i < index; i++){
        int dif = (*(array1 + i) - *(array2 + i));
        printf("%d - %d = %d\n", *(array1+i), *(array2 + i), dif );
        total_distance += abs(dif);
    }
    printf("Total Distance: %d\n", total_distance);

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}
