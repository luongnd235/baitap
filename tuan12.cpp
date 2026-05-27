#include <stdio.h>

void printArray(int arr[], int n) {
    printf("[");
    for (int i = 1; i <= n; i++) {
        printf("%d", arr[i]);
        if (i < n) printf(", ");
    }
    printf("]\n");
}

void printStatus(int arr[], int heapSize, int totalSize) {
    printf("   -> Heap hien tai: [");
    for (int i = 1; i <= heapSize; i++) {
        printf("%d", arr[i]);
        if (i < heapSize) printf(", ");
    }
    printf("] | Da xong: [");
    for (int i = heapSize + 1; i <= totalSize; i++) {
        printf("%d", arr[i]);
        if (i < totalSize) printf(", ");
    }
    printf("]\n");
}

void heapify(int arr[], int n, int i) {
    int largest = i;       
    int left = 2 * i;      
    int right = 2 * i + 1; 

    if (left <= n && arr[left] > arr[largest])
        largest = left;

    if (right <= n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int total_elements) {
    int n = total_elements - 1;

    printf("Mang dau vao (bo qua index 0): ");
    printArray(arr, n);
    printf("\n");
    printf("--- GIAI DOAN 1: BUILD MAX HEAP ---\n");
    for (int i = n / 2; i >= 1; i--) {
        heapify(arr, n, i);
        printf("  Vun dong tai nut %d (gia tri %d): ", i, arr[i]);
        printArray(arr, n);
    }
    printf("=> Ket qua sau khi Build Max-Heap: ");
    printArray(arr, n);
    printf("\n");

    printf("--- GIAI DOAN 2: SORTING ---\n");
    int step = 1;
    for (int i = n; i > 1; i--) {
        int temp = arr[1];
        arr[1] = arr[i];
        arr[i] = temp;
        
        printf("Buoc %d: Doi cho goc %d <-> cuoi %d\n", step, arr[i], arr[1]);
        
        heapify(arr, i - 1, 1);
        printStatus(arr, i - 1, n);
        printf("........................................\n");
        step++;
    }

    printf("=== KET QUA CUOI CUNG ===\n");
    printf("Mang da sap xep tang dan: ");
    printArray(arr, n);
    printf("========================================\n\n");
}

int main() {
    int cay1[] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int size1 = sizeof(cay1) / sizeof(cay1[0]);
    
    printf("**************** CAY VI DU 1 ****************\n");
    heapSort(cay1, size1);

    int cay2[] = {0, 11, 54, 32, 106, 38, 78, 208, 16, 84, 17, 39, 15};
    int size2 = sizeof(cay2) / sizeof(cay2[0]);
    
    printf("**************** CAY VI DU 2 ****************\n");
    heapSort(cay2, size2);

    return 0;
}
