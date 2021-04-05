// HINAN - simulate H8 microcomputer practice kit
// setting_manager.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_SETTING_MANAGER_H_
#define HINAN_SETTING_MANAGER_H_

#include <QMap>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QVariant>

namespace hinan {
class SettingManager : public QObject {
  Q_OBJECT
 private:
  QMap<QString, QString> settings_;

  QSettings ini_;
  SettingManager();

 public:
  enum SettingList {
    CheckUpdateWhenStartup,
    CheckUpdateTimeOut,
    ShowSplashScreen,
    LedColor,
    TactSwitchToggle
  };
  Q_ENUM(SettingList)

  QString GetValue(SettingList);
  void    SetValue(SettingList, QString);
  void    Save();
  void    Load();
  void    SetDefault();

  static SettingManager& Instance();

 signals:
  void SettingUpdatedSignal();
};
} // namespace hinan

#endif // HINAN_SETTING_MANAGER_H_