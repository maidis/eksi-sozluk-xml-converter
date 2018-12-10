#include "eksixml.h"
#include "ui_eksixml.h"

EksiXML::EksiXML(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EksiXML)
{
    ui->setupUi(this);

    QDomDocument doc;
    QFile file("maidis.xml");
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return;

    QDomNode root2 = doc.firstChildElement("backup");
    QDomNode elt = root2.firstChildElement("entries");
    QDomElement elt2 = elt.firstChildElement("entry");

    QString body = "<body style=\"background-color:#ececec;\">";

    //QString img = "<img src=\"eksisozluk_logo.png\" alt=\"Ekşi Sözlük\" height=\"48\" width=\"288\">";
    QString img = "<div style=\"text-align: center\"><a href=\"https://eksisozluk.com/\"><img src=\"eksisozluk_logo.png\" align=\"center\" height=\"96\" width=\"576\"></a></div>";


    //QString test = "Some text with a footnote.<sup><a href=\"#fn1\" id=\"ref1\">1</a></sup>";
    //QString test2 = "<sup id=\"fn1\">1. [Text of footnote 1]<a href=\"#ref1\" title=\"Jump back to footnote 1 in the text.\">↩</a></sup>";

    QDomElement root = doc.firstChildElement("backup");
    QString nick = root.attribute("nick");
    QString html = body  + img + "<h1 align=\"center\" style=\"color:#87b54f;\">" + nick + "</h1>";

    QString icerik = "<p></p>";
    QString eksi = "https://eksisozluk.com/";
    QString eksiEntry = "https://eksisozluk.com/entry/";

    for (; !elt2.isNull(); elt2 = elt2.nextSiblingElement("entry"))
    {
        QDomElement elt3 = elt2.previousSiblingElement("entry");
        QString str = "";
        if (elt3.attribute("title").toStdString() != elt2.attribute("title").toStdString())
            str =  elt2.attribute("title");

        QString str2 =  elt2.text();

        //std::cout << str2 << std::endl;

        QString str3 =  elt2.attribute("date");


        // br tags must be changed at the end
        replaceAll(str2, "&", "&amp;");
        replaceAll(str2, ">", "&gt;");
        replaceAll(str2, "<", "&lt;");
        replaceAll(str2, "\n", "<br>");

        str3.replace(10, 1, " ");

        QString qstr = str;

        // https://stackoverflow.com/questions/7696159/how-can-i-convert-entity-characterescape-character-to-html-in-qt
        // https://wiki.qt.io/Transition_from_Qt_4.x_to_Qt5#Qt::escape_is_deprecated
        QString qstr2 = str2;

        replaceAllTag(qstr2, "`", "<i style=\"color:#7faa6e;\">", "</i>");

        qstr2.replace(QRegExp("(bkz: ([a-z0-9-+!'^+%&/=?ığüşöç ]*))"), "bkz: <i style=\"color:#7faa6e;\">\\2</i>");

        QString qstr3 = str3;

        QString htmlyeni = "<h1 style=\"color:#48813d;\">" + qstr + "</h1>";

        QString icerik = "<p>" + qstr2 + "</p>";

        // <a href="url">link text</a> elt2.attribute("id").toStdString()
        QString tarih = "<p style=\"color:#5d5d5d;\" align=\"right\"> <a style=\"text-decoration:none; color:#5d5d5d;\" href=\"" + eksiEntry + elt2.attribute("id") + "\">" + qstr3 + "</a></p>";

        html = html + htmlyeni + icerik + tarih;
    }

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setOutputFileName("test.pdf");

    document.print(&printer);
}

void EksiXML::replaceAll(QString& str, const QString& from, const QString& to) {
    if(from.isEmpty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.indexOf(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void EksiXML::replaceAllTag(QString& str, const QString& from, const QString& to, const QString& to2) {
    if(from.isEmpty())
        return;
    size_t start_pos = 0;
    bool ilk = 1;
    while ((start_pos = str.indexOf(from, start_pos)) != -1)
    {
        if (ilk)
        {
            str.replace(start_pos, from.length(), to);
            ilk = 0;
        }
        else
        {
            str.replace(start_pos, from.length(), to2);
            //str.replace(start_pos, from.length(), to2.insert(1, QString("/")));
            ilk = 1;
        }
        start_pos += 1;
        //qDebug() << "Found <b> tag at index position" << j;
        //++start_pos;
    }
}

EksiXML::~EksiXML()
{
    delete ui;
}

void EksiXML::on_openXMLBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a XML file");
    ui->lineEdit->setText(filename);
}
