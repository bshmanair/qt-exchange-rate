#pragma once

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDataReceived();
    void onGetRateClicked();

private:
    void prepareCountryList(const QString& filePath);
    void populateCountryList();
    void getExchangeRateData(const QString& sourceCountry);

    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    QStringList m_countryList;
    QString m_apiKey;
};
