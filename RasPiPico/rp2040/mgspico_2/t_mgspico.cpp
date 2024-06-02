#include "stdafx.h"
#include "t_mgspico.h"

namespace mgspico
{
bool __time_critical_func(t_WriteMem)(const z80memaddr_t addr, const uint8_t b)
{
#if !defined(MGS_MUSE_MACHINA)

	gpio_put(MSX_LATCH_A, 1);
	// 	・アドレスバス0-15(GPIO_0-15) <= メモリアドレス
	for(int t = 0; t < 16; ++t) {
		gpio_put(MSX_A0_D0 +t, (addr>>t)&0x01);
	}
	// 	・ウェイト 2.5ns～10ns
	t_wait1us();
	// 	・LATCH_A <= L
	gpio_put(MSX_LATCH_A, 0);
	// 	・データバス0-7(GPIO_0-7) <= 1Byteデータ 
	for(int t = 0; t < 8; ++t) {
		gpio_put(MSX_A0_D0 +t, (b>>t)&0x01);
	}
	// 	・ウェイト 2.5cyc(279ns*2.5 = 698ns)
	t_wait1us();
	gpio_put(MSX_A8_IORQ,	 1);
	gpio_put(MSX_A9_MREQ,	 0);
	gpio_put(MSX_A10_RW,	 0);
	gpio_put(MSX_A11_RD,	 1);
	gpio_put(MSX_A12_SLTSL,	 0);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	gpio_put(MSX_LATCH_C,	 1);
	// 	・ウェイト 1us
	t_wait1us();
	gpio_put(MSX_A8_IORQ,	 1);
	gpio_put(MSX_A9_MREQ,	 1);
	gpio_put(MSX_A10_RW,	 1);
	gpio_put(MSX_A11_RD,	 1);
	gpio_put(MSX_A12_SLTSL,	 1);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	t_wait1us();
	gpio_put(MSX_LATCH_C,	 0);
	t_wait1us();
#endif
	return true;
}

uint8_t __time_critical_func(t_ReadMem)(const z80memaddr_t addr)
{
#if !defined(MGS_MUSE_MACHINA)
	gpio_put(MSX_LATCH_A,	 1);
	// 	・アドレスバス0-15(GPIO_0-15) <= メモリアドレス
	for(int t = 0; t < 16; ++t) {
		gpio_put(MSX_A0_D0 +t, (addr>>t)&0x01);
	}
	// 	・ウェイト 2.5ns～10ns
	t_wait1us();
	// 	・LATCH_A <= L
	gpio_put(MSX_LATCH_A,	 0);

	// 	・GPIO_0-7 をINに設定する
	for(int t = 0; t < 8; ++t) {
		gpio_set_dir(MSX_A0_D0 +t, GPIO_IN);
	}
	// 	・DDIR <= H(A->B)
	gpio_put(MSX_DDIR,		 1);

	gpio_put(MSX_A8_IORQ,	 1);
	gpio_put(MSX_A9_MREQ,	 0);
	gpio_put(MSX_A10_RW,	 1);
	gpio_put(MSX_A11_RD,	 0);
	gpio_put(MSX_A12_SLTSL,	 0);
	// 	・C1(GPIO_13)	<= * アドレス 0x4000-0x7FFFFの範囲は L
	// 	・C12(GPIO_14)	<= * アドレス 0x4000-0xBFFFFの範囲は L
	// 	・GPIO_15 		<= H
	gpio_put(MSX_A13_C1,	 (0x4000<=addr&&addr<=0x7fff)?0:1 );
	gpio_put(MSX_A14_C12,	 (0x4000<=addr&&addr<=0xbfff)?0:1 );
	gpio_put(MSX_A15_RESET,	 1);
	gpio_put(MSX_LATCH_C,	 1);
	// 	・ウェイト 1us
	t_wait1us();

	// 	・データバス0-7(GPIO_0-7) => データ 読み出し
	uint8_t dt8 = 0x00;
	for(int t = 0; t < 8; ++t) {
		dt8 |= (gpio_get(MSX_A0_D0+t)&0x01) << t;
	}

	gpio_put(MSX_A8_IORQ,	 1);
	gpio_put(MSX_A9_MREQ,	 1);
	gpio_put(MSX_A10_RW,	 1);
	gpio_put(MSX_A11_RD,	 1);
	gpio_put(MSX_A12_SLTSL,	 1);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	t_wait1us();
	gpio_put(MSX_LATCH_C,	 0);

	// 	・GPIO_0-7 をOUTに設定する
	for(int t = 0; t < 8; ++t) {
		gpio_set_dir(MSX_A0_D0 +t, GPIO_OUT);
	}
	// 	・DDIR <= L(B->A)
	gpio_put(MSX_DDIR,	 0);
	return dt8;
#else
	return 0x00;
#endif
}


bool __time_critical_func(t_OutPort)(const z80ioaddr_t addr, const uint8_t b)
{
#ifdef MGS_MUSE_MACHINA
	switch(addr)
	{
		// OPLL
		case 0x7C:
			gpio_put(MMM_AEX0, 0);
			for(int t = 0; t < 8; ++t) {
				gpio_put(MMM_D0 +t, (b>>t)&0x01);
			}
			gpio_put(MMM_CSWR_FM, 0);
			busy_wait_us(1);
			gpio_put(MMM_CSWR_FM, 1);
			busy_wait_us(12);
			break;
		case 0x7D:
			gpio_put(MMM_AEX0, 1);
			for(int t = 0; t < 8; ++t) {
				gpio_put(MMM_D0 +t, (b>>t)&0x01);
			}
			gpio_put(MMM_CSWR_FM, 0);
			busy_wait_us(1);
			gpio_put(MMM_CSWR_FM, 1);
			busy_wait_us(84);
			break;

		// PSG
		case 0xA0:
			gpio_put(MMM_AEX0, 0);
			for(int t = 0; t < 8; ++t) {
				gpio_put(MMM_D0 +t, (b>>t)&0x01);
			}
			gpio_put(MMM_CSWR_PSG, 0);
			busy_wait_us(1);
			gpio_put(MMM_CSWR_PSG, 1);
			busy_wait_us(1);
			break;
		case 0xA1:
			gpio_put(MMM_AEX0, 1);
			for(int t = 0; t < 8; ++t) {
				gpio_put(MMM_D0 +t, (b>>t)&0x01);
			}
			gpio_put(MMM_CSWR_PSG, 0);
			busy_wait_us(1);
			gpio_put(MMM_CSWR_PSG, 1);
			busy_wait_us(1);
			break;
		default:
			break;
	}

#else
	// 	・アドレスバス0-7(GPIO_0-7) <= ポート番号
	// 	・アドレスバス8-15(GPIO_8-15)  <= 0x00
	for(int t = 0; t < 8; ++t) {
		gpio_put(MSX_A0_D0 +t, (addr>>t)&0x01);
	}
	// 	・LATCH_A <= H
	gpio_put(MSX_LATCH_A,	 1);
	// 	・ウェイト 2.5ns～10ns
	t_wait1us();
	// 	・LATCH_A <= L
	gpio_put(MSX_LATCH_A,	 0);

	// 	・データバス0-7(GPIO_0-7) <= 1Byteデータ 
	for(int t = 0; t < 8; ++t) {
		gpio_put(MSX_A0_D0 +t, (b>>t)&0x01);
	}
	// 	・ウェイト 2.5cyc(279ns*2.5 = 698ns)
	//	t_wait1us();	// ←これは必要ない
	gpio_put(MSX_A11_RD,	 1);
	gpio_put(MSX_A8_IORQ,	 0);
	gpio_put(MSX_A9_MREQ,	 1);
	gpio_put(MSX_A12_SLTSL,	 1);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	gpio_put(MSX_LATCH_C,	 1);
	t_wait100ns();
	gpio_put(MSX_A10_RW,	 0);
	t_wait700ns();
	gpio_put(MSX_A10_RW,	 1);
	gpio_put(MSX_A11_RD,	 1);
	gpio_put(MSX_A8_IORQ,	 1);
	gpio_put(MSX_A9_MREQ,	 1);
	gpio_put(MSX_A12_SLTSL,	 1);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	t_wait100ns();
	gpio_put(MSX_LATCH_C,	 0);
#endif
	return true;
}

bool __time_critical_func(t_InPort)(uint8_t *pB, const z80ioaddr_t addr)
{
#if !defined(MGS_MUSE_MACHINA)
	// 	・アドレスバス0-7(GPIO_0-7) <= ポート番号
	// 	・アドレスバス8-15(GPIO_8-15)  <= 0x00
	for(int t = 0; t < 8; ++t) {
		gpio_put(MSX_A0_D0 +t, (addr>>t)&0x01);
	}
	// for(int t = 0; t < 8; ++t) {
	// 	gpio_put(MSX_A8_IORQ +t, 0);
	// }
	// 	・LATCH_A <= H
	gpio_put(MSX_LATCH_A,	 1);
	// 	・ウェイト 2.5ns～10ns
	t_wait1us();
	// 	・LATCH_A <= L
	gpio_put(MSX_LATCH_A,	 0);

	// 	・GPIO_0-7 をINに設定する
	for(int t = 0; t < 8; ++t) {
		gpio_set_dir(MSX_A0_D0 +t, GPIO_IN);
	}
	// 	・DDIR <= H(A->B)
	gpio_put(MSX_DDIR,		 1);
	gpio_put(MSX_A8_IORQ,	 0);
	gpio_put(MSX_A9_MREQ,	 1);
	gpio_put(MSX_A10_RW,	 1);
	gpio_put(MSX_A11_RD,	 0);
	gpio_put(MSX_A12_SLTSL,	 1);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	gpio_put(MSX_LATCH_C,	 1);
	// 	・ウェイト 1us
	t_wait1us();

	// 	・データバス0-7(GPIO_0-7) => データ 読み出し
	uint8_t dt8 = 0x00;
	for(int t = 0; t < 8; ++t) {
		dt8 |= (gpio_get(MSX_A0_D0+t)&0x01) << t;
	}
	gpio_put(MSX_A8_IORQ,	 1);
	gpio_put(MSX_A9_MREQ,	 1);
	gpio_put(MSX_A10_RW,	 1);
	gpio_put(MSX_A11_RD,	 1);
	gpio_put(MSX_A12_SLTSL,	 1);
	gpio_put(MSX_A13_C1,	 1);
	gpio_put(MSX_A14_C12,	 1);
	gpio_put(MSX_A15_RESET,	 1);
	// 	・ウェイト 1us
	//	t_wait1us();
	gpio_put(MSX_LATCH_C,	 0);

	// 	・GPIO_0-7 をOUTに設定する
	for(int t = 0; t < 8; ++t) {
		gpio_set_dir(MSX_A0_D0 +t, GPIO_OUT);
	}
	// 	・DDIR <= L(B->A)
	gpio_put(MSX_DDIR,	 0);

	*pB = dt8;
#endif
	return true;
}

void __time_critical_func(t_OutOPLL)(const uint16_t addr, const uint16_t data)
{
#ifdef MGS_MUSE_MACHINA
	gpio_put(MMM_AEX0, 0);
	for(int t = 0; t < 8; ++t) {
		gpio_put(MMM_D0 +t, (addr>>t)&0x01);
	}
	gpio_put(MMM_CSWR_FM, 0);
	busy_wait_us(1);
	gpio_put(MMM_CSWR_FM, 1);
	busy_wait_us(12);

	gpio_put(MMM_AEX0, 1);
	for(int t = 0; t < 8; ++t) {
		gpio_put(MMM_D0 +t, (data>>t)&0x01);
	}
	gpio_put(MMM_CSWR_FM, 0);
	busy_wait_us(1);
	gpio_put(MMM_CSWR_FM, 1);
	busy_wait_us(84);
#else
	mgspico::t_OutPort(0x7C, (uint8_t)addr);
	busy_wait_us(4);
	mgspico::t_OutPort(0x7D, (uint8_t)data);
	busy_wait_us(24);
#endif
	return;
}

void __time_critical_func(t_OutPSG)(const uint16_t addr, const uint16_t data)
{
#ifdef MGS_MUSE_MACHINA
	gpio_put(MMM_AEX0, 0);
	for(int t = 0; t < 8; ++t) {
		gpio_put(MMM_D0 +t, (addr>>t)&0x01);
	}
	gpio_put(MMM_CSWR_PSG, 0);
	busy_wait_us(1);
	gpio_put(MMM_CSWR_PSG, 1);
	busy_wait_us(1);

	gpio_put(MMM_AEX0, 1);
	for(int t = 0; t < 8; ++t) {
		gpio_put(MMM_D0 +t, (data>>t)&0x01);
	}
	gpio_put(MMM_CSWR_PSG, 0);
	busy_wait_us(1);
	gpio_put(MMM_CSWR_PSG, 1);
	busy_wait_us(1);

#else
	mgspico::t_OutPort(0xA0, (uint8_t)addr);
	busy_wait_us(1);
	mgspico::t_OutPort(0xA1, (uint8_t)data);
#endif
	return;
}

void __time_critical_func(t_OutSCC)(const z80memaddr_t addr, const uint16_t data)
{
#ifdef MGS_MUSE_MACHINA
	const uint32_t seg = addr&0xff00;
	gpio_put(MMM_ADDT_SCC, 1);	// ADDRESS
	switch(seg)
	{
		case 0x9000: gpio_put(MMM_AEX1, 0); gpio_put(MMM_AEX0, 0); break;
		case 0x9800: gpio_put(MMM_AEX1, 0); gpio_put(MMM_AEX0, 1); break;
		case 0xb800: gpio_put(MMM_AEX1, 1); gpio_put(MMM_AEX0, 0); break;
		case 0xbf00: gpio_put(MMM_AEX1, 1); gpio_put(MMM_AEX0, 1); break;
	}
	for(int t = 0; t < 8; ++t) {
		gpio_put(MMM_D0 +t, (addr>>t)&0x01);
	}
	busy_wait_us(1);

	gpio_put(MMM_ADDT_SCC, 0);	// DATA
	for(int t = 0; t < 8; ++t) {
		gpio_put(MMM_D0 +t, (data>>t)&0x01);
	}
	gpio_put(MMM_CSWR_SCC, 0);
	busy_wait_us(1);
	gpio_put(MMM_CSWR_SCC, 1);
	busy_wait_us(1);
#else
	mgspico::t_WriteMem(addr, data);
#endif
	return;
}



}; // namespace mgspico

