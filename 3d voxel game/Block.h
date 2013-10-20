#include "Voxel.h"

class Creature;

class Block : public virtual Voxel
{
public:
	virtual bool IsSolid()=0;
	virtual bool IsUnique()=0;
	virtual void OnCreate(unsigned short metadata)=0;
	virtual void OnRemove()=0;
	virtual void OnRightClick(Creature *creature, unsigned short metadata)=0;
	virtual Block *OnReceive(/*Packet*, GameUtilty**/)=0;
};