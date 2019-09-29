#pragma once
#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include <vector>
#include <tuple>

class MainWindow : public QWidget {
	Q_OBJECT
private:
	Ui::MainWindowClass ui;
public:
	MainWindow(QWidget *parent = Q_NULLPTR);

	std::vector<std::string> get_experts() const;
	std::vector<std::string> get_alternatives() const;
	std::vector<std::vector<double>> get_estimations() const;
	auto get() const { return std::make_tuple(get_experts(), get_alternatives(), get_estimations()); }

public slots:
	void on_size_changed();
	void on_cell_changed(int row, int col);
	void on_expert_name_changed(int id);
	void on_alternative_name_changed(int id);
};