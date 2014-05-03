#pragma once

#include <deque>
#include <functional>

template<class T>
class Deque2
{
	std::deque<T*> m_deque;
	long m_centerIndex;
public:

	Deque2()
		: m_centerIndex(0)
	{

	}

	// Expand to node
	void ExpandTo(const long index, std::function<T*()> constructor)
	{
		long newIndex = index + m_centerIndex;

		if (newIndex < 0)
		{
			m_centerIndex -= newIndex;

			for (int i = 0; i != newIndex; i--)
				m_deque.push_front(constructor());

			newIndex = 0;
		}
		
		if (newIndex >= m_deque.size())
		{
			int size = (newIndex-m_deque.size());
			for (int i = 0; i < size; i++)
				m_deque.push_back(constructor());
		}
	}

	// Remove empty nodes.
	void Clean()
	{
		for (std::deque<T*>::const_reverse_iterator it = m_deque.rend(); it != m_deque.rbegin(); --it)
		{
			if (*it != nullptr)
			{
				m_deque.erase(it.base(), m_deque.end());
				break;
			}
		}

		int i = 0;
		for (auto it = m_deque.begin(); it != m_deque.end(); ++it)
		{
			if (*it)
			{
				m_centerIndex -= --i;
				m_deque.erase(m_deque.begin(), --it);
				break;
			}
			i++;
		}
	}

	// Expand to index and return pointer to node to allow changes.
	T **ExpandGet(const long index, std::function<T*()> constructor)
	{
		ExpandTo(index, constructor);
		return &deque[index+m_centerIndex]
	}

	T **operator[](const long index)
	{
		long newIndex = index+m_centerIndex;

		if (newIndex >= 0 && newIndex < m_deque.size())
			return &m_deque[newIndex];
		else
			return nullptr;
	}
};