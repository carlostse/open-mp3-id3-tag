/* Copyright 2016 Carlos Tse <copperoxide@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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