typedef struct
{
    int *dir;
    int size;
} IntArray;

IntArray *int_array_create(int size);
void int_array_write(IntArray *arr, int pos, int dato);
void int_array_print(IntArray *arr);

void int_array_destroy(IntArray *arr);
void int_array_adjust(IntArray *arr);
