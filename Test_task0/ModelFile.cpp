#include "ModelFile.h"

#include <fstream>

void ModelFile::readFromFile(const std::string& fileName, Mesh& mesh)
{
	/*Как я уже описывал в header файле, скорее всего данная функция будет вызываться внутри одно объекта модели.
	Соответственно она будет вызываться один раз для Mesh, 
	поэтому не будет происходить перевыделения памяти,
	Однако всё равно предотвратим возможную утечку памяти.*/
	mesh.clear();

	std::ifstream file;
	file.open(fileName, std::ios::in |
		std::ios::binary);

	file.read(static_cast<char*>(static_cast<void*>(&mesh.nVertecis)),
		sizeof(mesh.nVertecis));

	mesh.vertecis = new Vector3[mesh.nVertecis];
	mesh.normals = new Vector3[mesh.nVertecis];
	mesh.uvs = new Vector2[mesh.nVertecis];

	file.read(static_cast<char*>(static_cast<void*>(mesh.vertecis)),
		sizeof(Vector3) * mesh.nVertecis);

	file.read(static_cast<char*>(static_cast<void*>(mesh.normals)),
		sizeof(Vector3) * mesh.nVertecis);

	file.read(static_cast<char*>(static_cast<void*>(mesh.uvs)),
		sizeof(Vector2) * mesh.nVertecis);

	file.read(static_cast<char*>(static_cast<void*>(&mesh.nIndecis)),
		sizeof(mesh.nIndecis));

	mesh.indecis = new uint32_t[mesh.nIndecis];

	file.read(static_cast<char*>(static_cast<void*>(mesh.indecis)),
		sizeof(uint32_t) * mesh.nIndecis);

	size_t strSize;
	file.read(static_cast<char*>(static_cast<void*>(&strSize)),
		sizeof(strSize));

	char* str = new char[strSize];
	file.read(str,
		sizeof(char) * strSize);

	mesh.textureName = std::string(str, strSize);

	delete[] str;

	file.close();
}

void ModelFile::writeToFile(const std::string& fileName, const Mesh& mesh)
{
	//Вылетаем если указатели не заполнены (в идеале тут можно добавить exeption, но для ускорения написания поставил assert)
	assert(mesh.vertecis && mesh.normals && mesh.uvs && mesh.indecis);

	std::ofstream file;
	file.open(fileName, std::ios::out |
		std::ios::binary |
		std::ios::trunc);

	file.write(static_cast<const char*>(static_cast<const void*>(&mesh.nVertecis)),
		sizeof(mesh.nVertecis));

	file.write(static_cast<const char*>(static_cast<const void*>(mesh.vertecis)),
			sizeof(Vector3) * mesh.nVertecis);

	file.write(static_cast<const char*>(static_cast<const void*>(mesh.normals)),
		sizeof(Vector3) * mesh.nVertecis);

	file.write(static_cast<const char*>(static_cast<const void*>(mesh.uvs)),
		sizeof(Vector2) * mesh.nVertecis);


	file.write(static_cast<const char*>(static_cast<const void*>(&mesh.nIndecis)),
		sizeof(mesh.nIndecis));

	file.write(static_cast<const char*>(static_cast<const void*>(mesh.indecis)),
		sizeof(uint32_t) * mesh.nIndecis);
	
	size_t strSize = mesh.textureName.size();
	file.write(static_cast<const char*>(static_cast<const void*>(&strSize)),
		sizeof(strSize));

	file.write(static_cast<const char*>(static_cast<const void*>(mesh.textureName.c_str())),
		sizeof(char) * strSize);

	file.close();
}
