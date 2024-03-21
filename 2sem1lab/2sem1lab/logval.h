class logical_values_array
{

private:

	unsigned int _value;

public:

	// Конструктор
	logical_values_array(unsigned int value = 0);

	unsigned int get_value() const;
	// Инверсия
	logical_values_array inversion() const;

	// Конъюнкция
	logical_values_array conjunction(const logical_values_array& other) const;

	// Дизъюнкция
	logical_values_array disjunction(const logical_values_array& other) const;

	// Имплекация
	logical_values_array implication(const logical_values_array& other) const;

	// Коимпликация
	logical_values_array coimplication(const logical_values_array& other) const;

	// Сложение по модулю 2
	logical_values_array modulo_sum(const logical_values_array& other) const;

	// Эквиалентность
	logical_values_array equivalence(const logical_values_array& other) const;

	// Стрелка Пирса
	logical_values_array pierce_arrow(const logical_values_array& other) const;

	// Штрих Шиффера
	logical_values_array sheffer_stroke(const logical_values_array& other) const;

	// Значение бита по позиции
	bool get_bit(int posisiton) const;

	// Сравнить два числа на эквиалентность
	static bool equals(const logical_values_array& a, const logical_values_array& b);

	// Преобразовать в строку
	void to_string(char* binary_string, int string_size) const;
};
