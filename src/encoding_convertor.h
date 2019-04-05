/* Copyright 2019 Carlos Tse <carlos@aboutmy.info>
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

#ifndef ENCODING_CONVERTOR_H
#define ENCODING_CONVERTOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
//#include "iconv/iconv.h"

namespace Mp3Id3EncCov
{
class EncodingConvertor
{

private:
    const char *_fromCharset;
//    const char *_toCharset;
//    iconv_t conv;

public:
    EncodingConvertor(const char* fromCharset/*, const char* toCharset*/);
    virtual ~EncodingConvertor();

    static void debugHex(const char *header, const char *content);

    QString convert(const char *input) const;
//    char *convert(const char *input) const;
};
}
#endif // ENCODING_CONVERTOR_H
