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

#include <QString>
#include <QStringList>

namespace hinan {
namespace port {
const QString     P1DDR     = "P1DDR";
const QString     P2DDR     = "P2DDR";
const QString     P3DDR     = "P3DDR";
const QString     P4DDR     = "P4DDR";
const QString     P5DDR     = "P5DDR";
const QString     P6DDR     = "P6DDR";
const QString     P7DDR     = "P7DDR";
const QString     P8DDR     = "P8DDR";
const QString     P9DDR     = "P9DDR";
const QString     PADDR     = "PADDR";
const QString     PBDDR     = "PBDDR";
const QString     P1DR      = "P1DR";
const QString     P2DR      = "P2DR";
const QString     P3DR      = "P3DR";
const QString     P4DR      = "P4DR";
const QString     P5DR      = "P5DR";
const QString     P6DR      = "P6DR";
const QString     P7DR      = "P7DR";
const QString     P8DR      = "P8DR";
const QString     P9DR      = "P9DR";
const QString     PADR      = "PADR";
const QString     PBDR      = "PBDR";
const QStringList port_list = {
    P1DDR, P2DDR, P3DDR, P4DDR, P5DDR, P6DDR, P7DDR, P8DDR, P9DDR, PADDR, PBDDR,
    P1DR,  P2DR,  P3DR,  P4DR,  P5DR,  P6DR,  P7DR,  P8DR,  P9DR,  PADR,  PBDR};
} // namespace port
} // namespace hinan

#endif // HINAN_PORT_H_
