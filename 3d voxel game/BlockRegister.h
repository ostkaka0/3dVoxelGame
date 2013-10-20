#include <functional>
#include <map>
#include <string>
#include <vector>

class Block;

class BlockRegister
{
private:
	std::map<size_t, unsigned short> blockIdMap;
	std::vector<Block*> blockList;
	std::vector<std::function<Block*()>> blockTypeList;
public:
	BlockRegister();
	void RegisterBlock(Block *block, size_t typeId);
	Block *getBlockType(unsigned short id);
	unsigned short getBlockIdByTypeId(size_t typeId);
};