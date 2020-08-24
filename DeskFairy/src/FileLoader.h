#pragma once

#include <string>

using Bytes = unsigned char;

//�ļ�������
class FileLoader
{
public:
	static Bytes* Load(const std::string filePath, unsigned int* outSize);

	static void Release(Bytes* byteData);
};

