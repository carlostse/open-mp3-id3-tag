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

#ifndef COMMON_H
#define COMMON_H

#define VERSION "0.5.0"
#define WIN_ICON QIcon(":/icon")

#ifdef __cplusplus
namespace Mp3Id3EncCov
{
#define NUM_OF_WIN_ROW 8
#define NUM_OF_COMMENT_ROW 5
#ifdef Q_OS_MAC
#define MIN_SIZE 420, 400
#else
#define MIN_SIZE 420, 340
#endif
#define MAX_SIZE 600, 420
#define LBL_WIDTH 70

enum Language {ENG, ZHT, ZHS};
}
#endif

#endif // COMMON_H
