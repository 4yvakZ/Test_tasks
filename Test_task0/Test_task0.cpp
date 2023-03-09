// Test_task0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ModelFile.h"

int main()
{
    Mesh verticalPlane;

    size_t nVertecis = 8;
    Vector3* vertecis = new Vector3[nVertecis];
    vertecis[0] = Vector3{ 1.0f, 1.0f, 0.0f };
    vertecis[1] = Vector3{ -1.0f, 1.0f, 0.0f };
    vertecis[2] = Vector3{ -1.0f, -1.0f, 0.0f };
    vertecis[3] = Vector3{ 1.0f, -1.0f, 0.0f };

    Vector3* normals = new Vector3[nVertecis];
    normals[0] = Vector3{ 0.0f, 0.0f, -1.0f };
    normals[1] = Vector3{ 0.0f, 0.0f, -1.0f };
    normals[2] = Vector3{ 0.0f, 0.0f, -1.0f };
    normals[3] = Vector3{ 0.0f, 0.0f, -1.0f };

    Vector2* uvs = new Vector2[nVertecis];
    uvs[0] = Vector2{ 0.0f, 0.0f };
    uvs[1] = Vector2{ 1.0f, 0.0f };
    uvs[2] = Vector2{ 1.0f, 1.0f };
    uvs[3] = Vector2{ 0.0f, 1.0f };

    size_t nIndecis = 6;
    //треугольники рисуются по часовой
    uint32_t* indecis = new uint32_t[nIndecis];
    indecis[0] = 0;
    indecis[1] = 2;
    indecis[2] = 1;
    indecis[3] = 0;
    indecis[4] = 3;
    indecis[5] = 2;

    verticalPlane.nVertecis = nVertecis;
    verticalPlane.vertecis = vertecis;
    verticalPlane.normals = normals;
    verticalPlane.uvs = uvs;
    verticalPlane.nIndecis = nIndecis;
    verticalPlane.indecis = indecis;
    verticalPlane.textureName = "texture.png";

    verticalPlane.printDebug();

    ModelFile::writeToFile("testModel.asset", verticalPlane);

    Mesh fromFileMesh;

    ModelFile::readFromFile("testModel.asset", fromFileMesh);

    fromFileMesh.printDebug();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
