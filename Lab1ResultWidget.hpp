#pragma once
#include <QWidget>
#include "ui_Lab1ResultWidget.h"

class MainWindow;
class Lab1ResultWidget : public QWidget {
	Q_OBJECT
private:
	Ui::Lab1ResultWidget ui;
	MainWindow* m_data;
public:
	Lab1ResultWidget(MainWindow *data, QWidget *parent = Q_NULLPTR);
public slots:
	void update_value();
};
