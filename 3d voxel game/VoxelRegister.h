/*#include <functional>
#include <map>
#include <string>
#include <vector>

class IVoxel;

class VoxelRegister
{
private:
	std::map<size_t, unsigned short> voxelIdMap;
	std::vector<IVoxel*> voxelList;
	std::vector<std::function<IVoxel*()>> voxelTypeList;
public:
	VoxelRegister();
	~VoxelRegister();
	void RegisterVoxel(IVoxel *voxel, size_t typeId);
	IVoxel *getVoxelType(unsigned short id);
	unsigned short getVoxelIdByTypeId(size_t typeId);
};*/