#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

float QuadVertices[] = {
	1.0f,  1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f,  1.0f
};

unsigned int QuadIndices[] = {
	0, 1, 3,
	1, 2, 3
};

class RenderQuad
{
public:
	RenderQuad()
		: mShader("res/shader/cell.vs", "res/shader/cell.fs")
	{
		QuadInitialize();
	}

	void Render(int texture_unit = GL_TEXTURE0)
	{
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
		glActiveTexture(texture_unit);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		mShader.Bind();
		mShader.SetUniformMat4("uModel", model);
		mShader.SetUniformI("uTexture", 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	Shader* GetShader() { return &mShader; }

private:
	unsigned int quadVBO, quadEBO, quadVAO;
	Shader mShader;

	void QuadInitialize()
	{
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glGenBuffers(1, &quadEBO);

		glBindVertexArray(quadVAO);

		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QuadIndices), QuadIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};