#include "direcoes.h"

Direcao get_direcao() {
    int16_t x = get_joystick_x_norm();
    int16_t y = get_joystick_y_norm();
  
    // Diagonais (prioridade máxima)
    if (x >= 25 && y >= 25) {
        if (x > 75 || y > 75) return DIAG_CIMA_DIREITA2;
        else return DIAG_CIMA_DIREITA1;
    }
    if (x >= 25 && y <= -25) {
        if (x > 75 || y < -75) return DIAG_CIMA_ESQUERDA2;
        else return DIAG_CIMA_ESQUERDA1;
    }
    if (x <= -25 && y >= 25) {
        if (x < -75 || y > 75) return DIAG_BAIXO_DIREITA2;
        else return DIAG_BAIXO_DIREITA1;
    }
    if (x <= -25 && y <= -25) {
        if (x < -75 || y < -75) return DIAG_BAIXO_ESQUERDA2;
        else return DIAG_BAIXO_ESQUERDA1;
    }
  
    // Direções principais (eixos individuais)
    if (x >= 25) {
        if (x > 75) return CIMA2;
        else return CIMA1;
    }
    if (x <= -25) {
        if (x < -75) return BAIXO2;
        else return BAIXO1;
    }
    if (y >= 25) {
        if (y > 75) return DIREITA2;
        else return DIREITA1;
    }
    if (y <= -25) {
        if (y < -75) return ESQUERDA2;
        else return ESQUERDA1;
    }
  
    return NEUTRO;
}
  
  // Sprite neutro (todos desligados)
  int neutro[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro com intensidade máxima
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
    };
  
  // Sprite esquerda nível 1
  int esq1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {100}, {100}, {0}, {0}}, // Dois LEDs à esquerda do centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite esquerda nível 2
  int esq2[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{100}, {100}, {100}, {0}, {0}}, // Três LEDs à esquerda do centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite cima nível 1
  int cima1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Um LED acima do centro
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite cima nível 2
  int cima2[5][5][3] = {
    {{0}, {0}, {100}, {0}, {0}}, // Um LED acima do centro
    {{0}, {0}, {100}, {0}, {0}}, // Um LED acima do centro
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite direita nível 1
  int dir1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {100}, {0}}, // Dois LEDs à direita do centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite direita nível 2
  int dir2[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {100}, {100}}, // Três LEDs à direita do centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite baixo nível 1
  int bai1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {100}, {0}, {0}}, // Um LED abaixo do centro
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite baixo nível 2
  int bai2[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {100}, {0}, {0}}, // Um LED abaixo do centro
    {{0}, {0}, {100}, {0}, {0}}  // Dois LEDs abaixo do centro
  };
  
  // Sprite diagonal esquerda-cima nível 1
  int esqcim1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {100}, {0}, {0}, {0}}, // LED superior esquerdo
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite diagonal esquerda-cima nível 2
  int esqcim2[5][5][3] = {
    {{100}, {0}, {0}, {0}, {0}}, // LED superior esquerdo
    {{0}, {100}, {0}, {0}, {0}}, // LED superior esquerdo
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite diagonal esquerda-baixo nível 1
  int esqbax1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {100}, {0}, {0}, {0}}, // LED inferior esquerdo
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite diagonal esquerda-baixo nível 2
  int esqbax2[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {100}, {0}, {0}, {0}}, // LED inferior esquerdo
    {{100}, {0}, {0}, {0}, {0}}  // LED inferior esquerdo
  };
  
  // Sprite diagonal direita-cima nível 1
  int dircim1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {100}, {0}}, // LED superior direito
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite diagonal direita-cima nível 2
  int dircim2[5][5][3] = {
    {{0}, {0}, {0}, {0}, {100}}, // LED superior direito
    {{0}, {0}, {0}, {100}, {0}}, // LED superior direito
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite diagonal direita-baixo nível 1
  int dirbax1[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {100}, {0}}, // LED inferior direito
    {{0}, {0}, {0}, {0}, {0}}
  };
  
  // Sprite diagonal direita-baixo nível 2
  int dirbax2[5][5][3] = {
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {0}, {0}, {0}},
    {{0}, {0}, {100}, {0}, {0}}, // Centro
    {{0}, {0}, {0}, {100}, {0}}, // LED inferior direito
    {{0}, {0}, {0}, {0}, {100}}  // LED inferior direito
  };