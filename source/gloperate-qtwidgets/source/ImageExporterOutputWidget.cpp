#include <gloperate-qtwidgets/ImageExporterOutputWidget.h>

#include <gloperate-qt/qt-includes-begin.h>
#include "ui_ImageExporterOutputWidget.h"
#include <QAbstractButton>
#include <QFile>
#include <QFileDialog>
#include <QSettings>
#include <QString>
#include <QWindow>
#include <gloperate-qt/qt-includes-end.h>

#include <gloperate/resources/ResourceManager.h>
#include <gloperate/painter/Painter.h>
#include <gloperate/tools/ImageExporter.h>

#include <gloperate-qt/QtOpenGLWindow.h>


namespace gloperate_qtwidgets
{

ImageExporterOutputWidget::ImageExporterOutputWidget(gloperate::ResourceManager & resourceManager, gloperate::Painter * painter, QWidget * parent)
:	QWidget(parent)
,	m_ui(new Ui_ImageExporterOutputWidget)
,	m_resolution(new QSize(1920, 1080))
{
    m_ui->setupUi(this);

    connect(m_ui->saveButton, &QPushButton::clicked,
        this, &ImageExporterOutputWidget::handleSave);
    connect(m_ui->openDirectoryButton, &QPushButton::clicked, 
        this, &ImageExporterOutputWidget::browseDirectory);
    
    m_imageExporter = new gloperate::ImageExporter(painter, resourceManager);

    if (!gloperate::ImageExporter::isApplicableTo(painter))
        m_ui->saveButton->setDisabled(true);

    restoreSettings();
}

ImageExporterOutputWidget::~ImageExporterOutputWidget()
{
}

void ImageExporterOutputWidget::initialize(gloperate_qt::QtOpenGLWindow * context)
{
    m_context = context;
    m_context->makeCurrent();
    m_imageExporter->initialize();
    m_context->doneCurrent();
}

void ImageExporterOutputWidget::updateResolution(const QSize & resolution)
{
    m_resolution->setHeight(resolution.height());
    m_resolution->setWidth(resolution.width());
}

void ImageExporterOutputWidget::handleSave(bool)
{
    m_context->makeCurrent();
    m_imageExporter->save(buildFileName(), std::max(1, m_resolution->width()), std::max(1, m_resolution->height()));
    m_context->doneCurrent();
}

void ImageExporterOutputWidget::saveSettings()
{
    QSettings settings;
    settings.beginGroup("ImageExporterOutputWidget");
    settings.setValue("filename", m_ui->fileNameLineEdit->text());
    settings.endGroup();
}

void ImageExporterOutputWidget::restoreSettings()
{
    QSettings settings;
    settings.beginGroup("ImageExporterOutputWidget");
    m_dirName = settings.value("dirname", QDir::homePath()).toString();
    m_ui->fileNameLineEdit->setText(settings.value("filename", "image").toString());
    settings.endGroup();
}

void ImageExporterOutputWidget::browseDirectory(bool)
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setDirectory(m_dirName);

    if (dialog.exec() && !dialog.selectedFiles().empty())
    {
        m_dirName = dialog.selectedFiles().first();
        updateDirectory();
    }
}

void ImageExporterOutputWidget::updateDirectory()
{
    m_ui->directoryLineEdit->setText(m_dirName);
    QSettings settings;
    settings.beginGroup("ImageExporterOutputWidget");
    settings.setValue("dirname", m_dirName);
    settings.endGroup();
}

std::string ImageExporterOutputWidget::buildFileName()
{
    std::string filename = m_ui->fileNameLineEdit->text().toStdString();
    const std::string sep("/");
    const std::string suf(".png");

    std::string final_filename = m_dirName.toStdString() + sep + filename + suf;

    int duplicate_count = 2;
    while (QFile::exists(QString::fromStdString(final_filename)))
        final_filename = m_dirName.toStdString() + sep + filename + " (" + std::to_string(duplicate_count++) + ")" + suf;

    return final_filename;
}

} //namespace gloperate_qtwidgets
