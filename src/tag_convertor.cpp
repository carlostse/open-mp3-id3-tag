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

#include "tag_convertor.h"

namespace Mp3Id3EncCov
{
TagConvertor::TagConvertor(const wchar_t *file)
{
    _mp3File = new TagLib::FileRef(TagLib::FileName(file));
    init();
}

TagConvertor::TagConvertor(const char *file)
{
    _mp3File = new TagLib::FileRef(TagLib::FileName(file));
    init();
}

void TagConvertor::init()
{
    _encoding = new char[ENCODING_LEN];
    _utf8Title = new QString();
    _utf8Artist = new QString();
    _utf8Album = new QString();
    _utf8Genre = new QString();
    _utf8Comment = new QString();
}

TagConvertor::~TagConvertor()
{
    if (_mp3File){
        delete _mp3File;
        _mp3File = nullptr;
    }
    if (_encoding) {
        delete _encoding;
        _encoding = nullptr;
    }
    if (_utf8Title) {
        delete _utf8Title;
        _utf8Title = nullptr;
    }
    if (_utf8Artist) {
        delete _utf8Artist;
        _utf8Artist = nullptr;
    }
    if (_utf8Album) {
        delete _utf8Album;
        _utf8Album = nullptr;
    }
    if (_utf8Genre) {
        delete _utf8Genre;
        _utf8Genre = nullptr;
    }
    if (_utf8Comment) {
        delete _utf8Comment;
        _utf8Comment = nullptr;
    }
}

bool TagConvertor::is_utf8_tag(TagLib::String str)
{
    return !str.isNull() && !str.isEmpty() && !str.isAscii() && !str.isLatin1();
}

bool TagConvertor::is_missing_mp3_file() const
{
    return !_mp3File || _mp3File->isNull() || !_mp3File->tag();
}

void TagConvertor::load(const char *manualEncoding)
{
    if (is_missing_mp3_file())
        return;

    const TagLib::Tag *tag = _mp3File->tag();
//    std::cout << "title   - " << tag->title()   << "\n" <<
//                 "artist  - " << tag->artist()  << "\n" <<
//                 "album   - " << tag->album()   << "\n" <<
//                 "genre   - " << tag->genre()   << "\n" <<
//                 "comment - " << tag->comment() << std::endl;

    _title = tag->title();
    _artist = tag->artist();
    _album = tag->album();
    _genre = tag->genre();
    _comment = tag->comment();

    if (!manualEncoding){
        // guess encoding (increase simple size for accuracy)
        TagLib::String all =
            _title + _title + _title +
            _artist + _artist + _artist +
            _album + _album +
            _genre + _comment;

        const char *src = all.toCString(TagConvertor::is_utf8_tag(all));
//        std::cout << "src: " << src << std::endl;

        uchardet_t ud = uchardet_new();
        uchardet_handle_data(ud, src, strlen(src));
        uchardet_data_end(ud);

        strcpy(_encoding, uchardet_get_charset(ud));
        std::cout << "auto encoding: " << _encoding << std::endl;
        uchardet_delete(ud);

    } else {
        std::cout << "manual encoding: " << manualEncoding << std::endl;
        strcpy(_encoding, manualEncoding);
    }

    _utf8Title->clear();
    _utf8Artist->clear();
    _utf8Album->clear();
    _utf8Genre->clear();
    _utf8Comment->clear();

    // convert to UTF-8 for display in GUI and save
    if (_encoding && strlen(_encoding) > 0 && strcmp(_encoding, "UTF-8") != 0){
        std::cout << "converting " << _encoding << " to UTF8..." << std::endl;
        EncodingConvertor *conv = new EncodingConvertor(_encoding/*, "UTF-8"*/);

//        _utf8Title->append(QString::fromUtf8(conv->convert((char *) _title.toCString())));
//        _utf8Artist->append(QString::fromUtf8(conv->convert((char *) _artist.toCString())));
//        _utf8Album->append(QString::fromUtf8(conv->convert((char *) _album.toCString())));
//        _utf8Genre->append(QString::fromUtf8(conv->convert((char *) _genre.toCString())));
//        _utf8Comment->append(QString::fromUtf8(conv->convert((char *) _comment.toCString())));

        _utf8Title->append(conv->convert((char *) _title.toCString()));
        _utf8Artist->append(conv->convert((char *) _artist.toCString()));
        _utf8Album->append(conv->convert((char *) _album.toCString()));
        _utf8Genre->append(conv->convert((char *) _genre.toCString()));
        _utf8Comment->append(conv->convert((char *) _comment.toCString()));

        delete conv;
        std::cout << "converted" << std::endl;

    } else {
        std::cout << "copy to utf8..." << std::endl;
        _utf8Title->append(QString::fromUtf8(_title.toCString(true)));
        _utf8Artist->append(QString::fromUtf8(_artist.toCString(true)));
        _utf8Album->append(QString::fromUtf8(_album.toCString(true)));
        _utf8Genre->append(QString::fromUtf8(_genre.toCString(true)));
        _utf8Comment->append(QString::fromUtf8(_comment.toCString(true)));
    }
}

bool TagConvertor::convert()
{
    if (is_missing_mp3_file()){
        std::cout << "nothing to save..." << std::endl;
        return false;
    }

    TagLib::Tag *tag = _mp3File->tag();
    tag->setTitle(TagLib::String(_utf8Title->toUtf8().data(), TagLib::String::UTF8));
    tag->setArtist(TagLib::String(_utf8Artist->toUtf8().data(), TagLib::String::UTF8));
    tag->setAlbum(TagLib::String(_utf8Album->toUtf8().data(), TagLib::String::UTF8));
    tag->setComment(TagLib::String(_utf8Comment->toUtf8().data(), TagLib::String::UTF8));
    tag->setGenre(TagLib::String(_utf8Genre->toUtf8().data(), TagLib::String::UTF8));
    return true;
}

bool TagConvertor::save() const
{
    if (is_missing_mp3_file()){
        std::cout << "mp3 file is null" << std::endl;
        return false;
    }

    return _mp3File->save();
}

const TagLib::FileRef *TagConvertor::mp3File() const
{
    return _mp3File;
}

const char *TagConvertor::encoding() const
{
    return _encoding;
}

const TagLib::String TagConvertor::title() const
{
    return _title;
}

const TagLib::String TagConvertor::artist() const
{
    return _artist;
}

const TagLib::String TagConvertor::album() const
{
    return _album;
}

const TagLib::String TagConvertor::comment() const
{
    return _comment;
}

const TagLib::String TagConvertor::genre() const
{
    return _genre;
}

QString *TagConvertor::utf8Title() const
{
    return _utf8Title;
}

QString *TagConvertor::utf8Artist() const
{
    return _utf8Artist;
}

QString *TagConvertor::utf8Album() const
{
    return _utf8Album;
}

QString *TagConvertor::utf8Genre() const
{
    return _utf8Genre;
}

QString *TagConvertor::utf8Comment() const
{
    return _utf8Comment;
}

void TagConvertor::setUtf8Title(QString qs)
{
    _utf8Title->clear();
    _utf8Title->append(qs);
}

void TagConvertor::setUtf8Artist(QString qs)
{
    _utf8Artist->clear();
    _utf8Artist->append(qs);
}

void TagConvertor::setUtf8Album(QString qs)
{
    _utf8Album->clear();
    _utf8Album->append(qs);
}

void TagConvertor::setUtf8Genre(QString qs)
{
    _utf8Genre->clear();
    _utf8Genre->append(qs);
}

void TagConvertor::setUtf8Comment(QString qs)
{
    _utf8Comment->clear();
    _utf8Comment->append(qs);
}
}
