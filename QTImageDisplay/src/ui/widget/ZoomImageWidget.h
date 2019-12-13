/**********************************************************************************
 * @file      ZoomImageLabel.h
 * @brief     A subclass of QLabel that supports to zoom in and out under the mouse position
              QLabel的子类，支持以鼠标位置为中心缩放图片
 * @version   1.1.1
 *
 * 更新历史
 * --
 * 版本号|修订者|修订日期|说明
 * ------|------|------|------
 * 1.1.1|Qiao Tan|2019/12/13|增加了FPS的计算和获取接口，用于粗略衡量显示效率
 * 1.1.0|Qiao Tan|2019/12/12|改用QPainter绘制图片，不再使用QLabel的setPixmap函数，提高显示效率
 * 1.0.1|Qiao Tan|2019/11/19|增加了resize事件，这样控件变化后图片的分辨率也可以匹配
 * 1.0.0|Qiao Tan|2019/11/18|创建
 * @author    Qiao Tan
 * @date      2019/12/13
 *********************************************************************************/
#pragma once
#include <QWidget>
#include <QMouseEvent>

class ZoomImageWidget : public QWidget
{
    Q_OBJECT

public:
    ZoomImageWidget(QWidget * parent = Q_NULLPTR);
    virtual ~ZoomImageWidget();

public:
    void setImage(const QImage& image);
    double getFPS();
    double getIPS();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void changeStartPoint(const QPointF displacement); ///< 根据参数调整图片显示的起始位置，即平移图片
    void adjustStartPoint(int label_width, int label_height); ///< 限制图片显示的起始位置在合理的范围内

protected:
    double max_zoom_ratio_ = 5.0f; ///< 最大缩放比例
    double min_zoom_ratio_ = 1.0f; ///< 最小缩放比例
    double zoom_ratio_ = 1.0f; ///< 当前缩放比例

    bool is_mouse_pressed_ = false; ///< 鼠标按键是否按下
    bool is_image_setted_ = false; ///< 图片是否已设置

    QImage origin_image_; ///< 保存的原图
    QPointF display_start_point_; ///< 图片显示的起始位置
    QPointF last_mouse_loc_; ///< 鼠标按下的起始位置
    QPointF current_mouse_loc_; ///< 鼠标当前位置
    int paint_count_ = 0; ///< paintEvent()被调用次数，用于计算frame per second即FPS
    int image_count_ = 0; ///< setImage()被调用次数，用于计算image per second即IPS
    double FPS_ = 0.0f; ///< 控件显示帧率
    double IPS_ = 0.0f; ///< 图片源帧率，通常小于FPS_
};
