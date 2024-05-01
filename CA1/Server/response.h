#ifndef RESPONSE_H
#define RESPONSE_H

#include <QJsonObject>
#include <QJsonDocument>

class Response
{
public:
    Response();
    Response(const QVariant &data);

    QVariant getData() const;
    void setData(const QVariant &data);

    QJsonObject toJson() const;
    static Response fromJson(const QJsonObject &json);

private:
    QVariant data_;
};

#endif // RESPONSE_H
