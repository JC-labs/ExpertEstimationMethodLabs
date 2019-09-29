#include "Lab1ResultWidget.hpp"
#include "MainWindow.h"

std::vector<double> Lab1ResultWidget::lab1(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> expert_sums(data.size());
	for (size_t i = 0; i < expert_sums.size(); i++) {
		expert_sums[i] = 0;
		for (size_t j = 0; j < data.front().size(); j++)
			expert_sums[i] += data[i][j];
	}
	std::vector<double> alternative_values(data.front().size());
	for (size_t j = 0; j < alternative_values.size(); j++) {
		alternative_values[j] = 0;
		for (size_t i = 0; i < expert_sums.size(); i++)
			alternative_values[j] += data[i][j] / expert_sums[i];
		alternative_values[j] /= alternative_values.size();
	}
	return alternative_values;
}

Lab1ResultWidget::Lab1ResultWidget(MainWindow* data, QWidget *parent) : QWidget(parent), m_data(data) {
	ui.setupUi(this);
	ui.alternatives->setRowCount(1);
	ui.alternatives->setVerticalHeaderItem(0, new QTableWidgetItem("Results"));

	connect(ui.o1, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
	connect(ui.o21, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
	connect(ui.o22, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
	connect(ui.o23, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
	connect(ui.o24, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
	connect(ui.o25, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
}

void Lab1ResultWidget::update_value() {
	auto& [experts, alternatives, estimations] = m_data->get();
	
	std::vector<double> alternative_values;
	if (ui.o1->isChecked())
		alternative_values = lab1(estimations);
	else {}

	ui.alternatives->setColumnCount(alternative_values.size());
	for (size_t j = 0; j < ui.alternatives->columnCount(); j++) {
		for (size_t i = 0; i < ui.alternatives->rowCount(); i++)
			if (auto temp = ui.alternatives->item(i, j); temp) {
				temp->setText(QString::number(alternative_values[j]));
				temp->setForeground(Qt::black);
			} else {
				ui.alternatives->setItem(i, j, new QTableWidgetItem(QString::number(alternative_values[j])));
				ui.alternatives->item(i, j)->setTextAlignment(Qt::AlignCenter);
			}
		if (auto temp = ui.alternatives->horizontalHeaderItem(j); temp)
			temp->setText(QString::fromStdString(alternatives[j]));
		else {
			ui.alternatives->setHorizontalHeaderItem(j, new QTableWidgetItem(QString::fromStdString(alternatives[j])));
			ui.alternatives->setColumnWidth(j, 100);
		}
	}
	auto max = std::distance(alternative_values.begin(), std::max_element(alternative_values.begin(), alternative_values.end()));
	if (auto temp = ui.alternatives->item(0, max); temp)
		temp->setForeground(QColor(128, 0, 128));
	m_data->set_accent(max);
}