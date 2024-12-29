#include "LTexture.h"

LTexture::LTexture(SDL_Renderer* renderer) :
renderer(renderer), texture(nullptr), width(0), height(0) {}

LTexture::~LTexture() {
    this->free();
}

int LTexture::getWidth(void) const {
    return this->width;
}

int LTexture::getHeight(void) const {
    return this->height;
}

void LTexture::free(void) {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
        this->width = 0;
        this->height = 0;
    }
}

void LTexture::loadFromFile(const std::string& path){
    this->free();

    // Criamos a superfície
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        throw std::runtime_error("Unable to load image " + path + "! SDL_image Error: " + IMG_GetError());
    }

    // Criamos um color key para deixar o fundo transparente
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

    // Criamos a textura
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (texture == nullptr) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Unable to create texture " + path + "! SDL Error: " + SDL_GetError());
    }

    // Salvamos as dimensões da superfície
    this->width = surface->w;
    this->height = surface->h;
    this->texture = texture;

    SDL_FreeSurface(surface);
}

void LTexture::loadFromRenderedText(TTF_Font* font, const std::string& textureText, SDL_Color textColor){
    this->free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == nullptr) {
        throw std::runtime_error("Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()));
    }

    // Criar textura a partir dos pixels da superfície
    this->texture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    if (this->texture == nullptr) {
        SDL_FreeSurface(textSurface);
        throw std::runtime_error("Unable to create texture from rendered text! SDL Error: " + std::string(SDL_GetError()));
    }

    // Salvamos as dimensões da superfície
    this->width = textSurface->w;
    this->height = textSurface->h;

    // Liberar a superfície antiga
    SDL_FreeSurface(textSurface);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, this->width, this->height};

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(this->renderer, this->texture, clip, &renderQuad, angle, center, flip);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(this->texture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(this->texture, alpha);
}
