#include "pch.h"
#include <fstream>
#include <string>
#include "Texture.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "ObjFace.h"
#include "ObjModel.h"


void CObjModel::ModelRender()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	for (int Face_index = 0; Face_index < m_FaceNum; ++Face_index) {
		//glBegin(GL_LINE_LOOP);
		glBegin(GL_POLYGON);

		int Vertex_in_Face = m_pFace[Face_index].GetVertexNum();
		
		for (int Vertex_Num = 0; Vertex_Num < Vertex_in_Face; ++Vertex_Num) {
			int vertex_index = m_pFace[Face_index].GetVertexIndex(Vertex_Num);
			int texture_index = m_pFace[Face_index].GetTextureIndex(Vertex_Num);
			int normal_index = m_pFace[Face_index].GetNormalIndex(Vertex_Num);

			glNormal3d(m_pNormal[normal_index - 1][0], m_pNormal[normal_index - 1][1], m_pNormal[normal_index - 1][2]);
			glTexCoord2d(m_pTexture[texture_index - 1][0], m_pTexture[texture_index - 1][1]);
			glVertex3f(m_pVertex[vertex_index - 1][0], m_pVertex[vertex_index - 1][1], m_pVertex[vertex_index - 1][2]);
		}

		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CObjModel::Find_VertexNum(const char*& filename)
{
	FILE * fp;
	char str[1024];
	fopen_s(&fp, filename, "r");

	bool IsFail = (fp == NULL);
	if (IsFail) {
		std::cout << filename <<  ": 파일 찾기 실패" << std::endl;
		return;
	}

	m_VertexNum = 0;
	m_FaceNum = 0;

	//파일 읽기
	//이 파일의 정점의 개수, 면의 개수를 구한다.
	//feof 파일의 끝을 만날 때까지 루프
	while (!feof(fp)) {
		fgets(str, 1024, fp);

		bool IsVertex = str[0] == 'v' && str[1] == ' ';
		bool IsFace = str[0] == 'f' && str[1] == ' ';
		bool IsTexture = str[0] == 'v' && str[1] == 't';
		bool IsNormal = str[0] == 'v' && str[1] == 'n';

		if (IsVertex) {
			m_VertexNum += 1;
		}
		else if (IsFace) {
			m_FaceNum += 1;
		}
		else if (IsTexture) {
			m_TextureNum += 1;
		}
		else if (IsNormal) {
			m_NormalNum += 1;
		}


	}

	fclose(fp);
	fp = NULL;

	///std::cout << m_VertexNum << std::endl;
	//std::cout << m_FaceNum << std::endl;

	//구한 개수를 동적할당 한다.
	//동적할당: 배열
	m_pVertex = new CVector3D[m_VertexNum];
	m_pNormal = new CVector3D[m_NormalNum];
	m_pTexture = new CVector3D[m_TextureNum];
	m_pFace = new CObjFace[m_FaceNum];

}

void CObjModel::Save_Information(const char*& filename)
{
	FILE * fp;
	char str[1024];
	fopen_s(&fp, filename, "r");

	bool IsFail = fp == NULL;
	if (IsFail) {
		std::cout << filename << ": 파일 찾기 실패" << std::endl;
		return;
	}

	int VertexIndex = 0;
	int TextureIndex = 0;
	int NormalIndex = 0;
	int FaceIndex = 0;

	//각 메모리에 정보를 입력한다.
	while (!feof(fp)) {
		int res = fscanf(fp, "%s", str);

		if (res == EOF) break;

		bool IsVertex = strcmp(str, "v") == 0;
		bool IsFace = strcmp(str, "f") == 0;
		bool IsTexture = strcmp(str, "vt") == 0;
		bool IsNormal = strcmp(str, "vn") == 0;

		if (IsVertex) {
			float x = -1.f;
			float y = -1.f;
			float z = -1.f;

			fscanf_s(fp, "%f %f %f\n", &x, &y, &z);

			m_pVertex[VertexIndex][0] = x;
			m_pVertex[VertexIndex][1] = y;
			m_pVertex[VertexIndex][2] = z;

			VertexIndex += 1;
		}

		if (IsTexture) {
			float x = -1.f;
			float y = -1.f;
			float z = -1.f;

			fscanf_s(fp, "%f %f %f\n", &x, &y, &z);

			m_pTexture[TextureIndex][0] = x;
			m_pTexture[TextureIndex][1] = y;
			m_pTexture[TextureIndex][2] = z;

			TextureIndex += 1;
		}

		if (IsNormal) {
			float x = -1.f;
			float y = -1.f;
			float z = -1.f;

			fscanf_s(fp, "%f %f %f\n", &x, &y, &z);

			m_pNormal[NormalIndex][0] = x;
			m_pNormal[NormalIndex][1] = y;
			m_pNormal[NormalIndex][2] = z;

			NormalIndex += 1;
		}


		if (IsFace) {
			int Vertex_index[6] = { -1, -1, -1, -1 , -1, -1 };
			int Texture_index[6] = { -1, -1, -1, -1 , -1, -1 };
			int Normal_index[6] = { -1, -1, -1, -1 , -1, -1 };
			int nouse = 0;

			//하드코딩..
			if (!strcmp(filename, "sample_moon.obj")) {
				fscanf_s(fp, "%d//%d %d//%d %d//%d %d//%d",
					&Vertex_index[0], &nouse,
					&Vertex_index[1], &nouse,
					&Vertex_index[2], &nouse,
					&Vertex_index[3], &nouse
				);
			}
			else {
				fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
					&Vertex_index[0], &Texture_index[0], &Normal_index[0],
					&Vertex_index[1], &Texture_index[1], &Normal_index[1],
					&Vertex_index[2], &Texture_index[2], &Normal_index[2],
					&Vertex_index[3], &Texture_index[3], &Normal_index[3],
					&Vertex_index[4], &Texture_index[4], &Normal_index[4],
					&Vertex_index[5], &Texture_index[5], &Normal_index[5]
				);
			}

			//면에 대한 정점의 개수를 센다.
			int vertex_num_of_face = 0;
			for (int x = 0; x < 6; ++x) {
				if (Vertex_index[x] != -1) {
					vertex_num_of_face += 1;
				}
			}

			int texture_num_of_face = 0;
			for (int x = 0; x < 6; ++x) {
				if (Texture_index[x] != -1) {
					texture_num_of_face += 1;
				}
			}

			int normal_num_of_face = 0;
			for (int x = 0; x < 6; ++x) {
				if (Normal_index[x] != -1) {
					normal_num_of_face += 1;
				}
			}

			//면에 대해서, 정점 개수를 동적할당한다.
			m_pFace[FaceIndex].SetVertexNum(vertex_num_of_face);
			m_pFace[FaceIndex].SetTextureNum(texture_num_of_face);
			m_pFace[FaceIndex].SetNormalNum(normal_num_of_face);

			for (int x = 0; x < vertex_num_of_face; ++x) {
				m_pFace[FaceIndex].Set_VertexIndex(x, Vertex_index[x]);
				m_pFace[FaceIndex].Set_VertexIndex(x, Vertex_index[x]);
				m_pFace[FaceIndex].Set_VertexIndex(x, Vertex_index[x]);
			}
			for (int x = 0; x < texture_num_of_face; ++x) {
				m_pFace[FaceIndex].Set_TextureIndex(x, Texture_index[x]);
				m_pFace[FaceIndex].Set_TextureIndex(x, Texture_index[x]);
				m_pFace[FaceIndex].Set_TextureIndex(x, Texture_index[x]);
			}
			for (int x = 0; x < normal_num_of_face; ++x) {
				m_pFace[FaceIndex].Set_NormalIndex(x, Normal_index[x]);
				m_pFace[FaceIndex].Set_NormalIndex(x, Normal_index[x]);
				m_pFace[FaceIndex].Set_NormalIndex(x, Normal_index[x]);
			}

			FaceIndex += 1;
		}
	}

	fclose(fp);
	fp = NULL;
}

