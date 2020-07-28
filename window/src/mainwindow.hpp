#ifndef WINDOW_SRC_MAINWINDOW
#define WINDOW_SRC_MAINWINDOW

#include <QMainWindow>
#include <QStringListModel>

#include <library/xmlpointparser.hpp>
#include <library/binpointparser.hpp>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void chooseXmlFileClicked();
    void chooseBinFileClicked();

signals:
    void updateXmlPoints(const QByteArray& data);
    void updateBinPath(const QString& path);

private:
    Ui::MainWindow* ui;
    XmlPointParser _xmlPointParser;
    BinPointParser _binPointParser;

private:
    void updateXmlFile();
    void updateBinFile();
    QByteArray getFileData(const QString& path);
};

#endif /* WINDOW_SRC_MAINWINDOW */
