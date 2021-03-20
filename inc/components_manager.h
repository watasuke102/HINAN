// HINAN - simulate H8 microcomputer practice kit
// components_manager.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_COMPONENTs_MANAGER_H_
#define HINAN_COMPONENTs_MANAGER_H_

#include "components/component_interface.h"
#include <QObject>
#include <QVector>
#include <QWidget>

namespace hinan {
class ComponentsManager : public QObject {
  Q_OBJECT
 private:
  QVector<components::ComponentInterface*> components_;

  QWidget* widget_;
  bool     isTerminated_;

 public:
  ComponentsManager();
  ~ComponentsManager();
  void Update();
  void SetWidgetsParent(QWidget*);

 public slots:
  void Run();
  void Terminate();
  void Resize(QSize, double);
};
} // namespace hinan

#endif // HINAN_COMPONENT_MANAGER_H_