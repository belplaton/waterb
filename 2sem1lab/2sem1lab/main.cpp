#include "rc4.cpp"

using namespace std;

int main()
{
    unsigned char key[] = { 0x01, 0x23, 0x45, 0x67, 0x89 }; // Example key
    size_t keySize = sizeof(key) / sizeof(key[0]);

    Encoder encoder(key, keySize);

    // Encrypting a file
    encoder.encode("input.txt", "encrypted.txt", true);
    cout << "File encrypted successfully!" << endl;

    // Decrypting the encrypted file
    encoder.encode("encrypted.txt", "decrypted.txt", false);
    cout << "File decrypted successfully!" << endl;

    return 0;
}