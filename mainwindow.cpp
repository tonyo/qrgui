#include <assert.h>
#include <qrencode.h>
#include <errno.h>
#include <iostream>
#include <QShortcut>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initElements();
    initShotrcuts();
}

void MainWindow::initElements()
{
    ui->passwordBox->setChecked(true);
}

void MainWindow::initShotrcuts()
{
    // add Ctrl-P shortcut
    QShortcut *activatePassShortcut = new QShortcut(QKeySequence(tr("Ctrl+P")), this);
    connect(activatePassShortcut, SIGNAL(activated()), ui->passwordBox, SLOT(toggle()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // generate QR image
    QString textToEncode = ui->lineEdit->text();

    // TODO: weird stuff
    while (textToEncode.size() < 3)
    {
        textToEncode += " ";
    }

    const char *str = textToEncode.toUtf8().data();
    const int caseSensitive = 1;
    QRcode *code = QRcode_encodeString(str, 0, QR_ECLEVEL_H, QR_MODE_8, caseSensitive);

    if (code == NULL)
    {
        std::cerr << "Error: " << strerror(errno);
        exit(EXIT_FAILURE);
    }

    // convert to QImage
    QImage myImage(code->width + 8, code->width + 8, QImage::Format_RGB32);
    myImage.fill(0xffffff);

    unsigned char *p = code->data;
    for (int y = 0; y < code->width; y++)
    {
        for (int x = 0; x < code->width; x++)
        {
            myImage.setPixel(x + 4, y + 4, ((*p & 1) ? 0x0 : 0xffffff));
            p++;
        }
    }
    QRcode_free(code);

    // display QR image
    int w = ui->pictureLabel->width();
    int h = ui->pictureLabel->height();
    Q_ASSERT(w == h);
    ui->pictureLabel->setPixmap(QPixmap::fromImage(myImage).scaled(w, h));
}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->pushButton->animateClick();
}

void MainWindow::on_passwordBox_toggled(bool checked)
{
    QLineEdit::EchoMode newEchoMode = checked ? QLineEdit::Password : QLineEdit::Normal;
    ui->lineEdit->setEchoMode(newEchoMode);
}
