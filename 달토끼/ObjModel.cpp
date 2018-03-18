#include "pch.h"
#include <fstream>
#include <string>
#include "TextureStorage.h"
#include "RotateMatrix.h"
#include "ObjFace.h"
#include "ObjModel.h"


void CObjModel::ModelRender()
{
	if (m_TextuerIndex > -1) {
		glBindTexture(GL_TEXTURE_2D, m_TextureID[m_TextuerIndex]);
	}
	for (int Face_index = 0; Face_index < m_FaceNum; ++Face_index) {
		glBegin(GL_POLYGON);

		int Vertex_in_Face = m_pFace[Face_index].GetVertexNum();
		
		for (int Vertex_Num = 0; Vertex_Num < Vertex_in_Face; ++Vertex_Num) {
			int vertex_index = m_pFace[Face_index].GetVertexIndex(Vertex_Num);
			int texture_index = m_pFace[Face_index].GetTextureIndex(Vertex_Num);
			int normal_index = m_pFace[Face_index].GetNormalIndex(Vertex_Num);

			glNormal3d(m_pNormal[normal_index - 1].x, m_pNormal[normal_index - 1].y, m_pNormal[normal_index - 1].z);
			glTexCoord2d(m_pTexture[texture_index - 1].x, m_pTexture[texture_index - 1].y);
			
			GLdouble x = m_pVertex[vertex_index - 1].x;
			GLdouble y = m_pVertex[vertex_index - 1].y;
			GLdouble z = m_pVertex[vertex_index - 1].z;
			glVertex3f(x, y, z);
		}

		glEnd();
	}
}

void CObjModel::Find_VertexNum(const char*& filename)
{
	FILE * fp;
	char str[1024];
	fopen_s(&fp, filename, "r");

	bool IsFail = (fp == NULL);
	if (IsFail) {
		std::cout << filename <<  ": ���� ã�� ����" << std::endl;
		return;
	}

	m_VertexNum = 0;
	m_FaceNum = 0;

	//���� �б�
	//�� ������ ������ ����, ���� ������ ���Ѵ�.
	//feof ������ ���� ���� ������ ����
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

	//���� ������ �����Ҵ� �Ѵ�.
	//�����Ҵ�: �迭
	m_pVertex = new CVector3D<>[m_VertexNum];
	m_pNormal = new CVector3D<>[m_NormalNum];
	m_pTexture = new CVector3D<>[m_TextureNum];
	m_pFace = new CObjFace[m_FaceNum];
}

void CObjModel::Save_Information(const char*& filename)
{
	FILE * fp;
	char str[1024];
	fopen_s(&fp, filename, "r");

	bool IsFail = fp == NULL;
	if (IsFail) {
		std::cout << filename << ": ���� ã�� ����" << std::endl;
		return;
	}

	int VertexIndex = 0;
	int TextureIndex = 0;
	int NormalIndex = 0;
	int FaceIndex = 0;

	//�� �޸𸮿� ������ �Է��Ѵ�.
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

			m_pVertex[VertexIndex].x = x;
			m_pVertex[VertexIndex].y = y;
			m_pVertex[VertexIndex].z = z;

			VertexIndex += 1;
		}

		if (IsTexture) {
			float x = -1.f;
			float y = -1.f;
			float z = -1.f;

			fscanf_s(fp, "%f %f %f\n", &x, &y, &z);

			m_pTexture[TextureIndex].x = x;
			m_pTexture[TextureIndex].y = y;
			m_pTexture[TextureIndex].z = z;

			TextureIndex += 1;
		}

		if (IsNormal) {
			float x = -1.f;
			float y = -1.f;
			float z = -1.f;

			fscanf_s(fp, "%f %f %f\n", &x, &y, &z);

			m_pNormal[NormalIndex].x = x;
			m_pNormal[NormalIndex].y = y;
			m_pNormal[NormalIndex].z = z;

			NormalIndex += 1;
		}


		if (IsFace) {
			int Vertex_index[6] = { -1, -1, -1, -1 , -1, -1 };
			int Texture_index[6] = { -1, -1, -1, -1 , -1, -1 };
			int Normal_index[6] = { -1, -1, -1, -1 , -1, -1 };
			int nouse = 0;

			//�ϵ��ڵ�..
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&Vertex_index[0], &Texture_index[0], &Normal_index[0],
				&Vertex_index[1], &Texture_index[1], &Normal_index[1],
				&Vertex_index[2], &Texture_index[2], &Normal_index[2],
				&Vertex_index[3], &Texture_index[3], &Normal_index[3],
				&Vertex_index[4], &Texture_index[4], &Normal_index[4],
				&Vertex_index[5], &Texture_index[5], &Normal_index[5]);


				//�鿡 ���� ������ ������ ����.
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

			//�鿡 ���ؼ�, ���� ������ �����Ҵ��Ѵ�.
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
	m_PivotMove_Matrix = new RotateMatrix;
	m_PivotReturn_Matrix = new RotateMatrix;
	m_RotateMatrix = new RotateMatrix;
}

