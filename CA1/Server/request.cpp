#include "request.h"

Request::Request() {}


Request::Request(const QString &type, const QVariant  &data) : type_(type), data_(data) {}

QString Request::getType() const {
    return type_;
}

void Request::setType(const QString &type) {
    type_ = type;
}

QVariant  Request::getData() const {
    return data_;
}

void Request::setData(const QVariant  &data) {
    data_ = data;
}

QJsonObject Request::toJson() const {
    return QJsonObject{{"type", type_}, {"data", QJsonValue::fromVariant(data_)}};
}

Request Request::fromJson(const QJsonObject &json) {
    return Request(json["type"].toString(), json["data"].toVariant());
}
