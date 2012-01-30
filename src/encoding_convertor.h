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

#ifndef ENCODING_CONVERTOR_H
#define ENCODING_CONVERTOR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
//#include "iconv/iconv.h"

class EncodingConvertor
{

private:
	const char *_fromCharset;
//	const char *_toCharset;
//	iconv_t conv;

public:
	EncodingConvertor(const char* fromCharset/*, const char* toCharset*/);
	virtual ~EncodingConvertor();

	static void debugHex(const char *header, const char *content);

	QString convert(const char *input) const;
	//char *convert(const char *input) const;
};

#endif // ENCODING_CONVERTOR_H
