#pragma once

#include <memory>

#include <gloperate-qt/qt-includes-begin.h>
#include <QWidget>
#include <gloperate-qt/qt-includes-end.h>

#include <gloperate-qtwidgets/gloperate-qtwidgets_api.h>

#include <widgetzeug/DockableScrollAreaWidget.h>

namespace gloperate
{

class ResourceManager;
class Painter;

}

namespace gloperate_qt
{

class QtOpenGLWindow;

}

namespace gloperate_qtwidgets
{

class ImageExporterOutputWidget;
class ImageExporterResolutionWidget;

class GLOPERATE_QTWIDGETS_API ImageExporterWidget : public widgetzeug::DockableScrollAreaWidget
{
    Q_OBJECT

public:
    ImageExporterWidget(gloperate::ResourceManager & resourceManager, gloperate::Painter * painter, QWidget * parent = nullptr);
    virtual ~ImageExporterWidget();

    void initialize(gloperate_qt::QtOpenGLWindow * context);

private:
    std::unique_ptr<ImageExporterOutputWidget> m_outputWidget;
    std::unique_ptr<ImageExporterResolutionWidget> m_resolutionWidget;
};

} //namespace gloperate_qtwidgets
