#include "Lab1ResultWidget.hpp"
#include "MainWindow.h"

size_t max_in_row(std::vector<std::vector<double>> const& data, size_t row) {
	return std::distance(data[row].begin(), std::max_element(data[row].begin(), data[row].end()));
}
size_t min_in_row(std::vector<std::vector<double>> const& data, size_t row) {
	return std::distance(data[row].begin(), std::min_element(data[row].begin(), data[row].end()));
}
size_t max_in_column(std::vector<std::vector<double>> const& data, size_t column) {
	size_t ret = -1; double value = std::numeric_limits<double>::min();
	for (size_t i = 0; i < data.size(); i++)
		if (value < data[i][column]) {
			ret = i;
			value = data[i][column];
		}
	return ret;
}
size_t min_in_column(std::vector<std::vector<double>> const& data, size_t column) {
	size_t ret = -1; double value = std::numeric_limits<double>::max();
	for (size_t i = 0; i < data.size(); i++)
		if (value > data[i][column]) {
			ret = i;
			value = data[i][column];
		}
	return ret;
}

size_t max_element(std::vector<double> const& data) {
	return std::distance(data.begin(), std::max_element(data.begin(), data.end()));
}
size_t min_element(std::vector<double> const& data) {
	return std::distance(data.begin(), std::min_element(data.begin(), data.end()));
}

std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab1(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> expert_sums(data.size());
	for (size_t i = 0; i < expert_sums.size(); i++) {
		expert_sums[i] = 0;
		for (size_t j = 0; j < data.front().size(); j++)
			expert_sums[i] += data[i][j];
	}
	std::vector<double> result(data.front().size());
	for (size_t j = 0; j < result.size(); j++) {
		result[j] = 0;
		for (size_t i = 0; i < expert_sums.size(); i++)
			result[j] += data[i][j] / expert_sums[i];
		result[j] /= result.size();
	}
	return { max_element(result), result };
}
std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab21(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> temp(data.size());
	for (size_t i = 0; i < temp.size(); i++)
		temp[i] = data[i][min_element(data[i])];
	return { max_element(temp), temp };
}
std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab22(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> temp(data.size());
	for (size_t i = 0; i < temp.size(); i++)
		temp[i] = data[i][max_element(data[i])];
	return { min_element(temp), temp };
}
std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab23(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> temp(data.size());
	for (size_t i = 0; i < temp.size(); i++)
		temp[i] = 0.6 * data[i][max_element(data[i])] + 
				  0.4 * data[i][min_element(data[i])];
	return { max_element(temp), temp };
}
std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab24(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> maxes(data.front().size());
	for (size_t j = 0; j < maxes.size(); j++)
		maxes[j] = max_in_column(data, j);
	auto r = data;
	for (size_t i = 0; i < r.size(); i++)
		for (size_t j = 0; j < r[i].size(); j++)
			r[i][j] = maxes[j] - r[i][j];
	return lab22(r);
}
std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab25(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> sums(data.size());
	for (size_t i = 0; i < sums.size(); i++) {
		sums[i] = 0;
		for (size_t j = 0; j < data[i].size(); j++)
			sums[i] += data[i][j];
		sums[i] /= data[i].size();
	}
	return { max_element(sums), sums };
}
std::pair<size_t, std::vector<double>> Lab1ResultWidget::lab3(std::vector<std::vector<double>>& data) {
	if (!data.size())
		return {};
	std::vector<double> counts(data.front().size());
	for (size_t i = 0; i < counts.size(); i++)
		for (size_t j = i + 1; j < counts.size(); j++) {
			bool first_is_better = false,
				second_is_better = false;
			for (size_t k = 0; k < data.size(); k++) {
				if (data[k][i] < data[k][j])
					first_is_better = true;
				else if (data[k][i] > data[k][j])
					second_is_better = true;
			}
			if (first_is_better && !second_is_better)
				counts[j]++;
			if (second_is_better && !first_is_better)
				counts[i]++;
		}
	return { 0, counts };
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
	connect(ui.o3, &QRadioButton::clicked, this, &Lab1ResultWidget::update_value);
}

void Lab1ResultWidget::update_value() {
	auto& [experts, alternatives, estimations] = m_data->get();
	
	std::pair<size_t, std::vector<double>> result;
	if (ui.o1->isChecked())
		result = lab1(estimations);
	else if (ui.o21->isChecked())
		result = lab21(estimations);
	else if (ui.o22->isChecked())
		result = lab22(estimations);
	else if (ui.o23->isChecked())
		result = lab23(estimations);
	else if (ui.o24->isChecked())
		result = lab24(estimations);
	else if (ui.o25->isChecked())
		result = lab25(estimations);
	else if (ui.o3->isChecked())
		result = lab3(estimations);
	else {}

	auto names = alternatives;
	if (!ui.o1->isChecked() && !ui.o3->isChecked())
		names = experts;

	ui.alternatives->setColumnCount(result.second.size());
	for (size_t j = 0; j < ui.alternatives->columnCount(); j++) {
		for (size_t i = 0; i < ui.alternatives->rowCount(); i++)
			if (auto temp = ui.alternatives->item(i, j); temp) {
				temp->setText(QString::number(result.second[j]));
				temp->setForeground(Qt::black);
			} else {
				ui.alternatives->setItem(i, j, new QTableWidgetItem(QString::number(result.second[j])));
				ui.alternatives->item(i, j)->setTextAlignment(Qt::AlignCenter);
			}
		if (auto temp = ui.alternatives->horizontalHeaderItem(j); temp)
			temp->setText(QString::fromStdString(names[j]));
		else {
			ui.alternatives->setHorizontalHeaderItem(j, new QTableWidgetItem(QString::fromStdString(names[j])));
			ui.alternatives->setColumnWidth(j, 100);
		}
	}
	if (!ui.o3->isChecked()) {
		if (auto temp = ui.alternatives->item(0, result.first); temp)
			temp->setForeground(QColor(96, 0, 96));
		if (ui.o1->isChecked())
			m_data->set_accent(result.first, true);
		else
			m_data->set_accent(result.first, false);
	} else {
		for (size_t j = 0; j < ui.alternatives->columnCount(); j++)
			if (auto temp = ui.alternatives->item(0, j); temp && temp->text() == "0")
				temp->setForeground(QColor(96, 0, 96));
		m_data->set_accent(0, false);
		m_data->multi_accent(result.second);
	}
}