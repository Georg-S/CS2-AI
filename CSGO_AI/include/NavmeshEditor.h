#pragma once
#include <qevent.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwidget.h>
#include <qscrollarea.h>
#include <Logging.h>
#include <qlineedit.h>
#include <fstream>
#include <vector>
#include "Vec3D.h"
#include "Vec2D.h"
#include "json.hpp"

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
		Edge(Node* from, Node* to, float weight) : from(from), to(to), weight(weight), render(false) {};

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

	void left_clicked(QMouseEvent* event);
	void render_editor();
	void load_image(const QString& file_name);
	void load_navmesh(const QString& file_name);
	void place_corner_points();
	bool save_navmesh();
protected:
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
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
	bool add_edge(Editor::Node* from, Editor::Node* to);
	Editor::Node* get_node_pointer_by_id(const std::vector<std::unique_ptr<Editor::Node>>& nodes, int id) const;

	QLabel* displayed_map = nullptr;
	QImage image;
	double zoom_factor = 1;
	State editor_state = State::NONE;
	QLineEdit* output_line = nullptr;
	bool corner_nodes_placed = false;
	bool valid_json_loaded = false;
	std::vector<std::unique_ptr<Editor::Node>> nodes;
	std::vector<std::unique_ptr<Editor::Edge>> edges;
	std::string map_name = "";
	Editor::Node* corner_node_1 = nullptr;
	Editor::Node* corner_node_2 = nullptr;
	Editor::Node* selected_node_1 = nullptr;
	Editor::Node* selected_node_2 = nullptr;
	static constexpr int NODE_SIZE = 10;
};