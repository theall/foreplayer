#
# Copyright (c) Bilge Theall
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
cmake_minimum_required(VERSION 2.6)

# project name: m1lib
project(m1lib)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CMAKE_CUSTOME_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set(CMAKE_CUSTOME_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DM1_DEBUG)
else()
    add_definitions(-DM1_RELEASE)
endif()

find_file(SDL2_HEADER sdl.h HINTS ${CMAKE_CUSTOME_INCLUDE_PATH}/SDL2)
find_library(SDL2_LIB sdl2 HINTS ${CMAKE_CUSTOME_LIB_PATH})
find_file(UNZIP_HEADER unzip.h HINTS ${CMAKE_CUSTOME_INCLUDE_PATH}/unzip)
find_library(UNZIP_LIB unzip HINTS ${CMAKE_CUSTOME_LIB_PATH})

include_directories(
    src
    src/libs/crypt
    src/libs/expat
    src/emulator
    src/emulator/cpu
    src/emulator/sound
    ../../include
    ${CMAKE_CUSTOME_INCLUDE_PATH/expat}
    ${CMAKE_CUSTOME_INCLUDE_PATH/SDL2}
    ${CMAKE_CUSTOME_INCLUDE_PATH}
)

add_definitions(
    -DSOUND_OUTPUT=1
    -DHAS_YM2612=1
    -DHAS_YM3438=1
    -DHAS_YM2203=1
    -DHAS_YM2610=1
    -DHAS_YM2610B=1
    -DHAS_YM3812=1
    -DHAS_YM3526=1
    -DHAS_M65C02=1
    -DLSB_FIRST=1
    -DHAS_M6803=1
    -DHAS_M6808=1
    -DHAS_ADSP2105=1
    -DHAS_ES5505=1
    -DHAS_ES5506=1
    -DHAS_K005289=1
    -DHAS_SN76496=1
    -DHAS_K007232=1
    -DHAS_NAMCO=1
    -DHAS_CEM3394=1
    -DHAS_YMZ280B=1
    -DHAS_AY8910=1
    -DHAS_DAC=1
    -DHAS_SEGAPCM=1
    -DHAS_OKIM6295=1
    -DHAS_TMS5220=1
    -DHAS_ADPCM=1
    -DHAS_K051649=1
    -DHAS_YM2151_ALT=1
    -DHAS_RF5C68=1
    -DHAS_QSOUND=1
    -DHAS_K054539=1
    -DHAS_UPD7759=1
    -DHAS_MULTIPCM=1
    -DHAS_YMF278B=1
    -DHAS_MSM5232=1
    -DHAS_K053260=1
    -DHAS_POKEY=1
    -DHAS_HC55516=1
    -DHAS_IREMGA20=1
    -DHAS_MSM5205=1
    -DHAS_C140=1
    -DHAS_BSMT2000=1
    -DHAS_HD63701=1
    -DHAS_CUSTOM=1
    -DHAS_ADSP2100=1
    -DHAS_ADSP2101=1
    -DHAS_ADSP2115=1
    -DHAS_YMF262=1
    -DHAS_YM2413=1
    -DHAS_YM2608=1
    -DHAS_VLM5030=1
    -DHAS_MPEG=1
    -DHAS_N7751=1
    -DHAS_PIC16C54=1
    -DHAS_PIC16C55=1
    -DHAS_PIC16C56=1
    -DHAS_PIC16C57=1
    -DHAS_PIC16C58=1
    -DHAS_C352=1
    -DHAS_YMF271=1
    -DHAS_SCSP=1
    -DHAS_Y8950=1
    -DHAS_ADSP2104=1
    -DM1=1
    -DUNIX=1
    -DX8664=0
    -DPS2=0
    -DINLINE=static\ __inline__
)

