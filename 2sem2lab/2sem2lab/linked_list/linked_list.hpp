#pragma once
#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <stdexcept>

template<class T>
class linked_list
{

private:

	struct node
	{
		node* p_next;
		T value;

		explicit node(T value) : value(value), p_next(nullptr) {}
	};

	node* _p_head = nullptr;
	node* _p_tail = nullptr;
	unsigned int _length = 0;

#pragma region Base

	node* insert_node(T value, unsigned int index)
	{
		if (index == _length)
		{
			return add_node(value);
		}

		if (index + 1 > _length)
		{
			throw std::invalid_argument("Out of range. Position should be less than length");
		}

		node* p_new = new node(value);
		if (index == 0)
		{
			p_new->p_next = _p_head;
			_p_head = p_new;
		}
		else
		{
			node* p_prev = get_node(index - 1);
			p_new->p_next = p_prev->p_next;
			p_prev->p_next = p_new;
		}

		if (index + 1 == _length)
		{
			_p_tail = p_new;
		}

		return p_new;
	}

	node* get_node(unsigned int index) const
	{
		if (index + 1 > _length)
		{
			throw std::invalid_argument("Out of range. Position should be less than length");
		}

		auto current = _p_head;
		while (index--)
		{
			current = current->p_next;
		}

		return current;
	}

	node* set_node(T value, unsigned int index)
	{
		if (index + 1 > _length)
		{
			throw std::invalid_argument("Out of range. Position should be less than length");
		}

		node* p_new = new node(value);
		if (index == 0)
		{
			if (_p_head != nullptr)
			{
				p_new->p_next = _p_head->p_next;
				delete _p_head;
				_p_head = p_new;
			}
			else
			{
				_p_head = p_new;
			}
		}
		else
		{
			node* p_prev = get_node(index - 1);
			node* p_current = p_prev->p_next;
			p_new->p_next = p_current->p_next;
			p_prev->p_next = p_new;
			delete p_current;
		}

		if (index + 1 == _length)
		{
			_p_tail = p_new;
		}

		return p_new;
	}

	node* add_node(T value)
	{
		node* p_new = new node(value);
		if (_p_tail != nullptr)
		{
			_p_tail->p_next = p_new;
			_p_tail = p_new;
		}
		else
		{
			_p_head = p_new;
			_p_tail = p_new;
		}

		_length++;

		return p_new;
	}

	node* find_node(T value) const
	{
		node* p_current = _p_head;
		while (p_current != nullptr)
		{
			if (p_current->value == value)
			{
				return p_current;
			}

			p_current = p_current->p_next;
		}

		return nullptr;
	}

#pragma endregion


public:

#pragma region Constructors

	linked_list()
	{

	}

	linked_list(const std::vector<T>& other)
	{
		for (size_t i = 0; i < other.size(); i++)
		{
			add_node(other[i]);
		}
	}

	linked_list(const T* other, unsigned int size)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			add_node(other[i]);
		}
	}

	linked_list(const std::initializer_list<T>& other)
	{
		for (size_t i = 0; i < other.size(); i++)
		{
			add_node(other[i]);
		}
	}

	linked_list(const linked_list<T>& other)
	{
		copy_from(other);
	}

	~linked_list()
	{
		clear();
	}

#pragma endregion

#pragma region Operators

	T& operator[](unsigned int index)
	{
		return get_value(index);
	}

	linked_list<T>& operator = (const linked_list<T>& other)
	{
		if (this != &other)
		{
			clear();
			copy_from(other);
		}

		return *this;
	}

	linked_list<T>& operator = (const std::initializer_list<T> other)
	{
		clear();
		for (size_t i = 0; i < other.size(); i++)
		{
			add_node(other[i]);
		}

		return *this;
	}
	
	linked_list<T>& operator += (const linked_list<T>& other)
	{
		add_value(other);
		return *this;
	}

	linked_list<T>& operator -= (const linked_list<T>& other)
	{
		remove(other);
		return *this;
	}

	linked_list<T> operator + (const linked_list<T>& other) const
	{
		auto temp = linked_list(*this);
		temp += other;
		return temp;
	}

	linked_list<T> operator - (const linked_list<T>& other) const
	{
		auto temp = linked_list<T>(this);
		temp -= other;
		return temp;
	}

	friend std::ostream& operator << (std::ostream& stream, linked_list<T>& other)
	{
		stream << other.to_string();

		return stream;
	}

#pragma endregion

