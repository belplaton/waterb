#pragma once

#include <utility>
#include <cstring>

class binary_priority_queue
{

private:

	struct node
	{
		char* value;
		size_t priority;
	};

	node* _elements;
	size_t _virtual_size;
	size_t _physical_size;

	// Перевыделение памяти
	void resize(size_t new_physical_size);

	// Получение родителського индекса
	size_t parent(size_t index) const;

	// Получение дочернего левеого индекса
	size_t left(size_t index) const;

	// Получение дочернего правого индекса
	size_t right(size_t index) const;

	// Сортировка "снизу-вверх"
	void heapify_up(size_t index);

	// Сортировка "сверху-вниз"
	void heapify_down(size_t index);

public:

	// Дефолтный конструктор
	binary_priority_queue();

	// Конструктор копирования
	binary_priority_queue(const binary_priority_queue& other);

	// Оператор присваивания
	binary_priority_queue& operator = (const binary_priority_queue& other);

	// Деструктор
	~binary_priority_queue();

	// Добавление элемента
	void enqueue(const char* value, size_t priority);

	// Удаление элемента с минимальным приоритетом
	char* dequeue_min();

	// Элемент с минимальным приоритетом
	char* peek_min() const;

	// Слияние двух бинарных приоритетных очередей
	void merge(const binary_priority_queue& other);

};