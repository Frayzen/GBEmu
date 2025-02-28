ld sp, hStackBottom
xor a
ld hl, _VRAM + SIZEOF(VRAM) - 1
ld [hld], a
bit 7, h
jr nz, .clearVRAM
ld hl, rNR52
ld a, AUDENA_ON
ld [hld], a
ldh [c], a
inc c
ldh [c], a
ld [hld], a
ld a, $77
ld [hl], a
ld a, %11_11_11_00
ldh [rBGP], a
ld hl, HeaderLogo
push hl
ld de, Logo
ld a, [de]
inc de
cp [hl]
jr nz, Lockup
inc hl
ld a, l
cp LOW(HeaderTitle)
jr nz, .checkLogo
ld b, HeaderChecksum - HeaderTitle
ld a, b
add a, [hl]
inc hl
dec b
jr nz, .computeChecksum
add a, [hl]
jr nz, Lockup
ld de, HeaderLogo
ld hl, vLogoTiles
ld a, [de]
call DecompressFirstNibble
call DecompressSecondNibble
inc de
ld a, e
cp LOW(HeaderTitle)
jr nz, .decompressLogo
ld de, RTile
ld b, 8
ld a, [de]
inc de
ld [hli], a
dec b
jr nz, .copyRTile
ld a, $19
ld a, $18
ld hl, vMainTilemap + SCRN_VX_B * 9 + 15
ld c, 12
ld [hld], a
dec a
jr z, ScrollLogo
ld [hld], a
dec c
jr nz, .writeTilemapByte
ld de, -(SCRN_VX_B - 12)
add hl, de
ld l, LOW(vMainTilemap + SCRN_VX_B * 8 + 15)
jr .writeTilemapRow
ld a, 100
ld d, a
ldh [rSCY], a
ld a, LCDCF_ON | LCDCF_BLK01 | LCDCF_BGON
ldh [rLCDC], a
ld e, 2
call DelayFrames
ld c, 12
ldh a, [rLY]
cp SCRN_Y
jr nz, .waitVBlank
dec c
jr nz, .waitVBlank
dec e
jr nz, .delayFrames
inc h
ld a, h
ld e, $83
cp $62
jr z, .playSound
ld e, $C1
cp $64
jr nz, .dontPlaySound
ld a, e
ldh [c], a
ld a, AUDHIGH_RESTART | 7
ldh [c], a
ldh a, [rSCY]
sub b
ldh [rSCY], a
dec d
jr nz, .loop
dec b
jr nz, Done
jr nz, CheckLogo
ld d, 32
jr .loop
ld a, LCDCF_ON | LCDCF_BLK01 | LCDCF_BGON
ldh [rLCDC], a
ld e, 20
call DelayFrames
ldh a, [rBGP]
xor a, $FF
ldh [rBGP], a
jr .loop
ld c, a
push bc
pop bc
dec b
jr nz, .loop
ld [hli], a
inc hl
ret
ld c, 12
ldh a, [rLY]
cp SCRN_Y
jr nz, .loop
dec c
jr nz, .loop
dec e
jr nz, DelayFrames
ret
logo_row_gfx_nybbles \
logo_row_gfx_nybbles \
PUSHO
OPT b.X
db %..XXXX..
db %.X....X.
db %X.XXX..X
db %X.X..X.X
db %X.XXX..X
db %X.X..X.X
db %.X....X.
db %..XXXX..
POPO
ld hl, HeaderLogo
ld de, Logo
ld a, [de]
inc de
cp [hl]
jr nz, .logoFailure
inc hl
ld a, l
cp LOW(HeaderTitle)
jr nz, .compare
ld b, HeaderChecksum - HeaderTitle
ld a, b
add a, [hl]
inc hl
dec b
jr nz, .computeChecksum
add a, [hl]
jr nz, .checksumFailure
ld a, BOOTUP_A_MGB
ld a, BOOTUP_A_DMG
ds 2
inc a
ldh [rBANK], a
ds TILE_SIZE
ds (HeaderTitle - HeaderLogo) * TILE_SIZE / 2
ds TILE_SIZE
ds SCRN_VX_B * SCRN_VY_B
ds $10
