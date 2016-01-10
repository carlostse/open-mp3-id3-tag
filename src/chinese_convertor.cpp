/*
Copyright (C) 2012 Carlos Tse <copperoxide@gmail.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "chinese_convertor.h"

namespace Mp3Id3EncCov
{
ChineseConvertor::ChineseConvertor(const char *config)
{
    opencc = opencc_open(config);
}

ChineseConvertor::~ChineseConvertor()
{
    if (opencc != NULL && opencc != (opencc_t) -1)
        opencc_close(opencc);
}

QString ChineseConvertor::convert(QString src) const
{
    QByteArray utf8Bytes = src.toUtf8();
    const char *utf8BuffIn = utf8Bytes.data();

    char *buffOut = opencc_convert_utf8(opencc, utf8BuffIn, -1);

    if (buffOut == (char *) -1){
        delete[] buffOut;
        return src;
    }

    QString result = QString::fromUtf8(buffOut);
    delete[] buffOut;
    return result;
}
}