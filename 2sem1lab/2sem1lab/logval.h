class logical_values_array
{

private:

	unsigned int _value;

public:

	// �����������
	logical_values_array(unsigned int value = 0);

	inline unsigned int get_value() const;
	// ��������
	inline logical_values_array inversion() const;

	// ����������
	inline logical_values_array conjunction(const logical_values_array& other) const;

	// ����������
	inline logical_values_array disjunction(const logical_values_array& other) const;

	// ����������
	inline logical_values_array implication(const logical_values_array& other) const;

	// ������������
	inline logical_values_array coimplication(const logical_values_array& other) const;

	// �������� �� ������ 2
	inline logical_values_array modulo_sum(const logical_values_array& other) const;

	// ��������������
	inline logical_values_array equivalence(const logical_values_array& other) const;

	// ������� �����
	inline logical_values_array pierce_arrow(const logical_values_array& other) const;

	// ����� �������
	inline logical_values_array sheffer_stroke(const logical_values_array& other) const;

	// �������� ���� �� �������
	inline bool get_bit(int posisiton) const;

	// �������� ��� ����� �� ��������������
	inline static bool equals(const logical_values_array& a, const logical_values_array& b);

	// ������������� � ������
	void to_string(char* binary_string, int string_size) const;
};