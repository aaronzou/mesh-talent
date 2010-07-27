#ifndef MESHTALENT_MESHVIEWERWIDGET_H
#define MESHTALENT_MESHVIEWERWIDGET_H

#include <QString>
#include <QMessageBox>
#include <QFileDialog>

#include <GL/glut.h>

#include "QGLViewerWidget.h"
#include "DeformableMesh3d.h"

using namespace meshtalent;

class MeshViewerWidget : public QGLViewerWidget {
	Q_OBJECT
public:
	typedef DeformableMesh3d::InterMesh InterMesh;
public:
	MeshViewerWidget(QWidget* parent = 0);
	~MeshViewerWidget();
public:
	void open_mesh_gui(QString fname);
	bool openMesh(const char* filename);
	InterMesh& mesh() { return mesh_; };
	const InterMesh& mesh() const { return mesh_; };
public slots:
	void open_mesh_query() {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open mesh file"),
            tr("../models/"),
            tr( "OFF Files (*.off);;"
			"OBJ Files (*.obj);;"
            "STL Files (*.stl);;"
            "All Files (*)"));
        if (!fileName.isEmpty())
            open_mesh_gui(fileName);
	}
	void gen_graph_query();
private:
	void genGraph();
protected:
	virtual void draw_scene(int drawmode);
	virtual void mousePressEvent(QMouseEvent* _event);
	virtual void mouseMoveEvent(QMouseEvent* _event);
	virtual void mouseReleaseEvent(QMouseEvent* _event);
private:
	QPoint pick_press_point_; // for pick mode.
private:
	void draw_mesh_wireframe() const;
	void draw_mesh_solidflat() const;
	void draw_mesh_solidsmooth() const;
	void draw_mesh_pointset() const;
	void draw_graph() const;
	void drawSelectBox(const OpenMesh::Vec3d& center, double radius);
	void draw_select_boxes();
private:
	void processPick(QMouseEvent* _event);
	void processHits(GLint hits, GLuint* buffer, bool controled);
private:
	InterMesh mesh_;
	DeformableMesh3d* pdmesh_;
	DeformationGraph* pdgraph_;
public:
	enum { MOUSE_PICK = N_MOUSE_MODES, MOUSE_DEFORM };
	enum { DRAW_GRAPH = N_DRAW_MODES };
};

#endif // MESHTALENT_MESHVIEWERWIDGET_H