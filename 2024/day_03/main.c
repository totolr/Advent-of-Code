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
  FILE *file = fopen("../../../2024/day_03/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  char buffer[500000];
  int sum_part1 = 0;
  int sum_part2 = 0;
  bool todo = true;

  while (fgets(buffer, sizeof(buffer), file))
  {
    const char *ptr = buffer;

    while (*ptr)
    {
      // Recherche du motif "mul("
      if (strncmp(ptr, "mul(", 4) == 0)
      {
        ptr += 4; // Avance après "mul("

        // Extraction du premier nombre
        if (!isdigit(*ptr))
        {
          continue; // Ignore si ce n'est pas un chiffre
        }
        int num1 = extract_number(&ptr);

        // Vérifie la virgule
        if (*ptr != ',')
        {
          continue; // Ignore si pas de virgule
        }
        ptr++; // Passe la virgule

        // Extraction du second nombre
        if (!isdigit(*ptr))
        {
          continue; // Ignore si ce n'est pas un chiffre
        }
        int num2 = extract_number(&ptr);

        // Vérifie la parenthèse fermante
        if (*ptr != ')')
        {
          continue; // Ignore si pas de parenthèse fermante
        }
        ptr++; // Passe la parenthèse fermante

        // Ajoute le produit des deux nombres au total
        sum_part1 += num1 * num2;
        printf("Instruction valide : mul(%d,%d) = %d ", num1, num2, num1 * num2);
        if (todo)
        {
          printf("do()\n");
          sum_part2 += num1 * num2;
        }
        else
        {
          printf("don't()\n");
        }
      }
      else if (strncmp(ptr, "do", 2) == 0)
      {
        ptr += 2;

        if (*ptr != '(' && *ptr != 'n')
        {
          continue;
        }
        ptr++;

        if (*ptr != ')' && *ptr != '\'')
        {
          continue;
        }
        else if (*ptr == ')')
        {
          todo = true;
          continue;
        }
        ptr++;
        if (*ptr != 't')
        {
          continue;
        }
        ptr++;
        if (*ptr != '(')
        {
          continue;
        }
        ptr++;
        if (*ptr != ')')
        {
          continue;
        }
        ptr++;
        todo = false;
      }
      else
      {
        ptr++; // Avance d'un caractère si le motif "mul(" n'est pas trouvé
      }
    }
  }

  fclose(file);
  printf("Résultat total des multiplications valides : %d\n", sum_part1);
  printf("Résultat total des multiplications valides et do () : %d\n", sum_part2);
  return 0;
}
