#pragma once
#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include <vector>
#include <tuple>

class Lab1ResultWidget;
class MainWindow : public QWidget {
	Q_OBJECT
private:
	Ui::MainWindowClass ui;

	size_t m_current_accent = -1;
	bool m_current_accent_direction = false;
	bool m_multi_accent = false;
	Lab1ResultWidget* m_results;
protected:
	void connect_all();
	void disconnect_all();

	void clear_accent();
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	std::vector<std::string> get_experts() const;
	std::vector<std::string> get_alternatives() const;
	std::vector<std::vector<double>> get_estimations() const;
	auto get() const { return std::make_tuple(get_experts(), get_alternatives(), get_estimations()); }

	void set_accent(size_t index, bool is_column = true);
	void multi_accent(std::vector<double> const& input, bool is_column = true);

public slots:
	void on_size_changed();
	void on_cell_changed(int row, int col);
	void on_expert_name_changed(int id);
	void on_alternative_name_changed(int id);
};