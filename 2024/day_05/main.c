#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int extract_number(const char **ptr)
{
  int num = 0;
  while (isdigit(**ptr))
  {
    num = num * 10 + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

int main()
{
  FILE *file = fopen("../../../2024/day_05/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  int *rules_left = (int *)malloc(1200 * sizeof(int));
  int *rules_right = (int *)malloc(1200 * sizeof(int));
  int i = 0;

  while (fscanf(file, "%d|%d", &rules_left[i], &rules_right[i]) == 2)
  {
    i++;
  }
  fseek(file, 0, SEEK_SET); // Remettre le curseur au début du fichier

  int each_update[200][23] = {0};
  char line[1024];
  int row = 0;

  while (fgets(line, sizeof(line), file) && row < 200)
  {
    if (strchr(line, ','))
    { // Vérifie si la ligne contient des virgules
      int col = 0;
      char *token = strtok(line, ",");
      while (token && col < 23)
      {
        each_update[row][col] = atoi(token); // Convertit le token en entier
        token = strtok(NULL, ",");
        col++;
      }
      row++;
    }
  }

  // Affiche le tableau pour vérifier les données

  fclose(file);

  // for (int i = 0; rules_right[i] != 0; i++)
  // {
  //   printf("%d|%d\n", rules_left[i], rules_right[i]);
  // }
  // printf("\n");

  int sum_part1 = 0;
  int sum_part2 = 0;
  for (int i = 0; i < row; i++) // Parcours les lignes
  {
    bool valid = true;
    bool valid_part2 = false;
    int max_col = 0;
    for (int j = 0; each_update[i][j] != 0 && j < 23; j++)
    {
      printf("%d ", each_update[i][j]);
    }
    printf("\n");
    for (int j = 1; each_update[i][j] != 0 && j < 23; j++) // Parcours les colonnes
    {
      for (int k = 0; rules_right[k] != 0; k++) // Parcours les règles colonne gauche
      {
        if (each_update[i][j] == rules_left[k])
        {
          for (int l = 0; l < j; l++) // Parcours les règles colonne droite
          {
            if (each_update[i][l] == rules_right[k])
            {
              int tochange1 = each_update[i][j];
              int tochange2 = each_update[i][l];
              // printf("Erreur détectée à la ligne %d, colonne %d car la règle est %d|%d\n", i, j, rules_left[k], rules_right[k]);
              printf("%d|%d ", rules_left[k], rules_right[k]);
              each_update[i][j] = tochange2;
              each_update[i][l] = tochange1;
              j = 1;
              valid = false;
              valid_part2 = true;
            }
          }
        }
      }
      max_col = j;
    }

    if (valid)
    {
      sum_part1 += each_update[i][(max_col / 2)];
      printf("Ligne %d valide avec la page du milieu = %d", i + 1, each_update[i][(max_col / 2)]);
    }
    if (valid_part2)
    {
      sum_part2 += each_update[i][(max_col / 2)];
      printf("\n");
      for (int j = 0; each_update[i][j] != 0 && j < 23; j++)
      {
        printf("%d ", each_update[i][j]);
      }
      printf("\nLigne %d corrigée avec la page du milieu = %d", i + 1, each_update[i][(max_col / 2)]);
    }
    printf("\n\n");
  }
  printf("Somme des pages du milieu valide = %d\n", sum_part1);
  printf("Somme des pages du milieu corrigée = %d\n", sum_part2);
  printf("Somme des pages du milieu = %d\n", sum_part1 + sum_part2);

  return EXIT_SUCCESS;
}