#include "../lib/io.c"
#include "../lib/sort.c"

void test_one() {
    int array[] = { 2, 1 };
    insertion_sort(array, 1);
    assert(array[0] == 2);
    assert(array[1] == 1);
}

void test_two() {
    int array[] = { 2, 1 };
    insertion_sort(array, 2);
    assert(array[0] == 1);
    assert(array[1] == 2);
}

void test_three() {
    int array[] = { 3, 2, 1 };
    insertion_sort(array, 3);
    assert(array[0] == 1);
    assert(array[1] == 2);
    assert(array[2] == 3);
}

void test_alot() {
    int array[] = { 3, 2, 1, 5, 5, 2, 6, 9, 0 };
    insertion_sort(array, 9);
    for(int i = 0; i < 8; i += 1) {
        assert(array[i] <= array[i + 1]);
    }
}

int main() {
    test_one();
    test_two();
    test_three();
    test_alot();
}
