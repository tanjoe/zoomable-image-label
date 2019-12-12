/**********************************************************************************
 * @file      ZoomImageLabel.h
 * @brief     A subclass of QLabel that supports to zoom in and out under the mouse position
              QLabel的子类，支持以鼠标位置为中心缩放图片
 * @version   1.0.1
 *
 * 更新历史
 * --
 * 版本号|修订者|修订日期|说明
 * ------|------|------|------
 * 1.0.1|Qiao Tan|2019/11/19|增加了resize事件，这样控件变化后图片的分辨率也可以匹配
 * 1.0.0|Qiao Tan|2019/11/18|创建
 * @author    Qiao Tan
 * @date      2019/11/19
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
    void setImage(const QImage& image);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void changeStartPoint(const QPointF displacement); ///< 根据参数调整图片显示的起始位置，即平移图片
    void adjustStartPoint(int label_width, int label_height); ///< 限制图片显示的起始位置在合理的范围内
    void showImage(); ///< 显示图片

protected:
    float max_zoom_ratio_ = 5.0f; ///< 最大缩放比例
    float min_zoom_ratio_ = 1.0f; ///< 最小缩放比例
    float zoom_ratio_ = 1.0f; ///< 当前缩放比例

    bool is_mouse_pressed_ = false; ///< 鼠标按键是否按下
    bool is_image_setted_ = false; ///< 图片是否已设置

    QImage origin_image_; ///< 保存的原图
    QPointF display_start_point_; ///< 图片显示的起始位置
    QPointF last_mouse_loc_; ///< 鼠标按下的起始位置
    QPointF current_mouse_loc_; ///< 鼠标当前位置
};
