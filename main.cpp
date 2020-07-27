//JOGO SLIDING PUZZLE, quebra cabeça com peças que deslizam

#include "slidingPuzzle.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow("Sliding Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    int tabuleiro[3][3] = {{0, 0,  0},
                           {0, 0,  0},
                           {0, 0, -1}};

    SDL_Rect posicoesOriginais[3][3];
    definePosicoesOriginais(posicoesOriginais[0], 3, 3);

    SDL_Rect posicoesJogo[3][3];
    SDL_Texture *imagem = carregaImagem("assets/bne.bmp", renderizador);
    bool termina = false;

    sorteiaPosicoes(posicoesOriginais[0], posicoesJogo[0], tabuleiro[0], 3);
    while (!termina) {
        escolheJogada(tabuleiro[0], posicoesJogo[0], posicoesOriginais[0], 3, termina);
        imprimeJogada(posicoesOriginais[0], posicoesJogo[0], renderizador, imagem, 3);
        verificaGanhou(posicoesOriginais[0], posicoesJogo[0], 3, termina);
    }

    SDL_DestroyWindow(janela);
    SDL_DestroyTexture(imagem);
    SDL_DestroyRenderer(renderizador);

    SDL_Quit();

    return 0;
}
