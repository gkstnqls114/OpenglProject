#pragma once
class CLighting
{
	CVector3D<GLfloat, 3> m_AmbientLight;
	CVector3D<GLfloat, 3> m_DiffuseLight;
	CVector3D<GLfloat, 3> m_SpecularLight;
	CVector3D<GLfloat, 3> m_specref;

	CVector3D<GLfloat, 4> m_LightPos;

	GLenum GL_LIGHTx{ 0 };

private:


public:
	CLighting(const int& gl_lightx);
	~CLighting();

	void Initilaize(
		const CVector3D<GLfloat, 3>& ambient,
		const CVector3D<GLfloat, 3>& diffuse,
		const CVector3D<GLfloat, 3>& specular,
		const CVector3D<GLfloat, 3>& specref
	);

	void SettingLight();

	void Enable();
	void Disable();
};