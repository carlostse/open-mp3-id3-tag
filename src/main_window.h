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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTranslator>
#include <QLocale>
#include <QStatusBar>
#include "taglib/fileref.h"
#include "taglib/tag.h"
#include "common.h"
#include "tag_convertor.h"
#include "chinese_convertor.h"

#define NUM_OF_WIN_ROW 6
#define NUM_OF_COMMENT_ROW 5
#define MIN_SIZE 380, 275
#define MAX_SIZE 580, 420

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	TagConvertor *tc;
	QPushButton *btnOpen, *btnConvert;
	QLineEdit *editTitle, *editArtist, *editAlbum, *editGenre;
	QPlainTextEdit *editComment;
	TagLib::FileRef *mp3File;

	QMenu *menuFile, *menuInterface, *menuChiConv, *menuHelp;
	QAction *actOpen, *actConvert, *actExit,
			*actEn, *actZht, *actZhs,
			*actZhsToZht, *actZhtToZhs,
			*actHelp, *actAbout;
	QLabel *lbl1, *lbl2, *lbl3, *lbl4, *lbl5;

	QTranslator *trans;
	enum Language {ENG, ZHT, ZHS};
	Language language;

	QLabel* getQLabel(int);
	void updateLangCheckbox();
	void updateInterface();

	void createMenu();
	void initWidget();
	void loadMp3(const char *mp3FilePath);
	void setText();
	static void setPlainTextHeight(QPlainTextEdit *edit, int nRows);

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

public slots:
	void openFile();
	void convertMp3();
	void help();
	void about();
	void changeLangEn();
	void changeLangZht();
	void changeLangZhs();
	void convertToZht();
	void convertToZhs();
};

#endif // MAIN_WINDOW_H
