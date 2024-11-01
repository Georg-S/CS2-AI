#pragma once
#include <qevent.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwidget.h>
#include <qscrollarea.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <optional>
#include <iostream>
#include "Utility/Logging.h"
#include "Utility/Vec3D.h"
#include "Utility/Vec2D.h"
#include "Utility/json.hpp"

using json = nlohmann::json;

namespace Editor
{
	struct Node
	{
		Node(int id, bool corner, Vec3D<float> pos) : id(id), corner(corner), pos(pos), canvas_pos(Vec2D<int>()), render(false) {};

		int id;
		bool corner;
		Vec3D<float> pos;
		Vec2D<int> canvas_pos;
		bool render = false;
	};

	struct Edge
	{
		Edge(Node* from, Node* to, float weight, bool render = false) : from(from), to(to), weight(weight), render(render) {};

		Node* from;
		Node* to;
		float weight;
		bool render = false;
	};
}


class NavmeshEditor : public QScrollArea
{
	enum class State
	{
		NONE, PLACE_CORNER_1, PLACE_CORNER_2, ADD_EDGES
	};

	Q_OBJECT

public:
	explicit NavmeshEditor(QWidget* parent, QLineEdit* output);
	~NavmeshEditor();

	void load_navmesh(const QString& file_name);
	void load_image(const QString& file_name);
	void place_corner_points();
	bool save_navmesh();
	void add_node(const Vec3D<float>& cs2_pos);

protected:
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	Vec2D<int> get_cursor_pos_on_canvas() const;
	void left_clicked(QMouseEvent* event);
	void delete_node_and_corresponding_edges(Editor::Node* node);
	void delete_edge(Editor::Edge* edge);
	void right_clicked(QMouseEvent* event);
	void render_editor();
	void zoom(double factor);
	void output(const std::string& message);
	void output(const QString& message, Qt::GlobalColor color);
	void output(const QString& message);
	void output_error(const QString& message);
	void output_success(const QString& message);
	void load_nodes(const json& navmesh_json);
	void load_edges(const json& navmesh_json);
	void set_corner_nodes();
	void render_edges(QPixmap& pixmap);
	void render_nodes(QPixmap& pixmap);
	void adjust_all_nodes();
	Editor::Node* get_clicked_node(const std::vector<std::unique_ptr<Editor::Node>>& nodes, const Vec2D<int>& click_pos);
	Editor::Edge* get_clicked_edge(const std::vector<std::unique_ptr<Editor::Edge>>& edges, const Vec2D<int>& click_pos);
	bool add_edge(Editor::Node* from, Editor::Node* to, bool render = true);
	Editor::Node* get_node_pointer_by_id(const std::vector<std::unique_ptr<Editor::Node>>& nodes, int id) const;
	void setNodesAndEdgesInvisible() const;

	QLabel* m_displayed_map = nullptr;
	QImage m_image;
	double m_zoom_factor = 1;
	State m_editor_state = State::NONE;
	QLineEdit* m_output_line = nullptr;
	bool m_corner_nodes_placed = false;
	bool m_valid_json_loaded = false;
	int m_next_node_id = 0;
	std::vector<std::unique_ptr<Editor::Node>> m_nodes;
	std::vector<std::unique_ptr<Editor::Edge>> m_edges;
	std::string m_map_name = "";
	Editor::Node* m_corner_node_1 = nullptr;
	Editor::Node* m_corner_node_2 = nullptr;
	Editor::Node* m_selected_node_1 = nullptr;
	Editor::Node* m_selected_node_2 = nullptr;
	static constexpr int NODE_SIZE = 12;
};