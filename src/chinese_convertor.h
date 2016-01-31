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

#ifndef CHINESE_CONVERTOR_H
#define CHINESE_CONVERTOR_H

#include <QString>
#include <opencc.h>
#include "encoding_convertor.h"

namespace Mp3Id3EncCov
{
#define CONFIG_ZHS_TO_ZHT OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD
#define CONFIG_ZHT_TO_ZHS OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP

class ChineseConvertor
{
private:
    opencc_t opencc;

public:
    ChineseConvertor(const char *config);
    ~ChineseConvertor();

    QString convert(QString src) const;

};
}
#endif // CHINESE_CONVERTOR_H
