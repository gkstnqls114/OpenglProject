#pragma once

class CObjFace;
class CMatrix;
class CTexture;

class CObjModel
{
	char m_count[100];
	int m_VertexNum{ 0 };
	int m_FaceNum { 0 };
	
	CVector3D *		m_pVertex			{ nullptr };
	CVector3D *		m_pTexure			{ nullptr };
	CVector3D *		m_pNormal			{ nullptr };

	CObjFace *		m_pFace				{ nullptr };

	CTexture*		m_TextureImage		{ nullptr };

	CMatrix*		m_PivotMove_Matrix	{ nullptr };
	CMatrix*		m_PivotReturn_Matrix{ nullptr };
	CMatrix*		m_Matrix			{ nullptr };

private:
	void ModelRender();
	void Find_VertexNum(const char*& filename);
	void Save_Information(const char*& filename);

public:
	CObjModel();
	~CObjModel();

	void LoadObj(const char* filename);
	void Render();
	
	void MovePivot(const GLdouble& x, const GLdouble& y, const GLdouble& z);
	void MovePivot(const CVector3D& Pos);

	void Rotate(const int& degree, const int& x, const int& y, const int& z);
	void Rotate(const float& degree, const int& x, const int& y, const int& z);
	void Reset_Rotate();
	
	void Scale(const float& x, const float& y, const float& z);
};

