#include <stdio.h>

int main()
{
    int p, c, count = 0, i, j;
    int alc[5][3], max[5][3], need[5][3];
    int safe[5], available[3], done[5], terminate;

    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &p, &c);

    printf("Enter allocation matrix (%dx%d):\n", p, c);
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &alc[i][j]);

    printf("Enter maximum matrix (%dx%d):\n", p, c);
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources (%d):\n", c);
    for (i = 0; i < c; i++)
        scanf("%d", &available[i]);

    // Calculate need matrix
    printf("\nNeed matrix:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            need[i][j] = max[i][j] - alc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < p; i++)
        done[i] = 0;

    while (count < p)
    {
        terminate = 0;  // Reset for each round

        for (i = 0; i < p; i++)
        {
            if (done[i] == 0)
            {
                for (j = 0; j < c; j++)
                {
                    if (need[i][j] > available[j])
                        break;
                }

                if (j == c)
                {
                    safe[count] = i;
                    done[i] = 1;

                    for (j = 0; j < c; j++)
                        available[j] += alc[i][j];

                    count++;
                }
                else
                {
                    terminate++;
                }
            }
        }

        // If no process was able to run in this pass, system is unsafe
        if (terminate == p) {
            printf("\nSystem is in UNSAFE state. No safe sequence exists.\n");
            return 1;
        }
    }

    // Output results
    printf("\nAvailable resources after execution:\n");
    for (i = 0; i < c; i++)
        printf("%d\t", available[i]);

    printf("\n\nSafe sequence:\n");
    for (i = 0; i < p; i++)
        printf("P%d\t", safe[i]);

    printf("\n");

    return 0;
}
