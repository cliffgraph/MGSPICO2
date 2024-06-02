# MGSPICO2 (MGS MUSE MACHINA)
2024/06/02 harumakkin

![mgspico2-01](docs/pics/mgspico2.png)</br>**fig.1 MGSPICO2**

## これは何？
OPLL、PSG、SCCの音源とRaspberryPi Picoを実装し、[MGSDRV](https://gigamix.jp/mgsdrv/)と[勤労五号(KINROU5.DRV)](https://sakuramail.net/fswold/music.html#muskin)を使用して、MGSとMuSICA楽曲データ再生し鑑賞できる個人製作のハードウェアです。
[MGSPICO](https://github.com/cliffgraph/MGSPICO)は、MSX用音源カートリッジを別途用意し使用していましたがMGSPICO2では音源部分もワンボード化したものです。
MGSPICO2と呼称していますが機能的にはMGSPICOと変わりありません。"2"は過剰なので、MGS MUSE MACHINAは別称を持っています。
この作品は多く廃版部品を使用しているので、製作はおすすめしません。

## 使い方
### 用意するもの
- MGSPICO2(MGS MUSE MACHINA)
- [MGSDRV.COM(Ver3.20)](https://gigamix.jp/mgsdrv/)
- MGS楽曲データファイル（.MGSファイル）
- [KINROU5.DRV(Ver2.00)](https://sakuramail.net/fswold/music.html#muskin)
- MuSICA楽曲データファイル（.BGMファイル）
- microSD カード
- DC5V電源(センタープラス 2.1mm DCプラグ）

### microSD カードの準備、セットアップ
- [MGSPICO](https://github.com/cliffgraph/MGSPICO)と同様です。

## 操作方法
- [MGSPICO](https://github.com/cliffgraph/MGSPICO)と同様です。
- MGSPICOとは異なり、MGSPICO2ではA/Bスイッチが有りますがこれはB側に切り替えたまま使用してください。

## ガーバーデータと部品表
- MGSPICO2-xxx/ ディレクトリ内を参照のこと。はんだ付けの難度は高いです。
- raspberry Pi Picoにインストールするファイルは、RasPiPico/dist/mgspico2.uf2 です
- TangNanoに書き込むファイルは、RasPiPico/dist/mmmscc.fs です

# LICENSEと利用に関する注意事項
1. MGSPICOのファームウェアとそのソースコード、回路図データおよび資料ファイルは MIT License で配布されます。ただし、MGSPICO は、FatFsと8x16文字フォントを使用しています。FatFs/8x16文字フォントのソースコードの扱いに関しては各々のLICENSEに従ってください。
2. 本作品は同人ハードウェア＆ソフトウェアです。本作品の設計およびソフトウェアは品質を保証していません。音源カートリッジや音響設備、その周辺機器が故障、破損したとしても自身で責任を負える方のみ本作品をご利用ください。特にハードウェアの製作を伴いますのでリスクがあります。製作の腕に自身のある方のみご利用ください。
3. 本作品の設計資料とソースコードの改変や改造、また、別の作品への利用、商用利用は自由です。ただし、1. 2.の制限を超える利用は各自でその責任と義務を負ってください。

### MGSPICOが組込利用しているソフトウェア(PICO-SDK以外)
- FatFs Copyright (C) 20xx, ChaN, all right reserved. http://elm-chan.org/fsw/ff/00index_e.html
- 8x16 文字フォント FONT8X16MIN.h https://github.com/askn37/OLED_SSD1306
- mmmscc.fs wave_table_sound https://github.com/hra1129/wave_table_sound (mmmscc.fsはwave_table_soundをMGSPICO2用途に一部修正を加えたものです）

### 起動時に読み込んで使用しているソフトウェア
- MGSDRV (C) Ain./Gigamix https://gigamix.jp/mgsdrv/
- 勤労５号（MuSICA互換ドライバ）
(C) 1996,1997 Keiichi Kuroda / BTO(MuSICA Laboratory) All rights reserved. https://sakuramail.net/fswold/music.html#muskin

## 修正履歴
|date|MGSPICO2|firmware|note|
|:--|:--|:--|:--|
|2024/06/02|MGSPICO2-02A|mgspico2.uf2(v1.6)|初版、MGSPICO v1.5相当です|

## 余禄
MGSPICO2 の機能に関係ないですが、開発中に見つけたものをメモ書きしておきます。
##### 特になし、、、
##### その他
- MGSPICOのRaspberryPiPicoはCPUのクロックアップを行っていません。mgspico2.uf2ファームウェアは標準の125MHzのままで動作しています。
- mgspico2.uf2ファームウェアはMGSPICOには使用できません。MGSPICO2のファームウェアもMGSPICOには使用できません。ただ、SDカードはそのまま使用できます。
