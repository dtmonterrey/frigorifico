/*
    Copyright 2017 Evandro Pires Alves

    This file is part of Frigorifico.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_REMOTE
  #define HEADER_REMOTE

#include "IRremote.h"

#define REMOTE_ON   0xFFA25D
#define REMOTE_MODE 0xFF629D
#define REMOTE_MUTE 0xFFE21D
#define REMOTE_PLAY 0xFF22DD
#define REMOTE_PREV 0xFF02FD
#define REMOTE_NEXT 0xFFC23D
#define REMOTE_EQ   0xFFE01F
#define REMOTE_LESS 0xFFA857
#define REMOTE_MORE 0xFF906F
#define REMOTE_SHUF 0XFF9867
#define REMOTE_USD  0xFFB04F
#define REMOTE_0    0xFF6897
#define REMOTE_1    0xFF30CF
#define REMOTE_2    0xFF18E7
#define REMOTE_3    0xFF7A85
#define REMOTE_4    0xFF10EF
#define REMOTE_5    0xFF38C7
#define REMOTE_6    0xFF5AA5
#define REMOTE_7    0xFF42BD
#define REMOTE_8    0xFF4AB5
#define REMOTE_9    0xFF52AD

class Remote
{
  public:
};
#endif
