#include "chinese_convertor.h"

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
