#include "rc4.h"

using namespace std;

class Encoder
{

private:

	const int _stateSize = 256;

	vector<unsigned char> _key;

	void rc4(vector<unsigned char>& data)
	{
		int i = 0;
		int j = 0;

		vector<unsigned char> state = ksa(_key);

		for (int n = 0; n < data.size(); n++)
		{
			data[n] ^= prga(&state, &i, &j);
		}
	}

	// Key-Scheduling Algorithm
	vector<unsigned char> ksa(vector<unsigned char> key)
	{
		vector<unsigned char> state(_stateSize);

		for (int n = 0; n < _stateSize; n++)
		{
			state[n] = n;
		}

		int j = 0;

		for (int i = 0; i < _stateSize; i++)
		{
			j = (j + state[i] + key[i % key.size()]) % _stateSize;
			swap(state[i], state[j]);
		}

		return state;
	}

	// Pseudo-Random Generator Alghoritm
	unsigned char prga(vector<unsigned char> *state, int *i, int *j)
	{
		*i = (*i + 1) % _stateSize;
		*j = (*j + (*state)[*i]) % _stateSize;

		swap(state[*i], state[*j]);

		int pseudoRandomIndex = (*state)[((*state)[*i] + (*state)[*j]) % _stateSize];

		return pseudoRandomIndex;
	}

public:

	Encoder(unsigned char const * keyBytes, size_t keySize)
	{
		_key.assign(keyBytes, keyBytes + keySize);
	}

	~Encoder()
	{
		_key.clear();
	}

	Encoder(const Encoder& other)
	{
		_key = other._key;
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
	}
};