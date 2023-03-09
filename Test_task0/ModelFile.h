#pragma once

#include <string>
#include <cassert>
#include <iostream>

/*������ ���� ��������� �������� ��� �������� ��������� ���������, �� �������� � uv
���� �� ���� ������ ������� ������� �� ��������� ������������, ����������� ����������� (��� � ���������� ��� move ���������) � �������� <<*/
struct Vector3
{
	Vector3() :
		x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) :
		x(x), y(y), z(z) {}
	float x;
	float y;
	float z;
};

struct Vector2
{
	Vector2() :
		x(0), y(0) {}
	Vector2(float x, float y) :
		x(x), y(y) {}

	float x;
	float y;
};

//��������� ��� �������� ���� ������ ������
struct Mesh
{
	~Mesh() {
		if (vertecis) delete[] vertecis;
		if (normals) delete[] normals;
		if (uvs) delete[] uvs;
		if (indecis) delete[] indecis;
	}

	//�������� ������ � ����� ������� ������ ����� �� ���������� assimp, ������� � ������� �����������.
	size_t nVertecis = 0;

	//��� ������� ����� ���� ������������ std::vector, �� ��� ������ ����� ������� ��� �������� � ������������� ����
	//�� ����� ������ � ������� ������������ ����� �������, ������ ���� ���, ��� 
	Vector3* vertecis = nullptr;
	Vector3* normals = nullptr;
	Vector2* uvs = nullptr;

	size_t nIndecis = 0;
	uint32_t* indecis = nullptr;

	std::string textureName = "";

	void clear() 
	{
		if (vertecis) delete[] vertecis;
		if (normals) delete[] normals;
		if (uvs) delete[] uvs;
		if (indecis) delete[] indecis;

		nVertecis = nIndecis = 0;

		textureName = "";
	}

	void printDebug() 
	{
		std::cout << "Vertecis " << nVertecis << ":\n";

		for (size_t i = 0; i < nVertecis; i++)
		{
			std::cout << vertecis[i].x << " "
				<< vertecis[i].y << " "
				<< vertecis[i].z << "\n";

			std::cout << normals[i].x << " "
				<< normals[i].y << " "
				<< normals[i].z << "\n";

			std::cout << uvs[i].x << " "
				<< uvs[i].y << "\n\n";
		}

		std::cout << "Indecis " << nIndecis << ":\n";
		for (size_t i = 0; i < nIndecis; i++)
		{
			std::cout << indecis[i] << " ";
		}
		std::cout << "\n";

		std::cout << "Texture: " << textureName << "\n";
	}
};


/*��� ��� � ���� ���������� ModelFile ������ �� ������, �� ������ ������ static � �������� ����������� � private,
����� ����� �� ������ ��������� ������*/
class ModelFile
{
public:
	static void readFromFile(const std::string& fileName, Mesh& mesh);

	static void writeToFile(const std::string& fileName, const Mesh& mesh);
private:
	ModelFile() {};
};

