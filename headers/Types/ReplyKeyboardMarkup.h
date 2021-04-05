#ifndef REPLYKEYBOARDMARKUP_H
#define REPLYKEYBOARDMARKUP_H

#include "Type.h"
#include "KeyboardButton.h"

class TELEGRAMAPI_EXPORT ReplyKeyboardMarkup : public Type
{
public:
    ReplyKeyboardMarkup();

    ReplyKeyboardMarkup(QVector<QVector<KeyboardButton>> keyboard);

    ReplyKeyboardMarkup(QJsonObject jsonObject);

    QVector<QVector<KeyboardButton>> keyboard();
    void                             setKeyboard(QVector<QVector<KeyboardButton>> keyboard);

    bool    resizeKeyboard();
    void    setResizeKeyboard(bool resizeKeyboard);
    bool    hasResizeKeyboard();

    bool    oneTimeKeyboard();
    void    setOneTimeKeyboard(bool oneTimeKeyboard);
    bool    hasOneTimeKeyboard();

    bool    selective();
    void    setSelective(bool selective);
    bool    hasSelective();
};

#endif // REPLYKEYBOARDMARKUP_H