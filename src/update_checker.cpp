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
#include <QApplication>
#include <QDesktopServices>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
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
  connect(manager_, &QNetworkAccessManager::finished,
          [=](QNetworkReply* reply) {
            RequestFinished(reply);
            emit FinishedSignal();
          });
}

void UpdateChecker::ShowDialog(DialogKind dialog_kind, QString body) {
  if (!isShowDialog_) {
    qInfo("%s", body.toUtf8().data());
    return;
  }
  switch (dialog_kind) {
    case DialogKind::info: Core::InfoDialog(body); break;
    case DialogKind::critical: Core::ErrorDialog(body); break;
  }
}

void UpdateChecker::Check() {
  manager_->get(QNetworkRequest(
      QUrl("https://api.github.com/repos/watasuke102/HINAN/releases/latest")));
}

void UpdateChecker::RequestFinished(QNetworkReply* reply) {
  QString message;
  if (reply->error()) {
    ShowDialog(DialogKind::critical, tr("Error occurred"));
    return;
  }

  QJsonObject json(QJsonDocument::fromJson(reply->readAll()).object());
  if (!json.contains("tag_name") || !json.contains("assets")) {
    ShowDialog(DialogKind::critical, tr("Irregular json format"));
    return;
  }
  message = tr("Current version: %1<br>Latest version: %2"
               "<hr>")
                .arg(QApplication::applicationVersion())
                .arg(json["tag_name"].toString());

  const int current_version = VersionToInt(QApplication::applicationVersion());
  const int latest_version  = VersionToInt(json["tag_name"].toString());
  if (current_version >= latest_version) {
    message += tr("This software is up to date.");
    ShowDialog(DialogKind::info, message);
  } else {
    message +=
        tr("Do you want to download the latest version?<br>(The browser will "
           "open)");
    int r = QMessageBox::question(nullptr, tr("Check for update"), message);
    if (r == QMessageBox::Yes) {
      const QString asset_name =
#if defined(_WIN64)
          "windows-x64"
#elif defined(__linux)
          "linux-x64"
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
}
} // namespace hinan
