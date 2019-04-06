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

#include "common.h"
#include <QByteArray>
#include <QFile>

namespace Mp3Id3EncCov
{
wchar_t *Util::qfileToWChar(QString &file){
    wchar_t *data = new wchar_t[file.length() + sizeof(wchar_t)]();
    file.toWCharArray(data);
    return data;
}

char *Util::qfileToChar(QString &file){
    QByteArray ba = QFile::encodeName(file);
    char *data = new char[ba.length() + sizeof(char)]();
    strcpy(data, ba.constData());
    return data;
}
}