#pragma region  Base

	unsigned int get_length() { return _length; } const

	T get_value(unsigned int index) const
	{
		node* p_node = get_node(index);
		return p_node->value;
	}

	void set_value(T value, unsigned int index)
	{
		set_node(value, index);
	}

	void add_value(T value)
	{
		add_node(value);
	}

	void add_value(const linked_list<T>& other)
	{
		for (size_t i = 0; i < other._length; i++)
		{
			add_node(other.get_value(i));
		}
	}

	void remove(T value)
	{
		node* p_prev = nullptr;
		node* p_current = _p_head;
		while (p_current != nullptr)
		{
			if (p_current->value == value) break;

			p_prev = p_current;
			p_current = p_current->p_next;
		}

		if (p_current == nullptr) return;

		if (p_prev != nullptr)
		{
			p_prev->p_next = p_current->p_next;
		}
		else
		{
			_p_head = p_current->p_next;
		}

		if (_p_tail == p_current)
		{
			_p_tail = p_prev;
		}

		delete p_current;
		_length--;
	}

	void remove(const linked_list<T>& other)
	{
		for (size_t i = 0; i < other._length; i++)
		{
			remove(other.get_value(i));
		}
	}

	void remove_at(unsigned int index)
	{
		if (index + 1 > _length)
		{
			throw std::invalid_argument("Out of range. Position should be less than length");
		}

		node* p_prev = nullptr;
		node* p_current = _p_head;
		while (index--)
		{
			p_prev = p_current;
			p_current = p_current->p_next;
		}

		if (p_prev != nullptr)
		{
			p_prev->p_next = p_current->p_next;
		}
		else
		{
			_p_head = p_current->p_next;
		}

		if (_p_tail == p_current)
		{
			_p_tail = p_prev;
		}

		_length--;
		delete p_current;
	}

	bool contains(T value) const
	{
		node* p_current = _p_head;
		while (p_current != nullptr)
		{
			if (p_current->value == value) return true;

			p_current = p_current->p_next;
		}

		return false;;
	}

#pragma endregion

#pragma region Utility

	void clear()
	{
		node* p_prev = nullptr;
		node* p_current = _p_head;
		while (p_current != nullptr)
		{
			p_prev = p_current;
			p_current = p_current->p_next;
			delete p_prev;
		}

		_p_head = nullptr;
		_p_tail = nullptr;
		_length = 0;
	}

	linked_list copy()
	{
		linked_list result = linked_list();
		node* p_current = _p_head;
		for (unsigned int i = 0; i < _length; i++)
		{
			auto value = p_current->value;
			result.add_node(value);
		}

		return result;
	}

	void copy_to(linked_list other) const
	{
		other.clear();
		node* p_current = _p_head;
		for (unsigned int i = 0; i < _length; i++)
		{
			auto value = p_current->value;
			p_current = p_current->p_next;
			other.add_node(value);
		}
	}

	void copy_from(const linked_list& other)
	{
		clear();
		node* p_current = other._p_head;
		for (unsigned int i = 0; i < other._length; i++)
		{
			auto value = p_current->value;
			p_current = p_current->p_next;
			add_node(value);
		}
	}

	std::string to_string()  const
	{
		std::stringstream result = std::stringstream();
		result << "{";

		node* p_current = _p_head;
		while (p_current != nullptr)
		{
			result << p_current->value;
			p_current = p_current->p_next;
			if (p_current != nullptr)
			{
				result << ",";
			}
		}

		result << "}";


		return result.str();
	}

	node* split(node* head) {
		node* fast = head;
		node* slow = head;
		node* prev = nullptr;

		while (fast && fast->p_next) {
			fast = fast->p_next->p_next;
			prev = slow;
			slow = slow->p_next;
		}

		if (prev) {
			prev->p_next = nullptr;
		}

		return slow;
	}

	node* merge(node* left, node* right, std::function<bool(T, T)> compare)
	{
		if (!left) return right;
		if (!right) return left;

		if (compare(left->value, right->value)) {
			left->p_next = merge(left->p_next, right, compare);
			return left;
		}
		else {
			right->p_next = merge(left, right->p_next, compare);
			return right;
		}
	}

	node* merge_sort(node* head, std::function<bool(T, T)> compare)
	{
		if (!head || !head->p_next) {
			return head;
		}

		node* middle = split(head);
		node* left = merge_sort(head, compare);
		node* right = merge_sort(middle, compare);

		return merge(left, right, compare);
	}

	void sort(std::function<bool(T, T)> compare)
	{
		_p_head = merge_sort(_p_head, compare);

		// Update tail after sorting
		_p_tail = _p_head;
		if (_p_tail)
		{
			while (_p_tail->p_next)
			{
				_p_tail = _p_tail->p_next;
			}
		}
	}
		
#pragma endregion

};

#endif // ! _LINKED_LIST_
