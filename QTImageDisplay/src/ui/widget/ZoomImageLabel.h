/**********************************************************************************
 * @file      ZoomImageLabel.h
 * @brief     A subclass of QLabel that supports to zoom in and out under the mouse position
              QLabel的子类，支持以鼠标位置为中心缩放图片
 * @version   1.0.0
 *
 * 更新历史
 * --
 * 版本号|修订者|修订日期|说明
 * ------|------|------|------
 * 1.0.0|Qiao Tan|2019/11/18|创建
 * @author    Qiao Tan
 * @date      2019/11/18
 *********************************************************************************/
#pragma once
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QtGlobal>
#include <QDebug>

class ZoomImageLabel : public QLabel 
{
    Q_OBJECT

public:
    ZoomImageLabel(QWidget * parent = Q_NULLPTR);
	virtual ~ZoomImageLabel();

public:
    void setImage(QImage image);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent *event) override;
	
private:
    void changeStartPoint(const QPointF displacement);
    void adjustStartPoint(int label_width, int label_height);
    void showImage();

protected:
    float max_zoom_ratio_ = 6.0f;
    float min_zoom_ratio_ = 1.0f;
    float zoom_ratio_ = 1.0f;

    bool is_mouse_pressed_ = false;
    bool is_image_setted_ = false;

    QImage origin_image_;
    QPointF display_start_point_;
    QPointF last_mouse_loc_;
    QPointF current_mouse_loc_;
};
