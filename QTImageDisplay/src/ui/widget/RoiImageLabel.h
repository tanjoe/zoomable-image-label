/**********************************************************************************
 * @file      RoiImageLabel.h
 * @brief     A subclass of ZoomImageLabel, in addition to picture zooming in and out,
supports ROI selection.
              ZoomImageLabel�����࣬��������ͼƬ����֧��ROI�Ŀ�ѡ����
 * @version   1.0.0
 *
 * ������ʷ
 * --
 * �汾��|�޶���|�޶�����|˵��
 * ------|------|------|------
 * 1.0.0|Qiao Tan|2019/11/18|����
 * @author    Qiao Tan
 * @date      2019/11/18
 *********************************************************************************/
#pragma once
#include <QPainter>
#include "ZoomImageLabel.h"

class RoiImageLabel : public ZoomImageLabel
{
    Q_OBJECT

public:
    RoiImageLabel(QWidget *parent);
    virtual ~RoiImageLabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void calculateRoi();
    void calculateRect();
    void widgetToImage(QPointF& point);
    void imageToWidget(QPointF& point);

public slots:
    void enableRoiSelection(bool value);

signals:
    void signalRefreshROI(const QRectF& roi);

private:
    bool is_selection_enabled_ = false;
    bool is_mouse_left_press_ = false;
    bool is_selection_cancelled_ = false;
    QPointF begin_point_;
    QPointF end_point_;
    QRectF selected_rect_;
};
