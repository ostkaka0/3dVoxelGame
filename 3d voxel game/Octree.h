#include <iostream>
#include <typeinfo>

template<class T, size_t size>
class Octree
{
	void **childs;
	bool isOctree[8];
public:
	class Element;

	Octree()
	{
		childs = static_cast<void**>(malloc(sizeof(void*)<<3));//new void*[8];
		for (int i = 0; i < 8; i++)
		{
			childs[i] = nullptr;
			isOctree[i] = false;
		}
	}

	Octree(T *t)
	{
		childs = new void*[8];
		for (int i = 0; i < 8; i++)
		{
			childs[i] = nullptr;
			isOctree[i] = false;
		}
	}

	Octree(T *t[8])
	{
		childs = new void*[8];
		childs = t;
		*static_cast<char*>(&isOctree) = 0;
	}

	Octree(Octree *octrees[8])
	{
		childs = new void*[8];
		childs = octrees;
		*static_cast<char*>(&isOctree) = 0;
	}

	Octree(void **childs, bool *isOctree)
	{
		this->childs = childs;
		this->isOctree = isOctree;
	}

	virtual void Virtual()
	{
		throw -1;
	}

	inline Element operator[] (size_t i)
	{
		reinterpret_cast<char*>(&i)[0] << 1;
		reinterpret_cast<char*>(&i)[1] << 1;
		reinterpret_cast<char*>(&i)[2] << 1;
		//reinterpret_cast<unsigned char*>(&i)[3]++;

		void *child = childs[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1];

		if (child != nullptr)
		{
			std::cout << typeid(child).name() << std::endl;
		}

		if (isOctree[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1])
			return (*reinterpret_cast<Octree<T, size>**>
			(childs)
			[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1])
			[i];
		else
			return Element(child, &isOctree[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1]);

		/*if (child == nullptr)
			return new Element<t,size>(child, &isOctree[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1]);
		//return childs[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1];
		else if (isOctree[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1])
			return (*reinterpret_cast<Octree<T, size>**>
			(childs)
			[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1])
			[i];
		else
			return new Element<t,size>(child, &isOctree[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1]);*/
		//return childs[i&(1<<size)-1|i&(1<<(size<<1))-1|i&(1<<(size<<2))-1];
		/*if (isOctree[i&(1<<size)|i&(1<<(size<<1))|i&(1<<(size<<2))])
			return (*reinterpret_cast<Octree<T, size>**>
			(childs)
			[i&(1<<size)|i&(1<<(size<<1))|i&(1<<(size<<2))])
			[i];
		else
			return childs[i&(1<<size)|i&(1<<(size<<1))|i&(1<<(size<<2))];*/
	}

	/*inline T* operator[] (size_t i)
	{
		return reinterpret_cast<T*>((*this)[i].element);
	}*/

	inline void *const getBlock(size_t i)
	{
		reinterpret_cast<char*>(&i)[0] << 1;	//x
		reinterpret_cast<char*>(&i)[1] << 1;	//y
		reinterpret_cast<char*>(&i)[2] << 1;	//z
		//reinterpret_cast<unsigned char*>(&i)[3]++; //4:th variable

		if (isOctree[i&(1<<size)|i&(1<<(size<<1))|i&(1<<(size<<2))])
			return reinterpret_cast<Octree<T, size>**>
			(childs)
			[i&(1<<size)|i&(1<<(size<<1))|i&(1<<(size<<2))]->
			GetBlock(i);
		else
			return childs[i&(1<<size)|i&(1<<(size<<1))|i&(1<<(size<<2))];
	}

	/*inline T* operator[,,](size_t x, size_t y, size_t z)
	{
		(*this)[x | y >>size | z>>(size<<1)]
	}*/
//};

//template<class T2, size_t size>
	class Element
	{
		public:

		void *element;
		bool *isOctree;


		Element(void *c, bool *i)
		{
			element = c;
			isOctree = i;
		}

		inline void operator=(T *t)
		{
			element = t;
			*isOctree = false;
		}

		inline void operator=(Octree<T,size> *o)
		{
			element = o;
			*isOctree = true;
		}

		/*inline T* operator ()()
		{
			return static_cast<T*>(child);
		}

		inline Octree<T, size>* operator ()()
		{
			return static_cast<Octree<T, size>*>(child);
		}*/
	};
};