#ifndef SLIDINGPUZZLE_H
#define SLIDINGPUZZLE_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

SDL_Texture *carregaImagem(const char *imagem, SDL_Renderer *renderizador);

void definePosicoesOriginais(SDL_Rect *posicoesOriginais, int tamanhoTabuleiro, int colunas);

void sorteiaPosicoes(SDL_Rect *posicoesOriginais, SDL_Rect *posicoesJogo, int *tabuleiro, int colunas);

void validaMovimentacao(int indiceLinha, int indiceColuna, SDL_Rect *posicoesJogo, SDL_Rect *posicoesOriginais, int *tabuleiro, int colunas);

void escolheJogada(int *tabuleiro, SDL_Rect *posicoesJogo, SDL_Rect *posicoesOriginais, int colunas, bool &termina);

void imprimeJogada(SDL_Rect *posicoesOriginais, SDL_Rect *posicoesJogo, SDL_Renderer *renderizador, SDL_Texture *imagem, int colunas);

void verificaGanhou(SDL_Rect *posicoesOriginais, SDL_Rect *posicoesJogo, int colunas, bool &termina);

#endif // SLIDINGPUZZLE_H
