#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

// Encoder which based on RC4 alghoritm
class encoder
{

private:

	const int _stateSize = 256;

	std::vector<unsigned char> _key;

	// RC4
	void rc4(std::ifstream* inputFile, std::ofstream* outputFile);

	// Key-Scheduling Algorithm
	std::vector<unsigned char> ksa(std::vector<unsigned char> key);

	// Pseudo-Random Generator Alghoritm
	unsigned char prga(std::vector<unsigned char>* state, int* i, int* j);

public:

	// �����������
	encoder(unsigned char const* keyBytes, size_t keySize);

	// ����������
	~encoder();

	// ����������� ������������
	encoder(const encoder& other);

	// ����������� ��� ������������� ������
	void encode(const std::string& inputFilePath, const std::string& outputFilePath, bool encrypt);

	// ������� ��� �����
	inline void set_key(unsigned char const* keyBytes, size_t keySize);
};
