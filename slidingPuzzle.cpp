#include "slidingPuzzle.h"

SDL_Texture *carregaImagem(const char *imagem, SDL_Renderer *renderizador){
    SDL_Surface *img = SDL_LoadBMP(imagem);
    if(img == nullptr){
        cout << "Erro no carregamento da imagem!";
    }
    SDL_Texture *textura  = SDL_CreateTextureFromSurface(renderizador, img);
    SDL_FreeSurface(img);
    return textura;
}

void definePosicoesOriginais(SDL_Rect *posicoesOriginais, int tamanhoTabuleiro, int colunas){
    int tamanhoIndividual = 600/tamanhoTabuleiro;
    int posicaoY;
    int posicaoX;
    for (int i = 0; i < tamanhoTabuleiro; ++i) {
        posicaoY = i * tamanhoIndividual;
        for (int j = 0; j < tamanhoTabuleiro; ++j) {
            posicaoX = j * tamanhoIndividual;
            posicoesOriginais[i*colunas+j] = {posicaoX, posicaoY, tamanhoIndividual, tamanhoIndividual};
        }

    }
}

void sorteiaPosicoes(SDL_Rect *posicoesOriginais, SDL_Rect *posicoesJogo, int *tabuleiro, int colunas){
    int linhas = colunas;
    for (int i = 0; i <  linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            posicoesJogo[i*colunas+j] = posicoesOriginais [i*colunas+j];
        }
    }
    int indice1, indice2, indice3, indice4, vezes=1;
    srand(time(nullptr));
    while (vezes <9) {
        indice1 = rand() % colunas;
        indice2 = rand() % colunas;
        indice3 = rand() % colunas;
        indice4 = rand() % colunas;
        if(tabuleiro[indice1 * colunas + indice2] != -1 and tabuleiro[indice3 * colunas + indice4] != -1){
            auto temp = posicoesJogo[indice1 * colunas + indice2];
            posicoesJogo[indice1 * colunas + indice2] = posicoesJogo[indice3 * colunas + indice4];
            posicoesJogo[indice3 * colunas + indice4] = temp;
            vezes++;
        }
    }
}

void validaMovimentacao(int indiceLinha, int indiceColuna, SDL_Rect *posicoesJogo, SDL_Rect *posicoesOriginais, int *tabuleiro, int colunas){
    int linhas = colunas;
    if    ((tabuleiro[indiceLinha * colunas + indiceColuna + 1] == -1 and indiceColuna != colunas-1)
        or (tabuleiro[indiceLinha * colunas + indiceColuna - 1] == -1 and indiceColuna != 0)
        or (tabuleiro[(indiceLinha + 1) * colunas + indiceColuna] == -1 and indiceLinha  != colunas-1)
        or (tabuleiro[(indiceLinha - 1) * colunas + indiceColuna] == -1 and indiceLinha  != 0))

    {
        auto temp = posicoesJogo[indiceLinha * colunas + indiceColuna];
        for(int i = 0; i < linhas; i++){
            for(int j = 0; j <colunas; j++){
                if (tabuleiro[i * colunas +j] == -1){
                    posicoesJogo[i * colunas + j] = temp;
                    tabuleiro[i * colunas + j] = 0;
                }
            }
        }
        tabuleiro[indiceLinha * colunas + indiceColuna] = -1;
        posicoesJogo[indiceLinha * colunas + indiceColuna] = posicoesOriginais[(linhas-1) * colunas + colunas-1];
    }
}

void escolheJogada(int *tabuleiro, SDL_Rect *posicoesJogo, SDL_Rect *posicoesOriginais, int colunas, bool &termina){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: {
            termina = true;
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            int x, y;
            SDL_GetMouseState(&x, &y);
            int indiceColuna = x / (600/colunas);
            int indiceLinha = y / (600/colunas);
            validaMovimentacao(indiceLinha, indiceColuna, posicoesJogo, posicoesOriginais, tabuleiro, colunas);
            break;
        }
        default:
            break;
        }

    }
}

void imprimeJogada(SDL_Rect *posicoesOriginais, SDL_Rect *posicoesJogo, SDL_Renderer *renderizador, SDL_Texture *imagem, int colunas){
    int linhas = colunas;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j){
            auto destino = posicoesOriginais[i * colunas + j];
            SDL_RenderCopy(renderizador, imagem, &posicoesJogo[i * colunas +j], &destino);
        }
    }
    SDL_RenderPresent(renderizador);
    SDL_Delay(1000/60);
}

void verificaGanhou(SDL_Rect *posicoesOriginais, SDL_Rect *posicoesJogo, int colunas, bool &termina){
    int cont = 0;
    int linhas = colunas;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (    posicoesJogo[i * colunas + j].x == posicoesOriginais[i * colunas + j].x
                and posicoesJogo[i * colunas + j].y == posicoesOriginais[i * colunas + j].y
                and posicoesJogo[i * colunas + j].h == posicoesOriginais[i * colunas + j].h
                and posicoesJogo[i * colunas + j].w == posicoesOriginais[i * colunas + j].w
            ){
                cont++;
            }
        }
    }
    if(cont == 9){
        termina = true;
    }
}
