#pragma once
class CLighting
{
	CVector3D<GLfloat> m_AmbientLight;
	CVector3D<GLfloat> m_DiffuseLight;
	CVector3D<GLfloat> m_SpecularLight;
	CVector3D<GLfloat> m_specref;

	CVector3D<GLfloat> m_LightPos;

	GLenum GL_LIGHTx{ 0 };

private:


public:
	CLighting(const int& gl_lightx);
	~CLighting();

	void Initilaize(
		const CVector3D<GLfloat>& ambient,
		const CVector3D<GLfloat>& diffuse,
		const CVector3D<GLfloat>& specular,
		const CVector3D<GLfloat>& specref
	);

	void SettingLight();

	void Enable();
	void Disable();
};