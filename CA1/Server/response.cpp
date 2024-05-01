#include "response.h"

Response::Response() {}

Response::Response(const QVariant &data) : data_(data) {}

QVariant Response::getData() const {
    return data_;
}

void Response::setData(const QVariant &data) {
    data_ = data;
}

QJsonObject Response::toJson() const {
    QJsonObject json;
    json["data"] = data_.toJsonObject();
    return json;
}

Response Response::fromJson(const QJsonObject &json) {
    return Response(QVariant::fromValue(json["data"]));
}
