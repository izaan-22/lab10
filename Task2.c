#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 120

char levels[MAX][LEN];
int count = 0;

void load() {
    FILE *fp = fopen("levels.txt", "r");
    if (!fp) return;
    while (count < MAX && fgets(levels[count], LEN, fp)) {
        levels[count][strcspn(levels[count], "\n")] = '\0';
        count++;
    }
    fclose(fp);
}

void save() {
    FILE *fp = fopen("levels.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", levels[i]);
    fclose(fp);
}

void add() {
    if (count >= MAX) return;
    printf("Enter level: ");
    fgets(levels[count], LEN, stdin);
    levels[count][strcspn(levels[count], "\n")] = '\0';
    count++;
}

void del() {
    char s[LEN];
    printf("Delete which: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(levels[i], s) == 0) {
            for (int j = i; j < count - 1; j++)
                strcpy(levels[j], levels[j + 1]);
            count--;
            return;
        }
    printf("Not found.\n");
}

void update() {
    char s[LEN];
    printf("Update which: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(levels[i], s) == 0) {
            printf("New text: ");
            fgets(levels[i], LEN, stdin);
            levels[i][strcspn(levels[i], "\n")] = '\0';
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
        if (strcmp(levels[i], s) == 0)
            printf("Found: %s\n", levels[i]);
}

void list() {
	printf("List title: ");
    
    for (int i = 0; i < count; i++)
        printf("%s\n", levels[i]);
    
}

int main() {
    load();
    printf("Game Information Tracker");

    char c[5];
    while (1) {
        printf("\n1.Add 2.Update 3.Delete 4.Search 5.List (-1 exit): ");
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

