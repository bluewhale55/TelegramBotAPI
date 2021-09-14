﻿#ifndef TELEGRAM_BOT_H
#define TELEGRAM_BOT_H

#include "WebhookManager.h"
#include "RequestManager.h"
#include "Types/Error.h"
#include "Types/InlineKeyboardMarkup.h"
#include "Types/ReplyKeyboardMarkup.h"
#include "Types/ReplyKeyboardRemove.h"
#include "Types/ForceReply.h"
#include "Types/MessageId.h"
#include "Types/InputMediaAudio.h"
#include "Types/InputMediaDocument.h"
#include "Types/InputMediaPhoto.h"
#include "Types/InputMediaVideo.h"
#include "Types/UserProfilePhotos.h"
#include "Types/File.h"
#include "Types/ChatPermissions.h"
#include "Types/BotCommand.h"
#include "Types/BotCommandScopeAllChatAdministrators.h"
#include "Types/BotCommandScopeAllGroupChats.h"
#include "Types/BotCommandScopeAllPrivateChats.h"
#include "Types/BotCommandScopeChat.h"
#include "Types/BotCommandScopeChatAdministrators.h"
#include "Types/BotCommandScopeChatMember.h"
#include "Types/BotCommandScopeDefault.h"

class QFile;
#include "qstring.h"

#include <variant>

/* Your bot token provided by Telegram BotFather (@BotFather) */
#define BOT_TOKEN "1871273454:AAFpFGujteQPDuMoivE7VFpmMmZU9LUT9H0"

/* Your payment token provided by Telegram BotFather (@BotFather) */
#define PAYMENT_TOKEN "EXAMPLE"

namespace Telegram 
{
    class Bot : public QObject
    {
        Q_OBJECT

    public:
        Bot();

    signals:
        void messageReceived(qint32 update_id, Message message);
        void messageWasUpdated(qint32 update_id, Message message);

        void channelPostReceived(qint32 update_id, Message message);
        void channelPostWasUpdated(qint32 update_id, Message message);

        //void inlineQueryReceived(qint32 update_id, InlineQuery message);

        //void chosenInlineResult(qint32 update_id, ChosenInlineResult message);

        void callbackQueryReceived(qint32 update_id, CallbackQuery message);

        //void shippingQueryReceived(qint32 update_id, ShippingQuery message);

        //void preCheckoutQueryReceived(qint32 update_id, PreCheckoutQuery message);

        void pollReceived(qint32 update_id, Poll message);
        void pollAnswerReceived(qint32 update_id, PollAnswer message);

        void myChatMemberStatusUpdated(qint32 update_id, ChatMemberUpdated message);
        void chatMemberStatusUpdated(qint32 update_id, ChatMemberUpdated message);

        void errorOccured(Error error);

    public:
        /** @brief A simple method for testing your bot's auth token. Requires no parameters. Returns basic information about the bot in form of a User object */
        User getMe();

        /** @brief Use this method to log out from the cloud Bot API server before launching the bot locally. Returns True on success
         * 
         * You must log out the bot before running it locally, otherwise there is no guarantee that the bot will receive updates. After a successful call, you can immediately log in on a local server,
         * but will not be able to log in back to the cloud Bot API server for 10 minutes */
        bool logOut();

        /** @brief Use this method to close the bot instance before moving it from one local server to another. Returns True on success
         *
         * You need to delete the webhook before calling this method to ensure that the bot isn't launched again after server restart. The method will return error 429 in the first 10 minutes after the bot is launched */
        bool close();

        /** @brief Use this methods to send text messages. On success, the sent Message is returned
		 *
		 * @param qint32 or QString	                                                                    Unique identifier for the target chat or username of the target channel(in the format @channelusername)
		 * @param QString	                                                                            Text of the message to be sent, 1 - 4096 characters after entities parsing
		 * @param QString	                                                                            Optional. Mode for parsing entities in the message text. See formatting options for more details
		 * @param QVector of MessageEntity	                                                            Optional. List of special entities that appear in message text, which can be specified instead of parse_mode
		 * @param bool             	                                                        	        Optional. Disables link previews for links in this message
		 * @param bool	                                                                                Optional. Sends the message silently. Users will receive a notification with no sound
		 * @param qint32	                                                                            Optional. If the message is a reply, ID of the original message
		 * @param bool	                                                                                Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
		 * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply      Optional. Additional interface options.A JSON - serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        Message sendMessage(const std::variant<qint32, QString>& chat_id, const QString& text, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& entities = std::nullopt, const std::optional<bool>& disable_web_page_preview = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>> reply_markup = std::nullopt);

        /** @brief Use this method to forward messages of any kind. Service messages can't be forwarded. On success, the sent Message is returned
         * 
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32 or QString	    Unique identifier for the chat where the original message was sent (or channel username in the format @channelusername)
         * @param qint32                Message identifier in the chat specified in from_chat_id
         * @param bool                  Optional. Sends the message silently. Users will receive a notification with no sound */
        Message forwardMessage(const std::variant<qint32, QString>& chat_id, const std::variant<qint32, QString>& from_chat_id, const qint32& message_id, const std::optional<bool>& disable_notification = std::nullopt);

