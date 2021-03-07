// HINAN - simulate H8 microcomputer practice kit
// port.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_PORT_H_
#define HINAN_PORT_H_

#include <QStringList>

namespace hinan {
namespace port {
  constexpr char    P1DDR[]   = "P1DDR";
  constexpr char    P2DDR[]   = "P2DDR";
  constexpr char    P3DDR[]   = "P3DDR";
  constexpr char    P4DDR[]   = "P4DDR";
  constexpr char    P5DDR[]   = "P5DDR";
  constexpr char    P6DDR[]   = "P6DDR";
  constexpr char    P7DDR[]   = "P7DDR";
  constexpr char    P8DDR[]   = "P8DDR";
  constexpr char    P9DDR[]   = "P9DDR";
  constexpr char    PADDR[]   = "PADDR";
  constexpr char    PBDDR[]   = "PBDDR";
  constexpr char    P1DR[]    = "P1DR";
  constexpr char    P2DR[]    = "P2DR";
  constexpr char    P3DR[]    = "P3DR";
  constexpr char    P4DR[]    = "P4DR";
  constexpr char    P5DR[]    = "P5DR";
  constexpr char    P6DR[]    = "P6DR";
  constexpr char    P7DR[]    = "P7DR";
  constexpr char    P8DR[]    = "P8DR";
  constexpr char    P9DR[]    = "P9DR";
  constexpr char    PADR[]    = "PADR";
  constexpr char    PBDR[]    = "PBDR";
  const QStringList port_list = {P1DDR, P2DDR, P3DDR, P4DDR, P5DDR, P6DDR,
                                 P7DDR, P8DDR, P9DDR, PADDR, PBDDR, P1DR,
                                 P2DR,  P3DR,  P4DR,  P5DR,  P6DR,  P7DR,
                                 P8DR,  P9DR,  PADR,  PBDR};
} // namespace port
} // namespace hinan

#endif // HINAN_PORT_H_
