#ifndef EKSIXML_H
#define EKSIXML_H

#include <QMainWindow>

#include <QApplication>
#include <QPrinter>
#include <QTextDocument>
#include <QDomDocument>
#include <QFile>
#include <QtGlobal>
#include <QTextStream>
#include <QFileDialog>

#include <iostream>
#include <algorithm>
#include <string>

namespace Ui {
class EksiXML;
}

class EksiXML : public QMainWindow
{
    Q_OBJECT

public:
    explicit EksiXML(QWidget *parent = nullptr);
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
    void replaceAllTag(QString& str, const QString& from, const QString& to, const QString& to2);
    ~EksiXML();

private slots:
    void on_openXMLBtn_clicked();

private:
    Ui::EksiXML *ui;
};

#endif // EKSIXML_H