CObjModel::~CObjModel()
{
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

	delete m_RotateMatrix;
	m_RotateMatrix = nullptr;
	delete m_PivotMove_Matrix;
	m_PivotMove_Matrix = nullptr;
	delete m_PivotReturn_Matrix;
	m_PivotReturn_Matrix = nullptr;
}

void CObjModel::Reset()
{
	m_RotateMatrix->ResetRotate();
}

void CObjModel::LoadObj(const char * filename)
{
	std::cout << "CObjModel �� ����: " << filename << std::endl;

	Find_VertexNum(filename);
	Save_Information(filename);
}

void CObjModel::LoadTexture(const char* filename)
{
	GLuint ID;
	m_TextureStroage->StoreBitmap(filename, ID);
	m_TextureID.push_back(ID);
	m_TextuerIndex += 1;
}

void CObjModel::Render()
{
	glPushMatrix();
	m_PivotReturn_Matrix->Rotate();

	glPushMatrix();
	m_RotateMatrix->Rotate();

	glPushMatrix();
	m_PivotMove_Matrix->Rotate();

	ModelRender();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void CObjModel::SetTextuerIDindex(const int& index)
{
	m_TextuerIndex = index;
}

void CObjModel::MovePivot(const GLdouble & x, const GLdouble & y, const GLdouble & z)
{
	//m_PivotMove_Matrix->Calu_Tranlate(CVector3D<>(x, y, z));
	//m_PivotReturn_Matrix->Calu_Tranlate(CVector3D<>(-x, -y, -z));
}

void CObjModel::MovePivot(const CVector3D<> & Pos)
{
	//m_PivotMove_Matrix->Calu_Tranlate(Pos);
	//���߿� ���׿����� �����ε� ã�ƺ���
	//������ �ϴ� .. ���� ��
	//m_PivotReturn_Matrix->Calu_Tranlate(CVector3D<>(-Pos.x, -Pos.y, -Pos.z));
}

void CObjModel::MovePivot(CVector3D<>&& Pos)
{
	//m_PivotMove_Matrix->Calu_Tranlate(Pos);
	//���߿� ���׿����� �����ε� ã�ƺ���
	//������ �ϴ� .. ���� ��
	//m_PivotReturn_Matrix->Calu_Tranlate(CVector3D<>(-Pos.x, -Pos.y, -Pos.z));
}

void CObjModel::Rotate(const int & Nowdegree, const int & x, const int & y, const int & z)
{
	m_RotateMatrix->Calu_Rotate(Nowdegree, x, y, z);
}

void CObjModel::Rotate(const float & Nowdegree, const int & x, const int & y, const int & z)
{
	m_RotateMatrix->Calu_Rotate(Nowdegree, x, y, z);
}

void CObjModel::Translate(const CVector3D<>& rhs)
{
//	m_Matrix->Calu_Tranlate(rhs);
}

void CObjModel::Translate(CVector3D<>&& rhs)
{
//	m_Matrix->Calu_Tranlate(rhs);
}

void CObjModel::ResetRotate()
{
	m_RotateMatrix->ResetRotate();
}

void CObjModel::Scale(const float & x, const float & y, const float & z)
{
	//m_RotateMatrix->Calu_Scale(x, y, z);
}

void CObjModel::Set_Scale(const float & x, const float & y, const float & z)
{
	//m_RotateMatrix->Set_Scale(x, y, z);
}
