#pragma once

class CObjFace;
class CMatrix;
class CTextureStorage;

class CObjModel
{
	char m_count[100];
	int m_VertexNum{ 0 };
	int m_TextureNum{ 0 };
	int m_NormalNum{ 0 };
	int m_FaceNum { 0 };
	
	CTextureStorage* m_TextureStroage	{ nullptr };
	GLuint			m_TextureID			;
	
	CVector3D<GLdouble> *		m_pVertex			{ nullptr };
	CVector3D<GLdouble> *		m_pTexture			{ nullptr };
	CVector3D<GLdouble> *		m_pNormal			{ nullptr };
	CObjFace *					m_pFace				{ nullptr };


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
	void LoadTexture(const char* filename);
	void Render();
	
	void MovePivot(const GLdouble& x, const GLdouble& y, const GLdouble& z);
	void MovePivot(const CVector3D<>& Pos);

	void Rotate(const int& degree, const int& x, const int& y, const int& z);
	void Rotate(const float& degree, const int& x, const int& y, const int& z);
	void Reset_Rotate();
	
	void Scale(const float& x, const float& y, const float& z);
};

