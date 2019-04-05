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

#ifndef TAG_CONVERTOR_H
#define TAG_CONVERTOR_H

#include <iostream>
#include <QString>
#include <uchardet.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "encoding_convertor.h"

namespace Mp3Id3EncCov
{
#define ENCODING_LEN 30

class TagConvertor
{
private:
    TagLib::FileRef *_mp3File;
    TagLib::String _title, _artist, _album, _genre, _comment;

    char *_encoding;
    QString *_utf8Title, *_utf8Artist, *_utf8Album, *_utf8Genre, *_utf8Comment;

    void init();

public:
    TagConvertor(const wchar_t *file);
    TagConvertor(const char *file);
    ~TagConvertor();

    static bool is_utf8_tag(const TagLib::String);
    bool is_missing_mp3_file() const;

    void load(const char *manualEncoding = NULL);
    bool convert();
    bool save() const;
    const TagLib::FileRef *mp3File() const;
    const char *encoding() const;
    const TagLib::String title() const;
    const TagLib::String artist() const;
    const TagLib::String album() const;
    const TagLib::String genre() const;
    const TagLib::String comment() const;
    QString *utf8Title() const;
    QString *utf8Artist() const;
    QString *utf8Album() const;
    QString *utf8Genre() const;
    QString *utf8Comment() const;
    void setUtf8Title(QString);
    void setUtf8Artist(QString);
    void setUtf8Album(QString);
    void setUtf8Genre(QString);
    void setUtf8Comment(QString);
};
}
#endif // TAG_CONVERTOR_H
