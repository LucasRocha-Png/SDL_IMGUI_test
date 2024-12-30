#include "LTexture.h"

LTexture::LTexture(SDL_Renderer* renderer = nullptr) :
renderer(renderer), texture(nullptr), colorKey(nullptr), width(0), height(0) {}

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
    //Get rid of preexisting texture
	free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == nullptr){
		throw std::runtime_error(std::string("Unable to load image! SDL_image Error: ") + std::string(IMG_GetError()));
	}
	
    //Color key image
    if (this->colorKey) SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, this->colorKey->r, this->colorKey->g, this->colorKey->b));
    
    //Create texture from surface pixels
    this->texture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
    if(this->texture == nullptr){
        throw std::runtime_error(std::string("Unable to create texture! SDL Error: ") + std::string(SDL_GetError()));
    }

    //Get image dimensions
    this->width = loadedSurface->w;
    this->height = loadedSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
}


void LTexture::loadFromRenderedText(TTF_Font* font, const std::string& textureText, SDL_Color textColor){
    this->free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == nullptr) {
        throw std::runtime_error("Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()));
    }


    this->texture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    if (this->texture == nullptr) {
        SDL_FreeSurface(textSurface);
        throw std::runtime_error("Unable to create texture from rendered text! SDL Error: " + std::string(SDL_GetError()));
    }

    this->width = textSurface->w;
    this->height = textSurface->h;

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

void LTexture::setColorKey(SDL_Color* colorKey){
    this->colorKey = colorKey;
}

void LTexture::createBlank(int width, int height, SDL_TextureAccess access){
    free();

    //Create uninitialized texture
    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );
    if(this->texture == nullptr){
        throw std::runtime_error(std::string("Unable to create streamable blank texture! SDL Error: ") + std::string(SDL_GetError()));
    }

    this->width = width;
    this->height = height;
}

void LTexture::setAsRenderTarget(){
    //Make self render target
    SDL_SetRenderTarget(this->renderer, this->texture);
}

void LTexture::resetRenderTarget(){
    SDL_SetRenderTarget(this->renderer, nullptr);
}