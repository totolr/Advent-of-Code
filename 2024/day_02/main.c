#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
  FILE *file = fopen("../../../2024/day_02/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  int line_count = 0;
  char caractere;
  int last_char = 0;
  while ((caractere = fgetc(file)) != EOF)
  { // Lire caractère par caractère
    if (caractere == '\n')
    {
      line_count++; // Incrémenter à chaque saut de ligne
      last_char = 1;
    }
    else
    {
      last_char = 0;
    }
  }
  fseek(file, 0, SEEK_SET); // Remettre le curseur au début du fichier

  if (!last_char)
  {
    line_count++;
  }

  printf("Nombre de lignes : %d\n", line_count);

  char line[line_count]; // Buffer pour stocker une ligne
  int number;
  int nb_safe_part1 = 0;
  int nb_safe_part2 = 0;

  // Lire le fichier ligne par ligne
  while (fgets(line, sizeof(line), file) != NULL)
  {
    char *ptr = line;   // Pointeur pour parcourir la ligne
    int level[8] = {0}; // Tableau pour stocker les nombres
    int i = 0;
    // Extraire les nombres dans la ligne
    while (sscanf(ptr, "%d", &number) == 1)
    {
      level[i++] = number;
      printf("%d ", number);
      // Avancer le pointeur après le nombre extrait
      while (*ptr != ' ' && *ptr != '\n' && *ptr != '\0')
      {
        ptr++;
      }
      if (*ptr == ' ')
        ptr++; // Sauter l'espace
    }
    bool croissant = false;
    bool decroissant = false;
    bool safe = false;
    if (level[1] > level[0])
    {
      croissant = true;
    }
    else if (level[1] < level[0])
    {
      decroissant = true;
    }
    for (int j = 1; j < 8; j++)
    {
      if (level[j] == 0)
      {
        break;
      }

      if (level[j] > level[j - 1] && croissant)
      {
        safe = true;
      }
      else if (level[j] < level[j - 1] && decroissant)
      {
        safe = true;
      }
      else
      {
        safe = false;
        break;
      }
      if ((level[j] - level[j - 1]) <= 3 && (level[j] - level[j - 1]) >= -3)
      {
        safe = true;
      }
      else
      {
        safe = false;
        break;
      }
    }
    if (safe)
    {
      printf("Safe");
      nb_safe_part1++;
      nb_safe_part2++;
    }
    else
    {
      printf("Unsafe");
    }
    printf("\n"); // Nouvelle ligne après avoir traité une ligne du fichier

    if (!safe)
    {
      int new_level[9];

      for (int j = 0; j < 9; j++)
      {
        croissant = false;
        decroissant = false;
        for (int i = 0; i < 8; i++)
        {
          new_level[i] = level[i];
        }
        new_level[8] = 0;
        if (new_level[j] == 0)
        {
          break;
        }
        for (int k = j; k < 8; k++)
        {
          new_level[k] = new_level[k + 1];
        }
        for (int l = 0; new_level[l] != 0; l++)
        {
          printf("%d ", new_level[l]);
        }

        if (new_level[1] > new_level[0])
        {
          croissant = true;
        }
        else if (new_level[1] < new_level[0])
        {
          decroissant = true;
        }
        for (int m = 1; m < 9; m++)
        {
          if (new_level[m] == 0)
          {
            break;
          }

          if (new_level[m] > new_level[m - 1] && croissant)
          {
            safe = true;
          }
          else if (new_level[m] < new_level[m - 1] && decroissant)
          {
            safe = true;
          }
          else
          {
            safe = false;
            break;
          }
          if ((new_level[m] - new_level[m - 1]) <= 3 && (new_level[m] - new_level[m - 1]) >= -3)
          {
            safe = true;
          }
          else
          {
            safe = false;
            break;
          }
        }
        if (safe)
        {
          printf("Safe\n");
          nb_safe_part2++;
          break;
        }
        else
        {
          printf("Unsafe\n");
        }
      }

      printf("\n");
    }
  }
  printf("Nombre de lignes safe partie 1 : %d\n", nb_safe_part1);
  printf("Nombre de lignes safe partie 2 : %d\n", nb_safe_part2);

  fclose(file);
}