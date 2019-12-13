/**********************************************************************************
 * @class     ::ZoomImageLabel
 * @brief     A subclass of QLabel that supports to zoom in and out under the mouse position
              QLabel的子类，支持以鼠标位置为中心缩放图片
 * @version   1.1.1
 * @author    Qiao Tan
 * @date      2019/12/13
 *********************************************************************************/
#include <QPainter>
#include <QtGlobal>
#include <QDebug>
#include <QTimer>
#include "ZoomImageWidget.h"

/******************************************************************
 * @brief     
 * @details   
 * @param     parent
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
ZoomImageWidget::ZoomImageWidget(QWidget * parent /*= Q_NULLPTR*/) : QWidget(parent)
{
    QTimer* timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, [=] () {
        FPS_ = paint_count_ / 0.5f;
        IPS_ = image_count_ / 0.5F;
        paint_count_ = 0;
        image_count_ = 0;
    });
    timer->start();
}

/******************************************************************
 * @brief     
 * @details   
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
ZoomImageWidget::~ZoomImageWidget() 
{
}

/******************************************************************
 * @brief     设置需要显示的图片
 * @details
 * @param     image
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     set the image to be displayed
 * @details   
 * @param     image
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageWidget::setImage(const QImage& image)
{
    origin_image_ = image;
    ++image_count_; //统计图片设置次数，用于计算IPS
    is_image_setted_ = true;
    this->repaint();
}

/******************************************************************
 * @brief     获取控件显示帧率
 * @details   
 * @return    double
 * @author    Qiao Tan
 * @date      2019/12/12

 * @brief     get FPS of the widget
 * @details
 * @return    double
 * @author    Qiao Tan
 * @date      2019/12/12
 ******************************************************************/
double ZoomImageWidget::getFPS()
{
    return FPS_;
}

/******************************************************************
 * @brief     获取图片源帧率
 * @details   所谓的图片源帧率，是指单位时间内setImage()被调用了多少次，
即图片更新的频率
 * @return    double
 * @author    Qiao Tan
 * @date      2019/12/12

 * @brief     get IPS of the image source
 * @details   the so-called IPS means the times that setImage() has been
called during a unit of time, i.e. the image updating frequency
 * @return    double
 * @author    Qiao Tan
 * @date      2019/12/12
 ******************************************************************/
double ZoomImageWidget::getIPS()
{
    return IPS_;
}

/******************************************************************
 * @brief     更新is_mouse_pressed_及last_mouse_loc_
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     change is_mouse_pressed_ to true and update last_mouse_loc_
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageWidget::mousePressEvent(QMouseEvent *event) 
{
    if (event->button() == Qt::LeftButton)
    {
        is_mouse_pressed_ = true;
        last_mouse_loc_ = event->localPos();
    }
    QWidget::mousePressEvent(event);
}

/******************************************************************
 * @brief     更新display_start_point_，计算鼠标移动的位移，刷新图片显示
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     update display_start_point_, then update the displayed image
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageWidget::mouseMoveEvent(QMouseEvent *event) 
{
    if (is_mouse_pressed_)
    {
        current_mouse_loc_ = event->localPos();
        this->changeStartPoint(last_mouse_loc_ - current_mouse_loc_);
        this->repaint();
    }
    QWidget::mouseMoveEvent(event);
}

/******************************************************************
 * @brief     设置is_mouse_pressed_为false
 * @details
 * @param     evt
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     change is_mouse_pressed_ to false
 * @details   
 * @param     evt
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        is_mouse_pressed_ = false;
    }
    QWidget::mouseReleaseEvent(event);
}

/******************************************************************
 * @brief     调整缩放比例，并计算图片需要移动的距离，以保证鼠标位置就是
缩放的中心
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     change zoom_ratio_ and adjust display_start_point_ to make 
the mouse position is exactly the zoom center
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageWidget::wheelEvent(QWheelEvent *event) 
{
    if (is_image_setted_)
    {
        float wheel_degree = event->delta() * 1.0 / 640;
        if (zoom_ratio_ + wheel_degree > max_zoom_ratio_ || zoom_ratio_ + wheel_degree < min_zoom_ratio_)
        {
            return;
        }
        QPointF displacement = (event->posF() + display_start_point_) * (wheel_degree / zoom_ratio_);
        display_start_point_ += displacement;
        zoom_ratio_ += wheel_degree;
        this->repaint();
    }
    QWidget::wheelEvent(event);
}

/******************************************************************
 * @brief     控件尺寸发生变化时，调用showImage()重绘图片，以保证显示
图片的分辨率和控件尺寸匹配
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/19

 * @brief     repaint displayed image whenever the widget size is changed,
so that the image resolution could match the widget size
 * @details
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/19
 ******************************************************************/
void ZoomImageWidget::resizeEvent(QResizeEvent* event)
{
    this->repaint();
    QWidget::resizeEvent(event);
}

/******************************************************************
 * @brief     
 * @details   
 * @param     event
 * @return    void
 * @author    Qiao Tan
 * @date      2019/12/12
 ******************************************************************/
void ZoomImageWidget::paintEvent(QPaintEvent* event)
{
    if (!this->is_image_setted_)
    {
        return;
    }
    ++paint_count_; //统计paintEvent被调用次数，用于计算FPS
    int label_width = this->width();
    int label_height = this->height();
    this->adjustStartPoint(label_width, label_height);
    QPointF display_ratio(origin_image_.width() / (this->width() * zoom_ratio_), origin_image_.height() / (this->height() * zoom_ratio_));
    QRect display_area(display_start_point_.x() * display_ratio.x(), display_start_point_.y() * display_ratio.y(), 
        this->width() * display_ratio.x(), this->height() * display_ratio.y());
    QPainter painter(this);
    painter.drawImage(this->rect(), origin_image_, display_area);
}

/******************************************************************
 * @brief     根据传入的参数调整图片显示起点，即display_start_point_
 * @details
 * @param     displacement: display_start_point_需要叠加的二维矢量
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18

 * @brief     change display_start_point_ according to displacemnt
 * @details   
 * @param     displacement: the 2D-vector that display_start_point_ needs to add
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/18
 ******************************************************************/
void ZoomImageWidget::changeStartPoint(const QPointF displacement)
{
    if (displacement.manhattanLength() < 5)
    {
        return;
    }
    display_start_point_ += displacement;
    this->adjustStartPoint(this->width(), this->height());
    last_mouse_loc_ = current_mouse_loc_;
}

/******************************************************************
 * @brief     将display_start_point_的值限制到一个可行区间内
 * @details
 * @param     label_width
 * @param     label_height
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     limit the value of display_start_point_ to a viable interval
 * @details   
 * @param     label_width
 * @param     label_height
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageWidget::adjustStartPoint(int label_width, int label_height)
{
    display_start_point_.rx() = qMax(0.0, display_start_point_.x());
    display_start_point_.rx() = qMin(display_start_point_.x(), qreal(zoom_ratio_ * label_width - label_width));
    display_start_point_.ry() = qMax(0.0, display_start_point_.y());
    display_start_point_.ry() = qMin(display_start_point_.y(), qreal(zoom_ratio_ * label_height - label_height));
}
