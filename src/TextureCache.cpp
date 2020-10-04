#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

using namespace std;

TextureCache::TextureCache(){

}

TextureCache::~TextureCache(){

}

GLTexture TextureCache::getTexture(std::string texturePath){
    map<string, GLTexture>::iterator textureCacheIterator = textureMap.find(texturePath);

    cout << "Buscando.. " << texturePath << endl;

    if(textureCacheIterator == textureMap.end()){
        GLTexture texture = ImageLoader::loadPNG(texturePath);
        pair<string, GLTexture> newPair(texturePath, texture);
        textureMap.insert(newPair);
        //textureMap[texturePath] = Texture
        //Lo de arriba reemplaza las últimas 2 líneas de código
    }

    return textureCacheIterator->second;
}