#pragma once
#include <QDialog>
#include <QValidator>

#include "CS2/Config.h"
#include "ui_settingswidget.h"

class SettingsWindow : public QDialog 
{
	Q_OBJECT
public:
	explicit SettingsWindow(QWidget* parent = nullptr);
	void save_to_file();
	void load_from_file();
	Config get_config();
	
private:
	Ui::SettingsWidget m_ui;
	QIntValidator* m_delay_validator = nullptr;
	QString m_settings_path;
};
