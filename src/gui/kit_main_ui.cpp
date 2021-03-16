// HINAN - simulate H8 microcomputer practice kit
// kit_main_ui.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/kit_main_ui.h"
#include <QDebug>
#include <QLayout>
#include <QSize>
#include <QtSvg/QSvgWidget>

namespace hinan {
namespace gui {
SvgWidget::SvgWidget(QString path, QSize* size)
    : QSvgWidget(path), parent_size_(size) {}

void SvgWidget::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  QSize s = event->size();
  // svg size is 1000*700 (10:7)
  s.setHeight(s.width() / 10 * 7);
  // when image is larger than widget's height + margin
  if (s.height() > (parent_size_->height() - 20)) {
    qDebug("LARGE");
    s.setHeight(parent_size_->height() - 20);
    s.setWidth(s.height() / 7 * 10);
  }
  resize(s);
}

KitMainUi::KitMainUi() {
  window_size_ = new QSize;
  window_size_->setWidth(this->size().width());
  window_size_->setHeight(this->size().height());
  QVBoxLayout* layout = new QVBoxLayout;
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(new SvgWidget("assets/canvas.svg", window_size_));
  setLayout(layout);
}
void KitMainUi::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  window_size_->setWidth(event->size().width());
  window_size_->setHeight(event->size().height());
}
} // namespace gui
} // namespace hinan
