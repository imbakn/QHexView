#ifndef QHEXRENDERER_H
#define QHEXRENDERER_H

/*
 * Nibble encoding:
 *           AB -> [A][B]
 * Nibble Index:    1  0
 */

#include <QTextDocument>
#include <QPainter>
#include "qhexdocument.h"

class QHexRenderer : public QObject
{
    Q_OBJECT

    public:
        enum { AddressArea, HexArea, AsciiArea, ExtraArea };

    public:
        explicit QHexRenderer(QHexDocument* document, const QFontMetrics& fontmetrics, QObject *parent = nullptr);
        void renderFrame(QPainter* painter);
        void render(QPainter* painter, quint64 start, int count, quint64 firstline);
        void enableCursor(bool b = true);
        void selectArea(const QPoint& pt);

    public:
        void blinkCursor();
        bool hitTest(const QPoint& pt, QHexPosition* position, quint64 firstline) const;
        int hitTestArea(const QPoint& pt) const;
        int selectedArea() const;
        quint64 documentLastLine() const;
        int documentLastColumn() const;
        quint64 documentLines() const;
        int documentWidth() const;
        int lineHeight() const;
        QRect getLineRect(quint64 line, quint64 firstline) const;
        int borderSize() const;
        qint8 hexLineWidth() const;

    private:
        QString hexString(quint64 line, QByteArray *rawline = nullptr) const;
        QString asciiString(quint64 line, QByteArray *rawline = nullptr) const;
        QByteArray getLine(quint64 line) const;
        qint64 rendererLength() const;
        int getAddressWidth() const;
        int getHexColumnX() const;
        int getAsciiColumnX() const;
        int getEndColumnX() const;
        int getCellWidth() const;
        int getNibbleIndex(int line, int relx) const;
        void unprintableChars(QByteArray &ascii) const;

    private:
        void applyDocumentStyles(QPainter* painter, QTextDocument *textdocument) const;
        void applyBasicStyle(QTextCursor& textcursor, const QByteArray& rawline, int factor = 1) const;
        void applyMetadata(QTextCursor& textcursor, quint64 line, int factor = 1) const;
        void applySelection(QTextCursor& textcursor, quint64 line, int factor = 1) const;
        void applyCursorAscii(QTextCursor& textcursor, quint64 line) const;
        void applyCursorHex(QTextCursor& textcursor, quint64 line) const;
        void drawAddress(QPainter *painter, const QPalette &palette, const QRect &linerect, quint64 line);
        void drawHex(QPainter *painter, const QPalette &palette, const QRect &linerect, quint64 line);
        void drawAscii(QPainter *painter, const QPalette &palette, const QRect &linerect, quint64 line);

    private:
        QHexDocument* m_document;
        QFontMetrics m_fontmetrics;
        int m_selectedarea;
        bool m_cursorenabled;
};

#endif // QHEXRENDERER_H
