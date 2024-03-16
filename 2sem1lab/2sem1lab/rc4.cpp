#include "rc4.h"

using namespace std;

class Encoder
{

private:

	const int _stateSize = 256;

	vector<unsigned char> _key;

	void rc4(ifstream *inputFile, ofstream *outputFile)
	{
		int i = 0;
		int j = 0;
		char ch;

		// Create Encrypt State.
		vector<unsigned char> state = ksa(_key);

		// XOR all symbols to output file.
		while ((*inputFile).get(ch))
		{
			ch ^= prga(&state, &i, &j);

			(*outputFile).put(ch);
		}
	}

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

	unsigned char prga(vector<unsigned char> *state, int *i, int *j)
	{
		*i = (*i + 1) % _stateSize;
		*j = (*j + (*state)[*i]) % _stateSize;

		swap((*state)[*i], (*state)[*j]);

		unsigned char pseudoRandomIndex = (*state)[((*state)[*i] + (*state)[*j]) % _stateSize];

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

	void encode(string inputFilePath, const string& outputFilePath, bool encrypt)
	{
		if (inputFilePath == outputFilePath)
		{
			cerr << "Error. You should use different files." << endl;
			return;
		}

		// Open input and output files.
		ifstream inputFile(inputFilePath, ios::binary);
		ofstream outputFile(outputFilePath, ios::binary | ios::trunc);

		if (!inputFile.is_open())
		{
			cerr << "Error with opening input file." << endl;
			return;
		}

		if (!outputFile.is_open())
		{
			cerr << "Error with opening output file." << endl;
			return;
		}

		// Same alghoritms.
		if (encrypt)
		{
			rc4(&inputFile, &outputFile);
		}
		else
		{
			rc4(&inputFile, &outputFile);
		}

		// Make closed opened files.
		inputFile.close();
		outputFile.close();
	}

	inline void set_key(unsigned char const* keyBytes, size_t keySize)
	{
		_key.assign(keyBytes, keyBytes + keySize);
	}
};