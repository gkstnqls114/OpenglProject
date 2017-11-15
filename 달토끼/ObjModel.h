#pragma once

class CObjVertex;
class CObjFace;

class CObjModel
{
	char m_count[100];
	int m_VertexNum{ 0 };
	int m_FaceNum { 0 };
	
	CObjVertex * m_pVertex{ nullptr };
	CObjFace * m_pFace{ nullptr };

public:
	CObjModel();
	~CObjModel();

	void LoadObj(const char* filename);
	void Render();
	
};

