#include <stdio.h>
#include <limits.h>

void fifo(int pages[], int n, int capacity) {
    int frame[capacity], front = 0, pageFaults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[front] = page;
            front = (front + 1) % capacity;
            pageFaults++;
        }

        printf("Step %d: ", i + 1);
        for (int j = 0; j < capacity; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

void lru(int pages[], int n, int capacity) {
    int frame[capacity], lastUsed[capacity], pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0, lruIndex = 0, minLastUsed = INT_MAX;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < capacity; j++) {
                if (lastUsed[j] < minLastUsed) {
                    minLastUsed = lastUsed[j];
                    lruIndex = j;
                }
            }

            frame[lruIndex] = page;
            lastUsed[lruIndex] = i;
            pageFaults++;
        }

        printf("Step %d: ", i + 1);
        for (int j = 0; j < capacity; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void optimal(int pages[], int n, int capacity) {
    int frame[capacity], pageFaults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replaceIndex = -1, farthest = -1;

            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k])
                        break;
                }

                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            frame[replaceIndex] = page;
            pageFaults++;
        }

        printf("Step %d: ", i + 1);
        for (int j = 0; j < capacity; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}
