#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Analyse_lix(char *tab, int ligne, FILE *dictionnaire, FILE *Erreur){
    char dict[100];
    int a = 0;
    rewind(dictionnaire);
    while (fgets(dict, sizeof(dict), dictionnaire)){
        dict[strcspn(dict, "\n")] = 0;
        if (strcmp(tab, dict) == 0){
            printf("%s\n", dict);
            a = 1;
            break;
        }
    }
    if (a == 0){ // Si aucune correspondance n'est trouvée, écrire dans le fichier d'erreur
        fprintf(Erreur,"Ligne numero = %d , mot non trouvé = '%s'\n", ligne, tab);
    }
}

int main() {
    FILE *programme;
    FILE *dictionnaire = fopen("Dictionnaire.h","r");
    FILE *Erreur = fopen("Erreur.h", "a");

    programme = fopen("programme.h", "r");
    if (!programme || !dictionnaire || !Erreur) {
        perror("Erreur d'ouvrir le fichier");
        return 1;
    }

    char ch;
    char Tab_Ligne[100] = {0};
    char verif[10] = "Random";
    int ligne = 1;
    int caractere = 1;
    while ((ch = fgetc(programme)) != EOF){
        if (ch != ' ' && ch != '\n'){
            Tab_Ligne[caractere - 1] = ch;
            caractere += 1;
        }
        if ((ch == ' ' && strcmp(Tab_Ligne, verif) != 0) || (ch == '\n' && strcmp(Tab_Ligne, verif) != 0)){
            Tab_Ligne[caractere - 1] = '\0';
            Analyse_lix(Tab_Ligne, ligne, dictionnaire, Erreur);
            strcpy(verif, Tab_Ligne);
            caractere = 1;

            if (ch == '\n')
                ligne += 1;
        }
    }
    fclose(programme);
    fclose(dictionnaire);
    fclose(Erreur);

    return 0;
}
