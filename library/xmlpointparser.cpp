#include <library/xmlpointparser.hpp>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QPointF>

XmlPointParser::XmlPointParser(QObject *parent) : QObject(parent) {}

XmlPointParser::~XmlPointParser() {}

void XmlPointParser::updatePoints(const QByteArray& data) 
{
    QXmlStreamReader xmlDoc(data);

    QList<QPointF> result;

    while (not xmlDoc.atEnd() and not xmlDoc.hasError()) {
        QXmlStreamReader::TokenType token = xmlDoc.readNext();

        if (token == QXmlStreamReader::StartElement) {
            if (xmlDoc.name() == "Point") {
                QXmlStreamAttributes attrib = xmlDoc.attributes();

                float x = 0;
                float y = 0;

                if (attrib.hasAttribute("X")) {
                    auto value = attrib.value("X");

                    if (not value.isEmpty())
                        x = value.toFloat();
                }

                if (attrib.hasAttribute("Y")) {
                    auto value = attrib.value("Y");

                    if (not value.isEmpty())
                        y = value.toFloat();
                }

                result.push_back(QPointF(x, y));
            }
        }
    }

    emit points(result);
}
