#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

// ej 2
int binsearch(int a[], int len, int v)
{
    int s = 0, e = len - 1, half = (s + e) / 2;

    while (s <= e && a[half] != v)
    {
        if (a[half] > v)
            e--;
        else
            s++;

        half = (s + e) / 2;
    }

    return a[half] == v ? half : -1;
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

// ej 3
/* void insertion_sort(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        int j = i;
        while (j >= 1 && arr[j] < arr[j - 1])
            swap(&arr[j], &arr[j--]);
    }
} */

void insertion_sort_upgrade(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        int j = i, k = 0, l = i;
        while (j >= 1 && arr[l] < arr[j - 1])
            j--, k++;

        int aux = arr[l];

        for (; k > 0; k--)
            arr[l] = arr[--l];

        arr[j] = aux;
    }
}

// ej 4
void copy_segment(int *arr, int *dest, int s, int e)
{
    for (int i = 0; i < e; i++)
        dest[i] = arr[s + i];
}

void merge(int *arr, int start, int half, int end)
{
    int size_l = half - start + 1;
    int size_r = end - half;

    int *arr_l = malloc(sizeof(int) * size_l);
    int *arr_r = malloc(sizeof(int) * size_r);

    copy_segment(arr, arr_l, start, size_l);
    copy_segment(arr, arr_r, half + 1, size_r);

    int l = 0, r = 0, i = start;

    while (l < size_l && r < size_r)
    {
        /* arr[i++] = arr_l[l] < arr_r[r] ? arr_l[l++] : arr_r[r++]; */
        if (arr_l[l] < arr_r[r])
            arr[i] = arr_l[l++];
        else
            arr[i] = arr_r[r++];

        i++;
    }

    for (; l < size_l; l++, i++)
        arr[i] = arr_l[l];
    for (; r < size_r; r++, i++)
        arr[i] = arr_r[r];

    free(arr_l);
    free(arr_r);
}

void merge_sort_R(int *arr, int s, int e)
{
    if (s >= e)
        return;

    int half = (s + e) / 2;
    merge_sort_R(arr, s, half);
    merge_sort_R(arr, half + 1, e);

    merge(arr, s, half, e);
}

void merge_sort(int *arr, int len)
{
    merge_sort_R(arr, 0, len - 1);
}

// ej 5
int lomuto(int *arr, int p, int end)
{
    int i = -1, j = 0;
    for (; j < end; j++)
    {
        if (arr[j] <= p)
            swap(&arr[++i], &arr[j]);
    }

    return i;
}

void quick_sort(int *arr, int len)
{
    if (len < 2)
        return;

    int p = arr[len - 1];
    int end_sub = lomuto(arr, p, len);
    /* printf("PIVOTE: %d, ENDLOMUTO: %d\n", p, end_sub);
    print_arr(arr, len); */
    quick_sort(arr, end_sub);
    quick_sort(arr + end_sub + 1, len - end_sub - 1);
}

// ej 6
void quick_sort_6(int *arr, int len)
{
    if (len < 2)
        return;

    int posP = lomuto(arr, arr[len - 1], len);
    int k = posP;
    while (k > 0 && arr[k] == arr[k - 1])
        k--;

    quick_sort(arr, k);
    quick_sort(arr + posP + 1, len - posP - 1);
}

int mediana(int *arr, int len, int medio)
{
    if (len < 2)
        return arr[medio];

    int pos = lomuto(arr, arr[len - 1], len);

    if (pos == medio)
        return arr[pos];
    else if (pos < medio)
        return mediana(arr + pos + 1, len - pos - 1, medio - pos - 1);
    else
        return mediana(arr, pos, medio);
}

int main()
{
    // ej 2
    /* int arr[] = {2, 3, 5, 7, 9};
    printf("%d", binsearch(arr, 5, 8)); */

    // ej 3
    /* int arr[] = {2, 8, 1, 4, 6};
    print_arr(arr, 5);

    insertion_sort_upgrade(arr, 5);
    print_arr(arr, 5); */

    // ej 4
    /* int len = 9;
    int arr[] = {3, -1, 2, -5, 4, -2, 0, -3, 1, -4};
    print_arr(arr, len);

    merge_sort(arr, len);
    print_arr(arr, len); */

    // ej 5
    /* int len = 10;
    int arr[] = {3, 4, 5, 4, 10, 7, 8, 4, 1, 4};
    print_arr(arr, len);

    quick_sort(arr, len);
    print_arr(arr, len); */

    // ej 6
    /* int len = 10;
    int arr[] = {3, 4, 7, 4, 10, 5, 8, 4, 1, 4};

    quick_sort_6(arr, len);

    print_arr(arr, len); */

    // ej 7
    /* int len = 10;
    int arr[] = {3, 4, 7, 4, 10, 5, 8, 4, 1, 4};

    printf("%d", mediana(arr, len, len / 2)); */

    return 0;
}