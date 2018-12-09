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

    for (; !elt2.isNull(); elt2 = elt2.nextSiblingElement("entry"))
    {
        QDomElement elt3 = elt2.previousSiblingElement("entry");
        std::string str = "";
        if (elt3.attribute("title").toStdString() != elt2.attribute("title").toStdString())
            str =  elt2.attribute("title").toStdString();

        std::string str2 =  elt2.text().toStdString();

        //std::cout << str2 << std::endl;

        std::string str3 =  elt2.attribute("date").toStdString();


        // br tags must be changed at the end
        replaceAll(str2, "&", "&amp;");
        replaceAll(str2, ">", "&gt;");
        replaceAll(str2, "<", "&lt;");
        replaceAll(str2, "\n", "<br>");

        str3.replace(10, 1, " ");

        QString qstr = QString::fromStdString(str);

        // https://stackoverflow.com/questions/7696159/how-can-i-convert-entity-characterescape-character-to-html-in-qt
        // https://wiki.qt.io/Transition_from_Qt_4.x_to_Qt5#Qt::escape_is_deprecated
        QString qstr2 = QString::fromStdString(str2);

        replaceAllTag(qstr2, "`", "<i style=\"color:#7faa6e;\">", "</i>");

        QString qstr3 = QString::fromStdString(str3);

        QString htmlyeni = "<h1 style=\"color:#48813d;\">" + qstr + "</h1>";

        QString icerik = "<p>" + qstr2 + "</p>";

        QString tarih = "<p style=\"color:#5d5d5d;\" align=\"right\">" + qstr3 + "</p>";

        html = html + htmlyeni + icerik + tarih;
    }

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setOutputFileName("test.pdf");

    document.print(&printer);
}

void EksiXML::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
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
