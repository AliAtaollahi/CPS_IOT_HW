// customizedhttpserver.cpp
#include "customizedhttpserver.h"

CustomizedHttpServer::CustomizedHttpServer(int port, const QString &initialDataPath, QObject *parent) :
    QObject(parent), employeesDatabase_(EmployeesDatabase(initialDataPath)), httpServer_(new QHttpServer())
{
    httpServer_->route("/rfid",QHttpServerRequest::Method::Post, [this](const QHttpServerRequest& request) {
        return this->handleRequest(request);
    });

    startServer(port);
}

bool CustomizedHttpServer::startServer(int port)
{
    return httpServer_->listen(QHostAddress::Any, port);
}

QHttpServerResponse CustomizedHttpServer::handleRequest(const QHttpServerRequest& request)
{
    QByteArray requestData = request.body();
    QString rfid = requestData;

    bool isAuthorized = employeesDatabase_.handleRfidReceived(rfid);

    emit resultRfidCheck(isAuthorized, rfid);

    QByteArray result;
    QHttpServerResponse::StatusCode statusCode;
    if (isAuthorized) {
        result = "1";
        statusCode = QHttpServerResponse::StatusCode::Ok;
    }
    else {
        result = "0";
        statusCode = QHttpServerResponse::StatusCode::Unauthorized;
    }

    return QHttpServerResponse(result, statusCode);
}
