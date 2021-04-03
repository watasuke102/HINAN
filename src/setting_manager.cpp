// HINAN - simulate H8 microcomputer practice kit
// setting_manager.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "setting_manager.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMetaEnum>
#include <QObject>
#include <QTextCodec>

namespace hinan {
SettingManager::SettingManager()
    : ini_(QApplication::applicationDirPath() + "/settings.ini",
           QSettings::IniFormat) {
  ini_.setIniCodec(QTextCodec::codecForName("UTF-8"));

  QMetaEnum list = QMetaEnum::fromType<SettingList>();
  for (int i = 0; i < list.keyCount(); i++) {
    QString key = list.valueToKey(i);
    settings_.insert(key, ini_.value(key, "").toString());
  }

  if (!QFile::exists(ini_.fileName())) {
    qDebug("Setting file not found");
    SetDefault();
  }
}
SettingManager& SettingManager::Instance() {
  static SettingManager manager;
  return manager;
}

QString SettingManager::GetValue(SettingList i) {
  QString str = QMetaEnum::fromType<SettingList>().valueToKey(i);
  return settings_[str];
}
void SettingManager::SetValue(SettingList i, QString value) {
  QString str    = QMetaEnum::fromType<SettingList>().valueToKey(i);
  settings_[str] = value;
}
void SettingManager::Save() {
  QMetaEnum list = QMetaEnum::fromType<SettingList>();
  for (int i = 0; i < list.keyCount(); i++) {
    QString key = list.valueToKey(i);
    ini_.setValue(key, settings_[key]);
  }
  ini_.sync();
}
void SettingManager::Load() {
  QMetaEnum list = QMetaEnum::fromType<SettingList>();
  for (int i = 0; i < list.keyCount(); i++) {
    QString key    = list.valueToKey(i);
    settings_[key] = ini_.value(key, "").toString();
  }
}

void SettingManager::SetDefault() {
  QMetaEnum list = QMetaEnum::fromType<SettingList>();
  settings_[list.valueToKey(CheckUpdateWhenStartup)] = "true";
  settings_[list.valueToKey(CheckUpdateTimeOut)]     = "10000";
  settings_[list.valueToKey(ShowSplashScreen)]       = "true";
  settings_[list.valueToKey(LedColor)]               = "#ff0123";
  settings_[list.valueToKey(TactSwitchToggle)]       = "true";
  Save();
}

} // namespace hinan
