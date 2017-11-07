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
