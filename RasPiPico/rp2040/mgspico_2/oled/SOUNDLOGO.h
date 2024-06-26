/*
* Copyright (c) 2024 Harumakkin.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif



extern const int MSX_MUSIC_LOGO_LX = 32;
extern const int MSX_MUSIC_LOGO_LY = 32;
extern const uint8_t MSX_MUSIC_LOGO_32x32_BITMAP[] = {
	// MSX-MUSIC,  32x32px
	0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
	0x03, 0xf3, 0xf3, 0xf3, 0xe3, 0xc3, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0x07, 0x07, 0x0f, 0x0f, 0x1f, 0x1f, 0x3e, 0xfc, 0xf8, 0xc0, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
	0xfc, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc3, 0xcf, 0xcf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xcf, 0xcf, 
	0xc7, 0xc3, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff
};

extern const int SCC_LOGO_LX = 80;
extern const int SCC_LOGO_LY = 32;
extern const uint8_t SCC_80x32_BITMAP[] = {
	// SCC, 80x32px
	0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xe3, 0xf3, 
	0xf3, 0xfb, 0x7b, 0x7b, 0x7b, 0x7b, 0xf3, 0xf3, 0xe3, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
	0x03, 0x03, 0xc3, 0xe3, 0xf3, 0xf3, 0xfb, 0x7b, 0x7b, 0x7b, 0xfb, 0xf3, 0xf3, 0xe3, 0x03, 0x03, 
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xc3, 0xe3, 0xf3, 0xf3, 0xfb, 0x7b, 0x7b, 0x7b, 0xfb, 
	0xf3, 0xf3, 0xe3, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7f, 
	0xff, 0xff, 0xf0, 0xe0, 0xe0, 0xc0, 0x83, 0x03, 0x03, 0x03, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x06, 0x00, 
	0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x07, 
	0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 
	0xe0, 0x81, 0x01, 0x03, 0x07, 0x0f, 0xff, 0xff, 0xfe, 0xfc, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 
	0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xf0, 
	0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0xcf, 
	0xcf, 0xdf, 0xde, 0xdc, 0xde, 0xde, 0xdf, 0xcf, 0xc7, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
	0xc0, 0xc0, 0xc3, 0xc7, 0xcf, 0xdf, 0xdf, 0xde, 0xdc, 0xde, 0xdf, 0xcf, 0xcf, 0xc7, 0xc0, 0xc0, 
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc7, 0xcf, 0xdf, 0xdf, 0xde, 0xdc, 0xde, 0xdf, 
	0xcf, 0xcf, 0xc7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff
};



extern const int PLAY_LX = 8;
extern const int PLAY_LY = 16;
extern const uint8_t PLAY_8x16_BITMAP[] = {
// 'PLAY_8x16', 8x16px
0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00
	// // 'PLAY_13x16', 13x16px
	// 0xfc, 0xfc, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x7f, 0x7f, 0x3f, 
	// 0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x00
};

extern const int RANDOM_LX = 13;
extern const int RANDOM_LY = 16;
extern const uint8_t RANDOM_13x16_BITMAP[] = {
 // 'RANDOM_13x16', 13x16px
	0x10, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x40, 0x20, 0x10, 0x54, 0x38, 0x10, 0x10, 0x10, 0x08, 
	0x04, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x54, 0x38, 0x10
};

#ifdef __cplusplus
}
#endif


// end of header
