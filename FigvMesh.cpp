//
// Created by fconde on 4/10/23.
//

#include "FigvMesh.h"
#include "FigvAuxiliaryFunctions.h"
#include <glad/glad.h>

FigvMesh::FigvMesh(std::vector<FigvVertex> vertices,
                   std::vector<unsigned int> indices) {

    FigvLog("FigvMesh" , __LINE__, "vertices: " + std::to_string(vertices.size()) + " indices " + std::to_string(indices.size()));
    
    this->vertices = vertices;
    this->indices = indices;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(FigvVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FigvVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FigvVertex), (void*)offsetof(FigvVertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FigvVertex), (void*)offsetof(FigvVertex, texCoords));

    glBindVertexArray(0);
}

void FigvMesh::draw() {
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
