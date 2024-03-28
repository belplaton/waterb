#include "priorqueue.h"

using namespace std;

void binary_priority_queue::resize(size_t new_physical_size)
{
	auto new_elements = new node[new_physical_size];
	auto new_virtual_size = 0;
	auto new_virtual_size = min(_virtual_size, new_physical_size);

	for (auto i = 0; i < new_virtual_size; i++)
	{
		new_elements[i] = _elements[i];
	}

	delete[] _elements;
	_elements = new_elements;
	_physical_size = new_physical_size;
	_virtual_size = new_virtual_size;
}

size_t binary_priority_queue::parent(size_t index) const
{
	return (index - 1) / 2;
}

size_t binary_priority_queue::left(size_t index) const
{
	return 2 * index + 1;
}

size_t binary_priority_queue::right(size_t index) const
{
	return 2 * index + 2;
}

void binary_priority_queue::heapify_up(size_t index)
{
	while (index > 0 && _elements[index].priority < _elements[parent(index)].priority) {
		swap(_elements[index], _elements[parent(index)]);
		index = parent(index);
	}
}

void binary_priority_queue::heapify_down(size_t index)
{
	while (true)
	{
		auto min_index = index;
		auto left_index = left(index);
		auto right_index = right(index);

		// Левый приоритет
		if (left_index < _virtual_size
			&& _elements[left_index].priority < _elements[min_index].priority)
		{
			min_index = left_index;
		}

		// Правый приоритет
		if (right_index < _virtual_size
			&& _elements[right_index].priority < _elements[min_index].priority)
		{
			min_index = right_index;
		}

		// Помещение элемента с минимальным приоритетом выше
		if (index != min_index)
		{
			swap(_elements[index], _elements[min_index]);
			index = min_index;
			continue;
		}

		break;
	}
}

binary_priority_queue::binary_priority_queue()
{
	_virtual_size = 0;
	_physical_size = 16;
	_elements = new node[_physical_size];
}

binary_priority_queue::binary_priority_queue(const binary_priority_queue& other)
{
	_virtual_size = other._virtual_size;
	_physical_size = other._physical_size;
	_elements = new node[_physical_size];
	for (auto i = 0; i < _virtual_size; i++)
	{
		_elements[i] = other._elements[i];
	}
}

binary_priority_queue& binary_priority_queue::operator = (const binary_priority_queue& other)
{
	if (this != &other)
	{
		delete[] _elements;
		_virtual_size = other._virtual_size;
		_physical_size = other._physical_size;
		_elements = new node[_virtual_size];
		for (auto i = 0; i < _virtual_size; i++)
		{
			_elements[i] = other._elements[i];
		}
	}

	return *this;
}

binary_priority_queue::~binary_priority_queue()
{
	delete[] _elements;
}

void binary_priority_queue::enqueue(const char* value, size_t priority)
{
	if (_virtual_size == _physical_size)
	{
		resize(_physical_size * 2);
	}

	_elements[_virtual_size].value = strdup(value);
	_elements[_virtual_size].priority = priority;
	heapify_up(_virtual_size);
	_virtual_size++;
}

char* binary_priority_queue::dequeue_min()
{
	if (_virtual_size == 0)
	{
		return nullptr;
	}

	char* minValue = strdup(_elements[0].value);
	delete[] _elements[0].value;
	_virtual_size--;
	_elements[0] = _elements[_virtual_size];
	heapify_down(0);
	return minValue;
}

char* binary_priority_queue::peek_min() const
{
	if (_virtual_size == 0)
	{
		return nullptr;
	}

	return _elements[0].value;
}

void binary_priority_queue::merge(const binary_priority_queue& other)
{
	auto new_size = _virtual_size + other._virtual_size;
	if (new_size > _physical_size)
	{
		resize(new_size);
	}

	for (auto i = 0; i < other._virtual_size; i++)
	{
		_elements[_virtual_size + i] = other._elements[i];
	}

	_virtual_size = new_size;	

	// Поскольку каждый новый уровень листьев дерева это *2
	for (auto i = _virtual_size / 2; i > 0; i--)
	{
		heapify_down(i - 1);
	}
}