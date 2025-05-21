#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void addBuffer(const class VertexBuffer& vb, const class VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

