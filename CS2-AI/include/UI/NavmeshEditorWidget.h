#pragma once
#include <memory>
#include <qfiledialog.h>
#include <iostream>
#include <qwidget.h>
#include "ui_NavmeshEditorWidget.h"
#include "NavmeshEditor.h"
#include "CS2Runner.h"

class NavmeshEditorWidget : public QWidget 
{
	Q_OBJECT;
public:
	explicit NavmeshEditorWidget(CS2Runner* cs2_runner, QWidget* parent = nullptr);
	~NavmeshEditorWidget();

private:
	Ui::NavmeshEditorWidget* m_ui;
	std::unique_ptr<NavmeshEditor> m_navmesh_editor;
	CS2Runner* m_cs2_runner = nullptr;

private slots:
	void on_button_load_map_clicked();
	void on_button_load_navmesh_clicked();
	void on_button_place_corner_points_clicked();
	void on_button_save_navmesh_clicked();
	void on_button_create_node_from_game_pos_clicked();
};