#include "rc4.cpp"

using namespace std;

void rc4_check();

int main()
{
    rc4_check();

    return 0;
}

void rc4_check()
{
    cout << "[First exercise --]\n" << endl;

    unsigned char key[] = { 0x01, 0x23, 0x45, 0x67, 0x89 };
    size_t keySize = sizeof(key) / sizeof(key[0]);

    Encoder encoder(key, keySize);

    encoder.encode("rc4_input.txt", "rc4_encrypted.txt", true);
    cout << "File \"rc4_input.txt\" encrypted to \"rc4_encrypted.txt\" successfully!" << endl;

    encoder.encode("rc4_encrypted.txt", "rc4_decrypted.txt", false);
    cout << "File \"rc4_encrypted.txt\" decrypted to \"rc4_decrypted.txt\" successfully!" << endl;

    cout << "\n[-- First exercise]" << endl;
}