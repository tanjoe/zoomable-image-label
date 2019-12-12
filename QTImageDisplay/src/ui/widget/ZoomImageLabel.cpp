/**********************************************************************************
 * @class     ::ZoomImageLabel
 * @brief     A subclass of QLabel that supports to zoom in and out under the mouse position
              QLabel的子类，支持以鼠标位置为中心缩放图片
 * @version   1.0.1
 * @author    Qiao Tan
 * @date      2019/11/19
 *********************************************************************************/
#include "ZoomImageLabel.h"

/******************************************************************
 * @brief     
 * @details   
 * @param     parent
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
ZoomImageLabel::ZoomImageLabel(QWidget * parent /*= Q_NULLPTR*/) : QLabel(parent)
{
}

/******************************************************************
 * @brief     
 * @details   
 * @return    
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
ZoomImageLabel::~ZoomImageLabel() 
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
void ZoomImageLabel::setImage(const QImage& image)
{
    origin_image_ = image;
    is_image_setted_ = true;
    this->showImage();
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
void ZoomImageLabel::mousePressEvent(QMouseEvent *event) 
{
    if (event->button() == Qt::LeftButton)
    {
        is_mouse_pressed_ = true;
        last_mouse_loc_ = event->localPos();
    }
    QLabel::mousePressEvent(event);
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
void ZoomImageLabel::mouseMoveEvent(QMouseEvent *event) 
{
    if (is_mouse_pressed_)
    {
        current_mouse_loc_ = event->localPos();
        this->changeStartPoint(last_mouse_loc_ - current_mouse_loc_);
        this->showImage();
    }
    QLabel::mouseMoveEvent(event);
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
void ZoomImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        is_mouse_pressed_ = false;
    }
    QLabel::mouseReleaseEvent(event);
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
void ZoomImageLabel::wheelEvent(QWheelEvent *event) 
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
        this->showImage();
    }
    QLabel::wheelEvent(event);
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
void ZoomImageLabel::resizeEvent(QResizeEvent* event)
{
    this->showImage();
    QLabel::resizeEvent(event);
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
void ZoomImageLabel::changeStartPoint(const QPointF displacement)
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
void ZoomImageLabel::adjustStartPoint(int label_width, int label_height)
{
    display_start_point_.rx() = qMax(0.0, display_start_point_.x());
    display_start_point_.rx() = qMin(display_start_point_.x(), qreal(zoom_ratio_ * label_width - label_width));
    display_start_point_.ry() = qMax(0.0, display_start_point_.y());
    display_start_point_.ry() = qMin(display_start_point_.y(), qreal(zoom_ratio_ * label_height - label_height));
}

/******************************************************************
 * @brief     根据zoom_ratio_和display_start_point_计算显示区域并显示图片
 * @details
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15

 * @brief     display image according to the zoom_ratio_ and display_start_point_
 * @details
 * @return    void
 * @author    Qiao Tan
 * @date      2019/11/15
 ******************************************************************/
void ZoomImageLabel::showImage()
{
    if (!this->is_image_setted_)
    {
        return;
    }
    int label_width = this->width();
    int label_height = this->height();
    this->adjustStartPoint(label_width, label_height);
    QSize display_size(label_width * zoom_ratio_, label_height * zoom_ratio_);
    QRect display_area(display_start_point_.x(), display_start_point_.y(), label_width, label_height);
    QImage display_image = origin_image_.scaled(display_size).copy(display_area);
    this->setPixmap(QPixmap::fromImage(display_image));
}