        /** @brief Use this method to copy messages of any kind. Service messages and invoice messages can't be copied. Returns the MessageId of the sent message on success
         *      
         * This method is analogous to the method forwardMessage, but the copied message doesn't have a link to the original message
         * 
         * @param qint32 or QString	                                                                    Unique identifier for the target chat or username of the target channel(in the format @channelusername)
         * @param qint32 or QString	                                                                    Unique identifier for the chat where the original message was sent(or channel username in the format @channelusername)
         * @param qint32	                                                                            Message identifier in the chat specified in from_chat_id
         * @param QString	                                                                            Optional. New caption for media, 0 - 1024 characters after entities parsing.If not specified, the original caption is kept
         * @param QString	                                                                            Optional. Mode for parsing entities in the new caption.See formatting options for more details
         * @param QVector of MessageEntity	                                                            Optional. List of special entities that appear in the new caption, which can be specified instead of parse_mode
         * @param bool	                                                                                Optional. Sends the message silently.Users will receive a notification with no sound
         * @param qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                                Optional. Pass True, if the message should be sent even if the specified replied - to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	    Optional. Additional interface options. A JSON - serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        MessageId copyMessage(const std::variant<qint32, QString>& chat_id, const std::variant<qint32, QString>& from_chat_id, const qint32& message_id, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to send photos. On success, the sent Message is returned
         *
         * @param qint32 or QString	                                                                    Unique identifier for the target chat or username of the target channel(in the format @channelusername)
         * @param QFile* or QString	                                                                    Photo to send. Pass a file_id as QString to send a photo that exists on the Telegram servers(recommended), pass an HTTP URL as a QString for Telegram to get a photo from the Internet, or upload a new photo using QFile(should be opened). The photo must be at most 10 MB in size.The photo's width and height must not exceed 10000 in total. Width and height ratio must be at most 20
         * @param QString	                                                                            Optional. Photo caption(may also be used when resending photos by file_id), 0-1024 characters after entities parsing
         * @param QString	                                                                            Optional. Mode for parsing entities in the photo caption. See formatting options for more details.
         * @param QVector of MessageEntity	                                                            Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param bool	                                                                                Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                            Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                                Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	    Optional. Additional interface options.A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.*/
        Message sendPhoto(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& photo, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to send audio files, if you want Telegram clients to display them in the music player
         * 
         * Your audio must be in the .MP3 or .M4A format. On success, the sent Message is returned. Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future.
         * For sending voice messages, use the sendVoice method instead
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile* or QString	                                                                Audio file to send. Pass a file_id as String to send an audio file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an audio file from the Internet, or upload a new photo using QFile(should be opened)
         * @param QString	                                                                        Optional. Audio caption, 0-1024 characters after entities parsing
         * @param QString	                                                                        Optional. Mode for parsing entities in the audio caption. See formatting options for more details.
         * @param QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param qint32	                                                                        Optional. Duration of the audio in seconds
         * @param QString	                                                                        Optional. Performer
         * @param QString	                                                                        Optional. Track name
         * @param QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile* to upload new one
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendAudio(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& audio, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<qint32>& duration = std::nullopt, const std::optional<QString>& performer = std::nullopt, const std::optional<QString>& title = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
    
        /** @brief Use this method to send general files. On success, the sent Message is returned
         * 
         * Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile* or QString	                                                                File to send. Pass a file_id as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new photo using QFile(should be opened)
         * @param QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile* to upload new one
         * @param QString	                                                                        Optional. Document caption (may also be used when resending documents by file_id), 0-1024 characters after entities parsing
         * @param QString	                                                                        Optional. Mode for parsing entities in the document caption. See formatting options for more details.
         * @param QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param bool	                                                                            Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        Message sendDocument(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& document, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_content_type_detection = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to send video files, Telegram clients support mp4 videos (other formats may be sent as Document). On success, the sent Message is returned
         *
         *  Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
         * 
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile* or QString	                                                                Video to send. Pass a file_id as String to send a video that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a video from the Internet, or upload a new photo using QFile(should be opened)
         * @param qint32	                                                                        Optional. Duration of sent video in seconds
         * @param qint32	                                                                        Optional. Video width
         * @param qint32	                                                                        Optional. Video height
         * @param QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile* to upload new one
         * @param QString	                                                                        Optional. Video caption (may also be used when resending videos by file_id), 0-1024 characters after entities parsing
         * @param QString	                                                                        Optional. Mode for parsing entities in the video caption. See formatting options for more details.
         * @param QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param bool	                                                                            Optional. Pass True, if the uploaded video is suitable for streaming
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user. */
        Message sendVideo(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& video, const std::optional<qint32>& duration = std::nullopt, const std::optional<qint32>& width = std::nullopt, const std::optional<qint32>& height = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& supports_streaming = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound). On success, the sent Message is returned
         *
         * Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future
         * 
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile* or QString	                                                                Animation to send. Pass a file_id as String to send an animation that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get an animation from the Internet, or upload a new photo using QFile(should be opened)
         * @param qint32	                                                                        Optional. Duration of sent animation in seconds
         * @param qint32	                                                                        Optional. Animation width
         * @param qint32	                                                                        Optional. Animation height
         * @param QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile* to upload new one
         * @param QString	                                                                        Optional. Animation caption (may also be used when resending animation by file_id), 0-1024 characters after entities parsing
         * @param QString	                                                                        Optional. Mode for parsing entities in the animation caption. See formatting options for more details
         * @param QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendAnimation(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& animation, const std::optional<qint32>& duration = std::nullopt, const std::optional<qint32>& width = std::nullopt, const std::optional<qint32>& height = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message. On success, the sent Message is returned
         *
         * For this to work, your audio must be in an .OGG file encoded with OPUS (other formats may be sent as Audio or Document). Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future
         * 
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile* or QString	                                                                Audio file to send. Pass a file_id as String to send a file that exists on the Telegram servers (recommended), pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new photo using QFile(should be opened)
         * @param QString	                                                                        Optional. Voice message caption, 0-1024 characters after entities parsing
         * @param QString	                                                                        Optional. Mode for parsing entities in the voice message caption. See formatting options for more details.
         * @param QVector of MessageEntity	                                                        Optional. List of special entities that appear in the caption, which can be specified instead of parse_mode
         * @param qint32	                                                                        Optional. Duration of the voice message in seconds
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendVoice(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& voice, const std::optional<QString>& caption = std::nullopt, const std::optional<QString>& parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& caption_entities = std::nullopt, const std::optional<qint32>& duration = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        

        /** @brief Use this method to send video messages. As of v.4.0, Telegram clients support rounded square mp4 videos of up to 1 minute long. On success, the sent Message is returned.
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile* or QString	                                                                Video note to send. Pass a file_id as String to send a video note that exists on the Telegram servers (recommended) or upload a new photo using QFile(should be opened). Sending video notes by a URL is currently unsupported
         * @param qint32	                                                                        Optional. Duration of sent video in seconds
         * @param qint32	                                                                        Optional. Video width and height, i.e. diameter of the video message
         * @param QFile* or QString	                                                                Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side. The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320. Ignored if the file is not uploaded using QFile*. Thumbnails can't be reused and can be only uploaded as a new file, so you can pass QFile* to upload new one
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendVideoNote(const std::variant<qint32, QString>& chat_id, const std::variant<QFile*, QString>& video_note, const std::optional<qint32>& duration = std::nullopt, const std::optional<qint32>& length = std::nullopt, const std::optional<std::variant<QFile*, QString>>& thumb = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        
        /** @brief Use this method to send a group of audios as an album. On success, an array of Messages that were sent is returned.
         *
         * @param qint32 or QString	                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QVector of InputMediaAudio        Vector of InputMediaAudio describing bunch of audios to be sent, must include 2-10 items
         * @param bool	                            Optional. Sends messages silently. Users will receive a notification with no sound.
         * @param qint32	                        Optional. If the messages are a reply, ID of the original message
         * @param bool	                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found */
        QVector<Message> sendMediaGroup(const std::variant<qint32, QString>& chat_id, const QVector<InputMediaAudio>& media, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt);

        /** @brief Use this method to send a group of documents as an album. On success, an array of Messages that were sent is returned.
         *
         * @param qint32 or QString	                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QVector of InputMediaDocument     Vector of InputMediaDocument describing bunch of documents to be sent, must include 2-10 items
         * @param bool	                            Optional. Sends messages silently. Users will receive a notification with no sound.
         * @param qint32	                        Optional. If the messages are a reply, ID of the original message
         * @param bool	                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found */
        QVector<Message> sendMediaGroup(const std::variant<qint32, QString>& chat_id, const QVector<InputMediaDocument>& media, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt);

        /** @brief Use this method to send a group of photos and videos as an album. On success, an array of Messages that were sent is returned
         *
         * @param qint32 or QString	                                                    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QVector of InputMediaPhoto and QVector of InputMediaVideo             Vectors of InputMediaPhoto and InputMediaVideo describing bunch of photos and videos to be sent, must include 2-10 items
         * @param bool	                                                                Optional. Sends messages silently. Users will receive a notification with no sound.
         * @param qint32	                                                            Optional. If the messages are a reply, ID of the original message
         * @param bool	                                                                Optional. Pass True, if the message should be sent even if the specified replied-to message is not found */
        QVector<Message> sendMediaGroup(const std::variant<qint32, QString>& chat_id, const QPair<QVector<InputMediaPhoto>, QVector<InputMediaVideo>> media, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt);

        /** @brief Use this method to send point on the map. On success, the sent Message is returned
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param float	                                                                            Latitude of the location
         * @param float	                                                                            Longitude of the location
         * @param float	                                                                            Optional. The radius of uncertainty for the location, measured in meters; 0-1500
         * @param qint32	                                                                        Optional. Period in seconds for which the location will be updated (see Live Locations, should be between 60 and 86400
         * @param qint32	                                                                        Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified
         * @param qint32	                                                                        Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendLocation(const std::variant<qint32, QString>& chat_id, const float& latitude, const float& longitude, const std::optional<float>& horizontal_accuracy = std::nullopt, const std::optional<qint32>& live_period = std::nullopt, const std::optional<qint32>& heading = std::nullopt, const std::optional<qint32>& proximity_alert_radius = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to edit live location messages. On success, if the edited message is not an inline message, the edited Message is returned, otherwise empty Message is returned
         *
         * A location can be edited until its live_period expires or editing is explicitly disabled by a call to stopMessageLiveLocation
         * 
         * @param float	                Latitude of new location
         * @param float	                Longitude of new location
         * @param qint32 or QString     Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32	            Optional. Required if inline_message_id is not specified. Identifier of the message to edit
         * @param QString	            Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param float	                Optional. The radius of uncertainty for the location, measured in meters; 0-1500
         * @param qint32	            Optional. Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified
         * @param qint32	            Optional. Maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified
         * @param InlineKeyboardMarkup	Optional. A JSON-serialized object for a new inline keyboard */
        Message editMessageLiveLocation(const float& latitude, const float& longitude, const std::optional<std::variant<qint32, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<float>& horizontal_accuracy = std::nullopt, const std::optional<qint32>& heading = std::nullopt, const std::optional<qint32>& proximity_alert_radius = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);

        /** @brief Use this method to stop updating a live location message before live_period expires. On success, if the message is not an inline message, the edited Message is returned, otherwise empty Message is returned.
         *
         * @param qint32 or QString	    Optional. Required if inline_message_id is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32	            Optional. Required if inline_message_id is not specified. Identifier of the message with live location to stop
         * @param QString	            Optional. Required if chat_id and message_id are not specified. Identifier of the inline message
         * @param InlineKeyboardMarkup	Optional. A JSON-serialized object for a new inline keyboard */
        Message stopMessageLiveLocation(const std::optional<std::variant<qint32, QString>>& chat_id = std::nullopt, const std::optional<qint32>& message_id = std::nullopt, const std::optional<QString>& inline_message_id = std::nullopt, const std::optional<InlineKeyboardMarkup>& reply_markup = std::nullopt);

        /** @brief Use this method to send information about a venue. On success, the sent Message is returned.
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param float	                                                                            Latitude of the venue
         * @param float	                                                                            Longitude of the venue
         * @param QString	                                                                        Name of the venue
         * @param QString	                                                                        Address of the venue
         * @param QString	                                                                        Optional. Foursquare identifier of the venue
         * @param QString	                                                                        Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
         * @param QString	                                                                        Optional. Google Places identifier of the venue
         * @param QString	                                                                        Optional. Google Places type of the venue. (See supported types.)
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendVenue(const std::variant<qint32, QString>& chat_id, const float& latitude, const float& longitude, const QString& title, const QString& address, const std::optional<QString>& foursquare_id = std::nullopt, const std::optional<QString>& foursquare_type = std::nullopt, const std::optional<QString>& google_place_id = std::nullopt, const std::optional<QString>& google_place_type = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Use this method to send phone contacts. On success, the sent Message is returned.
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString	                                                                        Contact's phone number
         * @param QString	                                                                        Contact's first name
         * @param QString	                                                                        Optional. Contact's last name
         * @param QString	                                                                        Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove keyboard or to force a reply from the user */
        Message sendContact(const std::variant<qint32, QString>& chat_id, const QString& phone_number, const QString& first_name, const std::optional<QString>& last_name = std::nullopt, const std::optional<QString>& vcard = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        
        /** @brief Use this method to send a native poll. On success, the sent Message is returned.
         *
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString	                                                                        Poll question, 1-300 characters
         * @param QVector of QString	                                                            A JSON-serialized list of answer options, 2-10 strings 1-100 characters each
         * @param bool	                                                                            Optional. True, if the poll needs to be anonymous, defaults to True
         * @param QString	                                                                        Optional. Poll type, “quiz” or “regular”, defaults to “regular”
         * @param bool	                                                                            Optional. True, if the poll allows multiple answers, ignored for polls in quiz mode, defaults to False
         * @param qint32	                                                                        Optional. 0-based identifier of the correct answer option, required for polls in quiz mode
         * @param QString	                                                                        Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters with at most 2 line feeds after entities parsing
         * @param QString	                                                                        Optional. Mode for parsing entities in the explanation. See formatting options for more details
         * @param QVector of MessageEntity	                                                        Optional. List of special entities that appear in the poll explanation, which can be specified instead of parse_mode
         * @param qint32	                                                                        Optional. Amount of time in seconds the poll will be active after creation, 5-600. Can't be used together with close_date
         * @param qint32	                                                                        Optional. Point in time (Unix timestamp) when the poll will be automatically closed. Must be at least 5 and no more than 600 seconds in the future. Can't be used together with open_period
         * @param bool	                                                                            Optional. Pass True, if the poll needs to be immediately closed. This can be useful for poll preview.
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound.
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param Boolean	                                                                        Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendPoll(const std::variant<qint32, QString>& chat_id, const QString& question, const QVector<QString>& options, const std::optional<bool>& is_anonymous = std::nullopt, const std::optional<QString>& type = std::nullopt, const std::optional<bool>& allows_multiple_answers = std::nullopt, const std::optional<qint32>& correct_option_id = std::nullopt, const std::optional<QString>& explanation = std::nullopt, const std::optional<QString>& explanation_parse_mode = std::nullopt, const std::optional<QVector<MessageEntity>>& explanation_entities = std::nullopt, const std::optional<qint32>& open_period = std::nullopt, const std::optional<qint32>& close_date = std::nullopt, const std::optional<bool>& is_closed = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);
        
        /** @brief Use this method to send an animated emoji that will display a random value. On success, the sent Message is returned
         * 
         * @param qint32 or QString	                                                                Unique identifier for the target chat or username of the target channel (in the format @channelusername) 
         * @param QString	                                                                        Optional. Emoji on which the dice throw animation is based. Currently, must be one of “🎲”, “🎯”, “🏀”, “⚽”, “🎳”, or “🎰”. Dice can have values 1-6 for “🎲”, “🎯” and “🎳”, values 1-5 for “🏀” and “⚽”, and values 1-64 for “🎰”. Defaults to “🎲”
         * @param bool	                                                                            Optional. Sends the message silently. Users will receive a notification with no sound
         * @param qint32	                                                                        Optional. If the message is a reply, ID of the original message
         * @param bool	                                                                            Optional. Pass True, if the message should be sent even if the specified replied-to message is not found
         * @param InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply	Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user */
        Message sendDice(const std::variant<qint32, QString>& chat_id, const std::optional<QString>& emoji = std::nullopt, const std::optional<bool>& disable_notification = std::nullopt, const std::optional<qint32>& reply_to_message_id = std::nullopt, const std::optional<bool>& allow_sending_without_reply = std::nullopt, const std::optional<std::variant<InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove, ForceReply>>& reply_markup = std::nullopt);

        /** @brief Enum that represents all available types of chat action that is written near bot's nickname */
        enum class ChatActionType
        {
            TYPING, //  ex. For text messages[sendMessage()]
            UPLOAD_PHOTO, // ex. For photos[sendPhoto()]
            RECORD_VIDEO, // ex. For videos[sendVideo()]
            UPLOAD_VIDEO, // ex. For videos[sendVideo()]
            RECORD_VOICE, // ex. For voice notes[sendVoice()]
            UPLOAD_VOICE, // ex. For voice notes[sendVoice()]
            UPLOAD_DOCUMENT, // ex. For general files[sendDocument()]
            FIND_LOCATION, // ex. For location data[sendLocation()]
            RECORD_VIDEO_NOTE, // ex. For video note[sendVideoNote]
            UPLOAD_VIDEO_NOTE  // ex. For video note[sendVideoNote]
        };

        /** @brief Use this method when you need to tell the user that something is happening on the bot's side. The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status). Returns True on success.
         *
         * > Example: The ImageBot needs some time to process a request and upload the image. Instead of sending a text message along the lines of “Retrieving image, please wait…”, the bot may use
         * > sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
         * 
         *  We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
         * 
         * @param qint32 or QString Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString	        Type of action to broadcast */
        bool sendChatAction(const std::variant<qint32, QString>& chat_id, const ChatActionType& action);

        /** @brief Use this method to get a list of profile pictures for a user. Returns an empty UserProfilePhotos object if error eccured.
         *
         * @param qint32 Unique identifier of the target user
         * @param qint32 Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
         * @param qint32 Optional. Limits the number of photos to be retrieved. Values between 1-100 are accepted. Defaults to 100 */
        UserProfilePhotos getUserProfilePhotos(const qint32& user_id, const std::optional<qint32>& offset = std::nullopt, const std::optional<qint32>& limit = std::nullopt);

        /** @brief Use this method to get basic info about a file and prepare it for downloading. Returns an empty File object if error eccured.
         *
         * For the moment, bots can download files of up to 20MB in size. The file can then be downloaded via the link https://api.telegram.org/file/bot<token>/<file_path>, where <file_path> is taken
         * from the response. It is guaranteed that the link will be valid for at least 1 hour. When the link expires, a new one can be requested by calling getFile() again.
         * 
         * > Note: This function may not preserve the original file name and MIME type. You should save the file's MIME type and name (if available) when the File object is received.
         * 
         * @param QString File identifier to get info about
         */
        File getFile(const QString& file_id);

        /** @brief Use this method to ban a user in a group, a supergroup or a channel. In the case of supergroups and channels, the user will not be able to return to the chat on their own using invite links, etc., unless unbanned first.
         *         The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. Returns True on success.
         *
         * @param qint32 or QString	Unique identifier for the target group or username of the target supergroup or channel (in the format @channelusername)
         * @param qint32	        Unique identifier of the target user
         * @param qint32	        Optional. Date when the user will be unbanned, unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever. Applied for supergroups and channels only
         * @param bool	            Optional. Pass True to delete all messages from the chat for the user that is being removed. If False, the user will be able to see messages in the group that were sent before the user was removed. Always True for supergroups and channels */
        bool banChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const std::optional<qint32>& until_date = std::nullopt, const std::optional<bool>& revoke_messages = std::nullopt);
        
        /** @brief Use this method to unban a previously banned user in a supergroup or channel. Returns True on success.
         *
         *  The user will not return to the group or channel automatically, but will be able to join via link, etc. The bot must be an administrator for this to work. By default, this method
         *  guarantees that after the call the user is not a member of the chat, but will be able to join it. So if the user is a member of the chat they will also be removed from the chat. If you don't want
         *  this, use the parameter only_if_banned
         * 
         * @param qint32 or QString	Unique identifier for the target group or username of the target supergroup or channel (in the format @username)
         * @param qint32	        Unique identifier of the target user
         * @param bool	            Optional. Do nothing if the user is not banned */
        bool unbanChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const std::optional<bool>& only_if_banned = std::nullopt);

        /** @brief Use this method to restrict a user in a supergroup. The bot must be an administrator in the supergroup for this to work and must have the appropriate admin rights.
         *         Pass True for all permissions to lift restrictions from a user. Returns True on success.
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
         * @param qint32	            Unique identifier of the target user
         * @param ChatPermissions	    A JSON-serialized object for new user permissions
         * @param qint32	            Optional. Date when restrictions will be lifted for the user, unix time. If user is restricted for more than 366 days or less than 30 seconds from the current time, they are considered to be restricted forever */
        bool restrictChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const ChatPermissions& permissions, const std::optional<qint32>& until_date = std::nullopt);
        
        /* @brief Use this method to promote or demote a user in a supergroup or a channel. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. 
         *        Pass False for all boolean parameters to demote a user. Returns True on success.
         *
         * @param qint32 or QString	Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32	        Unique identifier of the target user
         * @param bool	            Optional. Pass True, if the administrator's presence in the chat is hidden
         * @param bool	            Optional. Pass True, if the administrator can access the chat event log, chat statistics, message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode. Implied by any other administrator privilege
         * @param bool	            Optional. Pass True, if the administrator can create channel posts, channels only
         * @param bool	            Optional. Pass True, if the administrator can edit messages of other users and can pin messages, channels only
         * @param bool	            Optional. Pass True, if the administrator can delete messages of other users
         * @param bool	            Optional. Pass True, if the administrator can manage voice chats
         * @param bool	            Optional. Pass True, if the administrator can restrict, ban or unban chat members
         * @param bool	            Optional. Pass True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that he has promoted, directly or indirectly (promoted by administrators that were appointed by him)
         * @param bool	            Optional. Pass True, if the administrator can change chat title, photo and other settings
         * @param bool	            Optional. Pass True, if the administrator can invite new users to the chat
         * @param bool	            Optional. Pass True, if the administrator can pin messages, supergroups only */
        bool promoteChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const std::optional<bool>& is_anonymous = std::nullopt, const std::optional<bool>& can_manage_chat = std::nullopt, const std::optional<bool>& can_post_messages = std::nullopt, const std::optional<bool>& can_edit_messages = std::nullopt, const std::optional<bool>& can_delete_messages = std::nullopt, const std::optional<bool>& can_manage_voice_chats = std::nullopt, const std::optional<bool>& can_restrict_members = std::nullopt, const std::optional<bool>& can_promote_members = std::nullopt, const std::optional<bool>& can_change_info = std::nullopt, const std::optional<bool>& can_invite_users = std::nullopt, const std::optional<bool>& can_pin_messages = std::nullopt);
        
        /* @brief Use this method to set a custom title for an administrator in a supergroup promoted by the bot. Returns True on success.
         *
         * @param qint32 or QString Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
         * @param qint32	        Unique identifier of the target user
         * @param QString	        New custom title for the administrator; 0-16 characters, emoji are not allowed */
        bool setChatAdministratorCustomTitle(const std::variant<qint32, QString>& chat_id, const qint32& user_id, const QString& custom_title);
        
        /* @brief Use this method to set default chat permissions for all members. The bot must be an administrator in the group or a supergroup for this to work and must have the can_restrict_members admin rights. Returns True on success.
         *
         * @param qint32 or QString Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
         * @param ChatPermission    New default chat permissions */
        bool setChatPermissions(const std::variant<qint32, QString>& chat_id, const ChatPermissions& permissions);
        
        /** @brief Use this method to generate a new primary invite link for a chat; any previously generated primary link is revoked. Returns the new invite link as String on success.
         * 
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights.
         * 
         * > Note: Each administrator in a chat generates their own invite links. Bots can't use invite links generated by other administrators. If you want your bot to work with invite links, it will need to generate
         * > its own link using exportChatInviteLink or by calling the getChat method. If your bot needs to generate a new primary invite link replacing its previous one, use exportChatInviteLink again. 
         * 
         * @param Integer or String     Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        QString exportChatInviteLink(const std::variant<qint32, QString>& chat_id);
        
        /* @brief Use this method to create an additional invite link for a chat. Returns the new invite link as ChatInviteLink object, in case of error returns empty ChatInviteLink object
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. The link can be revoked using the method revokeChatInviteLink.
         * 
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32	            Optional. Point in time (Unix timestamp) when the link will expire
         * @param qint32	            Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999 */
        ChatInviteLink createChatInviteLink(const std::variant<qint32, QString>& chat_id, const std::optional<qint32>& expire_date = std::nullopt, const std::optional<qint32>& member_limit = std::nullopt);
        
        /* @brief Use this method to edit a non-primary invite link created by the bot. Returns the edited invite link as a ChatInviteLink object, in case of error returns empty ChatInviteLink object
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString	            The invite link to edit
         * @param qint32	            Optional. Point in time (Unix timestamp) when the link will expire
         * @param qint32	            Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999 */
        ChatInviteLink editChatInviteLink(const std::variant<qint32, QString>& chat_id, const QString& invite_link, const std::optional<qint32>& expire_date = std::nullopt, const std::optional<qint32>& member_limit = std::nullopt);

        /* @brief Use this method to revoke an invite link created by the bot. If the primary link is revoked, a new link is automatically generated. Returns the revoked invite link as ChatInviteLink object, in case of error returns an empty ChatInviteLink object
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         * 
         * @param qint32 or QString     Unique identifier of the target chat or username of the target channel (in the format @channelusername)
         * @param QString	            The invite link to revoke */
        ChatInviteLink revokeChatInviteLink(const std::variant<qint32, QString>& chat_id, const QString& invite_link);
        
        /* @brief Use this method to set a new profile photo for the chat. Returns True on success
         *
         * Photos can't be changed for private chats. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights.
         * 
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QFile*	            New chat photo, uploaded using QFile*(should be opened) */
        bool setChatPhoto(const std::variant<qint32, QString>& chat_id, const QFile* photo);

        /* @brief Use this method to delete a chat photo. Returns True on success
         *
         * Photos can't be changed for private chats. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        bool deleteChatPhoto(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method to change the title of a chat. Returns True on success.
         *
         * Titles can't be changed for private chats. The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString	            New chat title, 1-255 characters */
        bool setChatTitle(const std::variant<qint32, QString>& chat_id, const QString& title);

        /* @brief Use this method to change the description of a group, a supergroup or a channel. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString	            Optional. New chat description, 0-255 characters */
        bool setChatDescription(const std::variant<qint32, QString>& chat_id, const std::optional<QString>& description = std::nullopt);

        /* @brief Use this method to add a message to the list of pinned messages in a chat. Returns True on success
         *
         * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32	            Identifier of a message to pin
         * @param bool                  Optional. Pass True, if it is not necessary to send a notification to all chat members about the new pinned message. Notifications are always disabled in channels and private chats */
        bool pinChatMessage(const std::variant<qint32, QString>& chat_id, const qint32& message_id, const std::optional<bool>& disable_notification = std::nullopt);

        /* @brief Use this method to remove a message from the list of pinned messages in a chat. Returns True on success
         *
         * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param qint32	            Identifier of a message to unpin. If not specified, the most recent pinned message (by sending date) will be unpinned */
        bool unpinChatMessage(const std::variant<qint32, QString>& chat_id, const std::optional<qint32>& message_id = std::nullopt);

        /* @brief Use this method to clear the list of pinned messages in a chat. Returns True on success
         *
         * If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'can_pin_messages' admin right in a supergroup or 'can_edit_messages' admin right in a channel
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        bool unpinAllChatMessages(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method for your bot to leave a group, supergroup or channel. Returns True on success
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        bool leaveChat(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method to get up to date information about the chat (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.). Returns a Chat object on success, in case of error returns an empty Chat object
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        Chat getChat(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method to get a list of administrators in a chat. On success, returns an Array of ChatMember objects that contains information about all chat administrators except other bots. 
         *        If the chat is a group or a supergroup and no administrators were appointed, only the creator will be returned. Returns empty QVector in case of error
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        QVector<ChatMember> getChatAdministrators(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method to get the number of members in a chat. Returns -1 in case of error.
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        int getChatMemberCount(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method to get information about a member of a chat. Returns a ChatMember object on success, in case of error returns empty ChatMember object
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) 
         * @param qint32                Unique identifier of the target user */
        ChatMember getChatMember(const std::variant<qint32, QString>& chat_id, const qint32& user_id);

        /* @brief Use this method to set a new group sticker set for a supergroup. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. Use the field can_set_sticker_set optionally returned in getChat() requests to check if the bot can use this method
         * 
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername)
         * @param QString               Name of the sticker set to be set as the group sticker set */
        bool setChatStickerSet(const std::variant<qint32, QString>& chat_id, const QString& sticker_set_name);
        
        /* @brief Use this method to delete a group sticker set from a supergroup. Returns True on success
         *
         * The bot must be an administrator in the chat for this to work and must have the appropriate admin rights. Use the field can_set_sticker_set optionally returned in getChat() requests to check if the bot can use this method
         *
         * @param qint32 or QString	    Unique identifier for the target chat or username of the target channel (in the format @channelusername) */
        bool deleteChatStickerSet(const std::variant<qint32, QString>& chat_id);

        /* @brief Use this method to send answers to callback queries sent from inline keyboards. The answer will be displayed to the user as a notification at the top of the chat screen or as an alert. On success, True is returned
         *
         * > Alternatively, the user can be redirected to the specified Game URL. For this option to work, you must first create a game for your bot via @Botfather and accept the terms.
         * > Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter
         * 
         * @param QString	Unique identifier for the query to be answered
         * @param QString	Optional. Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
         * @param bool 	    Optional. If true, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false
         * @param QString	Optional. URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @Botfather, specify the URL that opens your game — note that this will only work if the query comes from a callback_game button. Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter
         * @param qint32	Optional. The maximum amount of time in seconds that the result of the callback query may be cached client-side. Telegram apps will support caching starting in version 3.14. Defaults to 0 */
        bool answerCallbackQuery(const QString& callback_query_id, const std::optional<QString>& text = std::nullopt, const std::optional<bool>& show_alert = std::nullopt, const std::optional<QString>& url = std::nullopt, const std::optional<qint32>& cache_time = std::nullopt);

        /* @brief Use this method to change the list of the bot's commands. See https://core.telegram.org/bots#commands for more details about bot commands. Returns True on success.
         *
         * @param QVector of BotCommand	                                                                                           A JSON-serialized list of bot commands to be set as the list of the bot's commands. At most 100 commands can be specified.
         * @param BotCommandScopeAllChatAdministrators or BotCommandScopeAllGroupChats or BotCommandScopeAllPrivateChats or
         *        BotCommandScopeChat or BotCommandScopeChatAdministrators or BotCommandScopeChatMember or BotCommandScopeDefault  Optional. Object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
         * @param QString	                                                                                                       Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands */
        bool setMyCommands(const QVector<BotCommand>& commands, const std::optional<std::variant<BotCommandScopeAllChatAdministrators, BotCommandScopeAllGroupChats, BotCommandScopeAllPrivateChats, BotCommandScopeChat, BotCommandScopeChatAdministrators, BotCommandScopeChatMember, BotCommandScopeDefault>>& scope = std::nullopt, const std::optional<QString>& language_code = std::nullopt);
        
        /* @brief Use this method to delete the list of the bot's commands for the given scope and user language. After deletion, higher level commands will be shown to affected users. Returns True on success
         *
         * @param BotCommandScopeAllChatAdministrators or BotCommandScopeAllGroupChats or BotCommandScopeAllPrivateChats or
         *        BotCommandScopeChat or BotCommandScopeChatAdministrators or BotCommandScopeChatMember or BotCommandScopeDefault	Optional. Object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
         * @param QString	                                                                                                        Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands */
        bool deleteMyCommands(const std::optional<std::variant<BotCommandScopeAllChatAdministrators, BotCommandScopeAllGroupChats, BotCommandScopeAllPrivateChats, BotCommandScopeChat, BotCommandScopeChatAdministrators, BotCommandScopeChatMember, BotCommandScopeDefault>>& scope = std::nullopt, const std::optional<QString>& language_code = std::nullopt);
        
        /* @brief Use this method to get the current list of the bot's commands for the given scope and user language. Returns Array of BotCommand on success. If commands aren't set, an empty list is returned
         *
         * @param BotCommandScopeAllChatAdministrators or BotCommandScopeAllGroupChats or BotCommandScopeAllPrivateChats or
         *        BotCommandScopeChat or BotCommandScopeChatAdministrators or BotCommandScopeChatMember or BotCommandScopeDefault	Optional. Object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
         * @param QString	                                                                                                        Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands */
        QVector<BotCommand> getMyCommands(const std::optional<std::variant<BotCommandScopeAllChatAdministrators, BotCommandScopeAllGroupChats, BotCommandScopeAllPrivateChats, BotCommandScopeChat, BotCommandScopeChatAdministrators, BotCommandScopeChatMember, BotCommandScopeDefault>>& scope = std::nullopt, const std::optional<QString>& language_code = std::nullopt);

        /* @brief
         * 
         * @param 
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         * @param
         */

    private:
        RequestManager requestManager;
        WebhookManager webhookManager;
    };

}

#endif // TELEGRAM_BOT_H