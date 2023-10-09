#pragma once
#include <QLabel>

class Label : public QLabel
{
	Q_OBJECT
  signals:
	void clicked();
  public:
	explicit Label(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  protected:
	void mouseReleaseEvent(QMouseEvent* ev) override;
};
