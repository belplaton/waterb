#include "rc4.h"

using namespace std;

class Encoder
{

private:

	const int _stateSize = 256;

	vector<unsigned char> _state;

	void rc4(vector<unsigned char>& data)
	{

	}

	vector<unsigned char> ksa(unsigned char const* keyBytes, size_t keySize)
	{
		vector<unsigned char> state(_stateSize);
		for (int n = 0; n < _stateSize; n++)
		{
			state[n] = n;
		}

		int j = 0;
		for (int i = 0; i < _stateSize; i++)
		{
			j = (j + state[i] + keyBytes[i % keySize]) % _stateSize;
			swap(state[i], state[j]);
		}

		return state;
	}

public:

	Encoder(unsigned char const * keyBytes, size_t keySize)
	{
		_state = ksa(keyBytes, keySize);
	}

	~Encoder()
	{
		_state.clear();
	}

	Encoder(const Encoder& other)
	{
		_state = other._state;
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
		_key.assign(keyBytes, keyBytes + keySize);
		_state = ksa(_key);
	}
};