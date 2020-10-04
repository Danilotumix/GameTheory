#pragma once

#include "GLTexture.h"
#include "TextureCache.h"
#include <string>

class ResourceManager{
    static TextureCache textureCache;
public:
    static GLTexture getTexture(std::string texturePath);
};