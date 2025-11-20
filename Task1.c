#include <stdio.h>
#include <string.h>

#define MAX 10
#define LEN 120

char songs[MAX][LEN];
int count = 0;

void load() {
    FILE *fp = fopen("playlist.txt", "r");
    if (!fp) return;
    while (count < MAX && fgets(songs[count], LEN, fp)) {
        songs[count][strcspn(songs[count], "\n")] = '\0';
        count++;
    }
    fclose(fp);
}

void save() {
    FILE *fp = fopen("playlist.txt", "w");
    for (int i = 0; i < count; i++){
        fprintf(fp, "%s\n", songs[i]);
    fclose(fp);
    }
}

void add() {
    if (count >= MAX) { 
        printf("Playlist full.\n"); 
        return; 
    }
    printf("Enter song: ");
    fgets(songs[count], LEN, stdin);
    songs[count][strcspn(songs[count], "\n")] = '\0';
    count++;
}

void del() {
    char name[LEN];
    printf("Delete which song: ");
    fgets(name, LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(songs[i], name) == 0) {
            for (int j = i; j < count - 1; j++)
                strcpy(songs[j], songs[j + 1]);
            count--;
            return;
        }
    printf("Not found.\n");
}

void update() {
    char name[LEN];
    printf("Update which song: ");
    fgets(name, LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(songs[i], name) == 0) {
            printf("New title: ");
            fgets(songs[i], LEN, stdin);
            songs[i][strcspn(songs[i], "\n")] = '\0';
            return;
        }
    printf("Not found.\n");
}

void search() {
    char key[LEN];
    printf("Search title: ");
    fgets(key, LEN, stdin);
    key[strcspn(key, "\n")] = '\0';

    for (int i = 0; i < count; i++)
        if (strcmp(songs[i], key) == 0)
            printf("Found: %s\n", songs[i]);
}

void list() {
	printf("List title: \n");
    
    for (int i = 0; i < count; i++)
        printf("%s\n", songs[i]);
    
}

int main() {
    load();
    printf("Music Playlist");

    char c[5];
    while (1) {
        printf("\n1.Add 2.Delete 3.Update 4.Search 5.List (-1 exit): ");
        fgets(c, 5, stdin);

        if (strcmp(c, "-1\n") == 0) break;
        else if (c[0] == '1') add();
        else if (c[0] == '2') del();
        else if (c[0] == '3') update();
        else if (c[0] == '4') search();
        else if (c[0] == '5') list();
    }

    save();
    return 0;
}

