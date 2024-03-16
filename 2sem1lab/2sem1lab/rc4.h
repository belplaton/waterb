#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

// Encoder which based on RC4 alghoritm
class Encoder
{

private:

	const int _stateSize = 256;

	vector<unsigned char> _key;

	// RC4
	void rc4(ifstream* inputFile, ofstream* outputFile);

	// Key-Scheduling Algorithm
	vector<unsigned char> ksa(vector<unsigned char> key);

	// Pseudo-Random Generator Alghoritm
	unsigned char prga(vector<unsigned char>* state, int* i, int* j);

public:

	// �����������
	Encoder(unsigned char const* keyBytes, size_t keySize);

	// ����������
	~Encoder();

	// ����������� ������������
	Encoder(const Encoder& other);

	// ����������� ��� ������������� ������
	void encode(string inputFilePath, const string& outputFilePath, bool encrypt);

	// ������� ��� �����
	inline void set_key(unsigned char const* keyBytes, size_t keySize);
};