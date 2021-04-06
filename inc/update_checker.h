// HINAN - simulate H8 microcomputer practice kit
// update_checker.h
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef HINAN_UPDATE_CHECKER_H_
#define HINAN_UPDATE_CHECKER_H_

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace hinan {
class UpdateChecker : public QObject {
  Q_OBJECT
 private:
  QNetworkAccessManager* manager_;

  enum class DialogKind { info, critical };
  bool isShowDialog_;
  QTimer timer_;
  void ShowDialog(DialogKind, QString, QString);

 public:
  UpdateChecker(bool);
  void Check();

 signals:
  void FinishedSignal();

 private slots:
  void RequestFinished(QNetworkReply*);
};
} // namespace hinan

#endif // HINAN_UPDATE_CHECKER_H_
