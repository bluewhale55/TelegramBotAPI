#ifndef TELEGRAM_TYPES_INPUTMEDIADOCUMENT_H
#define TELEGRAM_TYPES_INPUTMEDIADOCUMENT_H

#include "MessageEntity.h"

#include <variant>

#include "qvector.h"

namespace Telegram
{
    /**
     *
     * @brief Represents a general file to be sent
     *
     */

    struct InputMediaDocument
    {
//** Constructors **//

        /** @brief Default constructor. Constructs an empty InputMediaDocument object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        InputMediaDocument();

        /** @brief Constructs InputMediaDocument object from parameters */
        InputMediaDocument(const std::variant<QFile*, QString>& media,
                           const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt,
                           const std::optional<QString>& caption = std::nullopt,
                           const std::optional<QString>& parse_mode = std::nullopt,
                           const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt,
                           const std::optional<bool>& disable_content_type_detection = std::nullopt);

        /** @brief JSON constructor. Constructs InputMediaDocument object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to InputMediaDocument class fields. For example it should contain pairs such as "type" = "...",
         * "media" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        InputMediaDocument(const QJsonObject& jsonObject);

        /* @brief Returns InputMediaDocument in form of JSON object. Returns empty QJsonObject if InputMediaDocument is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if InputMediaDocument is empty */
        bool isEmpty() const;

//** Fields **// 

        /** @brief Type of the result, must be document */
        const QString type = "document";

        /** @brief File to send
         *
         * Pass a file_id to send a file that exists on the Telegram servers, pass an HTTP URL for Telegram to get a file from the Internet, or pass QFile* to upload a new one */
        std::variant<QFile*, QString> media;

        /** @brief Optional. Thumbnail of the file sent
         *
         * Сan be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Thumbnails can't be reused with file_id and can be only uploaded as a new file via QFile* */
        std::optional<std::variant<QFile*, QString>> thumb;

        /** @brief Optional. Caption of the animation to be sent, 0-1024 characters after entities parsing */
        std::optional<QString> caption;

        /** @brief Optional. Mode for parsing entities in the animation caption. See formatting options for more details. */
        std::optional<QString> parse_mode;

        /** @brief Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode */
        std::optional<QVector<MessageEntity>> caption_entities;

        /** @brief Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data. Always true, if the document is sent as part of an album. */
        std::optional<bool> disable_content_type_detection;
    };
}

#endif // TELEGRAM_TYPES_INPUTMEDIADOCUMENT_H
