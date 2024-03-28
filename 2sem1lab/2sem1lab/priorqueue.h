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

	// ������������� ������
	void resize(size_t new_physical_size);

	// ��������� ������������� �������
	size_t parent(size_t index) const;

	// ��������� ��������� ������� �������
	size_t left(size_t index) const;

	// ��������� ��������� ������� �������
	size_t right(size_t index) const;

	// ���������� "�����-�����"
	void heapify_up(size_t index);

	// ���������� "������-����"
	void heapify_down(size_t index);

public:

	// ��������� �����������
	binary_priority_queue();

	// ����������� �����������
	binary_priority_queue(const binary_priority_queue& other);

	// �������� ������������
	binary_priority_queue& operator = (const binary_priority_queue& other);

	// ����������
	~binary_priority_queue();

	// ���������� ��������
	void enqueue(const char* value, size_t priority);

	// �������� �������� � ����������� �����������
	char* dequeue_min();

	// ������� � ����������� �����������
	char* peek_min() const;

	// ������� ���� �������� ������������ ��������
	void merge(const binary_priority_queue& other);

};