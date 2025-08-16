#include "UI/SettingsWindow.h"

#include <QSettings>

SettingsWindow::SettingsWindow(QWidget* parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	m_delay_validator = new QIntValidator(0, 999999, this);
	m_ui.lineEdit_triggerBotDelayBetweenShots->setValidator(m_delay_validator);
	m_settings_path = QApplication::applicationDirPath() + "/settings.ini";
	load_from_file();
}

void SettingsWindow::save_to_file()
{
	QSettings settings(m_settings_path, QSettings::IniFormat);
	settings.setValue("WindowName", m_ui.lineEdit_windowName->text());
	settings.setValue("ClientDLLName", m_ui.lineEdit_clientDllName->text());
	settings.setValue("EngineDLLName", m_ui.lineEdit_engineDllName->text());
	settings.setValue("TriggerBotDelayBetweenShots", m_ui.lineEdit_triggerBotDelayBetweenShots->text());
	settings.setValue("IgnoreSameTeam", m_ui.checkBox_ignoreSameTeam->isChecked());
}

void SettingsWindow::load_from_file()
{
	auto config = get_config();
	m_ui.lineEdit_windowName->setText(QString::fromStdString(config.windowname));
	m_ui.lineEdit_clientDllName->setText(QString::fromStdString(config.client_dll_name));
	m_ui.lineEdit_engineDllName->setText(QString::fromStdString(config.engine_dll_name));
	m_ui.lineEdit_triggerBotDelayBetweenShots->setText(QString::number(config.delay_between_shots));
	m_ui.checkBox_ignoreSameTeam->setChecked(config.ignore_same_team);
}

Config SettingsWindow::get_config()
{
	Config config = {};
	QSettings settings(m_settings_path, QSettings::IniFormat);
	config.windowname = settings.value("WindowName", "Counter-Strike 2").toString().toStdString();
	config.client_dll_name = settings.value("ClientDLLName", "client.dll").toString().toStdString();
	config.engine_dll_name = settings.value("EngineDLLName", "engine2.dll").toString().toStdString();
	config.delay_between_shots = settings.value("TriggerBotDelayBetweenShots", 500).toInt();
	config.ignore_same_team = settings.value("IgnoreSameTeam", true).toBool();

	return config;
}
