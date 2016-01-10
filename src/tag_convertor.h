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

#ifndef TAG_CONVERTOR_H
#define TAG_CONVERTOR_H

#include <iostream>
#include <QString>
#include <uchardet.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "encoding_convertor.h"

using std::cout;
using std::endl;

#define ENCODING_LEN 30

class TagConvertor
{
private:
	TagLib::FileRef *mp3File;
	TagLib::String _title, _artist, _album, _genre, _comment;

	char *_encoding;
	QString *_utf8Title, *_utf8Artist, *_utf8Album, *_utf8Genre, *_utf8Comment;

public:
	TagConvertor(TagLib::FileRef *mp3File);
	~TagConvertor();

	static bool isUtf8Tag(const TagLib::String str);

	void load(const char *manualEncoding = NULL);
	bool convert();
	bool save() const;
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

#endif // TAG_CONVERTOR_H
