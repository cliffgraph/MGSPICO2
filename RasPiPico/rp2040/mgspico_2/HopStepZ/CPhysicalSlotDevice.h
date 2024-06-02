#pragma once
#include "msxdef.h"
#include "IPhysicalSlotDevice.h"

class CPhysicalSlotDevice : public IPhysicalSlotDevice
{
public:
	CPhysicalSlotDevice();
	virtual ~CPhysicalSlotDevice();

private:
	uint8_t	m_ExtReg;
	bool	m_bExt;
private:
	static const z80memaddr_t SCC_ADDR_START = 0x9800;
	static const z80memaddr_t SCC_ADDR_END = 0x98FF;
	static const z80memaddr_t SCC_MEM_SIZE = (SCC_ADDR_END-SCC_ADDR_START+1);
	uint8_t	m_M9000;
	uint8_t	m_M9800[SCC_MEM_SIZE];

	// bool (CPhysicalSlotDevice::*m_pWriteMem)(const z80memaddr_t addr, const uint8_t b);
	// uint8_t (CPhysicalSlotDevice::*m_pReadMem)(const z80memaddr_t addr) const;
	// bool (CPhysicalSlotDevice::*m_pOutPort)(const z80ioaddr_t addr, const uint8_t b);
	// bool (CPhysicalSlotDevice::*m_pInPort)(uint8_t *pB, const z80ioaddr_t addr);

private:
	void init(uint8_t v);
	bool enableFMPAC();

public:
	bool Setup();

public:
/*IZ80MemoryDevice*/
	void SetSlotToPage(const msxpageno_t pageNo, const msxslotno_t slotNo);
	msxslotno_t GetSlotByPage(const msxpageno_t pageNo);
	bool WriteMem(const z80memaddr_t addr, const uint8_t b);
	uint8_t ReadMem(const z80memaddr_t addr) const;

/*IZ80IoDevice*/
	bool OutPort(const z80ioaddr_t addr, const uint8_t b);
	bool InPort(uint8_t *pB, const z80ioaddr_t addr);
};


