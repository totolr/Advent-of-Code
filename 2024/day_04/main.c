#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *file = fopen("../../../2024/day_04/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  int sum_part1 = 0;
  int sum_part2 = 0;
  char buffer_file[150][150]; // 140 caractères sur une ligne + 10 caractères de marge et 140 lignes + 10 lignes de marge
  char buffer[150];
  int lignes = 0;
  int colonnes = 0;

  while (fgets(buffer, sizeof(buffer), file))
  {
    const char *ptr = buffer;

    while (*ptr)
    {
      buffer_file[lignes][colonnes] = *ptr;
      colonnes++;
      ptr++;
    }
    colonnes = 0;
    lignes++;
  }
  fclose(file);

  printf("Tableau \"XMAS\" :\n");
  for (int i = 0; i < 140; i++) // 140 lignes
  {
    printf("Ligne : %d = ", i + 1);
    for (int j = 0; j < 140; j++) // 140 colonnes
    {
      if (buffer_file[i][j] == 'X')
      {
        if (buffer_file[i][j + 1] == 'M' && buffer_file[i][j + 2] == 'A' && buffer_file[i][j + 3] == 'S') // Vérification horizontale droite
        {
          sum_part1++;
        }
        if (buffer_file[i + 1][j] == 'M' && buffer_file[i + 2][j] == 'A' && buffer_file[i + 3][j] == 'S') // Vérification verticale bas
        {
          sum_part1++;
        }
        if (buffer_file[i + 1][j + 1] == 'M' && buffer_file[i + 2][j + 2] == 'A' && buffer_file[i + 3][j + 3] == 'S') // Vérification diagonale bas droite
        {
          sum_part1++;
        }
        if (buffer_file[i - 1][j + 1] == 'M' && buffer_file[i - 2][j + 2] == 'A' && buffer_file[i - 3][j + 3] == 'S') // Vérification diagonale haut droite
        {
          sum_part1++;
        }
        if (buffer_file[i - 1][j] == 'M' && buffer_file[i - 2][j] == 'A' && buffer_file[i - 3][j] == 'S') // Vérification verticale haut
        {
          sum_part1++;
        }
        if (buffer_file[i][j - 1] == 'M' && buffer_file[i][j - 2] == 'A' && buffer_file[i][j - 3] == 'S') // Vérification horizontale gauche
        {
          sum_part1++;
        }
        if (buffer_file[i + 1][j - 1] == 'M' && buffer_file[i + 2][j - 2] == 'A' && buffer_file[i + 3][j - 3] == 'S') // Vérification diagonale bas gauche
        {
          sum_part1++;
        }
        if (buffer_file[i - 1][j - 1] == 'M' && buffer_file[i - 2][j - 2] == 'A' && buffer_file[i - 3][j - 3] == 'S') // Vérification diagonale haut gauche
        {
          sum_part1++;
        }
      }
      printf("%c", buffer_file[i][j]);
    }
    printf("\n");
  }
  printf("\nTableau \"X-MAS\" :\n");
  for (int i = 0; i < 140; i++) // 140 lignes
  {
    printf("Ligne : %d = ", i + 1);
    for (int j = 0; j < 140; j++) // 140 colonnes
    {
      if (buffer_file[i][j] == 'A')
      {
        if (buffer_file[i - 1][j + 1] == 'S' && buffer_file[i - 1][j - 1] == 'S' && buffer_file[i + 1][j + 1] == 'M' && buffer_file[i + 1][j - 1] == 'M')
        {
          sum_part2++;
        }
        if (buffer_file[i - 1][j + 1] == 'S' && buffer_file[i - 1][j - 1] == 'M' && buffer_file[i + 1][j + 1] == 'S' && buffer_file[i + 1][j - 1] == 'M')
        {
          sum_part2++;
        }
        if (buffer_file[i - 1][j + 1] == 'M' && buffer_file[i - 1][j - 1] == 'M' && buffer_file[i + 1][j + 1] == 'S' && buffer_file[i + 1][j - 1] == 'S')
        {
          sum_part2++;
        }
        if (buffer_file[i - 1][j + 1] == 'M' && buffer_file[i - 1][j - 1] == 'S' && buffer_file[i + 1][j + 1] == 'M' && buffer_file[i + 1][j - 1] == 'S')
        {
          sum_part2++;
        }
      }
      printf("%c", buffer_file[i][j]);
    }

    printf("\n");
  }

  printf("Nombre de \"XMAS\" : %d\n", sum_part1);
  printf("Nombre de \"X-MAS\" : %d\n", sum_part2);
  return 0;
}
