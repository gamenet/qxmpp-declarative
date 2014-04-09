/*
 * Copyright (C) 2014 qxmpp-declarative developers
 *
 * Author:
 *  Nikita Gorbunov
 *
 * Source:
 *  https://github.com/n-gorbunov/qxmpp-declarative
 *
 * This file is a part of qxmpp-declarative library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include <QDebug>

#include <VCardPhotoProvider.h>

VCardPhotoProvider::VCardPhotoProvider()
  : QDeclarativeImageProvider(Image)
{
}

QImage VCardPhotoProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
  //qDebug() << "VCardPhotoProvider::requestImage id==" << id;
  //qDebug() << "VCardPhotoProvider::requestImage id==" << id;
  
  QImage image/*("D:/avatar_1.png")*/;

  //qDebug() << "Image loaded" << image.width() << "x" << image.height();
  if(image.isNull()) {
    //qDebug() << "Failed load image: " << "D:/avatar_1.png";
  }

  if (requestedSize.isValid())
    image = image.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

  if (size)
    *size = image.size();

  //qDebug() << "returning image of size: " << image.width() << "x" << image.height();
  return image;
}
