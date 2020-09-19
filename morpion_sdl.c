#include "morpion_sdl.h"

int setWindowColor(SDL_Renderer * renderer, SDL_Color color) {
  if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
    return -1;
  if (SDL_RenderClear(renderer) < 0)
    return -1;
  return 0;
}

int setColor(SDL_Renderer * renderer, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

int drawButton(SDL_Renderer * renderer, SDL_Color color, int x, int y, int w, int h, char text[]) {
  SDL_Surface * texte;
  SDL_Texture * texture;
  TTF_Font * police = NULL;

  SDL_Color fontColor = {
    188,
    0,
    0,
    0
  };
  SDL_Rect bt = {
    x,
    y,
    w,
    h
  };
  police = TTF_OpenFont("BebasNeue-Regular.ttf", 65);
  setColor(renderer, color);
  SDL_RenderFillRect(renderer, & bt);
  texte = TTF_RenderText_Blended(police, text, fontColor);
  texture = SDL_CreateTextureFromSurface(renderer, texte);
  SDL_RenderCopy(renderer, texture, NULL, & bt);
}

int drawCase(SDL_Renderer * renderer, SDL_Color color, int x, int y, int w) {
  setColor(renderer, color);
  SDL_Rect bt = {
    x,
    y,
    w,
    w
  };
  SDL_RenderDrawRect(renderer, & bt);
}

int isInCoords(int x, int y, int w, int h, SDL_Event event) {
  return (event.button.y > y &&
    event.button.y <= y + h &&
    event.button.x > x &&
    event.button.x <= x + w);
}

int askN(SDL_Event event, SDL_Renderer * renderer) {
  int n;
  int continuer = 1;
  SDL_Color color = {
    50,
    0,
    0,
    255
  };
  SDL_Color white = {
    255,
    255,
    255,
    255
  };
  SDL_RenderClear(renderer);
  setWindowColor(renderer, white) ;
  drawButton(renderer, color, 50, 200, 500, 75, "N = ? (avec les chiffres du haut du clavier)");
  SDL_RenderPresent(renderer);
  while (continuer) {
    SDL_WaitEvent( & event);
    switch (event.type) {
    case SDL_QUIT:
      continuer = 0;
      SDL_Quit();
      break;
    case SDL_KEYDOWN:
      // printf("%s\n", SDL_GetKeyName(event.key.keysym.sym));
      sscanf(SDL_GetKeyName(event.key.keysym.sym), "%d", & n);
      continuer = 0;
      break;
    }
  }

  return n;
}

int waitToPlay(int size, SDL_Renderer * renderer, char player, SDL_Event event, int * i, int * j) {
  int continuer = 1;

  while (continuer) {
    SDL_WaitEvent( & event);
    switch (event.type) {
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_MOUSEBUTTONUP:
      *
      i = event.button.y / (600 / size);
      * j = event.button.x / (600 / size);
      continuer = 0;
      break;
    }
  }
  return 0;
}

int drawCircle(SDL_Renderer * renderer, int i, int j, int size) {
  SDL_Color color = {
    200,
    0,
    0,
    255
  };
  int wCase = 600 / size;
  setColor(renderer, color);
  SDL_Rect rect = {
    wCase * i + wCase / 20,
    wCase * j + wCase / 20,
    wCase - 2 * wCase / 20,
    wCase - 2 * wCase / 20
  };
  SDL_RenderDrawRect(renderer, & rect);
}

int drawCross(SDL_Renderer * renderer, int i, int j, int size) {
  SDL_Color color = {
    200,
    0,
    0,
    255
  };
  int wCase = 600 / size;
  setColor(renderer, color);
  SDL_RenderDrawLine(renderer, wCase * i + wCase / 20, wCase * j + wCase / 20, wCase * (i + 1) - wCase / 20, wCase * (j + 1) - wCase / 20);
  SDL_RenderDrawLine(renderer, wCase * i + wCase / 20, wCase * (j + 1) - wCase / 20, wCase * (i + 1) - wCase / 20, wCase * j + wCase / 20);
}

int drawGrille(int size, SDL_Renderer * renderer, morpion jeu) {
  int i, j;
  int wCase = 600 / size;

  SDL_Color white = {
    255,
    255,
    255,
    255
  };
  SDL_Rect background = {
    0,
    0,
    600,
    600
  };
  SDL_Color color1 = {
    50,
    0,
    0,
    255
  };
  SDL_Color color2 = {
    0,
    67,
    50,
    200
  };
  SDL_RenderClear(renderer);
  setColor(renderer, white);
  SDL_RenderFillRect(renderer, & background);

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      drawCase(renderer, color1, i * wCase, j * wCase, wCase);
      if (jeu[j][i] == 0) {
        drawCircle(renderer, i, j, size);
      } else if (jeu[j][i] == 1) {
        drawCross(renderer, i, j, size);
      }
    }

  }

  SDL_RenderPresent(renderer);

}