#include "rc4.cpp"
#include "logval.cpp"

using namespace std;

void rc4_check();
void logval();

int main()
{
    // rc4_check();
    logval();

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

void logval()
{
    logical_values_array a(14);
    logical_values_array b(28);

    cout << "a = " << a.get_value() << ", b = " << b.get_value() << endl;
    cout << "a AND b = " << a.conjunction(b).get_value() << endl;
    cout << "a OR b = " << a.disjunction(b).get_value() << endl;
    cout << "a IMPLIES b = " << a.implication(b).get_value() << endl;
    cout << "a COIMPLIES b = " << a.coimplication(b).get_value() << endl;
    cout << "a MODULO_SUM b = " << a.modulo_sum(b).get_value() << endl;
    cout << "a EQUIVALENT b = " << a.equivalence(b).get_value() << endl;
    cout << "a PIERCE_ARROW b = " << a.pierce_arrow(b).get_value() << endl;
    cout << "a SHEFFER_STROKE b = " << a.sheffer_stroke(b).get_value() << endl;

    cout << "a equals b: " << logical_values_array::equals(a, b) << endl;

    cout << "Bit at position 2 in b: " << b.get_bit(2) << endl;

    int string_length = sizeof(unsigned char) * 8;
    char* binary_string = (char*)malloc(string_length + 1);

    a.to_binary_string(binary_string, string_length);

    cout << "Binary representation of a: " << binary_string << endl;

    free(binary_string);
}