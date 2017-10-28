#include "pch.h"
#include <fstream>
#include <string>
#include "ObjVertex.h"
#include "ObjFace.h"
#include "ObjModel.h"



CObjModel::CObjModel()
{
}


CObjModel::~CObjModel()
{
	delete m_pVertex;
	m_pVertex = nullptr;
}

void CObjModel::Initialize()
{
	m_VertexNum = 0;
	m_FaceNum = 0;

	FILE * fp;
	char str[1024];
	fopen_s(&fp, "TestObject.obj", "r");

	bool IsFail = fp == NULL;
	if (IsFail) {
		std::cout << "파일 찾기 실패" << std::endl;
		return;
	}

	//파일 읽기
	//이 파일의 정점의 개수, 면의 개수를 구한다.
	//feof 파일의 끝을 만날 때까지 루프
	while (!feof(fp)){
		fgets(str, 1024, fp);

		bool IsVertex = str[0] == 'v' && str[1] == ' ';
		bool IsFace = str[0] == 'f' && str[1] == ' ';
		
		if (IsVertex) {
			m_VertexNum += 1;
		}
		else if (IsFace) {
			m_FaceNum += 1;
		}

	}

	fclose(fp);
	fp = NULL;
	
	//구한 개수를 동적할당 한다.
	//동적할당: 배열
	m_pVertex = new CObjVertex[m_VertexNum];
	m_pFace = new CObjFace[m_FaceNum];

	std::cout << m_FaceNum << std::endl << std::endl;

	fopen_s(&fp, "TestObject.obj", "rt");
	int VertexIndex = 0;
	int FaceIndex = 0;

	//각 메모리에 정보를 입력한다.
	while (!feof(fp)) {
		int res = fscanf(fp, "%s", str);

		if (res == EOF) break;

		bool IsVertex = strcmp(str, "v") == 0;
		bool IsFace = strcmp(str, "f") == 0;
		if (IsVertex) {
			float x = -1.f;
			float y = -1.f;
			float z = -1.f;

			fscanf(fp, "%f %f %f\n", &x, &y, &z);

			m_pVertex[VertexIndex].SetX(x);
			m_pVertex[VertexIndex].SetY(y);
			m_pVertex[VertexIndex].SetZ(z);

			VertexIndex += 1;
		}
		if (IsFace) {
			int index[4] = { -1, -1, -1, -1 };
			int nouse = 0;

			fscanf(fp, "%d/%d %d/%d %d/%d %d/%d\n",
				&index[0], &nouse,
				&index[1], &nouse,
				&index[2], &nouse,
				&index[3], &nouse
				);

			m_pFace[FaceIndex].SetIndex_0(index[0]);
			m_pFace[FaceIndex].SetIndex_1(index[1]);
			m_pFace[FaceIndex].SetIndex_2(index[2]);
			m_pFace[FaceIndex].SetIndex_3(index[3]);
			m_pFace[FaceIndex].InitVertexNum();

			m_pFace[FaceIndex].ShowData();

			FaceIndex += 1;
		}
		
	}
	fclose(fp);
}

void CObjModel::LoadObj(const char * filename)
{

}

void CObjModel::Render()
{
	for (int Face_index = 0; Face_index < m_FaceNum; ++Face_index) {
		glBegin(GL_LINE_LOOP);

		int Vertex_in_Face = m_pFace[Face_index].GetVertexNum();
		for (int Vertex_Num = 0; Vertex_Num < Vertex_in_Face; ++Vertex_Num) {
			int vertex_index = m_pFace[Face_index].GetIndex(Vertex_Num);
			
			float y = m_pVertex[vertex_index - 1].GetY();
			float x = m_pVertex[vertex_index - 1].GetX();
			float z = m_pVertex[vertex_index - 1].GetZ();

			glVertex3f(x, y, z);
		}

		glEnd();
	}
}
