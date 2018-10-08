#pragma once

class CObjFace;
class RotateMatrix;
class CTextureStorage;

class CObjModel
{
	CVector3D<> m_Position;

	int m_VertexNum{ 0 };
	int m_TextureNum{ 0 };
	int m_NormalNum{ 0 };
	int m_FaceNum { 0 };
	
	CTextureStorage*		 m_TextureStroage	{ nullptr };
	std::vector<GLuint> 	m_TextureID			;
	int						m_TextuerIndex		{ -1 };

	CVector3D<> *			m_pVertex			{ nullptr };
	CVector3D<> *			m_pTexture			{ nullptr };
	CVector3D<> *			m_pNormal			{ nullptr };
	CObjFace *				m_pFace				{ nullptr };

	RotateMatrix*		m_PivotMove_Matrix	{ nullptr };
	RotateMatrix*		m_PivotReturn_Matrix{ nullptr };
	RotateMatrix*		m_RotateMatrix			{ nullptr };
	
private:
	void ModelRender();
	void Find_VertexNum(const char*& filename);
	void Save_Information(const char*& filename);



public:
	CObjModel();
	~CObjModel();
	void Reset();

	void LoadObj(const char* filename);
	void LoadTexture(const char* filename);
	void Render();

	void SetTextuerIDindex(const int& index);
	
	void MovePivot(const GLdouble& x, const GLdouble& y, const GLdouble& z);
	void MovePivot(const CVector3D<>& Pos);
	void MovePivot(CVector3D<>&& Pos);

	void Rotate(const int& Nowdegree, const int& x, const int& y, const int& z);
	void Rotate(const float& Nowdegree, const int& x, const int& y, const int& z);
	
	void ResetRotate();
	
};

