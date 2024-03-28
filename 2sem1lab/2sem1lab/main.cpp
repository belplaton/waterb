#include "rc4.h"
#include "logval.h"
#include "comval.h"
#include "matrix.h"
#include "priorqueue.h"

using namespace std;

void rc4_check();
void logval();
void comval();
void matrix_test();
void queue_test();

int main()
{
    rc4_check();
    logval();
    comval();
    matrix_test();
    queue_test();

    return 0;
}

void rc4_check()
{
    cout << "[First exercise --]\n" << endl;

    unsigned char key[] = { 0x01, 0x23, 0x45, 0x67, 0x89 };
    size_t keySize = sizeof(key) / sizeof(key[0]);

    encoder encoder(key, keySize);

    encoder.encode("rc4_input.txt", "rc4_encrypted.txt", true);
    cout << "File \"rc4_input.txt\" encrypted to \"rc4_encrypted.txt\" successfully!" << endl;

    encoder.encode("rc4_encrypted.txt", "rc4_decrypted.txt", false);
    cout << "File \"rc4_encrypted.txt\" decrypted to \"rc4_decrypted.txt\" successfully!" << endl;

    cout << "\n[-- First exercise]" << endl;
}

void logval()
{
    cout << "[Second exercise --]\n" << endl;

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

    a.to_string(binary_string, string_length);

    cout << "Binary representation of a: " << binary_string << endl;

    free(binary_string);

    cout << "\n[-- Second exercise]" << endl;
}

void comval()
{
    cout << "[Third exercise --]\n" << endl;

    complex_value z1(7, 8);
    complex_value z2(-9, 6);

    cout << "Sum: " << z1 + z2 << endl;
    cout << "Dif: " << z1 - z2 << endl;
    cout << "Mult: " << z1 * z2 << endl;
    cout << "Div: " << z1 / z2 << endl;

    cout << "Modulus of z1: " << z1.modulus() << endl;
    cout << "Argument of z2: " << z2.argument() << endl;

    cout << "\n[-- Third exercise]" << endl;
}

void matrix_test()
{
    cout << "[Fourth exercise --]\n" << endl;

    matrix matrix1(3, 3,
        vector<double> { 3, 2, 1 },
        vector<double> { -2, 3, 1 },
        vector<double> { 4, 4, 3 });

    cout << "Original Matrix (first):\n" << matrix1 << endl;

    matrix matrix2(matrix1);

    cout << "Copied Matrix (second):\n" << matrix2 << endl;

    matrix matrix3 = matrix1 + (matrix2 * 0.5);

    cout << "first * (second * 0.5) = third:\n" << matrix3 << '\n' << endl;

    matrix matrix4 = matrix3 * matrix1;

    cout << "third * first = fourth:\n" << matrix4 << '\n' << endl;

    matrix matrix5 = matrix1.transpose();

    cout << "Transposed first matrix:\n" << matrix5 << '\n' << endl;

    matrix matrix6 = matrix1.inverse();

    cout << "Inversed first matrix:\n" << matrix6 << '\n' << endl;

    cout << "Determinant of first matrix: " << matrix1.determinant() << endl;

    cout << "\n[-- Fourth exercise]" << endl;
}

void queue_test()
{
    cout << "[Fifth exercise --]\n" << endl;

    binary_priority_queue queue1;
    queue1.enqueue("Hewwo", 6);
    queue1.enqueue("UwU", 3);

    binary_priority_queue queue2;
    queue2.enqueue("Meow", 3);
    queue2.enqueue("Rawr~", 4);

    queue1.merge(queue2);

    cout << "Dequeued Queue1: " << queue1.dequeue_min() << endl;
    cout << "Dequeued Queue1: " << queue1.dequeue_min() << endl;
    cout << "Dequeued Queue1: " << queue1.dequeue_min() << endl;
    cout << "Dequeued Queue1: " << queue1.dequeue_min() << endl;
    cout << "Dequeued Queue2: " << queue2.dequeue_min() << endl;
    cout << "Dequeued Queue2: " << queue2.dequeue_min() << endl;

    cout << "\n[-- Fifth exercise]" << endl;
}