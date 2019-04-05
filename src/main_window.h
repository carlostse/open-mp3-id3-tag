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
#include <QDesktopServices>
#include <QMessageBox>
#include <QTranslator>
#include <QLocale>
#include <QStatusBar>
#include <QComboBox>
#include "common.h"
#include "tag_convertor.h"
#include "chinese_convertor.h"
#include "drop_area.h"

namespace Mp3Id3EncCov
{
#define NUM_OF_WIN_ROW 8
#define NUM_OF_COMMENT_ROW 5
#ifdef Q_OS_MAC
#define MIN_SIZE 380, 400
#else
#define MIN_SIZE 380, 340
#endif
#define MAX_SIZE 580, 420
#define LBL_WIDTH 70

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool disableComboxSignal;
    TagConvertor *tc;

    QComboBox *cbEnc;
    QPushButton *btnSave, *btnClose;
    QLineEdit *editTitle, *editArtist, *editAlbum, *editGenre;
    QPlainTextEdit *editComment;
    DropArea *dropArea;

    QMenu *menuFile, *menuInterface, *menuChiConv, *menuHelp;
    QAction *actOpen, *actSave, *actClose, *actExit,
            *actEn, *actZht, *actZhs,
            *actZhsToZht, *actZhtToZhs,
            /**actHelp,*/ *actAbout;
    QLabel *lbl1, *lbl2, *lbl3, *lbl4, *lbl5, *lbl6;

    QTranslator *trans;
    Language language;

    QLabel* getQLabel();
    void updateLangCheckbox();
    void updateInterface();

    void createMenu();
    void initWidget();
    void loadMp3(QString mp3FilePath);
    void setText();
    void readMp3Info(const char *encoding = nullptr);
    static void setPlainTextHeight(QPlainTextEdit *edit, int nRows);

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void openFile();
    void droppedFiles(const QList<QUrl>);
    void convertMp3();
    void clear();
    void help();
    void about();
    void changeLangEn();
    void changeLangZht();
    void changeLangZhs();
    void convertToZht();
    void convertToZhs();
    void reloadEncoding(const QString &);
};
}
#endif // MAIN_WINDOW_H
