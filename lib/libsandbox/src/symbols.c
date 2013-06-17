/*******************************************************************************
 * Copyright (C) 2004-2009, 2011 LIU Yu, pineapple.liu@gmail.com               *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 *                                                                             *
 * 1. Redistributions of source code must retain the above copyright notice,   *
 *    this list of conditions and the following disclaimer.                    *
 *                                                                             *
 * 2. Redistributions in binary form must reproduce the above copyright        *
 *    notice, this list of conditions and the following disclaimer in the      *
 *    documentation and/or other materials provided with the distribution.     *
 *                                                                             *
 * 3. Neither the name of the author(s) nor the names of its contributors may  *
 *    be used to endorse or promote products derived from this software        *
 *    without specific prior written permission.                               *
 *                                                                             *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE    *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  *
 * POSSIBILITY OF SUCH DAMAGE.                                                 *
 ******************************************************************************/
/*
 * This file was automatically generated with "symbols.awk"
 */

#include "symbols.h"
#include <assert.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NDEBUG

const char *
s_event_type_name(int event)
{
    static const char * table[] = 
    {
        "ERROR", /* 0 */
        "EXIT", /* 1 */
        "SIGNAL", /* 2 */
        "SYSCALL", /* 3 */
        "SYSRET", /* 4 */
        "QUOTA", /* 5 */
    };
    assert(event < sizeof(table) / sizeof(char *));
    return table[event];
}

const char *
s_action_type_name(int action)
{
    static const char * table[] = 
    {
        "CONT", /* 0 */
        "FINI", /* 1 */
        "KILL", /* 2 */
    };
    assert(action < sizeof(table) / sizeof(char *));
    return table[action];
}

const char *
s_status_name(int status)
{
    static const char * table[] = 
    {
        "PRE", /* 0 */
        "RDY", /* 1 */
        "EXE", /* 2 */
        "BLK", /* 3 */
        "FIN", /* 4 */
        "S0", /* 5 */
        "S1", /* 6 */
        "S2", /* 7 */
    };
    assert(status < sizeof(table) / sizeof(char *));
    return table[status];
}

const char *
s_result_name(int result)
{
    static const char * table[] = 
    {
        "PD", /* 0 */
        "OK", /* 1 */
        "RF", /* 2 */
        "ML", /* 3 */
        "OL", /* 4 */
        "TL", /* 5 */
        "RT", /* 6 */
        "AT", /* 7 */
        "IE", /* 8 */
        "BP", /* 9 */
        "R0", /* 10 */
        "R1", /* 11 */
        "R2", /* 12 */
        "R3", /* 13 */
        "R4", /* 14 */
        "R5", /* 15 */
    };
    assert(result < sizeof(table) / sizeof(char *));
    return table[result];
}

const char *
trace_act_name(int action)
{
    static const char * table[] = 
    {
        "NOP", /* 0 */
        "ACK", /* 1 */
        "END", /* 2 */
        "NEXT", /* 3 */
        "KILL", /* 4 */
        "GETREGS", /* 5 */
        "GETDATA", /* 6 */
        "GETSIGINFO", /* 7 */
        "SETREGS", /* 8 */
    };
    assert(action < sizeof(table) / sizeof(char *));
    return table[action];
}

#endif /* NDEBUG */

#ifdef __cplusplus
} /* extern "C" */
#endif
