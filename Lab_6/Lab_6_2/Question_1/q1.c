#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// (i) Find maximum - O(n)
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// (ii) Find first and second largest - O(n)
void findTwoLargest(int arr[], int n, int *first, int *second) {
    *first = *second = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first) {
            *second = arr[i];
        }
    }
}

// (iii) Find mean - O(n)
double findMean(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return (double)sum / n;
}

// (iv) Find median - O(n log n) due to sorting
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double findMedian(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);
    
    double median;
    if (n % 2 == 0)
        median = (temp[n/2 - 1] + temp[n/2]) / 2.0;
    else
        median = temp[n/2];
    
    free(temp);
    return median;
}

// (v) Find standard deviation - O(n)
double findStdDev(int arr[], int n) {
    double mean = findMean(arr, n);
    double variance = 0;
    for (int i = 0; i < n; i++) {
        variance += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(variance / n);
}

// (vi) Find mode - O(n log n) due to sorting
int findMode(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);
    
    int mode = temp[0], maxCnt = 1, currCnt = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i-1]) {
            currCnt++;
        } else {
            if (currCnt > maxCnt) {
                maxCnt = currCnt;
                mode = temp[i-1];
            }
            currCnt = 1;
        }
    }
    if (currCnt > maxCnt)
        mode = temp[n-1];
    
    free(temp);
    return mode;
}

// (vii) Remove duplicates - O(n log n)
int removeDup(int arr[], int n) {
    if (n == 0) return 0;
    qsort(arr, n, sizeof(int), compare);
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

// (viii) Reverse array - O(n)
void reverseArr(int arr[], int n) {
    for (int i = 0; i < n/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-1-i];
        arr[n-1-i] = temp;
    }
}

// (ix) Partition - O(n)
int partition(int arr[], int n, int pivot) {
    int i = -1;
    for (int j = 0; j < n; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    return i + 1;
}

void printArr(int arr[], int n, int limit) {
    int show = (n < limit) ? n : limit;
    for (int i = 0; i < show; i++)
        printf("%d ", arr[i]);
    if (n > limit) printf("...");
    printf("\n");
}

int main() {
    int choice, n;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter n: ");
        scanf("%d", &n);
        int *arr = (int *)malloc(n * sizeof(int));
        printf("Enter %d elements: ", n);
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        
        printf("\nArray: ");
        printArr(arr, n, 20);
        
        printf("\n(i) Maximum: %d\n", findMax(arr, n));
        
        int first, second;
        findTwoLargest(arr, n, &first, &second);
        printf("(ii) First largest: %d, Second largest: %d\n", first, second);
        
        printf("(iii) Mean: %.2f\n", findMean(arr, n));
        printf("(iv) Median: %.2f\n", findMedian(arr, n));
        printf("(v) Std Deviation: %.2f\n", findStdDev(arr, n));
        printf("(vi) Mode: %d\n", findMode(arr, n));
        
        int *arr2 = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr2[i] = arr[i];
        int newN = removeDup(arr2, n);
        printf("(vii) After removing duplicates: ");
        printArr(arr2, newN, 20);
        free(arr2);
        
        reverseArr(arr, n);
        printf("(viii) Reversed array: ");
        printArr(arr, n, 20);
        
        for (int i = 0; i < n; i++) arr[i] = arr[n-1-i];
        int pivot = arr[n/2];
        partition(arr, n, pivot);
        printf("(ix) After partition (pivot=%d): ", pivot);
        printArr(arr, n, 20);
        
        free(arr);
    } else {
        srand(time(NULL));
        n = rand() % 20 + 10; // 10-29 elements
        int *arr = (int *)malloc(n * sizeof(int));
        
        printf("n = %d\n", n);
        printf("Array: ");
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        printf("\n(i) Maximum: %d\n", findMax(arr, n));
        
        int first, second;
        findTwoLargest(arr, n, &first, &second);
        printf("(ii) First: %d, Second: %d\n", first, second);
        
        printf("(iii) Mean: %.2f\n", findMean(arr, n));
        printf("(iv) Median: %.2f\n", findMedian(arr, n));
        printf("(v) Std Dev: %.2f\n", findStdDev(arr, n));
        printf("(vi) Mode: %d\n", findMode(arr, n));
        
        int *arr2 = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr2[i] = arr[i];
        int newN = removeDup(arr2, n);
        printf("(vii) Unique elements (%d): ", newN);
        printArr(arr2, newN, 20);
        free(arr2);
        
        reverseArr(arr, n);
        printf("(viii) Reversed: ");
        printArr(arr, n, 20);
        
        free(arr);
    }
    
    return 0;
}
