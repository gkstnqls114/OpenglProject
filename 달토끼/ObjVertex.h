#pragma once
class CObjVertex
{
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };

public:
	CObjVertex();
	~CObjVertex();

	void SetX(const float& a) { x = a; }
	void SetY(const float& b) { y = b; }
	void SetZ(const float& c) { z = c; }
	void SetXYZ(
		const float a,
		const float b,
		const float c
	)
	{
		x = a;
		y = b;
		z = c;
	}

	const float GetX() const { return x; }
	const float GetY() const { return y; }
	const float GetZ() const { return z; }

	void ShowData()
	{
		std::cout << x << ", " << y << ", " << z << std::endl;
	}
};

