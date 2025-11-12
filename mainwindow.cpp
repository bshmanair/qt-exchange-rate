#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , m_apiKey{"02a26161094176930b30168e"}
{
    ui->setupUi(this);
    prepareCountryList(":/resources/countries.json");
    populateCountryList();
    connect(ui->getRateButton, &QPushButton::clicked, this, &MainWindow::onGetRateClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGetRateClicked()
{
    QString sourceCountry = ui->sourceCountryComboBox->currentText().split(",")[2].trimmed();
    QString destinationCountry = ui->destinationCountryComboBox->currentText().split(",")[2].trimmed();

    getExchangeRateData(sourceCountry);

    qDebug() << "Source Country: " << sourceCountry << ", Destination Country: " << destinationCountry;
}

void MainWindow::prepareCountryList(const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Cannot open file:" << filePath;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError)
    {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    if  (!doc.isObject())
    {
        qWarning() << "JSON is not an object";
        return;
    }

    QJsonObject rootObj = doc.object();
    if (!rootObj.contains("countryList") || !rootObj["countryList"].isArray())
    {
        qWarning() << "JSON does not contain countryList array";
        return;
    }

    QJsonArray countries = rootObj["countryList"].toArray();
    for (const QJsonValue& val : countries)
    {
        if (!val.isObject())
            continue;

        QJsonObject obj = val.toObject();
        QString country = obj.value("country").toString();
        QString currency = obj.value("currency").toString();
        QString code = obj.value("code").toString();
        QString number = QString::number(obj.value("number").toInt());

        m_countryList.append(QString("%1, %2, %3, %4").arg(country, currency, code, number));
    }

    std::sort(m_countryList.begin(), m_countryList.end());
}

void MainWindow::populateCountryList()
{
    ui->sourceCountryComboBox->addItems(m_countryList);
    ui->destinationCountryComboBox->addItems(m_countryList);
}

void MainWindow::getExchangeRateData(const QString& sourceCountry)
{
    m_manager = new QNetworkAccessManager(this);
    QString url = QString("https://v6.exchangerate-api.com/v6/%1/latest/%2")
                      .arg(m_apiKey, sourceCountry);
    qDebug() << url;

    QNetworkRequest request((QUrl(url)));
    m_reply = m_manager->get(request);

    connect(m_reply, &QNetworkReply::finished, this, &MainWindow::onDataReceived);

    if (m_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Network error: " << m_reply->errorString();
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Error");
        msgBox.setText("Network error: No data found");
        msgBox.exec();
    }
}

void MainWindow::onDataReceived()
{
    qDebug() << "in onDataReceived()";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Data Received.";
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
        qDebug() << jsonString;
        ui->jsonResponseTextEdit->setText(jsonString);
        QString destinationCountry = ui->destinationCountryComboBox->currentText().split(",")[2].trimmed();
        QString sourceCountry = ui->sourceCountryComboBox->currentText().split(",")[2].trimmed();

        double exchangeRate = jsonObj["conversion_rates"].toObject()[destinationCountry].toDouble();
        qDebug() << "Exchange rate: " << exchangeRate;
        ui->exchangeRateLabel->setText("1 " + sourceCountry + " = " + QString::number(exchangeRate) + " " + destinationCountry);
    }
    else
    {
        qDebug() << "Network error: " << reply->errorString();
        qDebug() << reply->readAll();

        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Error");
        msgBox.setText(QString("No data found: %1").arg(reply->errorString()));
        msgBox.exec();
    }

    reply->deleteLater();
}
