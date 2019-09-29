#include "Lab1ResultWidget.hpp"
#include "MainWindow.h"

Lab1ResultWidget::Lab1ResultWidget(MainWindow* data, QWidget *parent) : QWidget(parent), m_data(data) {
	ui.setupUi(this);
	ui.alternatives->setRowCount(1);
	ui.alternatives->setVerticalHeaderItem(0, new QTableWidgetItem("Results"));
}

void Lab1ResultWidget::update_value() {
	auto& [experts, alternatives, estimations] = m_data->get();
	std::vector<double> expert_sums(experts.size());
	for (size_t i = 0; i < expert_sums.size(); i++) {
		expert_sums[i] = 0;
		for (size_t j = 0; j < alternatives.size(); j++)
			expert_sums[i] += estimations[i][j];
	}
	std::vector<double> alternative_values(alternatives.size());
	for (size_t j = 0; j < alternative_values.size(); j++) {
		alternative_values[j] = 0;
		for (size_t i = 0; i < expert_sums.size(); i++)
			alternative_values[j] += estimations[i][j] / expert_sums[i];
		alternative_values[j] /= alternative_values.size();
	}	

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
	ui.alternatives->item(0, max)->setForeground(QColor(128, 0, 128));
	m_data->set_accent(max);
}