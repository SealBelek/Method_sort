//
//  main.c
//  lab3
//
//  Created by barry on 26.01.2018.
//  Copyright © 2018 barry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000
void generation(void);
void read_file(int [N]);
void method_simple_sort(void);
void method_puzirek(void);
void method_comb_sort(void);
int qs(int *s_arr, int first, int last);
void swap(int*, int*);
int main(void) {
    FILE *fl = fopen("times.txt", "w");
    double time;
    generation();
    unsigned long t = clock();
    method_simple_sort();
    unsigned long t2 = clock();
    time = (double)(t2 - t) / CLOCKS_PER_SEC;
    fprintf(fl, "time simple sort = %lf\n", time);
    t = clock();
    method_puzirek();
    t2 = clock();
    time = (double)(t2 - t) / CLOCKS_PER_SEC;
    fprintf(fl, " Bubble sort = %lf\n", time);
    t = clock();
    method_comb_sort();
    t2 = clock();
    time = (double)(t2 - t) / CLOCKS_PER_SEC;
    fprintf(fl, "time comb sort = %lf\n", time);
    int a[N], c;
    read_file(a);
    t = clock();
    c = qs(a, 0, N-1);
    t2 = clock();
    time = (double)(t2 - t) / CLOCKS_PER_SEC;
    fprintf(fl, "qs = %lf\n", time);
    FILE *file = fopen("ravn.txt","a");
    fprintf(file, "qs %d\n", c);
    fclose(file);
    fclose(fl);
    return 0;
}
void swap(int*a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void generation(){
    srand(time(NULL));
    FILE *file = fopen("input.txt", "w");
    for (int i = 0; i < N; i++) {
        fprintf(file, "%d ", -25000 + rand()%(25000-(-25000)));
    }
    fclose(file);
}
void read_file(int array[N]){
    FILE *file = fopen("input.txt", "r");
    for (int i = 0; i < N; i++) {
        fscanf(file, "%d", &array[i]);
    }
    fclose(file);
}
void method_simple_sort() {
    FILE *file = fopen("ravn.txt","w");
    int a[N] = {0}, c = 0;
    read_file(a);
    int min;
    for (int i = 0; i < N - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < N; j++){
            if (a[j] < a[min])
                min = j;
        }
        swap(&a[i], &a[min]);
        c++;
    }
    fprintf(file, "simple sort%d\n", c);
    fclose(file);
}
void method_puzirek(){
    FILE *file = fopen("ravn.txt","a");
    int a[N] = {0}, c = 0;
    read_file(a);
    int count = 1, j = 1;
    while (count > 0) {
        count = 0;
        for (int i = 0; i < N - j; i++) {
            if (a[i] > a[i+1]){
                swap(&a[i], &a[i+1]); c++;
                count++;
            }
        }
        j++;
    }
    fprintf(file, "buble sort%d\n", c);
    fclose(file);
}
void method_comb_sort () {
    FILE *file = fopen("ravn.txt","a");
    int c = 0, a[N];
    read_file(a);
    double fakt = 1.2473309;
    int step = N-1;
    while (step <=1) {
        for (int i = 0; i + step < N-1; i++) {
            if (a[i] > a[i + step]){
                swap(&a[i], &a[i + step]); c++;
            }
        }
        step /= fakt;
    }
    int count = 1, j = 1;
    while (count > 0) {
        count = 0;
        for (int i = 0; i < N - j; i++) {
            if (a[i] > a[i+1]){
                swap(&a[i], &a[i+1]); c++;
                count++;
            }
        }
        j++;
    }
   fprintf(file, "comb sort%d\n", c);
    fclose(file);
}
int qs(int *s_arr, int first, int last){
    int c = 0;
    if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                swap(&s_arr[left], &s_arr[right]); c++;
                left++;
                right--;
            }
        } while (left <= right);
        c += qs(s_arr, first, right);
        c += qs(s_arr, left, last);
    }
    return c;
}
