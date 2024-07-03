#include "CZ80Regs.h"

// -----------------------------------------------------------------------------------------------
CZ80FlagReg::CZ80FlagReg()
	: C(0), Z(0), PV(0), S(0), N(0), H(0)
{
	return;
}

CZ80FlagReg::~CZ80FlagReg()
{
	return;
}

RAM_FUNC void CZ80FlagReg::Reset()
{
	C = Z = PV = S = N = H = 0;
	return;
}

RAM_FUNC uint8_t CZ80FlagReg::Get()
{
	const uint8_t F = (S<<7) | (Z<<6) | (H<<4) | (PV<<2) | C;
	return F;
}

RAM_FUNC void CZ80FlagReg::Set(const uint8_t F)
{
	S = (F >> 7) & 0x01;
	Z = (F >> 6) & 0x01;
	H = (F >> 4) & 0x01;
	PV= (F >> 2) & 0x01;
	C = F & 0x01;
	return;
}

RAM_FUNC const CZ80FlagReg &CZ80FlagReg::operator=(const CZ80FlagReg &rhs)
{
	if( this == &rhs)
		return *this;
	C = rhs.C;
	Z = rhs.Z;
	PV = rhs.PV;
	S = rhs.S;
	N = rhs.N;
	H = rhs.H;
	return *this;
}

// -----------------------------------------------------------------------------------------------
CZ80Regs::CZ80Regs()
{
	A = B = C = D = E = H = L = 0x00;
	Ad = Bd = Cd = Dd = Ed = Hd = Ld = 0x00;
	I = R = 0x00;
	IX = IY = SP = PC = 0x0000;
	CodePC = 0x0000;
	Code = 0x00;
	return;
};

CZ80Regs::~CZ80Regs()
{
	return;
}

RAM_FUNC void CZ80Regs::Reset()
{
	A = B = C = D = E = H = L = 0x00;
	Ad = Bd = Cd = Dd = Ed = Hd = Ld = 0x00;
	I = R = 0x00;
	IX = IY = SP = PC = 0x0000;
	CodePC = 0x0000;
	Code = 0x00;
	return;
}

RAM_FUNC uint16_t CZ80Regs::HILO(uint8_t hi, uint8_t lo) { return (hi<<8)|lo; }
RAM_FUNC uint16_t CZ80Regs::GetAF() { return HILO(A,F.Get()); }
RAM_FUNC uint16_t CZ80Regs::GetBC() { return HILO(B,C); }
RAM_FUNC uint16_t CZ80Regs::GetDE() { return HILO(D,E); }
RAM_FUNC uint16_t CZ80Regs::GetHL() { return HILO(H,L); }
RAM_FUNC void CZ80Regs::SetAF(const uint16_t AF) { A = (AF>>8)&0xff, F.Set(AF&0xff); }
RAM_FUNC void CZ80Regs::SetBC(const uint16_t BC) { B = (BC>>8)&0xff, C = BC&0xff; }
RAM_FUNC void CZ80Regs::SetDE(const uint16_t DE) { D = (DE>>8)&0xff, E = DE&0xff; }
RAM_FUNC void CZ80Regs::SetHL(const uint16_t HL) { H = (HL>>8)&0xff, L = HL&0xff; }
RAM_FUNC void CZ80Regs::Swap(uint8_t *pR1, uint8_t *pR2)
{
	uint8_t temp = *pR1;
	*pR1 = *pR2;
	*pR2 = temp;
	return;
}
RAM_FUNC void CZ80Regs::Swap(CZ80FlagReg *pR1, CZ80FlagReg *pR2)
{
	CZ80FlagReg temp = *pR1;
	*pR1 = *pR2;
	*pR2 = temp;
	return;
}

RAM_FUNC void CZ80Regs::Inc8(uint8_t *pReg8)
{
	++*pReg8;
	//
	F.C = F.C;						// 変化なし
	F.Z = (*pReg8==0)?1:0;			// 0になったかどうか
	F.PV= (*pReg8==0x80)?1:0;		// オーバーフローが発生したかどうか
	F.S = (*pReg8>>7) & 0x01;		// 符号付きかどうか
	F.N = 0;						// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((*pReg8&0x0F)==0)?1:0;	// 下位4ビットのから桁上がりが発生したかどうか
	return;
}