# set source files
set(m1lib 
    src/dsnd.cpp
    src/gamelist.cpp
    src/irem_cpu.cpp
    src/kabuki.cpp
    #src/m1filter.cpp
    src/m1queue.cpp
    src/m1snd.cpp
    src/trklist.cpp
    src/xmlout.cpp
    src/6821pia.c
    src/chd.c
    src/chdcd.c
    src/cpuintrf.c
    src/d7725.c
    src/harddisk.c
    src/memory.c
    src/rom.c
    src/sndintrf.c
    src/state.c
    src/taitosnd.c
    src/timer.c
    src/emulator/boards/brd_88games.cpp
    src/emulator/boards/brd_1942.cpp
    src/emulator/boards/brd_afega.cpp
    src/emulator/boards/brd_airbustr.cpp
    src/emulator/boards/brd_airgallet.cpp
    src/emulator/boards/brd_ajax.cpp
    src/emulator/boards/brd_aquarium.cpp
    src/emulator/boards/brd_arkanoid.cpp
    src/emulator/boards/brd_atarijsa.cpp
    src/emulator/boards/brd_atarisy1.cpp
    src/emulator/boards/brd_atarisy2.cpp
    src/emulator/boards/brd_bbusters.cpp
    src/emulator/boards/brd_beatmania.cpp
    src/emulator/boards/brd_bjack.cpp
    src/emulator/boards/brd_bladestl.cpp
    src/emulator/boards/brd_blzntrnd.cpp
    src/emulator/boards/brd_bottom9.cpp
    src/emulator/boards/brd_braveblade.cpp
    src/emulator/boards/brd_btime.cpp
    src/emulator/boards/brd_btoads.cpp
    src/emulator/boards/brd_bubblebobble.cpp
    src/emulator/boards/brd_buggyboy.cpp
    src/emulator/boards/brd_cage.cpp
    src/emulator/boards/brd_cavez80.cpp
    src/emulator/boards/brd_chipsqueakdeluxe.cpp
    src/emulator/boards/brd_circusc.cpp
    src/emulator/boards/brd_cischeat.cpp
    src/emulator/boards/brd_combatsc.cpp
    src/emulator/boards/brd_contra.cpp
    src/emulator/boards/brd_cps1.cpp
    src/emulator/boards/brd_darius.cpp
    src/emulator/boards/brd_dbz2.cpp
    src/emulator/boards/brd_dcs.cpp
    src/emulator/boards/brd_ddragon.cpp
    src/emulator/boards/brd_ddragon3.cpp
    src/emulator/boards/brd_deco8.cpp
    src/emulator/boards/brd_deco32.cpp
    src/emulator/boards/brd_djboy.cpp
    src/emulator/boards/brd_dooyong.cpp
    src/emulator/boards/brd_douni.cpp
    src/emulator/boards/brd_dsb.cpp
    src/emulator/boards/brd_dsbz80.cpp
    src/emulator/boards/brd_endurobl2.cpp
    src/emulator/boards/brd_equites.cpp
    src/emulator/boards/brd_f3.cpp
    src/emulator/boards/brd_fcombat.cpp
    src/emulator/boards/brd_flower.cpp
    src/emulator/boards/brd_frogger.cpp
    src/emulator/boards/brd_fuuki32.cpp
    src/emulator/boards/brd_galaga.cpp
    src/emulator/boards/brd_gauntlet.cpp
    src/emulator/boards/brd_genesis.cpp
    src/emulator/boards/brd_gladiator.cpp
    src/emulator/boards/brd_gng.cpp
    src/emulator/boards/brd_gott3.cpp
    src/emulator/boards/brd_gradius.cpp
    src/emulator/boards/brd_gradius3.cpp
    src/emulator/boards/brd_gx.cpp
    src/emulator/boards/brd_gyruss.cpp
    src/emulator/boards/brd_harddriv.cpp
    src/emulator/boards/brd_hatch.cpp
    src/emulator/boards/brd_hcastle.cpp
    src/emulator/boards/brd_hexion.cpp
    src/emulator/boards/brd_hotrock.cpp
    src/emulator/boards/brd_hyperduel.cpp
    src/emulator/boards/brd_itech32.cpp
    src/emulator/boards/brd_jaleco.cpp
    src/emulator/boards/brd_jedi.cpp
    src/emulator/boards/brd_legion.cpp
    src/emulator/boards/brd_lemmings.cpp
    src/emulator/boards/brd_logicpro.cpp
    src/emulator/boards/brd_m72.cpp
    src/emulator/boards/brd_m92.cpp
    src/emulator/boards/brd_macrossplus.cpp
    src/emulator/boards/brd_magiccat.cpp
    src/emulator/boards/brd_mappy.cpp
    src/emulator/boards/brd_megasys1.cpp
    src/emulator/boards/brd_mitchell.cpp
    src/emulator/boards/brd_mnight.cpp
    src/emulator/boards/brd_mpatrol.cpp
    src/emulator/boards/brd_ms32.cpp
    src/emulator/boards/brd_multi32.cpp
    src/emulator/boards/brd_namcona.cpp
    src/emulator/boards/brd_namh8.cpp
    src/emulator/boards/brd_namsys1.cpp
    src/emulator/boards/brd_namsys21.cpp
    src/emulator/boards/brd_namsys86.cpp
    src/emulator/boards/brd_neogeo.cpp
    src/emulator/boards/brd_njgaiden.cpp
    src/emulator/boards/brd_nmk16.cpp
    src/emulator/boards/brd_nslash.cpp
    src/emulator/boards/brd_null.cpp
    src/emulator/boards/brd_oneshot.cpp
    src/emulator/boards/brd_overdrive.cpp
    src/emulator/boards/brd_panicr.cpp
    src/emulator/boards/brd_parodius.cpp
    src/emulator/boards/brd_pizza.cpp
    src/emulator/boards/brd_popeye.cpp
    src/emulator/boards/brd_psychic5.cpp
    src/emulator/boards/brd_psycho.cpp
    src/emulator/boards/brd_qsound.cpp
    src/emulator/boards/brd_raiden2.cpp
    src/emulator/boards/brd_raizing.cpp
    src/emulator/boards/brd_rallyx.cpp
    src/emulator/boards/brd_rastan.cpp
    src/emulator/boards/brd_renegade.cpp
    src/emulator/boards/brd_rushcrash.cpp
    src/emulator/boards/brd_rygar.cpp
    src/emulator/boards/brd_s1945.cpp
    src/emulator/boards/brd_scsp.cpp
    src/emulator/boards/brd_segac2.cpp
    src/emulator/boards/brd_segamodel1.cpp
    src/emulator/boards/brd_segapcm.cpp
    src/emulator/boards/brd_segasys1.cpp
    src/emulator/boards/brd_sf1.cpp
    src/emulator/boards/brd_sharrier.cpp
    src/emulator/boards/brd_sidepck.cpp
    src/emulator/boards/brd_skns.cpp
    src/emulator/boards/brd_slapfight.cpp
    src/emulator/boards/brd_snk68k.cpp
    src/emulator/boards/brd_spacegun.cpp
    src/emulator/boards/brd_spi.cpp
    src/emulator/boards/brd_sshang.cpp
    src/emulator/boards/brd_ssio.cpp
    src/emulator/boards/brd_ssys22.cpp
    src/emulator/boards/brd_starwars.cpp
    src/emulator/boards/brd_sun16.cpp
    src/emulator/boards/brd_sys16.cpp
    src/emulator/boards/brd_sys1832.cpp
    src/emulator/boards/brd_taifx1.cpp
    src/emulator/boards/brd_tail2nose.cpp
    src/emulator/boards/brd_taito84.cpp
    src/emulator/boards/brd_taitosj.cpp
    src/emulator/boards/brd_tatass.cpp
    src/emulator/boards/brd_tatsumi.cpp
    src/emulator/boards/brd_tecmo16.cpp
    src/emulator/boards/brd_tecmosys.cpp
    src/emulator/boards/brd_thunder.cpp
    src/emulator/boards/brd_tnzs.cpp
    src/emulator/boards/brd_toaplan1.cpp
    src/emulator/boards/brd_twin16.cpp
    src/emulator/boards/brd_wecleman.cpp
    src/emulator/boards/brd_wmsadpcm.cpp
    src/emulator/boards/brd_wmscvsd.cpp
    src/emulator/boards/brd_xexex.cpp
    src/emulator/boards/brd_yunsun.cpp
    #src/emulator/boards/gen_inc_gems.cpp
    #src/emulator/boards/gen_inc_smpsz80.cpp
    #src/emulator/boards/gen_inc_soundimages.cpp
    src/emulator/cpu/2100dasm.c
    #src/emulator/cpu/2100ops.c
    #src/emulator/cpu/6309ops.c
    #src/emulator/cpu/6309tbl.c
    #src/emulator/cpu/6800ops.c
    #src/emulator/cpu/6800tbl.c
    #src/emulator/cpu/6809ops.c
    #src/emulator/cpu/6809tbl.c
    #src/emulator/cpu/32031ops.c
    src/emulator/cpu/adsp2100.c
    src/emulator/cpu/h8periph.c
    src/emulator/cpu/h6280.c
    src/emulator/cpu/h83002.c
    src/emulator/cpu/hd6309.c
    src/emulator/cpu/i8039.c
    src/emulator/cpu/i8085.c
    src/emulator/cpu/m68kcpu.c
    #src/emulator/cpu/m68kfpu.c
    src/emulator/cpu/m68kops.c
    src/emulator/cpu/m6502.c
    src/emulator/cpu/m6800.c
    src/emulator/cpu/m6809.c
    src/emulator/cpu/m37710.c
    src/emulator/cpu/m37710o0.c
    src/emulator/cpu/m37710o1.c
    src/emulator/cpu/m37710o2.c
    src/emulator/cpu/m37710o3.c
    src/emulator/cpu/nec.c
    src/emulator/cpu/pic16c5x.c
    #src/emulator/cpu/t65c02.c
    #src/emulator/cpu/t6502.c
    #src/emulator/cpu/tblh6280.c
    src/emulator/cpu/tms32010.c
    src/emulator/cpu/tms32031.c
    src/emulator/cpu/z80.c
    src/emulator/sound/262intf.c
    src/emulator/sound/2151intf.c
    src/emulator/sound/2203intf.c
    src/emulator/sound/2413intf.c
    src/emulator/sound/2608intf.c
    src/emulator/sound/2610intf.c
    src/emulator/sound/2612intf.c
    src/emulator/sound/3812intf.c
    src/emulator/sound/5220intf.c
    src/emulator/sound/adpcm.c
    src/emulator/sound/ay8910.c
    src/emulator/sound/bsmt2000.c
    src/emulator/sound/c140.c
    src/emulator/sound/c352.c
    src/emulator/sound/cem3394.c
    src/emulator/sound/dac.c
    src/emulator/sound/dmadac.c
    src/emulator/sound/es5506.c
    src/emulator/sound/flower.c
    src/emulator/sound/fm.c
    src/emulator/sound/fmopl.c
    src/emulator/sound/hc55516.c
    src/emulator/sound/iremga20.c
    src/emulator/sound/k005289.c
    src/emulator/sound/k007232.c
    src/emulator/sound/k051649.c
    src/emulator/sound/k053260.c
    src/emulator/sound/k054539.c
    src/emulator/sound/msm5205.c
    src/emulator/sound/msm5232.c
    src/emulator/sound/multipcm.c
    src/emulator/sound/namco.c
    src/emulator/sound/pokey.c
    src/emulator/sound/qsound.c
    src/emulator/sound/rf5c68.c
    src/emulator/sound/rf5c400.c
    src/emulator/sound/samples.c
    src/emulator/sound/scsp.c
    src/emulator/sound/scspdsp.c
    #src/emulator/sound/scsplfo.c
    src/emulator/sound/segapcm.c
    src/emulator/sound/sn76496.c
    src/emulator/sound/streams.c
    src/emulator/sound/tms5220.c
    src/emulator/sound/tms5220r.c
    src/emulator/sound/tms57002.c
    src/emulator/sound/upd7759.c
    src/emulator/sound/vlm5030.c
    src/emulator/sound/ym2151.c
    src/emulator/sound/ym2413.c
    src/emulator/sound/ymdeltat.c
    src/emulator/sound/ymf262.c
    src/emulator/sound/ymf271.c
    src/emulator/sound/ymf278b.c
    src/emulator/sound/ymz280b.c
    src/emulator/mpeg/audio.c
    src/emulator/mpeg/dump.c
    src/emulator/mpeg/getbits.c
    src/emulator/mpeg/getdata.c
    src/emulator/mpeg/huffman.c
    src/emulator/mpeg/layer2.c
    src/emulator/mpeg/layer3.c
    src/emulator/mpeg/misc2.c
    src/emulator/mpeg/position.c
    src/emulator/mpeg/transform.c
    src/emulator/mpeg/util.c
    src/libs/crypt/md5.c
    src/libs/crypt/sha1.c
    src/wavelog.cpp
    src/moddir.cpp
)

# set make to a static library
add_library(m1 SHARED ${m1lib})
target_link_libraries(m1 -LSDL2_LIBRARY -lSDL2 -LEXPAT_LIBRARY -lexpat -L${CMAKE_CUSTOME_LIB_PATH} -lunzip -lz)

install(FILES ${CMAKE_SOURCE_DIR}/src/m1ui.h DESTINATION include)
install(TARGETS m1
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib)
