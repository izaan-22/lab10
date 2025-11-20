#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 120

char notes[MAX][LEN];
int count = 0;

void load() {
    FILE *fp = fopen("episodes.txt", "r");
    if (!fp) return;
    while (count < MAX && fgets(notes[count], LEN, fp)) {
        notes[count][strcspn(notes[count], "\n")] = '\0';
        count++;
    }
    fclose(fp);
}

void save() {
    FILE *fp = fopen("episodes.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", notes[i]);
    fclose(fp);
}

void add() {
    if (count >= MAX) return;
    printf("Enter note: ");
    fgets(notes[count], LEN, stdin);
    notes[count][strcspn(notes[count], "\n")] = '\0';
    count++;
}

void search() {
    char key[LEN];
    printf("Search: ");
    fgets(key, LEN, stdin);
    key[strcspn(key, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strstr(notes[i], key))
            printf("Found: %s\n", notes[i]);
}

void update() {
    char old[LEN];
    printf("Update which: ");
    fgets(old, LEN, stdin);
    old[strcspn(old, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(notes[i], old) == 0) {
            printf("New note: ");
            fgets(notes[i], LEN, stdin);
            notes[i][strcspn(notes[i], "\n")] = '\0';
            return;
        }
    printf("Not found.\n");
}

void del() {
    char key[LEN];
    printf("Delete which: ");
    fgets(key, LEN, stdin);
    key[strcspn(key, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(notes[i], key) == 0) {
            for (int j = i; j < count - 1; j++)
                strcpy(notes[j], notes[j + 1]);
            count--;
            return;
        }
    printf("Not found.\n");
}

void list() {
	printf("List title: \n");
    
    for (int i = 0; i < count; i++)
        printf("%s\n", notes[i]);
    
}

int main() {
    load();
    printf("Game Information Tracker");

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

