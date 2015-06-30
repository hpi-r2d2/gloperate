#pragma once

#include <string>

#include <gloperate-qt/qt-includes-begin.h>
#include <QWidget>
#include <QScopedPointer>
#include <QString>
#include <gloperate-qt/qt-includes-end.h>

#include <gloperate-qtwidgets/gloperate-qtwidgets_api.h>

class Ui_ImageExporterOutputWidget;
class QSize;

namespace gloperate
{

class ResourceManager;
class Painter;
class ImageExporter;

} // namespace gloperate

namespace gloperate_qt
{

class QtOpenGLWindow;

} // namespace gloperate_qt

namespace gloperate_qtwidgets
{

class GLOPERATE_QTWIDGETS_API ImageExporterOutputWidget : public QWidget
{
    Q_OBJECT

public:
    ImageExporterOutputWidget(gloperate::ResourceManager & resourceManager, gloperate::Painter * painter, QWidget * parent = nullptr);
    virtual ~ImageExporterOutputWidget();

    void initialize(gloperate_qt::QtOpenGLWindow * context);

    void updateResolution(const QSize & resolution);

protected:
    void handleSave(bool);

    void saveSettings();
    void restoreSettings();

    void browseDirectory(bool);
    void updateDirectory();
    std::string buildFileName();

protected:
    gloperate::ImageExporter * m_imageExporter;
    gloperate_qt::QtOpenGLWindow * m_context;

private:
    const QScopedPointer<Ui_ImageExporterOutputWidget> m_ui;
    QString m_dirName;
    QScopedPointer<QSize> m_resolution;

};

} //namespace gloperate_qtwidgets
