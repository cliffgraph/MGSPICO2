#pragma once
#include "msxdef.h"
#include "pico/stdlib.h"

// ----------------------------------------------------------------------------------------------
class CZ80FlagReg
{
public:
	uint8_t C, Z, PV, S, N, H;
public:
	CZ80FlagReg();
	~CZ80FlagReg();
	void Reset();
	uint8_t Get();
	void Set(const uint8_t F);
	const CZ80FlagReg &operator=(const CZ80FlagReg &rhs);
};

// ----------------------------------------------------------------------------------------------
class CZ80Regs
{
public:
	uint16_t PC;
	uint8_t A,B,C,D,E,H,L,I,R;
	uint8_t Ad,Bd,Cd,Dd,Ed,Hd,Ld;
	uint16_t IX, IY, SP;
	CZ80FlagReg F, Fd;
	uint16_t CodePC;
	uint8_t Code;

public:
	CZ80Regs();
	~CZ80Regs();
	void Reset();
	uint16_t HILO(uint8_t hi, uint8_t lo);
	uint16_t GetAF();
	uint16_t GetBC();
	uint16_t GetDE();
	uint16_t GetHL();
	void SetAF(const uint16_t AF);
	void SetBC(const uint16_t BC);
	void SetDE(const uint16_t DE);
	void SetHL(const uint16_t HL);
	void Swap(uint8_t *pR1, uint8_t *pR2);
	void Swap(CZ80FlagReg *pR1, CZ80FlagReg *pR2);
	void Inc8(uint8_t *pReg8);
	void Dec8(uint8_t *pReg8);
	void Add8(uint8_t *pR1, const uint8_t R2);
	void Add8Cy(uint8_t *pR1, const uint8_t R2, const uint8_t Cy);
	void Add16(uint16_t *pR1, const uint16_t R2);
	void Sub8(uint8_t *pR1, const uint8_t R2);
	void Sub8Cy(uint8_t *pR1, const uint8_t R2, const uint8_t Cy);
	void And8(uint8_t *pR1, const uint8_t R2);
	void Xor8(uint8_t *pR1, const uint8_t R2);
	void Or8(uint8_t *pR1, const uint8_t R2);
	void Rlc8(uint8_t *pR);
	void Rrc8(uint8_t *pR);
	void Rl8(uint8_t *pR);
	void Rr8(uint8_t *pR);
	void Sla8(uint8_t *pR);
	void Sra8(uint8_t *pR);
	void Sll8(uint8_t *pR);
	void Srl8(uint8_t *pR);
	static uint8_t CheckParytyEven(const uint8_t tgt);	// 偶数パリティ
	void Sub16Cy(uint16_t *pR1, const uint16_t R2, const uint16_t Cy);
	void Add16Cy(uint16_t *pR1, const uint16_t R2, const uint16_t Cy);
	void SetFlagByIN(uint8_t r);
	void Exchange();
};