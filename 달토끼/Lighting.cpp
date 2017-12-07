#include "pch.h"
#include "Lighting.h"


CLighting::CLighting(const int& gl_lightx)
{
	GL_LIGHTx = gl_lightx;
}


CLighting::~CLighting()
{
}

void CLighting::Initilaize(
	const CVector3D<GLfloat, 3> & ambient,
	const CVector3D<GLfloat, 3> & diffuse,
	const CVector3D<GLfloat, 3> & specular,
	const CVector3D<GLfloat, 3> & specref)
{
	m_AmbientLight = ambient;
	m_DiffuseLight = diffuse;
	m_SpecularLight = specular;
	m_specref = specref;
}

void CLighting::SettingLight()
{
	glLightfv(GL_LIGHTx, GL_AMBIENT, m_AmbientLight.GetVector());
	glLightfv(GL_LIGHTx, GL_DIFFUSE, m_DiffuseLight.GetVector());
	glLightfv(GL_LIGHTx, GL_SPECULAR, m_SpecularLight.GetVector());
	glLightfv(GL_LIGHTx, GL_POSITION, m_LightPos.GetVector());
}

void CLighting::Enable()
{
	glEnable(GL_LIGHTx);
}

void CLighting::Disable()
{
	glDisable(GL_LIGHTx);
}
