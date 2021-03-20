// HINAN - simulate H8 microcomputer practice kit
// kit_main_ui.cpp
//
// CopyRight (c) 2021 Watasuke
// Email  : <watasuke102@gmail.com>
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/kit_main_ui.h"
#include "components/led.h"
#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QPalette>
#include <QSize>
#include <QtSvg/QSvgWidget>

constexpr int MARGIN = 10;

QRect Expantion(QRect base, double rate) {
  auto o = base;
  base.moveTo(base.x() * rate, base.y() * rate);
  base.setWidth(base.width() * rate);
  base.setHeight(base.height() * rate);
  return base;
}

namespace hinan {
namespace gui {
SvgWidget::SvgWidget(QWidget* parent, QString path)
    : QSvgWidget(path, parent) {}

void SvgWidget::changeSize(QSize parent_size) {
  QSize target = parent_size;
  // svg size is 1000*700 (10:7)
  target.setHeight(parent_size.width() / 10 * 7);
  target.setWidth(parent_size.width() - (MARGIN * 2));

  // when image is larger than widget's height + margin
  if (target.height() > (parent_size.height() - (MARGIN * 2))) {
    target.setHeight(parent_size.height() - (MARGIN * 2));
    target.setWidth((target.height() / 7 * 10) - (MARGIN * 2));
  }
  setGeometry(MARGIN, MARGIN, target.width(), target.height());
}

KitMainUi::KitMainUi() : original_width_(494) {
  widget_ = new SvgWidget(this, QApplication::applicationDirPath() +
                                    "/assets/canvas.svg");
  widget_->setGeometry(MARGIN, MARGIN, this->size().width() - MARGIN * 2, 0);
  // components
  components_.append(new components::LED(this));
  for (auto obj : components_) {
    obj->setGeometry(obj->OriginalSize());
  }
}
void KitMainUi::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  widget_->changeSize(event->size());
  const double expantion_rate =
      (double)widget_->size().width() / (double)original_width_;
  for (auto obj : components_) {
    obj->setGeometry(Expantion(obj->OriginalSize(), expantion_rate));
  }
}
} // namespace gui
} // namespace hinan