CObjModel::CObjModel()
{
	std::cout << "CObjModel 생성자" << std::endl;
	m_PivotMove_Matrix = new CMatrix;
	m_PivotReturn_Matrix = new CMatrix;
	m_Matrix = new CMatrix;
}

CObjModel::~CObjModel()
{
	std::cout << "CObjModel 소멸자" << std::endl;

	if (m_pVertex != nullptr) {
		delete[] m_pVertex;
		m_pVertex = nullptr;
	}

	if (m_pFace != nullptr) {
		delete[] m_pFace;
		m_pFace = nullptr;
	}

	if (m_pNormal != nullptr) {
		delete[] m_pNormal;
		m_pNormal = nullptr;
	}

	if (m_pFace != nullptr) {
		delete[] m_pFace;
		m_pFace = nullptr;
	}

	delete m_Matrix;
	m_Matrix = nullptr;
	delete m_PivotMove_Matrix;
	m_PivotMove_Matrix = nullptr;
	delete m_PivotReturn_Matrix;
	m_PivotReturn_Matrix = nullptr;
}

void CObjModel::LoadObj(const char * filename)
{
	std::cout << "CObjModel 모델 생성: " << filename << std::endl;

	Find_VertexNum(filename);
	Save_Information(filename);
}

void CObjModel::LoadTexture(const char * filename)
{
	m_TextureImage = new CTexture;
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	m_TextureImage->LoadDIBitmap(filename);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		m_TextureImage->GetWidth(), m_TextureImage->GetHeight(), 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE,
		m_TextureImage->GetTextureBit());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	std::cout << filename << ": 텍스쳐 로드 완료" << std::endl;
}

void CObjModel::Render()
{
	glPushMatrix();
	m_PivotReturn_Matrix->MultiMatrix();

	glPushMatrix();
	m_Matrix->MultiMatrix();

	glPushMatrix();
	m_PivotMove_Matrix->MultiMatrix();

	ModelRender();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void CObjModel::MovePivot(const GLdouble & x, const GLdouble & y, const GLdouble & z)
{
	m_PivotMove_Matrix->Calu_Tranlate(CVector3D(x, y, z));
	m_PivotReturn_Matrix->Calu_Tranlate(CVector3D(-x, -y, -z));
}

void CObjModel::MovePivot(const CVector3D & Pos)
{
	m_PivotMove_Matrix->Calu_Tranlate(Pos);
	//나중에 단항연산자 오버로딩 찾아보기
	//지금은 일단 .. 쓰자 ㅠ
	m_PivotReturn_Matrix->Calu_Tranlate(CVector3D(-Pos[0], -Pos[1], -Pos[2]));
}

void CObjModel::Rotate(const int & degree, const int & x, const int & y, const int & z)
{
	m_Matrix->Calu_Rotate(degree, x, y, z);
}

void CObjModel::Rotate(const float & degree, const int & x, const int & y, const int & z)
{
	m_Matrix->Calu_Rotate(degree, x, y, z);
}

void CObjModel::Reset_Rotate()
{
	m_Matrix->Reset_Rotate();
}

void CObjModel::Scale(const float & x, const float & y, const float & z)
{
	m_Matrix->Calu_Scale(x, y, z);
}
