#include "formatmanager.h"

#include <QStandardPaths>
#include <QFileInfo>

QTextCharFormat FormatManager::promptFormat()
{
    QTextCharFormat format;
    format.setForeground(this->promptColor);
    format.setFontWeight(QFont::Bold);
    return format;
}

QTextCharFormat FormatManager::errorFormat()
{
    QTextCharFormat format;
    format.setForeground(this->errorColor);
    format.setFontWeight(QFont::Bold);
    return format;
}

QTextCharFormat FormatManager::outputFormat()
{
    QTextCharFormat format;
    format.setForeground(this->outputColor);
    format.setFontWeight(QFont::Bold);
    return format;
}

QTextCharFormat FormatManager::inputFormat()
{
    QTextCharFormat format;
    format.setForeground(this->inputColor);
    format.setFontWeight(QFont::Bold);
    return format;
}

QTextCharFormat FormatManager::argumentFormat()
{
    QTextCharFormat format;
    format.setForeground(this->argumentColor);
    format.setFontItalic(true);
    return format;
}

void FormatManager::setPromptColor(const QColor &color) noexcept
{
    this->promptColor = color;
}

void FormatManager::setErrorColor(const QColor &color) noexcept
{
    this->errorColor = color;
}

void FormatManager::setOutputColor(const QColor &color) noexcept
{
    this->outputColor = color;
}

void FormatManager::setInputColor(const QColor &color) noexcept
{
    this->inputColor = color;
}

void FormatManager::setArgumentColor(const QColor &color) noexcept
{
    this->argumentColor = color;
}
