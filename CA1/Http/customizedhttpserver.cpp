// customizedhttpserver.cpp
#include "customizedhttpserver.h"
#include "request.h"

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
    // Read the JSON data from the request
    QByteArray requestData = request.body();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(requestData);
    Request receivedRequest = Request::fromJson(jsonDoc.object());
    QString type = receivedRequest.getType();
    QVariant data = receivedRequest.getData();
    if (type == "RFID") {
        QJsonObject jsonData = data.toJsonObject();
        QString rfid = jsonData["rfid"].toString();

        bool permitted = employeesDatabase_.handleRfidReceived(rfid);
        QDateTime currentTime = QDateTime::currentDateTime();
        emit resultRfidCheck(permitted, currentTime, rfid);

        QJsonObject resultJsonObject;
        QHttpServerResponse::StatusCode statusCode;
        if (permitted) {
            resultJsonObject = QJsonObject({
                {"status", "Succeed"},
                {"message", "RFID accepted"},
                {"data", QJsonValue::Null}
            });
            statusCode = QHttpServerResponse::StatusCode::Ok;
        }
        
        else {
            resultJsonObject = QJsonObject({
                {"status", "Failed"},
                {"message", "RFID is not accepted"},
                {"data", QJsonValue::Null}
            });
            statusCode = QHttpServerResponse::StatusCode::Unauthorized;
        }

        QJsonDocument resultJsonDoc(resultJsonObject);
        QByteArray resultJsonByte = resultJsonDoc.toJson();

        return QHttpServerResponse(resultJsonByte, statusCode);
    }
}
