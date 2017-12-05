#include "pch.h"
#include "ObjFace.h"


CObjFace::CObjFace()
{
}


CObjFace::~CObjFace()
{
	if (m_VertexIndex != nullptr) {
		delete[] m_VertexIndex;
	}
}

const int CObjFace::GetVertexIndex(const int & num) const noexcept
{
	if (num >= m_VertexNum) return -1;

	return m_VertexIndex[num];
}

const int CObjFace::GetTextureIndex(const int & num) const noexcept
{
	if (num >= m_TextureNum) return -1;

	return m_TextureIndex[num];
}

const int CObjFace::GetNormalIndex(const int & num) const noexcept
{
	if (num >= m_NormalNum) return -1;

	return m_NormalIndex[num];
}
