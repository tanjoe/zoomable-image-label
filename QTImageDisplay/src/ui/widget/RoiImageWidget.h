/**********************************************************************************
 * @file      RoiImageLabel.h
 * @brief     A subclass of ZoomImageLabel, in addition to picture zooming in and out,
supports ROI selection.
              ZoomImageLabel的子类，除了缩放图片，还支持ROI的框选功能
 * @version   1.0.1
 *
 * 更新历史
 * --
 * 版本号|修订者|修订日期|说明
 * ------|------|------|------
 * 1.0.1|Qiao Tan|2019/11/19|增加了菜单事件，可以通过右键菜单选择是否开启ROI框选
 * 1.0.0|Qiao Tan|2019/11/18|创建
 * @author    Qiao Tan
 * @date      2019/11/19
 *********************************************************************************/
#pragma once
#include <QAction>
#include "ZoomImageWidget.h"

class RoiImageWidget : public ZoomImageWidget
{
    Q_OBJECT

public:
    RoiImageWidget(QWidget *parent);
    virtual ~RoiImageWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    void calculateRoi(); ///< 计算框选区域在原图坐标系下对应的值
    void calculateRect(); ///< 计算框选区域在控件坐标系下对应的值
    void widgetToImage(QPointF& point); ///< 由控件坐标系转到原图坐标系
    void imageToWidget(QPointF& point); ///< 由原图坐标系转到控件坐标系

private slots:
    void enableRoiSelection(bool value); ///< 开启/关闭ROI框选

signals:
    void signalRefreshROI(const QRectF& roi);

private:
    bool is_selection_enabled_ = false; ///< 是否开启ROI框选
    bool is_mouse_left_press_ = false; ///< 鼠标左键是否按下
    bool is_selection_cancelled_ = false; ///< ROI框选是否已取消
    QPointF begin_point_; ///< ROI框选起点
    QPointF end_point_; ///< ROI框选结束点
    QRectF selected_rect_; ///< 框选的区域
    QAction enable_roi_act_; ///< 右键菜单的action，对应开启/关闭ROI框选
};
