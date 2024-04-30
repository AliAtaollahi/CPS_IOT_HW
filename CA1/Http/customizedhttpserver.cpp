#include "customizedhttpserver.h"

CustomizedHttpServer::CustomizedHttpServer(QObject *parent)
    : QObject{parent}
{
    http_server = new QHttpServer{this};
    http_server->route("/", [this] (const QHttpServerRequest &req) {
        return this->handleRequest(req);
    });
    if (!http_server->listen(QHostAddress::Any, 80)) {
        qCritical("Failed to listen on port 80");
    }
}

const QByteArray validTag = "0123456789";

QHttpServerResponse CustomizedHttpServer::handleRequest(const QHttpServerRequest &request)
{
    qDebug() << "salam";
    if (request.method() != QHttpServerRequest::Method::Post)
        return QHttpServerResponse(QHttpServerResponder::StatusCode::MethodNotAllowed);

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(request.body(), &error);
    if (error.error != QJsonParseError::NoError)
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);

    QJsonObject jsonObj = jsonDoc.object();
    if (!jsonObj.contains("valid_tag"))
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);

    QByteArray tag = jsonObj.value("valid_tag").toString().toUtf8();
    qDebug() << "salam";
    if (tag == validTag)
        return QHttpServerResponse("1", QHttpServerResponder::StatusCode::Ok);
    else
        return QHttpServerResponse("0", QHttpServerResponder::StatusCode::Unauthorized);
}
