#include <gloperate-qtwidgets/ImageExporterWidget.h>

#include <gloperate/resources/ResourceManager.h>
#include <gloperate/painter/Painter.h>
#include <gloperate/tools/ImageExporter.h>

#include <gloperate-qt/QtOpenGLWindow.h>

#include <gloperate-qt/qt-includes-begin.h>
#include <gloperate-qt/qt-includes-end.h>

#include <gloperate-qtwidgets/ImageExporterOutputWidget.h>
#include <gloperate-qtwidgets/ImageExporterResolutionWidget.h>

namespace gloperate_qtwidgets
{

ImageExporterWidget::ImageExporterWidget(gloperate::ResourceManager & resourceManager, gloperate::Painter * painter, QWidget * parent)
:	DockableScrollAreaWidget(parent)
,	m_outputWidget(new ImageExporterOutputWidget(resourceManager, painter, this))
,	m_resolutionWidget(new ImageExporterResolutionWidget(this))
{
    connect(m_resolutionWidget.get(), &ImageExporterResolutionWidget::resolutionChanged,
            m_outputWidget.get(), &ImageExporterOutputWidget::updateResolution);

    addWidget(m_outputWidget.get());
    addWidget(m_resolutionWidget.get());
}

ImageExporterWidget::~ImageExporterWidget()
{
}

void ImageExporterWidget::initialize(gloperate_qt::QtOpenGLWindow * context)
{
    m_outputWidget->initialize(context);
}

} //namespace gloperate_qtwidgets
