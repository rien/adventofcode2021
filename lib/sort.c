

void insertion_sort(int* values, int size) {
    int tmp, j;
    int i = 1;
    while (i < size) {
        tmp = values[i];
        j = i - 1;
        while(j >= 0 && values[j] > tmp) {
            values[j + 1] = values[j];
            j -= 1;
        }
        if (j + 1 != i) {
            values[j + 1] = tmp;
        }
        i += 1;
    }
}
