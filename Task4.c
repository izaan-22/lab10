#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 120

char affirm[MAX][LEN];
int count = 0;

void load() {
    FILE *fp = fopen("affirm.txt", "r");
    if (!fp) return;
    while (count < MAX && fgets(affirm[count], LEN, fp)) {
        affirm[count][strcspn(affirm[count], "\n")] = '\0';
        count++;
    }
    fclose(fp);
}

void save() {
    FILE *fp = fopen("affirm.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", affirm[i]);
    fclose(fp);
}

void add() {
    if (count >= MAX) return;
    printf("Enter affirmation: ");
    fgets(affirm[count], LEN, stdin);
    affirm[count][strcspn(affirm[count], "\n")] = '\0';
    count++;
}

void update() {
    char s[LEN];
    printf("Update which: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(affirm[i], s) == 0) {
            printf("New text: ");
            fgets(affirm[i], LEN, stdin);
            affirm[i][strcspn(affirm[i], "\n")] = '\0';
            return;
        }
    printf("Not found.\n");
}

void del() {
    char s[LEN];
    printf("Delete which: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(affirm[i], s) == 0) {
            for (int j = i; j < count - 1; j++)
                strcpy(affirm[j], affirm[j + 1]);
            count--;
            return;
        }
    printf("Not found.\n");
}

void search() {
    char s[LEN];
    printf("Search: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strstr(affirm[i], s))
            printf("Found: %s\n", affirm[i]);
}

void list() {
	printf("List title: \n");
    
    for (int i = 0; i < count; i++)
        printf("%s\n", affirm[i]);
    
}

int main() {
    load();
    printf("Wellness App");

    char c[5];
    while (1) {
        printf("\n1.Add 2.Delete 3.Update 4.Search 5.List (-1 exit): ");
        fgets(c, 5, stdin);

        if (strcmp(c, "-1\n") == 0) break;
        else if (c[0] == '1') add();
        else if (c[0] == '2') update();
        else if (c[0] == '3') del();
        else if (c[0] == '4') search();
        else if (c[0] == '5') list();
    }

    save();
    return 0;
}

