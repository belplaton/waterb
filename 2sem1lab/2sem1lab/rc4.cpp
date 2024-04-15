#include "rc4.h"

void encoder::rc4(std::ifstream *inputFile, std::ofstream *outputFile)
{
	if (inputFile == nullptr)
	{
		throw std::invalid_argument("Input file is null.");
	}

	if (outputFile == nullptr)
	{
		throw std::invalid_argument("Output file is null.");
	}

	int i = 0;
	int j = 0;
	char ch;

	// Create Encrypt State.
	std::vector<unsigned char> state = ksa(_key);

	// XOR all symbols to output file.
	while ((*inputFile).get(ch))
	{
		ch ^= prga(&state, &i, &j);

		(*outputFile).put(ch);
	}
}

std::vector<unsigned char> encoder::ksa(const std::vector<unsigned char>& key)
{
	std::vector<unsigned char> state(_stateSize);

	for (auto n = 0; n < _stateSize; n++)
	{
		state[n] = n;
	}

	int j = 0;

	for (auto i = 0; i < _stateSize; i++)
	{
		j = (j + state[i] + key[i % key.size()]) % _stateSize;
		std::swap(state[i], state[j]);
	}

	return state;
}

unsigned char encoder::prga(std::vector<unsigned char> *state, int *i, int *j)
{
	*i = (*i + 1) % _stateSize;
	*j = (*j + (*state)[*i]) % _stateSize;

	std::swap((*state)[*i], (*state)[*j]);

	unsigned char pseudoRandomIndex = (*state)[((*state)[*i] + (*state)[*j]) % _stateSize];

	return pseudoRandomIndex;
}

encoder::encoder(unsigned char const * keyBytes, size_t keySize)
{
	_key.assign(keyBytes, keyBytes + keySize);
}

encoder::~encoder()
{
	_key.clear();
}

encoder::encoder(const encoder& other) : encoder(other._key.data(), other._key.size())
{

}

encoder& encoder::operator = (const encoder& other)
{
	if (this == &other)
	{
		return *this;
	}

	_key = other._key;

	return *this;
}


void encoder::encode(const std::string& inputFilePath, const std::string& outputFilePath, bool encrypt)
{
	if (inputFilePath._Equal(outputFilePath))
	{
		std::cerr << "Error. You should use different files." << std::endl;
		return;
	}

	// Open input and output files.
	std::ifstream inputFile(inputFilePath, std::ios::binary);
	std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::trunc);

	if (!inputFile.is_open())
	{
		std::cerr << "Error with opening input file." << std::endl;
		return;
	}

	if (!outputFile.is_open())
	{
		std::cerr << "Error with opening output file." << std::endl;
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

inline void encoder::set_key(unsigned char const* keyBytes, size_t keySize)
{
	_key.assign(keyBytes, keyBytes + keySize);
}