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

    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Extract date and time separately
    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    // Convert date and time to strings
    QString dateString = currentDate.toString("yyyy-MM-dd");
    QString timeString = currentTime.toString("HH:mm:ss");

    bool isAuthorized = employeesDatabase_.checkRFIDMatch(rfid);

    emit resultRfidCheck(isAuthorized, rfid);
    emit resultRfidCheckHistory(isAuthorized, dateString, timeString, rfid);

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
