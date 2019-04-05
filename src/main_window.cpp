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

#include <QtDebug>
#include <QtPlugin>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#endif
#include "main_window.h"

namespace Mp3Id3EncCov
{
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // icon
    setWindowIcon(WIN_ICON);

    // Qt Translator
    trans = new QTranslator();
    QApplication::instance()->installTranslator(trans);

    // load default language
    QLocale *loc = new QLocale();
    language = loc->language() == QLocale::Chinese? loc->country() == QLocale::China? ZHS: ZHT: ENG;
    delete loc;
    std::cout << "language: " << language << std::endl;

    // initial interface
    initWidget();
    updateInterface();
}

MainWindow::~MainWindow()
{
    if (trans) {
        delete trans;
        trans = nullptr;
    }
}

QLabel* MainWindow::getQLabel()
{
    QLabel *lbl = new QLabel(this);
    lbl->setAlignment(Qt::AlignRight | Qt::AlignTop);
    lbl->setFixedWidth(LBL_WIDTH);
    return lbl;
}

void MainWindow::openFile()
{
    loadMp3(QFileDialog::getOpenFileName(
            this, tr("Open MP3 Files"),
#if QT_VERSION >= 0x050000
            QStandardPaths::writableLocation(QStandardPaths::MusicLocation),
#else
            QDesktopServices::storageLocation(QDesktopServices::MusicLocation),
#endif
            "MP3 Files (*.mp3)", nullptr)
    );
}

void MainWindow::droppedFiles(const QList<QUrl> list)
{
    if (list.size() < 1)
        return;

    QString url = list.at(0).path(), fileName;
    // the url starts with /
#ifdef Q_OS_WIN
    fileName = url.mid(1, url.length());
#else
    fileName = url.mid(0, url.length());
#endif
//    qDebug() << "file: " << fileName;
    loadMp3(fileName);
}

