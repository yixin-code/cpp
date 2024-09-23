#include <stdio.h>

int main(int argc, char *argv[]) {
    int arr[3][4] = {[2][1] = 11, [2][3] = 22};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%d ", arr[i][j]);
        }
    }
    printf("\n");

    return 0;
}