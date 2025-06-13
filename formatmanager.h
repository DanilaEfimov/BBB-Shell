#ifndef FORMATMANAGER_H
#define FORMATMANAGER_H

#include <QString>
#include <QTextCharFormat>
#include <QColor>

enum class TextType {
    Prompt,
    Error,
    Output,
    Input,
    Argument
};

class FormatManager
{
private:
    QColor promptColor =    QColor("#50fa7b");
    QColor errorColor =     QColor("#ff0000");
    QColor outputColor =    QColor("#ffffff");
    QColor inputColor =     QColor(Qt::yellow);
    QColor argumentColor =  QColor(Qt::gray);

public:
    FormatManager() = default;

    QTextCharFormat promptFormat();
    QTextCharFormat errorFormat();
    QTextCharFormat outputFormat();
    QTextCharFormat inputFormat();
    QTextCharFormat argumentFormat();

    void setPromptColor(const QColor& color) noexcept;
    void setErrorColor(const QColor& color) noexcept;
    void setOutputColor(const QColor& color) noexcept;
    void setInputColor(const QColor& color) noexcept;
    void setArgumentColor(const QColor& color) noexcept;
};

#endif // FORMATMANAGER_H
