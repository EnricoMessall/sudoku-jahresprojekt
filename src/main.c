//
// Created by Nicolas on 11.05.2020.
//

#include <stdio.h>
#include "generator/generator.c"

int main() {
    int array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = matchBox(array);
    printf("%d", result);
    return 0;
}
