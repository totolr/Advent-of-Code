#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Fonction récursive pour tester les combinaisons d'opérateurs
bool evaluate(long long *numbers, int size, long long target, long long current_value, int index)
{
  // Si on a utilisé tous les nombres, on vérifie si la valeur obtenue est égale à la cible
  if (index == size)
  {
    return (current_value == target);
  }

  // Essayer l'opérateur "+"
  if (evaluate(numbers, size, target, current_value + numbers[index], index + 1))
  {
    return true;
  }

  // Essayer l'opérateur "*"
  if (evaluate(numbers, size, target, current_value * numbers[index], index + 1))
  {
    return true;
  }

  return false;
}

int main()
{
  FILE *file = fopen("../../../2024/day_07/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  char buffer[5000];
  long long sum_part1 = 0;

  while (fgets(buffer, sizeof(buffer), file))
  {
    // On lit la ligne du type "190: 10 19"
    char *ptr = buffer;
    long long result = 0;

    // Extraction de la valeur cible avant les deux-points
    // On suppose un format "NombreCible: "
    if (sscanf(ptr, "%lld:", &result) != 1)
    {
      // Si on ne parvient pas à lire au moins le résultat, on ignore cette ligne
      continue;
    }

    // Aller jusqu'au ':' et avancer de 1 caractère pour pointer juste après
    ptr = strchr(ptr, ':');
    if (!ptr)
    {
      continue; // Pas de ':', ligne invalide
    }
    ptr++; // Passer le ':'

    // Ignorer les espaces après le ':'
    while (*ptr == ' ' || *ptr == '\t')
    {
      ptr++;
    }

    long long numbers[20];
    int i = 0;

    // Lire les nombres restants dans la ligne
    while (*ptr != '\0')
    {
      long long val;
      int n = 0;
      if ((n = sscanf(ptr, "%lld", &val)) == 1)
      {
        numbers[i++] = val;
        // Avancer ptr jusqu'au prochain espace ou fin de ligne
        char *space = strchr(ptr, ' ');
        if (space)
        {
          ptr = space + 1;
        }
        else
        {
          // plus d'espaces, on sortira à la prochaine iteration
          break;
        }
      }
      else
      {
        // Si on n'a pas pu lire de nombre, on avance d'un caractère pour réessayer
        ptr++;
      }
    }

    // Maintenant, on a 'i' nombres lus dans le tableau numbers et un résultat à vérifier.
    bool canMatch = false;
    if (i > 0)
    {
      // On démarre la récursion avec la première valeur dans current_value
      // index = 1, puisque numbers[0] est déjà utilisée
      canMatch = evaluate(numbers, i, result, numbers[0], 1);
    }
    else
    {
      // Si aucun nombre n'est lu, vérifier si result == 0 ou un cas particulier
      // mais logiquement, s'il n'y a aucun nombre, on ne peut pas obtenir result (sauf result=0?)
      canMatch = (result == 0 && i == 0);
    }

    if (canMatch)
    {
      sum_part1 += result;
    }
  }

  fclose(file);

  printf("Part 1: %lld\n", sum_part1);
  return 0;
}
