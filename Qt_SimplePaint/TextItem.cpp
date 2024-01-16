#include "TextItem.h"


TextItem::TextItem(const Point& position, const QString& text, const QFont& font)
	: Item(position)
	, text(text)
	, font(font)
{}

TextItem::TextItem(const TextItem& toCopy)
	: Item(toCopy.position)
	, text(toCopy.text)
	, font(toCopy.font)
{}

Item* TextItem::clone() const
{
	return new TextItem(position, text, font);
}

QString TextItem::getText() const
{
	return text;
}

const QFont& TextItem::getFont() const
{
	return font;
}

void TextItem::setFont(QFont& newFont)
{
	font = newFont;
}

void TextItem::computeBoundingBox()
{
	QFontMetrics metrics(font);
	int textWidth = metrics.horizontalAdvance(text); // Width of the text
	//int textHeight = metrics.height(); // Height of the font (not the text itself)
	int textHeight = metrics.ascent() - metrics.descent() + HEIGHT_CORRECTION; // Height of the font (not the text itself)

	boundingBox[0] = position;
	boundingBox[1] = Point(position.getX(), position.getY() + textHeight);
	boundingBox[2] = Point(position.getX() + textWidth, position.getY() + textHeight);
	boundingBox[3] = Point(position.getX() + textWidth, position.getY());

	updateBoundingBox = false;
}

void TextItem::draw(QPainter& painter)
{
	painter.setFont(font);
	painter.setPen(Qt::black);
	QFontMetrics metrics = QFontMetrics(font);
	painter.drawText(position.getX(), position.getY() + metrics.ascent() - metrics.descent() + HEIGHT_CORRECTION, text);
}
