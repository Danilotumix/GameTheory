#pragma once

#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

enum class GlyphSortType{
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE,
};

struct Glyph{
    GLuint texture;
    float depth;
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
};

struct RenderBatch{
    RenderBatch(GLuint offset, GLuint numVertices, GLuint texture);
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch{
    GLuint vbo;
    GLuint vba;
    std::vector<Glyph*> glyphs;
    std::vector<RenderBatch> renderBatches;

    void createVertexArray();
    void sortGlyph();
    GlyphSortType sortType;
    void createRenderBatches();
public:
    SpriteBatch();
    ~SpriteBatch();
    void init();
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, Color& color);
    void renderBatch();
    static bool compareFrontToBack(Glyph* a, Glyph*b);
    static bool compareBackToFront(Glyph* a, Glyph*b);
    static bool compareTexture(Glyph* a, Glyph*b);
};