RAM_FUNC void CZ80Regs::Dec8(uint8_t *pReg8)
{
	--*pReg8;
	//
	F.C = F.C;						// 変化なし
	F.Z = (*pReg8==0)?1:0;			// 0になったかどうか
	F.PV= (*pReg8==0x7F)?1:0;		// オーバーフローが発生したかどうか
	F.S = (*pReg8>>7) & 0x01;		// 符号付きかどうか
	F.N = 1;						// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((*pReg8&0xF)==0xF)?1:0;	// 下位4ビットへの桁借りが発生したかどうか
	return;
}

RAM_FUNC void CZ80Regs::Add8(uint8_t *pR1, const uint8_t R2)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	uint16_t old = *pR1;
	uint16_t temp = static_cast<uint16_t>(*pR1) + R2;
	*pR1 = static_cast<uint8_t>(temp&0xFF);
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = (temp>0xFF)?1:0;		// オーバーフローしたか
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1>>7)&0x01;
	F.N = 0; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((old&0xFFF0)<(temp&0xFFF0)) )?1:0; // ビット4からの桁上がりが生じたか
	return;
}

RAM_FUNC void CZ80Regs::Add8Cy(uint8_t *pR1, const uint8_t R2, const uint8_t Cy)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	uint16_t old = *pR1;
	uint16_t temp = static_cast<uint16_t>(*pR1) + R2 + Cy;
	*pR1 = static_cast<uint8_t>(temp&0xFF);
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = (temp>0xFF)?1:0;		// オーバーフローしたか
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1>>7)&0x01;
	F.N = 0; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((old&0xFFF0)<(temp&0xFFF0)) )?1:0; // ビット4からの桁上がりが生じたか
	return;
}

RAM_FUNC void CZ80Regs::Add16(uint16_t *pR1, const uint16_t R2)
{
	uint32_t old = *pR1;
	uint32_t temp = static_cast<uint32_t>(*pR1) + R2;
	*pR1 = static_cast<uint16_t>(temp&0xFFFF);
	//
	F.C = (temp>0xFFFF)?1:0;		// オーバーフローしたか
	F.Z = F.Z;
	F.PV= F.PV;
	F.S = F.S;
	F.N = 0; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((old&0xFFFFF000)<(temp&0xFFFFF000)) )?1:0; // ビット11からの桁上がりが生じたか
	return;
}

RAM_FUNC void CZ80Regs::Sub8(uint8_t *pR1, const uint8_t R2)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	uint16_t old = *pR1;
	uint16_t temp = static_cast<uint16_t>(*pR1) - R2;
	*pR1 = static_cast<uint8_t>(temp&0xFF);
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = (temp>0xFF)?1:0;		// オーバーフローしたか
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1>>7)&0x01;
	F.N = 1; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((temp&0x0F)<(old&0x0F)) )?1:0; // ビット4への桁借りが生じたか
	return;
}

RAM_FUNC void CZ80Regs::Sub8Cy(uint8_t *pR1, const uint8_t R2, const uint8_t Cy)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	uint16_t old = *pR1;
	uint16_t temp = static_cast<uint16_t>(*pR1) - R2 - Cy;
	*pR1 = static_cast<uint8_t>(temp&0xFF);
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = (temp>0xFF)?1:0;		// オーバーフローしたか
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1>>7)&0x01;
	F.N = 1; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((temp&0x0F)<(old&0x0F)) )?1:0; // ビット4への桁借りが生じたか
	return;
}

RAM_FUNC void CZ80Regs::And8(uint8_t *pR1, const uint8_t R2)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	*pR1 &= R2;
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = 0;
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1 >> 7) & 0x01;
	F.N = 0;
	F.H = 1;
	return;
}

