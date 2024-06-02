#include "pico/stdlib.h"
#include <stdio.h>
#include <memory.h>
#include "CPhysicalSlotDevice.h"
#include "../def_gpio.h"
#include "../t_mgspico.h"

CPhysicalSlotDevice::CPhysicalSlotDevice()
{
	// do nothing
	return;
}

CPhysicalSlotDevice::~CPhysicalSlotDevice()
{
	// do nothing
	return;
}

bool CPhysicalSlotDevice::Setup()
{
	// 拡張スロットの有無をチェックする -> m_bExt
	WriteMem(0xffff, 0x55);
	m_bExt = (ReadMem(0xffff)==0xaa)?true:false;
	WriteMem(0xffff, 0x00);
	m_ExtReg = ReadMem(0xffff) ^ 0xff;
	
	// For Yamanooto cartridge, enable PSG echo on standard ports #A0-#A3
	WriteMem(0x7fff, ReadMem(0x7fff) | 0x01);
	WriteMem(0x7ffd, ReadMem(0x7ffd) | 0x02);

	// FMPACKがいればFMPACKのIOアクセスを有効化する
	if( !m_bExt ) {
		enableFMPAC();
	}
	else {
		const msxslotno_t tempSlotNo = GetSlotByPage(1);
		for(int t = 0; t < EXTSLOTNO_NUM; ++t) {
			SetSlotToPage(1/*0x4000*/, t);
			if( enableFMPAC() )
				break;
		}
		SetSlotToPage(1, tempSlotNo);
	}

	m_M9000 = 0;
	return true;
}

bool CPhysicalSlotDevice::enableFMPAC()
{
	bool bRec = false;
	static const char *pMark = "PAC2OPLL";
	static const int MARKLEN = 8;
	char sample[MARKLEN+1] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0',};
	for( int cnt = 0; cnt < MARKLEN; ++cnt) {
		sample[cnt] = (char)ReadMem(0x4018 + cnt);
	}
	if( memcmp(sample, pMark, MARKLEN) == 0) {
		uint8_t v = ReadMem(0x7ff6);
		WriteMem(0x7ff6, v|0x01);
		bRec = true;;
	}
	return bRec;
}

void __time_critical_func(CPhysicalSlotDevice::SetSlotToPage)(const msxpageno_t pageNo, const msxslotno_t slotNo)
{
	m_ExtReg &= (0x03 << (pageNo*2)) ^ 0xff;
	m_ExtReg |= slotNo << (pageNo*2);
	WriteMem(0xffff, m_ExtReg);
	return;
}

msxslotno_t __time_critical_func(CPhysicalSlotDevice::GetSlotByPage)(const msxpageno_t pageNo)
{
	m_ExtReg = ReadMem(0xffff) ^ 0xff;
	const msxslotno_t extSlotNo = ( m_ExtReg >> (pageNo*2)) & 0x03; 
	return extSlotNo;
}

// ------------------------------------------------------------------------------------------------
bool __time_critical_func(CPhysicalSlotDevice::WriteMem)(const z80memaddr_t addr, const uint8_t b)
{
	bool bRetc = false;
	// for SCC
	if( addr == 0x9000 ){
		m_M9000 = b;
		mgspico::t_OutSCC(addr, b);
		bRetc = true;
	}
	else if(m_M9000 == 0x3f && SCC_ADDR_START <= addr && addr <= SCC_ADDR_END ){
		m_M9800[addr-SCC_ADDR_START] = b;
		mgspico::t_OutSCC(addr, b);
		bRetc = true;
	}
	else {
		bRetc = mgspico::t_WriteMem(addr, b);
	}
	return bRetc;
}
uint8_t __time_critical_func(CPhysicalSlotDevice::ReadMem)(const z80memaddr_t addr) const
{
	// for SCC
	if( addr == 0x9000 ){
		return m_M9000;
	}
	else if(m_M9000 == 0x3f && SCC_ADDR_START <= addr && addr <= SCC_ADDR_END ){
		return m_M9800[addr-SCC_ADDR_START];
	}
	return mgspico::t_ReadMem(addr);
}
bool __time_critical_func(CPhysicalSlotDevice::OutPort)(const z80ioaddr_t addr, const uint8_t b)
{
	return mgspico::t_OutPort(addr, b);
}
bool __time_critical_func(CPhysicalSlotDevice::InPort)(uint8_t *pB, const z80ioaddr_t addr)
{
	return mgspico::t_InPort(pB, addr);
}

