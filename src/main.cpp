// HINAN - simulate H8 microcomputer practice kit
// main.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "core.h"
#include "practice_kit.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Q_INIT_RESOURCE(resources);
  app.setApplicationName("HINAN");
  app.setApplicationVersion("0.1.0");

  // Command line option
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument(
      "file_path", QApplication::tr("File path that open on starting"));
  parser.process(QApplication::arguments());

  const QStringList args = parser.positionalArguments();
  if (!args.isEmpty()) {
    hinan::PracticeKit::Instance().reader->SetPath(args[0]);
  }

  hinan::Core* core = new hinan::Core();
  return app.exec();
}