RAM_FUNC void CZ80Regs::Xor8(uint8_t *pR1, const uint8_t R2)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	*pR1 ^= R2;
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = 0;
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1 >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Or8(uint8_t *pR1, const uint8_t R2)
{
	bool An = (((*pR1>>7)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>7)&0x1)!=0)?true:false;
	*pR1 |= R2;
	bool Rn = (((*pR1>>7)&0x1)!=1)?true:false;
	//
	F.C = 0;
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1 >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Rlc8(uint8_t *pR)
{
	F.C = (*pR >> 7) & 0x01;
	*pR = (*pR << 1) | F.C;
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = F.C;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Rrc8(uint8_t *pR)
{
	F.C = *pR & 0x01;
	*pR = (*pR >> 1) | (F.C<<7);
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = (*pR >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Rl8(uint8_t *pR)
{
	uint8_t tempCy = F.C;
	F.C = (*pR >> 7) & 0x01;
	*pR = (*pR << 1) | tempCy;
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = (*pR >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Rr8(uint8_t *pR)
{
	uint8_t tempCy = F.C;
	F.C = *pR & 0x01;
	*pR = (*pR >> 1) | (tempCy << 7);
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = (*pR >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Sla8(uint8_t *pR)
{
	F.C = (*pR >> 7) & 0x01;
	*pR = *pR << 1;
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = (*pR >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Sra8(uint8_t *pR)
{
	F.C = *pR & 0x01;
	uint8_t temp = *pR & 0x80;
	*pR = (*pR >> 1) | temp;
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = (*pR >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Sll8(uint8_t *pR)
{
	F.C = (*pR >> 7) & 0x01;
	*pR = (*pR << 1) | 0x01;
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = F.C;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC void CZ80Regs::Srl8(uint8_t *pR)
{
	F.C = *pR & 0x01;
	*pR = *pR >> 1;
	F.Z = (*pR==0)?1:0;
	F.PV= CheckParytyEven(*pR);
	F.S = (*pR >> 7) & 0x01;
	F.N = 0;
	F.H = 0;
	return;
}

RAM_FUNC uint8_t CZ80Regs::CheckParytyEven(const uint8_t tgt)	// 偶数パリティ
{
	uint8_t ep = tgt ^ (tgt >> 4);
	ep ^= ep >> 2;
	ep ^= ep >> 1;
	return (ep==0)?1:0;		
}

RAM_FUNC void CZ80Regs::Sub16Cy(uint16_t *pR1, const uint16_t R2, const uint16_t Cy)
{
	bool An = (((*pR1>>15)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>15)&0x1)!=0)?true:false;
	uint32_t old = *pR1;
	uint32_t temp = static_cast<uint32_t>(*pR1) - R2 - Cy;
	*pR1 = static_cast<uint16_t>(temp&0xFFFF);
	bool Rn = ((*pR1>>15)==1)?true:false;
	//
	F.C = (temp>0xFFFF)?1:0;		// オーバーフローしたか
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1>>15)&0x01;
	F.N = 1; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((temp&0x0FFF)<(old&0x0FFF)) )?1:0; // ビット１１への桁借りが生じたか
	return;
}

RAM_FUNC void CZ80Regs::Add16Cy(uint16_t *pR1, const uint16_t R2, const uint16_t Cy)
{
	bool An = (((*pR1>>15)&0x1)!=0)?true:false;
	bool Bn = (((R2  >>15)&0x1)!=0)?true:false;
	uint32_t old = *pR1;
	uint32_t temp = static_cast<uint32_t>(*pR1) + R2 + Cy;
	*pR1 = static_cast<uint16_t>(temp&0xFFFF);
	bool Rn = ((*pR1>>15)==1)?true:false;
	//
	F.C = (temp>0xFFFF)?1:0;		// オーバーフローしたか
	F.Z = (*pR1==0)?1:0;
	F.PV= ((Rn&&!An&&!Bn)||(!Rn&&An&&Bn))?1:0;
	F.S = (*pR1>>15)&0x01;
	F.N = 0; 	// 0 = 加算命令である/ 1= 減算命令である
	F.H = ((F.C!=0)||((temp&0x0FFF)<(old&0x0FFF)) )?1:0; // ビット１１への桁借りが生じたか
	return;
}

RAM_FUNC void CZ80Regs::SetFlagByIN(uint8_t r)
{
	F.C = F.C;
	F.Z = (r==0)?1:0;
	F.PV= CheckParytyEven(r);
	F.S = (r>>7)&0x01;
	F.N = 0;
	F.H = 0;
	return;
}

// B,C,D,E,H,L レジスタ：裏レジスタを入れ替える
RAM_FUNC void CZ80Regs::Exchange()
{
	Swap(&B, &Bd);
	Swap(&C, &Cd);
	Swap(&D, &Dd);
	Swap(&E, &Ed);
	Swap(&H, &Hd);
	Swap(&L, &Ld);
	return;
}
