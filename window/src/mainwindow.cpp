#include <window/src/mainwindow.hpp>
#include <../ui/ui_mainwindow.h>
#include <window/src/renderarea.hpp>

#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), _xmlPointParser(this), _binPointParser(this)
{
    ui->setupUi(this);

    RenderArea* render = new RenderArea(this);

    ui->renderLayout->addWidget(render);

    connect(ui->tbChooseXmlFile, &QToolButton::clicked, this, &MainWindow::chooseXmlFileClicked);
    connect(ui->tbChooseBinFile, &QToolButton::clicked, this, &MainWindow::chooseBinFileClicked);
    connect(this, &MainWindow::updateXmlPoints, &_xmlPointParser, &XmlPointParser::updatePoints);
    connect(this, &MainWindow::updateBinPath, _binPointParser.worker(), &BinPointParserWorker::updatePath);
    connect(&_xmlPointParser, &XmlPointParser::points, render, &RenderArea::xmlPoints);
    connect(_binPointParser.worker(), &BinPointParserWorker::points, render, &RenderArea::binPoints);
    connect(this, &MainWindow::updateBinPath, render, &RenderArea::updateBinPath);
}

MainWindow::~MainWindow() 
{
    delete ui;
}

void MainWindow::chooseXmlFileClicked()
{
    QString defaultPath;

    if (not ui->leXmlPath->text().isEmpty()) {
        auto fileInfo = QFileInfo(ui->leXmlPath->text());
        defaultPath = fileInfo.dir().path();
    }

    QString result = QFileDialog::getOpenFileName(this, "Выберите xml", defaultPath, "*.xml");

    if (not result.isEmpty()) {
        ui->leXmlPath->setText(result);
        updateXmlFile();
    }
}

void MainWindow::chooseBinFileClicked()
{
    QString defaultPath;

    if (not ui->leBinPath->text().isEmpty()) {
        auto fileInfo = QFileInfo(ui->leBinPath->text());
        defaultPath = fileInfo.dir().path();
    }

    QString result = QFileDialog::getOpenFileName(this, "Выберите bin", defaultPath, "*.bin");

    if (not result.isEmpty()) {
        ui->leBinPath->setText(result);
        updateBinFile();
    }
}

void MainWindow::updateXmlFile()
{
    emit updateXmlPoints(getFileData(ui->leXmlPath->text()));
}

void MainWindow::updateBinFile()
{
    emit updateBinPath(ui->leBinPath->text());
}

QByteArray MainWindow::getFileData(const QString& path)
{
    QByteArray result;
    auto fileInfo = QFileInfo(path);

    if (fileInfo.exists() and fileInfo.isFile()) {
        QFile file(fileInfo.filePath());

        if (file.open(QIODevice::ReadOnly)) {
            result = file.readAll(); 
            file.close();

            emit updateXmlPoints(result);
        }
    }

    return result;
}
