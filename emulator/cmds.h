/**
 *  archi/melbus - A melbus node for CD/MD emulation in swedish cars, for Arduino
 *  See https://github.com/archi/melbus
 *   Copyright (C) 2015-2016 Sebastian Meyer
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

enum Cmd {
    Init,
    InitIgn,
    InitWaiting, /* Pseudo command */
    TrackInfo,
    CartInfo,
    NextTrack,
    PrevTrack,
    NextDisc,
    PrevDisc,
    NopAck,
    Wait, //pseudo CMD -> waiting for a CMD
    PowerUp,
    PowerDown,
    FFWD,
    FREW,
    ScanMode,
    RndMode
};

struct cmd_t {
    Cmd cmd;
    const unsigned char length;
    const unsigned char code[6];
};

//TODO move to PROG_MEM?
#define g_cmdTableSize 14
const struct cmd_t g_cmdTable[g_cmdTableSize] = {
    {Init,      3, {0x07, 0x1a, 0xee}},
    {InitIgn,   3, {0x00, 0x1c, 0xed}},
    {TrackInfo, 4, {0x1b, 0xe0, 0x01, 0x08}}, //evtl no 0x10?
    {CartInfo,  2, {0x1e, 0xef}},
    {NextTrack, 4, {0x1b, 0x2d, 0x40, 0x01}},
    {PrevTrack, 4, {0x1b, 0x2d, 0x00, 0x01}},
    {NextDisc,  3, {0x1a, 0x50, 0x41}},
    {PrevDisc,  3, {0x1a, 0x50, 0x01}},
    {PowerUp,   2, {0x19, 0x2f}},    //PowerUp
    {PowerDown, 2, {0x19, 0x22}},    //PowerDown
    {FFWD,      2, {0x19, 0x29}},    //FastFwd
    {FREW,      2, {0x19, 0x26}},    //FastRew
    {ScanMode,  2, {0x19, 0x2e}},    //ScanMode
    {RndMode,   2, {0x19, 0x52}}     //RndMode
};

#ifdef ENABLE_SERIAL
void printCmd (Cmd c) {
#define PCMD(_Y_, _X_) case _X_: Serial.println (#_Y_); break        
    switch (c) {
        PCMD (I0, Init);
        PCMD (I1, InitIgn);
        PCMD (TI, TrackInfo);
        PCMD (CI, CartInfo);
        PCMD (T>, NextTrack);
        PCMD (T<, PrevTrack);
        PCMD (D>, NextDisc);
        PCMD (D<, PrevDisc);
        PCMD (NA, NopAck);
        PCMD (IW, InitWaiting);
        PCMD (WT, Wait);
        PCMD (PU, PowerUp);
        PCMD (PD, PowerDown);
        PCMD (FF, FFWD);
        PCMD (FR, FREW);
        PCMD (SM, ScanMode);
        PCMD (RM, RndMode);
    }
#undef PCMD
}
#endif
