#include "rc4.h"

using namespace std;

class Encoder
{

private:

	vector<unsigned char> key;

	void rc4(vector<unsigned char>& data)
	{

	}

public:

	Encoder(unsigned char const * keyBytes, size_t keySize)
	{
		key.assign(keyBytes, keyBytes + keySize);
	}

	~Encoder()
	{
		key.clear();
	}

	Encoder(const Encoder& other)
	{
		key = other.key;
	}

	void encode(const char* inputFilePath, const char* outputFilePath, bool encrypt)
	{
		ifstream inputFile(inputFilePath, ios::binary);
		ofstream outputFile(outputFilePath, ios::binary);

		if (!inputFile.is_open())
		{
			cerr << "Error with openingg input file." << endl;
			return;
		}

		if (!outputFile.is_open())
		{
			cerr << "Error with openingg output file." << endl;
			return;
		}

		if (encrypt)
		{

		}
		else
		{

		}

		inputFile.close();
		outputFile.close();
	}

	inline void set_key(unsigned char const* keyBytes, size_t keySize)
	{
		key.assign(keyBytes, keyBytes + keySize);
	}
};