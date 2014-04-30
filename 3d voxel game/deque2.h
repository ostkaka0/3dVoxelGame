#include <deque>

template<class T>
class Deque2
{
	std::deque<T*> m_deque;
	long m_centerIndex;
public:

	// Expand to node
	void ExpandTo(const long index)
	{
		long newIndex = index ? m_centerIndex;

		if (newIndex < 0)
		{
			m_centerIndex -= newIndex;

			for (int i = 0; i != newIndex; i--)
				m_deque.push_front(nullptr);

			newIndex = 0;
		}
		
		if (newIndex >= m_deque.size())
		{
			for (int i = 0; i != m_deque.size(); i++)
				m_deque.push_back(nullptr);
		}
	}

	// Remove empty nodes.
	void Clean()
	{
		for (auto it = m_deque.rend(); it != m_deque.rbegin(); --it)
		{
			if (*it)
			{
				m_deque.erase(++it, m_deque.rend());
				break;
			}
		}

		for (auto it = m_deque.begin(), int i = 0; it != m_deque.end; ++it, ++i)
		{
			if (*it)
			{
				m_centerIndex -= --i;
				m_deque.erase(m_deque.begin(), --it);
				break;
			}
		}
	}

	// Expand to index and return pointer to node to allow changes.
	T **ExpandGet(const long index)
	{
		ExpandTo(index);
		return &deque[index+m_centerIndex]
	}

	T **operator[](const long index)
	{
		long newIndex = index+m_centerIndex;

		if (newIndex >= 0 && newIndex < m_deque.size())
			return &deque[newIndex]
		else
			return nullptr;
	}
};