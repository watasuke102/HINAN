// HINAN - simulate H8 microcomputer practice kit
// icon.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_ICON_H_
#define HINAN_ICON_H_

#include <QApplication>
#include <QIcon>
#include <QString>

const QString icon_path =
    /*QApplication::applicationDirPath() + */ "assets/icon/%1.svg";

namespace hinan {
namespace icon {
const QIcon open        = QIcon(icon_path.arg("open"));
const QIcon exit        = QIcon(icon_path.arg("exit"));
const QIcon start       = QIcon(icon_path.arg("start"));
const QIcon stop        = QIcon(icon_path.arg("stop"));
const QIcon reload      = QIcon(icon_path.arg("reload"));
const QIcon info        = QIcon(icon_path.arg("info"));
const QIcon qt          = QIcon(icon_path.arg("qt"));
const QIcon update      = QIcon(icon_path.arg("update"));
const QIcon view_source = QIcon(icon_path.arg("source"));
} // namespace icon
} // namespace hinan

#endif // HINAN_ICON_H_
