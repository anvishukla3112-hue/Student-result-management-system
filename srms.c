#include <stdio.h>
#include <string.h>

#define STUDENTS 3      /* class size            */
#define SUBJECTS 4      /* number of subjects    */
#define PASS_MARK 40    /* minimum marks per subject */

int main()
{
    char name[STUDENTS][30], key[30], grade[STUDENTS];
    char sub[SUBJECTS][10] = {"C", "Maths", "Physics", "English"};
    int roll[STUDENTS], marks[STUDENTS][SUBJECTS];
    int total[STUDENTS], subTotal[SUBJECTS] = {0};
    int pass[STUDENTS], i, j, top = 0, found = 0;
    float percent[STUDENTS];

    /* ---- Module 1: input, expressions, formatted output ---- */
    for (i = 0; i < STUDENTS; i++) {
        printf("\nStudent %d\nRoll no: ", i + 1);
        scanf("%d", &roll[i]);
        printf("Name: ");
        scanf(" %29[^\n]", name[i]);
        total[i] = 0;
        pass[i] = 1;

        /* ---- Module 2: nested loops, validation, 2-D array ---- */
        for (j = 0; j < SUBJECTS; j++) {
            do {
                printf("Marks in %s (0-100): ", sub[j]);
                scanf("%d", &marks[i][j]);
            } while (marks[i][j] < 0 || marks[i][j] > 100);

            total[i] += marks[i][j];
            subTotal[j] += marks[i][j];
            if (marks[i][j] < PASS_MARK)      /* logical decision */
                pass[i] = 0;
        }
        percent[i] = (float) total[i] / SUBJECTS;   /* type casting */

        switch ((int) percent[i] / 10) {            /* grading */
            case 10: case 9: case 8: grade[i] = 'A'; break;
            case 7:  grade[i] = 'B'; break;
            case 6:  grade[i] = 'C'; break;
            case 5:  grade[i] = 'D'; break;
            case 4:  grade[i] = 'E'; break;
            default: grade[i] = 'F';
        }
        if (!pass[i]) grade[i] = 'F';
        if (percent[i] > percent[top]) top = i;
    }

    printf("\n%-5s %-14s", "Roll", "Name");
    for (j = 0; j < SUBJECTS; j++) printf("%8s", sub[j]);
    printf("%7s%8s%6s  %s\n", "Total", "Per%", "Gr", "Result");
    for (i = 0; i < STUDENTS; i++) {
        printf("%-5d %-14s", roll[i], name[i]);
        for (j = 0; j < SUBJECTS; j++) printf("%8d", marks[i][j]);
        printf("%7d%8.2f%6c  %s\n", total[i], percent[i], grade[i],
               pass[i] ? "PASS" : "FAIL");
    }

    printf("\nSubject averages: ");
    for (j = 0; j < SUBJECTS; j++)
        printf("%s=%.1f  ", sub[j], (float) subTotal[j] / STUDENTS);
    printf("\nClass topper: %s (%.2f%%)\n", name[top], percent[top]);

    /* ---- Module 2: string search ---- */
    printf("\nSearch name: ");
    scanf(" %29[^\n]", key);
    for (i = 0; i < STUDENTS; i++)
        if (strcmp(key, name[i]) == 0) {
            printf("Found: Roll %d, %.2f%%, Grade %c\n",
                   roll[i], percent[i], grade[i]);
            found = 1;
        }
    if (!found) printf("No record found for %s (%d characters)\n",
                       key, (int) strlen(key));
    return 0;
}
