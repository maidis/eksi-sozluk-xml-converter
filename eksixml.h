#ifndef EKSIXML_H
#define EKSIXML_H

#include <QMainWindow>

#include <QApplication>
#include <QPrinter>
#include <QTextDocument>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QtGlobal>
#include <QTextStream>
#include <QFileDialog>
#include <QRegularExpression>
#include <QRegExp>

#include <QTextBrowser>

#include <iostream>

namespace Ui {
class EksiXML;
}

class EksiXML : public QMainWindow
{
    Q_OBJECT

public:
    explicit EksiXML(QWidget *parent = nullptr);
    void replaceAll(QString& str, const QString& from, const QString& to);
    void replaceAllTag(QString& str, const QString& from, const QString& to, const QString& to2);
    void convert(QString& str);
    ~EksiXML();

private slots:
    void on_openXMLBtn_clicked();
    void on_convertBtn_clicked();
    void on_saveBtn_clicked();

private:
    Ui::EksiXML *ui;
    QString fileName, saveFileName;
    QFileInfo fileInfo;
    QTextDocument document;
};

#endif // EKSIXML_H
