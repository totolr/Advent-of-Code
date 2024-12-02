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
  int nb_safe = 0;

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
      printf("%d ", number); // Afficher ou stocker le nombre
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
      nb_safe++;
    }
    else
    {
      printf("Unsafe");
    }
    printf("\n"); // Nouvelle ligne après avoir traité une ligne du fichier
  }
  printf("Nombre de lignes safe : %d\n", nb_safe);

  fclose(file);
}