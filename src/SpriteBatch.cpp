#include "SpriteBatch.h"
#include <algorithm>

//Private

void SpriteBatch::createVertexArray(){
    if(vba == 0){
        glGenVertexArrays(1, &vba);
    }
    glBindVertexArray(vba);

    if(vbo == 0){
        glGenBuffers(1, &vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), (void*)offsetof(Vertex,position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
                        sizeof(Vertex), (void*)offsetof(Vertex,color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), (void*)offsetof(Vertex,uv));

    glBindVertexArray(0);
}

void SpriteBatch::sortGlyph(){
    switch(sortType)
    {
    case GlyphSortType::BACK_TO_FRONT:
        std::stable_sort(glyphs.begin(), glyphs.end(), compareBackToFront);
        break;
    case GlyphSortType::FRONT_TO_BACK:
        std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontToBack);
        break;
    case GlyphSortType::TEXTURE:
        std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
        break;
    case GlyphSortType::NONE:
        break;
    }
}

void SpriteBatch::createRenderBatches(){
    std::vector<Vertex> vertices;
    vertices.resize(glyphs.size() * 6);

    if(glyphs.empty()){
        return;
    }

    int cv = 0;
    int offset = 0;

    renderBatches.emplace_back(offset, 6, glyphs[0]->texture);
    
    vertices[cv++] = glyphs[0]->topLeft;
    vertices[cv++] = glyphs[0]->bottomLeft;
    vertices[cv++] = glyphs[0]->bottomRight;
    vertices[cv++] = glyphs[0]->bottomRight;
    vertices[cv++] = glyphs[0]->topRight;
    vertices[cv++] = glyphs[0]->topLeft;

    offset += 6;

    for(int i = 1; i < glyphs.size(); ++i){
        if(glyphs[i]->texture != glyphs[i-1]->texture){
            renderBatches.emplace_back(offset, 6, glyphs[0]->texture);
        }
        else{
            renderBatches.back().numVertices += 6;
        }

        vertices[cv++] = glyphs[0]->topLeft;
        vertices[cv++] = glyphs[0]->bottomLeft;
        vertices[cv++] = glyphs[0]->bottomRight;
        vertices[cv++] = glyphs[0]->bottomRight;
        vertices[cv++] = glyphs[0]->topRight;
        vertices[cv++] = glyphs[0]->topLeft;        
        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Public

SpriteBatch::SpriteBatch(){
    
}

SpriteBatch::~SpriteBatch(){

}

void SpriteBatch::init(){
    createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType = GlyphSortType::TEXTURE){
    this->sortType = sortType;
    renderBatches.clear();

    for(int i = 0; i < glyphs.size(); ++i){
        delete glyphs[i];
    }

    glyphs.clear();
}

void SpriteBatch::end(){
    sortGlyph();
    createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, Color& color){
    Glyph* glyph = new Glyph;
    glyph->texture = texture;
    glyph->depth = depth;

    glyph->topLeft.color = color;
    glyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
    glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    glyph->bottomLeft.color = color;
    glyph->bottomLeft.setPosition(destRect.x, destRect.y);
    glyph->bottomLeft.setUV(uvRect.x, uvRect.y);

    glyph->bottomRight.color = color;
    glyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
    glyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    glyph->topRight.color = color;
    glyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    glyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    glyphs.push_back(glyph);
}

void SpriteBatch::renderBatch(){
    glBindVertexArray(vba);

    for(int i = 0; i < renderBatches.size(); ++i){
        glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
        glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
    }
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph*b){
    return a->depth < b->depth;
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph*b){
    return a->depth > b->depth;
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph*b){
    return a->texture < b->texture;
}