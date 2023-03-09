#pragma once

#include <string>
#include <cassert>
#include <iostream>

/*—оздал свои структуры векторов дл€ хранени€ координат вертексов, их нормалей и uv
≈сли бы было больше времени добавил бы операторы присваивани€, конструктор копировани€ (оба с вариаци€ми дл€ move семантики) и оператор <<*/
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

//—труктура дл€ хранени€ всех данных модели
struct Mesh
{
	~Mesh() {
		if (vertecis) delete[] vertecis;
		if (normals) delete[] normals;
		if (uvs) delete[] uvs;
		if (indecis) delete[] indecis;
	}

	//’ранение данных в таком формате идейно вз€то из библиотеки assimp, которую € недавно использовал.
	size_t nVertecis = 0;

	//“ут конечно можно было использовать std::vector, но нет ничего лучше массива дл€ простоты и оптимальности кода
	//¬сЄ равно модель с большой веро€тностью будет создана, только один раз, что 
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


/*“ак как в моей реализации ModelFile ничего не хранит, то сделал методы static и поместил конструктор в private,
чтобы никто не создал экземпл€р класса*/
class ModelFile
{
public:
	static void readFromFile(const std::string& fileName, Mesh& mesh);

	static void writeToFile(const std::string& fileName, const Mesh& mesh);
private:
	ModelFile() {};
};

