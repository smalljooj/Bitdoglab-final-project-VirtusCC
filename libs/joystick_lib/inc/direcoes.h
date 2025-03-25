#ifndef DIRECOES_H
#define DIRECOES_H

#include <stdint.h>
#include "joystick_lib.h"

typedef enum {
  // Direções principais
  CIMA1,          // X entre 25 e 75
  CIMA2,          // X > 75
  BAIXO1,         // X entre -75 e -25
  BAIXO2,         // X < -75
  ESQUERDA1,      // Y entre -75 e -25
  ESQUERDA2,      // Y < -75
  DIREITA1,       // Y entre 25 e 75
  DIREITA2,       // Y > 75

  // Diagonais
  DIAG_CIMA_DIREITA1,   // X entre 25-75 e Y entre 25-75
  DIAG_CIMA_DIREITA2,   // X > 75 ou Y > 75 (prioridade)
  DIAG_CIMA_ESQUERDA1,  // X entre 25-75 e Y entre -75-(-25)
  DIAG_CIMA_ESQUERDA2,  // X > 75 ou Y < -75
  DIAG_BAIXO_DIREITA1,  // X entre -75-(-25) e Y entre 25-75
  DIAG_BAIXO_DIREITA2,  // X < -75 ou Y > 75
  DIAG_BAIXO_ESQUERDA1, // X entre -75-(-25) e Y entre -75-(-25)
  DIAG_BAIXO_ESQUERDA2, // X < -75 ou Y < -75

  NEUTRO          // Posição neutra
} Direcao;

// Protótipos de funções
Direcao get_direcao();

// Declarações externas dos sprites
extern int neutro[5][5][3];
extern int esq1[5][5][3];
extern int esq2[5][5][3];
extern int cima1[5][5][3];
extern int cima2[5][5][3];
extern int dir1[5][5][3];
extern int dir2[5][5][3];
extern int bai1[5][5][3];
extern int bai2[5][5][3];
extern int esqcim1[5][5][3];
extern int esqcim2[5][5][3];
extern int esqbax1[5][5][3];
extern int esqbax2[5][5][3];
extern int dircim1[5][5][3];
extern int dircim2[5][5][3];
extern int dirbax1[5][5][3];
extern int dirbax2[5][5][3];



#endif