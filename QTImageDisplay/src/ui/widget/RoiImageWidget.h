/**********************************************************************************
 * @file      RoiImageLabel.h
 * @brief     A subclass of ZoomImageLabel, in addition to picture zooming in and out,
supports ROI selection.
              ZoomImageLabel�����࣬��������ͼƬ����֧��ROI�Ŀ�ѡ����
 * @version   1.0.1
 *
 * ������ʷ
 * --
 * �汾��|�޶���|�޶�����|˵��
 * ------|------|------|------
 * 1.0.1|Qiao Tan|2019/11/19|�����˲˵��¼�������ͨ���Ҽ��˵�ѡ���Ƿ���ROI��ѡ
 * 1.0.0|Qiao Tan|2019/11/18|����
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
    void calculateRoi(); ///< �����ѡ������ԭͼ����ϵ�¶�Ӧ��ֵ
    void calculateRect(); ///< �����ѡ�����ڿؼ�����ϵ�¶�Ӧ��ֵ
    void widgetToImage(QPointF& point); ///< �ɿؼ�����ϵת��ԭͼ����ϵ
    void imageToWidget(QPointF& point); ///< ��ԭͼ����ϵת���ؼ�����ϵ

private slots:
    void enableRoiSelection(bool value); ///< ����/�ر�ROI��ѡ

signals:
    void signalRefreshROI(const QRectF& roi);

private:
    bool is_selection_enabled_ = false; ///< �Ƿ���ROI��ѡ
    bool is_mouse_left_press_ = false; ///< �������Ƿ���
    bool is_selection_cancelled_ = false; ///< ROI��ѡ�Ƿ���ȡ��
    QPointF begin_point_; ///< ROI��ѡ���
    QPointF end_point_; ///< ROI��ѡ������
    QRectF selected_rect_; ///< ��ѡ������
    QAction enable_roi_act_; ///< �Ҽ��˵���action����Ӧ����/�ر�ROI��ѡ
};
