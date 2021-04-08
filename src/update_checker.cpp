// HINAN - simulate H8 microcomputer practice kit
// update_checker.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "update_checker.h"
#include "core.h"
#include "setting_manager.h"
#include <QApplication>
#include <QDesktopServices>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTimer>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

int VersionToInt(QString version) { return version.remove(".").toInt(); }

namespace hinan {
// If set isShowDialog false, message will print to stdout.
// When there is newer version, show the dialog regardress of isShowDialog.
UpdateChecker::UpdateChecker(bool isShowDialog = true)
    : isShowDialog_(isShowDialog) {
  manager_ = new QNetworkAccessManager;
  timer_.setSingleShot(true);
  connect(manager_, &QNetworkAccessManager::finished, this,
          &UpdateChecker::RequestFinished);
  connect(&timer_, &QTimer::timeout, this, &UpdateChecker::FinishedSignal);
}

void UpdateChecker::ShowDialog(DialogKind dialog_kind, QString body,
                               QString detail) {
  if (!isShowDialog_) {
    body.replace(QRegExp("<[bh]r>"), "\n");
    qInfo("%s", body.toUtf8().data());
    return;
  }
  switch (dialog_kind) {
    case DialogKind::info: Core::InfoDialog(body, detail); break;
    case DialogKind::critical: Core::ErrorDialog(body, detail); break;
  }
}

void UpdateChecker::Check() {
  int timeout;
  {
    bool ok;
    timeout = SettingManager::Instance()
                  .GetValue(SettingManager::CheckUpdateTimeOut)
                  .toInt(&ok);
    if (!ok) {
      // 10 second
      timeout = 10000;
    }
  }
  timer_.start(timeout);

  manager_->get(QNetworkRequest(
      QUrl("https://api.github.com/repos/watasuke102/HINAN/releases/latest")));
}

void UpdateChecker::RequestFinished(QNetworkReply* reply) {
  QString message;
  if (reply->error()) {
    ShowDialog(DialogKind::critical, tr("Error occurred"),
               reply->errorString());
    return;
  }

  QJsonObject json(QJsonDocument::fromJson(reply->readAll()).object());
  if (!json.contains("tag_name") || !json.contains("assets")) {
    ShowDialog(DialogKind::critical, tr("Irregular json format"), "");
    return;
  }
  message = tr("Current version: %1<br>Latest version: %2"
               "<hr>")
                .arg(QApplication::applicationVersion())
                .arg(json["tag_name"].toString());

  QString detail = json["name"].toString() + "\n" +
                   json["html_url"].toString() + "\n\n" +
                   json["body"].toString();

  const int current_version = VersionToInt(QApplication::applicationVersion());
  const int latest_version  = VersionToInt(json["tag_name"].toString());
  if (current_version >= latest_version) {
    message += tr("This software is up to date.");
    ShowDialog(DialogKind::info, message, detail);
  } else {
    message +=
        tr("Do you want to download the latest version?<br>(The browser will "
           "open)");
    int r = Core::YesNoDialog(message, detail);

    if (r == QMessageBox::Yes) {
      const QString asset_name =
#if defined(_WIN64)
          "windows"
#elif defined(__linux)
          "linux"
#endif
          ".zip";
      QJsonArray array    = json["assets"].toArray();
      bool       isOpened = false;
      for (int i = 0; i < array.size(); i++) {
        if (array[i].toObject()["name"].toString() == asset_name) {
          isOpened = true;
          const QUrl url =
              array[i].toObject()["browser_download_url"].toString();
          QDesktopServices::openUrl(url);
        }
      }
      if (isOpened) {
        Core::InfoDialog(
            tr("Open the download page in browser.\n"
               "Please unzip downloaded file, and copy to %1 and overwrite.")
                .arg(QApplication::applicationDirPath()));
      } else {
        Core::ErrorDialog(tr("Cannot find downloadable file."));
      }
    }
  }
  timer_.stop();
  emit FinishedSignal();
}
} // namespace hinan
