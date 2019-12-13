/**********************************************************************************
 * @class     ::RoiImageLabel
 * @brief     A subclass of ZoomImageLabel, in addition to picture zooming in and out,
supports ROI selection.
              ZoomImageLabel�����࣬��������ͼƬ����֧��ROI�Ŀ�ѡ����
 * @version   1.0.1
 * @author    Qiao Tan
 * @date      2019/11/19
 *********************************************************************************/
#include <QPainter>
#include <QMenu>
#include "RoiImageWidget.h"

/******************************************************************
 * @brief     
 * @details   
 * @param     parent
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
RoiImageWidget::RoiImageWidget(QWidget *parent)
    : ZoomImageWidget(parent)
{
    enable_roi_act_.setText(tr("enable roi select"));
    enable_roi_act_.setCheckable(true);
    enable_roi_act_.setIconVisibleInMenu(false);
    connect(&enable_roi_act_, &QAction::toggled, this, &RoiImageWidget::enableRoiSelection);
}

/******************************************************************
 * @brief     
 * @details   
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
RoiImageWidget::~RoiImageWidget()
{
}

/******************************************************************
 * @brief     ������갴�µİ�����������һ�ֵ�ROI��ѡ��ȡ����ѡ��ROI
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     begin a new round of ROI selection or cancel the already selected
ROI, according to the mouse button pressed
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::mousePressEvent(QMouseEvent *event)
{
    if (!is_selection_enabled_)
    {
        ZoomImageWidget::mousePressEvent(event);
        return;
    }
    else
    {
        if (event->button() == Qt::LeftButton)
        {
            is_mouse_left_press_ = true;
            is_selection_cancelled_ = false;
            begin_point_ = event->localPos();
        }
        if (event->button() == Qt::RightButton)
        {
            is_mouse_left_press_ = false;
            is_selection_cancelled_ = true;
            begin_point_ = QPointF(0, 0);
            end_point_ = QPointF(0, 0);
            this->update();
        }
    }
}

/******************************************************************
 * @brief     ����end_point_����ˢ�������Ƶľ���
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     update end_point_ and the drawn rectangle that represents the ROI
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!is_selection_enabled_)
    {
        ZoomImageWidget::mouseMoveEvent(event);
        return;
    }
    else
    {
        if (is_mouse_left_press_)
        {
            QPointF pos = event->localPos();
            end_point_ = QPointF(qMin(pos.x(), (qreal)this->width()), qMin(pos.y(), (qreal)this->height()));
            this->update();
        }
    }
}

/******************************************************************
 * @brief     ����ɿ�ʱ���������������ROI
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     when the mouse is released, calculate the ROI if applicable
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!is_selection_enabled_)
    {
        ZoomImageWidget::mouseReleaseEvent(event);
        return;
    }
    else
    {
        is_mouse_left_press_ = false;
        this->calculateRoi();
    }
}

/******************************************************************
 * @brief     ���ø��෽������ͼƬ�������´�����ѡROI�ľ���
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     use the parent method to scale displayed image and update
the rectangle that represents the selected ROI
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::wheelEvent(QWheelEvent *event)
{
    ZoomImageWidget::wheelEvent(event);
    begin_point_ = selected_rect_.topLeft();
    end_point_ = selected_rect_.bottomRight();
    this->imageToWidget(begin_point_);
    this->imageToWidget(end_point_);
    this->update();
}

/******************************************************************
 * @brief     ���ƹ�ѡ����
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     paint the selected area
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::paintEvent(QPaintEvent *event)
{
    ZoomImageWidget::paintEvent(event);
    if (is_selection_enabled_ && !is_selection_cancelled_)
    {
        QPainter painter;
        painter.begin(this);
        QRectF rect(begin_point_, end_point_);
        painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap));
        painter.drawRect(rect);
        painter.end();
    }
}

/******************************************************************
 * @brief     �˵��¼����ṩ����/�ر�ROIѡ���ѡ��
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/19

 * @brief     menu event in which offer the option to enable/disable 
ROI selection
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/19
 ******************************************************************/
void RoiImageWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu* menu = new QMenu();
    menu->addAction(&enable_roi_act_);
    menu->exec(event->globalPos());
    delete menu;
}

/******************************************************************
 * @brief     ���㹴ѡ�����Ӧ��ROI������֮��Ϊ�źŵĲ������ͳ�ȥ
 * @details   ����õ���ROI��Ӧԭͼ�ϵ�����
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     calculate ROI and emit it out as a parameter of the signal
 * @details   The calculated ROI corresponds to the pixels on the original image
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::calculateRoi()
{
    if (!is_selection_enabled_)
    {
        return;
    }
    else
    {
        this->calculateRect();
        QPointF roi_start = selected_rect_.topLeft();
        QPointF roi_end = selected_rect_.bottomRight();
        this->widgetToImage(roi_start);
        this->widgetToImage(roi_end);
        selected_rect_ = QRectF(roi_start, roi_end);
        emit signalRefreshROI(selected_rect_);
    }
}

/******************************************************************
 * @brief     ��������ѡ�ľ��������ڿؼ�����ϵ�µ�����
 * @details
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     calculate coordinates of the selected rectangle. The coordinates
refer to the widget frame, i.e., the RoiImageLabel frame
 * @details   
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::calculateRect()
{
    int width = qAbs(begin_point_.x() - end_point_.x());
    int height = qAbs(begin_point_.y() - end_point_.y());
    QPointF top_left_point; // the actual top left point
    if ((begin_point_.x() < end_point_.x() && begin_point_.y() < end_point_.y())) // from top left to bottom right
    {
        top_left_point = begin_point_;
    }
    else if (begin_point_.x() > end_point_.x() && begin_point_.y() > end_point_.y()) // from bottom right to top left
    {
        top_left_point = end_point_;
    }
    else if (begin_point_.x() > end_point_.x() && begin_point_.y() < end_point_.y()) // from right top to left bottom
    {
        top_left_point.rx() = end_point_.x();
        top_left_point.ry() = begin_point_.y();
    }
    else // from left bottom to right top
    {
        top_left_point.rx() = begin_point_.x();
        top_left_point.ry() = end_point_.y();
    }
    selected_rect_ = QRectF(top_left_point.x(), top_left_point.y(), width, height);
}

/******************************************************************
 * @brief     ��һ����������ɿؼ�����ת����ԭͼ��Ӧ������
 * @details
 * @param     point
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     convert a point in the widget frame to the origin image frame
 * @details   
 * @param     point
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::widgetToImage(QPointF& widget_point)
{
    QPointF convert_factor;
    convert_factor.rx() = origin_image_.width() / (this->width() * zoom_ratio_);
    convert_factor.ry() = origin_image_.height() / (this->height() * zoom_ratio_);
    widget_point.rx() = (widget_point.x() + display_start_point_.x()) * convert_factor.x();
    widget_point.ry() = (widget_point.y() + display_start_point_.y()) * convert_factor.y();
}

/******************************************************************
 * @brief     ��һ�����������ԭͼ��Ӧ������ת�����ؼ�����
 * @details
 * @param     point
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     convert a point in the origin image frame to the widget frame
 * @details   
 * @param     point
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::imageToWidget(QPointF& image_point)
{
    QPointF convert_factor;
    convert_factor.rx() = origin_image_.width() / (this->width() * zoom_ratio_);
    convert_factor.ry() = origin_image_.height() / (this->height() * zoom_ratio_);
    image_point.rx() = image_point.x() / convert_factor.x() - display_start_point_.x();
    image_point.ry() = image_point.y() / convert_factor.y() - display_start_point_.y();
}

/******************************************************************
 * @brief     ������ر�ROIѡ����
 * @details
 * @param     value
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     enable or disable roi selection
 * @details   
 * @param     value
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void RoiImageWidget::enableRoiSelection(bool value)
{
    is_selection_enabled_ = value;
}
