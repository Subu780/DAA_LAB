#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard Merge Sort for simple integer arrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Two-pointer approach instead of using structs
void findPeakAttendance(int arr_in[], int arr_out[], int n) {
    // Sort both arrays independently: O(n log n)
    mergeSort(arr_in, 0, n - 1);
    mergeSort(arr_out, 0, n - 1);

    int current_guests = 0;
    int max_guests = 0;
    int peak_hour = 0;
    
    int i = 0; // Pointer for arrivals
    int j = 0; // Pointer for departures

    // Traverse both sorted arrays: O(n)
    while (i < n && j < n) {
        // If the next event is an arrival
        if (arr_in[i] < arr_out[j]) {
            current_guests++;
            
            if (current_guests > max_guests) {
                max_guests = current_guests;
                peak_hour = arr_in[i];
            }
            i++; 
        } 
        // If the next event is a departure
        else {
            current_guests--;
            j++;
        }
    }

    printf("\nMaximum people present simultaneously: %d\n", max_guests);
    printf("This peak started at time: %d\n", peak_hour);
}

int main() {
    int n, choice;

    printf("Enter the number of attendees: ");
    scanf("%d", &n);

    int *arr_in = (int *)malloc(n * sizeof(int));
    int *arr_out = (int *)malloc(n * sizeof(int));

    printf("1. Manual Input\n2. Random Generation\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter entry and exit times (e.g., 5 10):\n");
        for (int i = 0; i < n; i++) {
            printf("Guest %d: ", i + 1);
            scanf("%d %d", &arr_in[i], &arr_out[i]);
        }
    } else {
        srand(time(NULL)); 
        printf("\nRandomly generated times:\n");
        int base_time = 1; 
        for (int i = 0; i < n; i++) {
            arr_in[i] = base_time + (rand() % 5);
            arr_out[i] = arr_in[i] + 1 + (rand() % 15);
            base_time = arr_out[i] + 1; 
            printf("Guest %d: In = %d, Out = %d\n", i + 1, arr_in[i], arr_out[i]);
        }
    }
    findPeakAttendance(arr_in, arr_out, n);
    free(arr_in);
    free(arr_out);
    return 0;
}