void MainWindow::createMenu()
{
    // menu file
    actOpen = new QAction(this);
    actOpen->setShortcut(QKeySequence("Ctrl+O"));

    actSave = new QAction(this);
    actSave->setShortcut(QKeySequence("Ctrl+S"));

    actClose = new QAction(this);
    actClose->setShortcut(QKeySequence("Ctrl+W"));

    actExit = new QAction(this);
    actExit->setShortcut(QKeySequence("Ctrl+X"));

    menuFile = menuBar()->addMenu("");
    menuFile->addAction(actOpen);
    menuFile->addAction(actSave);
    menuFile->addAction(actClose);
    menuFile->addSeparator();
    menuFile->addAction(actExit);

    // menu interface
    actEn = new QAction(this);
    actZht = new QAction(this);
    actZhs = new QAction(this);
    actEn->setCheckable(true);
    actZht->setCheckable(true);
    actZhs->setCheckable(true);
    updateLangCheckbox();

    menuInterface = menuBar()->addMenu("");
    menuInterface->addAction(actEn);
    menuInterface->addAction(actZht);
    menuInterface->addAction(actZhs);

    // menu chinese convert
    actZhsToZht = new QAction(this);
    actZhtToZhs = new QAction(this);

    menuChiConv = menuBar()->addMenu("");
    menuChiConv->addAction(actZhsToZht);
    menuChiConv->addAction(actZhtToZhs);

    // menu help
//    actHelp = new QAction(this);
//    actHelp->setShortcut(QKeySequence("F1"));
    actAbout = new QAction(this);

    menuHelp = menuBar()->addMenu("");
//    menuHelp->addAction(actHelp);
    menuHelp->addAction(actAbout);

    // signal and slot
    QObject::connect(actOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(actClose, SIGNAL(triggered()), this, SLOT(clear()));
    QObject::connect(actExit, SIGNAL(triggered()), this, SLOT(close()));
//    QObject::connect(actHelp, SIGNAL(triggered()), this, SLOT(help()));
    QObject::connect(actAbout, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(actEn, SIGNAL(triggered()), this, SLOT(changeLangEn()));
    QObject::connect(actZht, SIGNAL(triggered()), this, SLOT(changeLangZht()));
    QObject::connect(actZhs, SIGNAL(triggered()), this, SLOT(changeLangZhs()));
    QObject::connect(actZhsToZht, SIGNAL(triggered()), this, SLOT(convertToZht()));
    QObject::connect(actZhtToZhs, SIGNAL(triggered()), this, SLOT(convertToZhs()));
}

void MainWindow::initWidget()
{
    // title and size
    this->setWindowTitle(QString("MP3 ID3 Tag Encoding Converter ") + QString(VERSION));
    this->setMinimumSize(MIN_SIZE);
    this->setMaximumSize(MAX_SIZE);

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    // menu
    createMenu();

    // layout
    QHBoxLayout *hLayout[NUM_OF_WIN_ROW];
    int row = 0;

    // row 0
    dropArea = new DropArea(QSize(380, 50), this);
    dropArea->setText(tr("Drop MP3 here"));

    hLayout[row] = new QHBoxLayout();
    hLayout[row]->addWidget(dropArea);

    // row 1
    btnSave = new QPushButton(this);
    btnClose = new QPushButton(this);

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(btnSave);
    hLayout[row]->addWidget(btnClose);

    // row 2
    lbl1 = getQLabel();
    cbEnc = new QComboBox(this);
    cbEnc->addItem("BIG5");
    cbEnc->addItem("BIG5-HKSCS");
    cbEnc->addItem("GB18030");
    cbEnc->addItem("UTF-8");

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(lbl1);
    hLayout[row]->addWidget(cbEnc);

    // row 3
    lbl2 = getQLabel();
    editTitle = new QLineEdit(this);

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(lbl2);
    hLayout[row]->addWidget(editTitle);

    // row 4
    lbl3 = getQLabel();
    editArtist = new QLineEdit(this);

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(lbl3);
    hLayout[row]->addWidget(editArtist);

    // row 5
    lbl4 = getQLabel();
    editAlbum = new QLineEdit(this);

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(lbl4);
    hLayout[row]->addWidget(editAlbum);

    // row 6
    lbl5 = getQLabel();
    editGenre = new QLineEdit(this);

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(lbl5);
    hLayout[row]->addWidget(editGenre);

    // row 7
    lbl6 = getQLabel();
    editComment = new QPlainTextEdit(this);
    MainWindow::setPlainTextHeight(editComment, NUM_OF_COMMENT_ROW);

    hLayout[++row] = new QHBoxLayout();
    hLayout[row]->addWidget(lbl6);
    hLayout[row]->addWidget(editComment);

    // vertical layout
    QVBoxLayout *vLayout = new QVBoxLayout();
    for (int i = 0; i < NUM_OF_WIN_ROW; i++)
        vLayout->addLayout(hLayout[i]);

    widget->setLayout(vLayout);

    // update interface text
    updateInterface();

    // signal and slot
    QObject::connect(btnSave, SIGNAL(clicked()), this, SLOT(convertMp3()));
    QObject::connect(btnClose, SIGNAL(clicked()), this, SLOT(clear()));
    QObject::connect(cbEnc, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(reloadEncoding(const QString &)));
    QObject::connect(dropArea, SIGNAL(dropped(const QList<QUrl>)), this, SLOT(droppedFiles(const QList<QUrl>)));
}

void MainWindow::updateLangCheckbox()
{
    actEn->setChecked(false);
    actZht->setChecked(false);
    actZhs->setChecked(false);

    if (language == ZHT)
        actZht->setChecked(true);
    else if (language == ZHS)
        actZhs->setChecked(true);
    else
        actEn->setChecked(true);
}

void MainWindow::updateInterface()
{
    if (language == ZHT)
        trans->load(QCoreApplication::applicationDirPath() + "/zht.qm");
    else if (language == ZHS)
        trans->load(QCoreApplication::applicationDirPath() + "/zhs.qm");
    else
        trans->load("");

    // menu
    menuFile->setTitle(tr("&File"));
    actOpen->setText(tr("Open"));
    actSave->setText(tr("Convert"));
    actClose->setText(tr("Clear"));
    actExit->setText(tr("E&xit"));
    actEn->setText(tr("&English"));
    actZht->setText(tr("&Traditional Chinese"));
    actZhs->setText(tr("&Simplified Chinese"));
    menuInterface->setTitle(tr("&Interface"));
    actZhsToZht->setText(tr("&Simplified Chinese to Traditional"));
    actZhtToZhs->setText(tr("&Traditional Chinese to Simplified"));
    menuChiConv->setTitle(tr("&Chinese Convert"));
//    actHelp->setText(tr("&Help"));
    actAbout->setText(tr("&About"));
    menuHelp->setTitle(tr("&Help"));

    // buttons
    btnSave->setText(tr("Convert"));
    btnClose->setText(tr("Clear"));

    // labels
    lbl1->setText(tr("Encoding: "));
    lbl2->setText(tr("Title: "));
    lbl3->setText(tr("Artist: "));
    lbl4->setText(tr("Album: "));
    lbl5->setText(tr("Genre: "));
    lbl6->setText(tr("Comment: "));

    // status bar
//	statusBar()->showMessage("");

    // drop area
    dropArea->setText(tr("Drop MP3 here"));
}

void MainWindow::loadMp3(QString mp3FilePath)
{
    if (mp3FilePath.length() < 1){
        statusBar()->clearMessage();
        return;
    }

    clear();

    statusBar()->showMessage(mp3FilePath);
    currentFile = mp3FilePath;
    readMp3Info();
}

void MainWindow::setText(const TagConvertor *tc)
{
    if (!tc)
        return;

    editTitle->setText(*tc->utf8Title());
    editArtist->setText(*tc->utf8Artist());
    editAlbum->setText(*tc->utf8Album());
    editGenre->setText(*tc->utf8Genre());
    editComment->setPlainText(*tc->utf8Comment());
//	statusBar()->showMessage(tr("Source Encoding: ").append(tc->encoding()).toUpper());
}

void MainWindow::readMp3Info(const char *encoding)
{
    auto tc = new TagConvertor(currentFile);
    tc->load(encoding);
    setText(tc);
    delete tc;

    if (!encoding){
        std::cout << "disable combox signal" << std::endl;
        disableComboxSignal = true;

        // default UTF-8
        cbEnc->setCurrentIndex(3);

        // match the encoding
        QString enc = QString(tc->encoding()).toUpper();
        for (int i = 0; i < cbEnc->count(); i++){
            if (cbEnc->itemText(i) == enc){
                cbEnc->setCurrentIndex(i);
            }
        }

        std::cout << "enable combox signal" << std::endl;
        disableComboxSignal = false;
    }
}

void MainWindow::setPlainTextHeight(QPlainTextEdit *edit, int nRows)
{
    QFontMetrics m(edit->font());
    edit->setFixedHeight(nRows * (m.lineSpacing() + 1));
}

void MainWindow::convertMp3()
{
    auto tc = new TagConvertor(currentFile);
    if (!tc || tc->is_missing_mp3_file())
        return;

    tc->setUtf8Title(editTitle->text());
    tc->setUtf8Artist(editArtist->text());
    tc->setUtf8Album(editAlbum->text());
    tc->setUtf8Genre(editGenre->text());
    tc->setUtf8Comment(editComment->toPlainText());

    bool success = tc->convert() && tc->save();
    std::cout << "save success: " << success << "endl" << std::endl;
    statusBar()->showMessage(success? tr("Saved"): tr("Save Failed"));
    delete tc;

    if (success)
        readMp3Info("UTF-8");
}

void MainWindow::clear()
{
    statusBar()->clearMessage();
    editTitle->setText(nullptr);
    editArtist->setText(nullptr);
    editAlbum->setText(nullptr);
    editGenre->setText(nullptr);
    editComment->setPlainText(nullptr);
}

void MainWindow::help()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(WIN_ICON);
    msgBox.setWindowTitle(tr("Help"));
    msgBox.setInformativeText(tr("Working in Process"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::about()
{
    QString t = tr("MP3 ID3 Tag Encoding Converter ");
    t.append(VERSION);
    t.append("\n\nBy Carlos Tse <carlos@aboutmy.info>\n\n");
    t.append("Licensed under the Apache License, Version 2.0\n");

    QMessageBox msgBox;
    msgBox.setWindowIcon(WIN_ICON);
    msgBox.setWindowTitle(tr("About"));
    msgBox.setInformativeText(t);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::changeLangEn()
{
    language = ENG;
    updateLangCheckbox();
    updateInterface();
}

void MainWindow::changeLangZht()
{
    language = ZHT;
    updateLangCheckbox();
    updateInterface();
}

void MainWindow::changeLangZhs()
{
    language = ZHS;
    updateLangCheckbox();
    updateInterface();
}

void MainWindow::convertToZht()
{
    ChineseConvertor *cc = new ChineseConvertor(CONFIG_ZHS_TO_ZHT);
    editTitle->setText(cc->convert(editTitle->text()));
    editArtist->setText(cc->convert(editArtist->text()));
    editAlbum->setText(cc->convert(editAlbum->text()));
    editGenre->setText(cc->convert(editGenre->text()));
    editComment->setPlainText(cc->convert(editComment->toPlainText()));
    delete cc;
}

void MainWindow::convertToZhs()
{
    ChineseConvertor *cc = new ChineseConvertor(CONFIG_ZHT_TO_ZHS);
    editTitle->setText(cc->convert(editTitle->text()));
    editArtist->setText(cc->convert(editArtist->text()));
    editAlbum->setText(cc->convert(editAlbum->text()));
    editGenre->setText(cc->convert(editGenre->text()));
    editComment->setPlainText(cc->convert(editComment->toPlainText()));
    delete cc;
}

void MainWindow::reloadEncoding(const QString &text)
{
    if (disableComboxSignal)
        return;

    std::string encoding = text.toStdString();
//	std::cout << "reload encoding: " << encoding << std::endl;
    readMp3Info(encoding.c_str());
}
}
