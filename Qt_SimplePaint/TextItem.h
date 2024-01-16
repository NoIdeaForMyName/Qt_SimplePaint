#pragma once

#include "Item.h"
#include <QString>
#include <QFont>

#define HEIGHT_CORRECTION 1

class TextItem : public Item
{

public:
	TextItem(const Point& position, const QString& text, const QFont& font);
	TextItem(const TextItem& toCopy);
	~TextItem() override = default;
	Item* clone() const override;

	QString getText() const;
	const QFont& getFont() const;
	void setFont(QFont& newFont);

	void computeBoundingBox() override;
	void draw(QPainter& painter) override;

private:
	QString text;
	QFont font;

};
