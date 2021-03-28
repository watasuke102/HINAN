// HINAN - simulate H8 microcomputer practice kit
// update_checker.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "update_checker.h"
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
UpdateChecker::UpdateChecker() {
  manager_ = new QNetworkAccessManager;
  connect(manager_, &QNetworkAccessManager::finished, this,
          &UpdateChecker::RequestFinished);
}

void UpdateChecker::Check() {
  manager_->get(QNetworkRequest(
      QUrl("https://api.github.com/repos/watasuke102/HINAN/releases/latest")));
}

void UpdateChecker::RequestFinished(QNetworkReply* reply) {
  QString message;
  if (reply->error()) {
    QMessageBox::critical(nullptr, tr("Check for update"),
                          tr("Error occurred"));
    return;
  }

  QJsonObject json(QJsonDocument::fromJson(reply->readAll()).object());
  if (!json.contains("tag_name") || !json.contains("assets")) {
    QMessageBox::critical(nullptr, tr("Check for update"),
                          tr("Irregular json format"));
    return;
  }
  message = tr("Current version: %1<br>Latest version: %2"
               "<hr>")
                .arg(QApplication::applicationVersion())
                .arg(json["tag_name"].toString());

  const int current_version = VersionToInt(QApplication::applicationVersion());
  const int latest_version  = VersionToInt(json["tag_name"].toString());
  if (current_version == latest_version) {
    message += tr("This software is up to date.");
    QMessageBox::information(nullptr, tr("Check for update"), message);
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
        QMessageBox::information(
            nullptr, tr("Info"),
            tr("Open the download page in browser.\n"
               "Please unzip downloaded file, and copy to %1 and overwrite.")
                .arg(QApplication::applicationDirPath()));
      } else {
        QMessageBox::critical(nullptr, tr("Error"),
                              tr("Cannot find downloadable file."));
      }
    }
  }
}
} // namespace hinan
