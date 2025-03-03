#include <stdio.h>
#include <stdbool.h>

#define N 5 // Number of processes

#define M 3 // Number of resources

void calculateNeed(int need[N][M], int max[N][M], int alloc[N][M])
{

    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < M; j++)
        {

            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe(int processes[], int avail[], int max[][M], int alloc[][M])
{

    int need[N][M];

    calculateNeed(need, max, alloc);

    bool finish[N] = {false};

    int safeSeq[N];

    int work[M];

    for (int i = 0; i < M; i++)

        work[i] = avail[i];

    int count = 0;

    while (count < N)
    {

        bool found = false;

        for (int p = 0; p < N; p++)
        {

            if (finish[p] == false)
            {

                int j;

                for (j = 0; j < M; j++)
                    if (need[p][j] > work[j])

                        break;

                if (j == M)
                {

                    for (int k = 0; k < M; k++)

                        work[k] += alloc[p][k];

                    safeSeq[count++] = p;

                    finish[p] = true;

                    found = true;
                }
            }
        }

        if (found == false)
        {

            printf("The system is not in a safe staten");

            return false;
        }
    }

    printf("The system is in a safe state.nSafe sequence is: ");

    for (int i = 0; i < N; i++)

        printf("%d ", safeSeq[i]);

    printf("n");

    return true;
}

int main()
{

    int processes[] = {0, 1, 2, 3, 4};

    int avail[] = {3, 3, 2};

    int max[N][M] = {

        {7, 5, 3},

        {3, 2, 2},

        {9, 0, 2},

        {2, 2, 2},

        {4, 3, 3}

    };

    int alloc[N][M] = {

        {0, 1, 0},

        {2, 0, 0},

        {3, 0, 2},

        {2, 1, 1},

        {0, 0, 2}

    };

    isSafe(processes, avail, max, alloc);

    return 0;
}
