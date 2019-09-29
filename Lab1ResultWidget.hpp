#pragma once
#include <QWidget>
#include "ui_Lab1ResultWidget.h"

class MainWindow;
class Lab1ResultWidget : public QWidget {
	Q_OBJECT
private:
	Ui::Lab1ResultWidget ui;
	MainWindow* m_data;
protected:
	std::pair<size_t, std::vector<double>> lab1(std::vector<std::vector<double>>& data);
	std::pair<size_t, std::vector<double>> lab21(std::vector<std::vector<double>>& data);
	std::pair<size_t, std::vector<double>> lab22(std::vector<std::vector<double>>& data);
	std::pair<size_t, std::vector<double>> lab23(std::vector<std::vector<double>> &data);
	std::pair<size_t, std::vector<double>> lab24(std::vector<std::vector<double>>& data);
	std::pair<size_t, std::vector<double>> lab25(std::vector<std::vector<double>>& data);
	std::pair<size_t, std::vector<double>> lab3(std::vector<std::vector<double>>& data);
public:
	Lab1ResultWidget(MainWindow *data, QWidget *parent = Q_NULLPTR);
public slots:
	void update_value();
};
