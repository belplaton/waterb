#pragma once
#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <memory>
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
		std::shared_ptr<node> p_next;
		T value;

		explicit node(T value) : value(value), p_next(nullptr) {}
	};

	std::shared_ptr<node> _p_head = nullptr;
	std::shared_ptr<node> _p_tail = nullptr;
	unsigned int _length = 0;

#pragma region Base

	std::shared_ptr<node> insert_node(T value, unsigned int index)
	{
		if (index == _length)
		{
			return add_node(value);
		}

		if (index + 1 > _length)
		{
			throw std::invalid_argument("Out of range. Position should be less than length");
		}

		std::shared_ptr<node> p_new = std::make_shared<node>(value);
		if (index == 0)
		{
			p_new->p_next = _p_head;
			_p_head = p_new;
		}
		else
		{
			std::shared_ptr<node> p_prev = get_node(index - 1);
			p_new->p_next = p_prev->p_next;
			p_prev->p_next = p_new;
		}

		if (index + 1 == _length)
		{
			_p_tail = p_new;
		}

		return p_new;
	}

	std::shared_ptr<node> get_node(unsigned int index) const
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

	std::shared_ptr<node> set_node(T value, unsigned int index)
	{
		if (index + 1 > _length)
		{
			throw std::invalid_argument("Out of range. Position should be less than length");
		}

		std::shared_ptr<node> p_new = std::make_shared<node>(value);
		if (index == 0)
		{
			if (_p_head != nullptr)
			{
				p_new->p_next = _p_head->p_next;
				_p_head.reset();
				_p_head = p_new;
			}
			else
			{
				_p_head = p_new;
			}
		}
		else
		{
			std::shared_ptr<node> p_prev = get_node(index - 1);
			std::shared_ptr<node> p_current = p_prev->p_next;
			p_new->p_next = p_current->p_next;
			p_prev->p_next = p_new;
			p_current.reset();
		}

		if (index + 1 == _length)
		{
			_p_tail = p_new;
		}

		return p_new;
	}

	std::shared_ptr<node> add_node(T value)
	{
		std::shared_ptr<node> p_new = std::make_shared<node>(value);
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

	std::shared_ptr<node> find_node(T value) const
	{
		std::shared_ptr<node> p_current = _p_head;
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

#pragma region Utility

	std::shared_ptr<node> split(std::shared_ptr<node> head) {
		std::shared_ptr<node> fast = head;
		std::shared_ptr<node> slow = head;
		std::shared_ptr<node> prev = nullptr;

		while (fast && fast->p_next)
		{
			fast = fast->p_next->p_next;
			prev = slow;
			slow = slow->p_next;
		}

		if (prev)
		{
			prev->p_next.reset();
		}

		return slow;
	}

	std::shared_ptr<node> merge(std::shared_ptr<node> left, std::shared_ptr<node> right, std::function<bool(T, T)> compare)
	{
		if (!left) return right;
		if (!right) return left;

		if (compare(left->value, right->value))
		{
			left->p_next = merge(left->p_next, right, compare);
			return left;
		}
		else
		{
			right->p_next = merge(left, right->p_next, compare);
			return right;
		}
	}

	std::shared_ptr<node> merge_sort(std::shared_ptr<node> head, std::function<bool(T, T)> compare)
	{
		if (!head || !head->p_next)
		{
			return head;
		}

		std::shared_ptr<node> middle = split(head);
		std::shared_ptr<node> left = merge_sort(head, compare);
		std::shared_ptr<node> right = merge_sort(middle, compare);

		return merge(left, right, compare);
	}

#pragma endregion

public:

#pragma region Iterator

	class iterator
	{

	private:

		std::shared_ptr<node> current;

	public:

		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(std::shared_ptr<node> ptr) : current(ptr) {}

		T& operator*() const { return current->value; }
		T* operator->() { return &current->value; }

		// Prefix increment
		iterator& operator++() {
			current = current->p_next;
			return *this;
		}

		// Postfix increment
		iterator operator++(int) {
			iterator temp = *this;
			++(*this);
			return temp;
		}

		friend bool operator==(const iterator& a, const iterator& b) { return a.current == b.current; }
		friend bool operator!=(const iterator& a, const iterator& b) { return a.current != b.current; }

	};

	iterator begin() const { return iterator(_p_head); }
	iterator end() const { return iterator(nullptr); }

#pragma endregion

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

	unsigned int get_length()  const { return _length; }

	T& get_value(unsigned int index) const
	{
		std::shared_ptr<node> p_node = get_node(index);
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
		std::shared_ptr<node> p_prev = nullptr;
		std::shared_ptr<node> p_current = _p_head;
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

		p_current.reset();
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

		std::shared_ptr<node> p_prev = nullptr;
		std::shared_ptr<node> p_current = _p_head;
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
		p_current.reset();
	}

	bool contains(T value) const
	{
		std::shared_ptr<node> p_current = _p_head;
		while (p_current != nullptr)
		{
			if (p_current->value == value) return true;

			p_current = p_current->p_next;
		}

		return false;;
	}

	T* find(std::function<bool(T)> compare) const
	{
		std::shared_ptr<node> p_current = _p_head;
		for (unsigned int i = 0; i < _length; i++)
		{
			if (compare(p_current->value))
			{
				return &p_current->value;
			}

			p_current = p_current->p_next;
		}

		return nullptr;
	}

	unsigned int find(const T& other) const
	{
		std::shared_ptr<node> p_current = _p_head;
		for (unsigned int i = 0; i < _length; i++)
		{
			if (p_current->value == other)
			{
				return i;
			}

			p_current = p_current->p_next;
		}

		return -1;
	}

#pragma endregion

#pragma region Utility

	void clear()
	{
		std::shared_ptr<node> p_prev = nullptr;
		std::shared_ptr<node> p_current = _p_head;
		while (p_current != nullptr)
		{
			p_prev = p_current;
			p_current = p_current->p_next;
			p_prev.reset();
		}

		_p_head.reset();
		_p_tail.reset();
		_length = 0;
	}

	linked_list copy()
	{
		linked_list result = linked_list();
		std::shared_ptr<node> p_current = _p_head;
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
		std::shared_ptr<node> p_current = _p_head;
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
		std::shared_ptr<node> p_current = other._p_head;
		for (unsigned int i = 0; i < other._length; i++)
		{
			auto value = p_current->value;
			p_current = p_current->p_next;
			add_node(value);
		}
	}

	std::string to_string() const
	{
		std::stringstream result = std::stringstream();
		result << "{";

		std::shared_ptr<node> p_current = _p_head;
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

	void sort(std::function<bool(T, T)> compare)
	{
		_p_head = merge_sort(_p_head, compare);

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
