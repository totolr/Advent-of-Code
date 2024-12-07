#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main()
{
  FILE *file = fopen("../../../2024/day_06/input.txt", "r");
  if (file == NULL)
  {
    perror("Erreur d'ouverture du fichier");
    return 1;
  }

  char buffer[5000];
  char input[130][130];
  int colonnes = 0;
  int lignes = 0;

  int garde_x = 0;
  int garde_y = 0;

  typedef enum Direction
  {
    UP,
    RIGHT,
    DOWN,
    LEFT
  } Direction;

  Direction direction = UP;

  while (fgets(buffer, sizeof(buffer), file))
  {
    const char *ptr = buffer;

    while (*ptr)
    {
      if (*ptr == '^')
      {
        garde_x = colonnes;
        garde_y = lignes;
      }
      input[lignes][colonnes] = *ptr;
      colonnes++;
      ptr++;
    }
    colonnes = 0;
    lignes++;
  }
  fclose(file);

  // for (int i = 0; i < 130; i++)
  // {
  //   for (int j = 0; j < 130; j++)
  //   {
  //     printf("%c", input[i][j]);
  //   }
  //   printf("\n");
  // }
  printf("Garde x: %d, Garde y: %d\n", garde_x + 1, garde_y + 1);

  while (garde_x < 130 && garde_y < 130)
  {
    switch (direction)
    {
    case UP:
      if (input[garde_y - 1][garde_x] == '#')
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y][garde_x + 1] = '^';
        garde_x++;
        direction = RIGHT;
      }
      else
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y - 1][garde_x] = '^';
        garde_y--;
        direction = UP;
      }
      break;
    case RIGHT:
      if (input[garde_y][garde_x + 1] == '#')
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y + 1][garde_x] = '^';
        garde_y++;
        direction = DOWN;
      }
      else
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y][garde_x + 1] = '^';
        garde_x++;
        direction = RIGHT;
      }
      break;
    case DOWN:
      if (input[garde_y + 1][garde_x] == '#')
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y][garde_x - 1] = '^';
        garde_x--;
        direction = LEFT;
      }
      else
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y + 1][garde_x] = '^';
        garde_y++;
        direction = DOWN;
      }
      break;
    case LEFT:
      if (input[garde_y][garde_x - 1] == '#')
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y - 1][garde_x] = '^';
        garde_y--;
        direction = UP;
      }
      else
      {
        input[garde_y][garde_x] = 'X';
        input[garde_y][garde_x - 1] = '^';
        garde_x--;
        direction = LEFT;
      }
      break;
    }
  }
  int sum_part1 = 0;
  for (int i = 0; i < 130; i++)
  {
    for (int j = 0; j < 130; j++)
    {
      if (input[i][j] == 'X')
      {
        sum_part1++;
      }
      printf("%c", input[i][j]);
    }
    printf("\n");
  }

  printf("Somme des cases visitées = %d\n", sum_part1);
}