#include <stdio.h>
#include <string.h>

#define MAX 40
#define LEN 120

char recipes[MAX][LEN];
int count = 0;

void load() {
    FILE *fp = fopen("recipes.txt", "r");
    if (!fp) return;
    while (count < MAX && fgets(recipes[count], LEN, fp)) {
        recipes[count][strcspn(recipes[count], "\n")] = '\0';
        count++;
    }
    fclose(fp);
}

void save() {
    FILE *fp = fopen("recipes.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", recipes[i]);
    fclose(fp);
}

void add() {
    if (count >= MAX) return;
    printf("Enter recipe: ");
    fgets(recipes[count], LEN, stdin);
    recipes[count][strcspn(recipes[count], "\n")] = '\0';
    count++;
}

void update() {
    char s[LEN];
    printf("Recipe to update: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(recipes[i], s) == 0) {
            printf("New recipe: ");
            fgets(recipes[i], LEN, stdin);
            recipes[i][strcspn(recipes[i], "\n")] = '\0';
            return;
        }
    printf("Not found.\n");
}

void del() {
    char s[LEN];
    printf("Recipe to delete: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(recipes[i], s) == 0) {
            for (int j = i; j < count - 1; j++)
                strcpy(recipes[j], recipes[j + 1]);
            count--;
            return;
        }
    printf("Not found.\n");
}

void search() {
    char s[LEN];
    printf("Search text: ");
    fgets(s, LEN, stdin);
    s[strcspn(s, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strstr(recipes[i], s))
            printf("Found: %s\n", recipes[i]);
}

void list() {
	printf("List title: \n");
    
    for (int i = 0; i < count; i++)
        printf("%s\n", recipes[i]);
    
}

int main() {
    load();
    printf("Recipe Book");
    
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

