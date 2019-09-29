#include "MainWindow.h"
#include "Lab1ResultWidget.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	connect(ui.expert_number, qOverload<int>(&QSpinBox::valueChanged), this, &MainWindow::on_size_changed);
	connect(ui.alternative_number, qOverload<int>(&QSpinBox::valueChanged), this, &MainWindow::on_size_changed);

	ui.experts->setColumnCount(1);
	ui.experts->setHorizontalHeaderItem(0, new QTableWidgetItem("Experts"));
	ui.experts->setColumnWidth(0, 100);
	ui.alternatives->setColumnCount(1);
	ui.alternatives->setHorizontalHeaderItem(0, new QTableWidgetItem("Alternatives"));
	ui.alternatives->setColumnWidth(0, 100);

	on_size_changed();

	connect(ui.experts, &QTableWidget::cellChanged, this, &MainWindow::on_expert_name_changed);
	connect(ui.alternatives, &QTableWidget::cellChanged, this, &MainWindow::on_alternative_name_changed);
	connect(ui.estimations, &QTableWidget::cellChanged, this, &MainWindow::on_cell_changed);

	auto lab1 = new Lab1ResultWidget(this);
	ui.result_layout->addWidget(lab1);
	connect(ui.experts, &QTableWidget::cellChanged, lab1, &Lab1ResultWidget::update_value);
	connect(ui.alternatives, &QTableWidget::cellChanged, lab1, &Lab1ResultWidget::update_value);
	connect(ui.estimations, &QTableWidget::cellChanged, lab1, &Lab1ResultWidget::update_value);
	lab1->update_value();
}

std::vector<std::string> MainWindow::get_experts() const {
	std::vector<std::string> ret;
	for (size_t i = 0; i < ui.experts->rowCount(); i++)
		ret.push_back(ui.experts->item(i, 0)->text().toStdString());
	return ret;
}
std::vector<std::string> MainWindow::get_alternatives() const {
	std::vector<std::string> ret;
	for (size_t i = 0; i < ui.alternatives->rowCount(); i++)
		ret.push_back(ui.alternatives->item(i, 0)->text().toStdString());
	return ret;
}
std::vector<std::vector<double>> MainWindow::get_estimations() const {
	std::vector<std::vector<double>> ret;
	for (size_t i = 0; i < ui.estimations->rowCount(); i++) {
		std::vector<double> temp;
		for (size_t j = 0; j < ui.estimations->columnCount(); j++)
			temp.push_back(ui.estimations->item(i, j)->text().toDouble());
		ret.push_back(temp);
	}
	return ret;
}

void MainWindow::set_accent(size_t index) {
	if (m_current_accent != index) {
		if (m_current_accent != -1) {
			if (auto temp = ui.alternatives->item(m_current_accent, 0); temp)
				temp->setForeground(Qt::black);
			if (auto temp = ui.estimations->horizontalHeaderItem(m_current_accent); temp)
				temp->setForeground(Qt::black);
		}
		if (auto temp = ui.alternatives->item(index, 0); temp)
			temp->setForeground(QColor(128, 0, 128));
		if (auto temp = ui.estimations->horizontalHeaderItem(index); temp)
			temp->setForeground(QColor(128, 0, 128));
		m_current_accent = index;
	}
}

void MainWindow::on_size_changed() {
	auto expert_number = ui.expert_number->value(),
		alternative_number = ui.alternative_number->value();

	ui.experts->setRowCount(expert_number);
	ui.alternatives->setRowCount(alternative_number);
	ui.estimations->setRowCount(expert_number);
	ui.estimations->setColumnCount(alternative_number);

	for (size_t i = 0; i < ui.estimations->rowCount(); i++) {
		for (size_t j = 0; j < ui.estimations->columnCount(); j++) 
			if (!ui.estimations->item(i, j)) {
				ui.estimations->setItem(i, j, new QTableWidgetItem("0"));
				ui.estimations->item(i, j)->setTextAlignment(Qt::AlignCenter);
			}
		if (!ui.estimations->verticalHeaderItem(i))
			ui.estimations->setVerticalHeaderItem(i, new QTableWidgetItem("Unnamed"));
	}
	for (size_t j = 0; j < ui.estimations->columnCount(); j++)
		if (!ui.estimations->horizontalHeaderItem(j)) {
			ui.estimations->setHorizontalHeaderItem(j, new QTableWidgetItem("Unnamed"));
			ui.estimations->setColumnWidth(j, 100);
		}

	for (size_t i = 0; i < ui.experts->rowCount(); i++) {
		for (size_t j = 0; j < ui.experts->columnCount(); j++)
			if (!ui.experts->item(i, j)) {
				ui.experts->setItem(i, j, new QTableWidgetItem("Unnamed"));
				ui.experts->item(i, j)->setTextAlignment(Qt::AlignCenter);
			}
		if (!ui.experts->verticalHeaderItem(i))
			ui.experts->setVerticalHeaderItem(i, new QTableWidgetItem(""));
	}
	for (size_t i = 0; i < ui.alternatives->rowCount(); i++) {
		for (size_t j = 0; j < ui.alternatives->columnCount(); j++)
			if (!ui.alternatives->item(i, j)) {
				ui.alternatives->setItem(i, j, new QTableWidgetItem("Unnamed"));
				ui.alternatives->item(i, j)->setTextAlignment(Qt::AlignCenter);
			}
		if (!ui.alternatives->verticalHeaderItem(i))
			ui.alternatives->setVerticalHeaderItem(i, new QTableWidgetItem(""));
	}
}

void MainWindow::on_cell_changed(int row, int col) {
	auto string = ui.estimations->item(row, col)->text();
	bool flag;
	if (auto temp = string.toDouble(&flag); !flag)
		ui.estimations->item(row, col)->setText("0");
	else
		ui.estimations->item(row, col)->setText(QString::number(temp));
}

void MainWindow::on_expert_name_changed(int id) {
	ui.estimations->verticalHeaderItem(id)->setText(
		ui.experts->item(id, 0)->text()
	);
}
void MainWindow::on_alternative_name_changed(int id) {
	ui.estimations->horizontalHeaderItem(id)->setText(
		ui.alternatives->item(id, 0)->text()
	);
}