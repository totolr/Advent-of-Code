#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

int main()
{
  FILE *file = fopen("../../../2024/day_01/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  // Première passe : compter le nombre de lignes
  int line_count = 0;
  int temp_left, temp_right;
  while (fscanf(file, "%d %d", &temp_left, &temp_right) == 2)
  {
    line_count++;
  }
  fseek(file, 0, SEEK_SET);

  printf("Nombre de lignes : %d\n", line_count);

  int *left = malloc(line_count * sizeof(int));
  int *right = malloc(line_count * sizeof(int));
  if (left == NULL || right == NULL)
  {
    perror("Erreur d'allocation mémoire");
    return 1;
  }

  int index = 0;
  while (fscanf(file, "%d %d", &left[index], &right[index]) == 2)
  {
    index++;
  }
  fclose(file);

  qsort(left, line_count, sizeof(int), compare);
  qsort(right, line_count, sizeof(int), compare);

  int sum = 0;
  int sim = 0;
  for (int i = 0; i < line_count; i++)
  {
    int nb_sim = 0;
    int diff = left[i] - right[i];
    sum += abs(diff);
    // printf("%d - %d = %d\n", left[i], right[i], abs(diff));

    for (int j = 0; j < line_count; j++)
    {
      if (left[i] == right[j])
      {
        nb_sim++;
        sim += left[i];
      }
    }
    if (nb_sim > 0)
    {
      printf("Nombre de valeurs similaires à %d : %d\n", left[i], nb_sim);
    }
  }

  printf("La distance totale est : %d\n", sum);
  printf("Score de similarité : %d\n", sim);

  free(left);
  free(right);
  return 0;
}